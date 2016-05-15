#include "../../image_matches/ImagesMatches.h"
#include "../../utils/Utils.h"
#include "DbscanRegionsSelector.h"

#include "../../dbscan/dbscan.h"

using namespace clustering;

MapsMerge::DbscanRegionsSelector::DbscanRegionsSelector(double eps, size_t minElements, int numThreads) {
	this->eps1 = eps;
	this->eps2 = eps;
	this->minElements1 = minElements;
	this->minElements2 = minElements;
	this->numThreads = numThreads;
}

MapsMerge::DbscanRegionsSelector::DbscanRegionsSelector(double eps1, size_t minElements1, double eps2, size_t minElements2, int numThreads) {
	this->eps1 = eps1;
	this->eps2 = eps2;
	this->minElements1 = minElements1;
	this->minElements2 = minElements2;
	this->numThreads = numThreads;
}

void MapsMerge::DbscanRegionsSelector::selectRegions(ImagesMatches& imgMatches) {
	imgMatches.imgFeatures1.keypointsClusters = findClusters(imgMatches.imgFeatures1.keypoints, eps1, minElements1);
	imgMatches.imgFeatures2.keypointsClusters = findClusters(imgMatches.imgFeatures2.keypoints, eps2, minElements2);
}

vector<int> MapsMerge::DbscanRegionsSelector::findClusters(vector<KeyPoint> keypoints, double eps, size_t minElements) {
	int numKeypoints = keypoints.size();

	DBSCAN::ClusterData points(numKeypoints, 2);

	for (size_t i = 0; i < numKeypoints; i++) {
		points(i, 0) = keypoints[i].pt.x;
		points(i, 1) = keypoints[i].pt.y;
	}

	DBSCAN dbs(eps, minElements, numThreads);

	dbs.fit(points);

	return dbs.get_labels();
}

vector<DMatch> MapsMerge::DbscanRegionsSelector::leaveRegionsMatches(ImagesMatches& imgsMatches, vector<Rect> r1, vector<Rect> r2) {

	// 1. Match regions

	// 1.1 Get Matrix with number of matches

	int numClusters1 = Utils::maxElement(imgsMatches.imgFeatures1.keypointsClusters) + 1;
	int numClusters2 = Utils::maxElement(imgsMatches.imgFeatures2.keypointsClusters) + 1;

	//debug
	cout << "numClusters1: " << numClusters1 << endl;
	cout << "numClusters2: " << numClusters2 << endl;
	//end

	vector<vector<int>> numMatchesMatrix(numClusters1, vector<int>(numClusters2));	
	
	for (int iKeyPoint1 = 0; iKeyPoint1 < imgsMatches.imgFeatures1.keypoints.size(); iKeyPoint1++) {
		int iKeyPoint2 = imgsMatches.matches[iKeyPoint1].trainIdx;
		int iCluster1 = imgsMatches.imgFeatures1.keypointsClusters[iKeyPoint1];
		int iCluster2 = imgsMatches.imgFeatures2.keypointsClusters[iKeyPoint2];
		if (iCluster1 != -1 && iCluster2 != -1) {
			numMatchesMatrix[iCluster1][iCluster2]++;
		}	
	}

	// An attempt to improve quality of clusters matching
	
	vector<int> pointsPerCluster2(numClusters2);
	for (int i = 0; i < imgsMatches.imgFeatures2.keypoints.size(); i++) {
		if (imgsMatches.imgFeatures2.keypointsClusters[i] != -1) {
			pointsPerCluster2[imgsMatches.imgFeatures2.keypointsClusters[i]]++;
		}
	}

	for (int iCluster2 = 0; iCluster2 < numClusters2; iCluster2++) {
		for (int iCluster1 = 0; iCluster1 < numClusters1; iCluster1++) {
			numMatchesMatrix[iCluster1][iCluster2] = (double) numMatchesMatrix[iCluster1][iCluster2] / pointsPerCluster2[iCluster2] * 100;
		}
	}
	
	// end

	//debug
	//Utils::printMatrix2("numMatchesMatrix", numMatchesMatrix);
	//end

	// 1.2 Find matched regions

	// Transpose matrix if needed
	vector<vector<int>> regionsMatches(min(numClusters1, numClusters2), vector<int>(max(numClusters1, numClusters2)));

	if (numClusters1 > numClusters2) {
		regionsMatches = Utils::transpose(numMatchesMatrix);
	} else {
		regionsMatches = numMatchesMatrix;
	}	

	// Find vector of matched clusters
	vector<int> matchedClusters(min(numClusters1, numClusters2));

	for (int i = 0; i < regionsMatches.size(); i++) {
		int idx1 = distance(regionsMatches[i].begin(), max_element(regionsMatches[i].begin(), regionsMatches[i].end()));
		matchedClusters[i] = idx1;

		for (int row = 0; row < regionsMatches.size(); row++) {
			regionsMatches[row][idx1] = -1;
		}
	}

	// Reassign clusters of corresponding keypoints vector

	vector<int> *keypointsClustersToChange;
	if (numClusters1 < numClusters2) {
		keypointsClustersToChange = &imgsMatches.imgFeatures2.keypointsClusters;
	} else {
		keypointsClustersToChange = &imgsMatches.imgFeatures1.keypointsClusters;		
	}

	vector<int> copyKeypointsClusters(*keypointsClustersToChange);

	for (int iCluster = 0; iCluster < (*keypointsClustersToChange).size(); iCluster++) {
		int position = find(matchedClusters.begin(), matchedClusters.end(), copyKeypointsClusters[iCluster]) - matchedClusters.begin();
		if (position >= matchedClusters.size()) { // Position not found
			(*keypointsClustersToChange).at(iCluster) = -1;			
		} else {
			(*keypointsClustersToChange).at(iCluster) = position;			
		}
	}

	// 2. Leave clusters matches

	vector<DMatch> goodMatches;

	for (int iKeyPoint1 = 0; iKeyPoint1 < imgsMatches.imgFeatures1.keypoints.size(); iKeyPoint1++) {
		int iKeyPoint2 = imgsMatches.matches[iKeyPoint1].trainIdx;
		
		if (imgsMatches.imgFeatures1.keypointsClusters[iKeyPoint1] != -1 && 
			imgsMatches.imgFeatures1.keypointsClusters[iKeyPoint1] == imgsMatches.imgFeatures2.keypointsClusters[iKeyPoint2]) {
				goodMatches.push_back(imgsMatches.matches[iKeyPoint1]);
		}
	}

	return goodMatches;
}
