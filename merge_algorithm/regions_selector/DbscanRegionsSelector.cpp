#include "../../image_matches/ImagesMatches.h"
#include "DbscanRegionsSelector.h"

#include "../../dbscan/dbscan.h"

using namespace clustering;

MapsMerge::DbscanRegionsSelector::DbscanRegionsSelector(double eps, size_t minElements, int numThreads) {
	this->eps = eps;
	this->minElements = minElements;
	this->numThreads = numThreads;
}

void MapsMerge::DbscanRegionsSelector::selectRegions(ImagesMatches& imgMatches) {
	imgMatches.imgFeatures1.keypointsClusters = findClusters(imgMatches.imgFeatures1.keypoints);
	imgMatches.imgFeatures2.keypointsClusters = findClusters(imgMatches.imgFeatures2.keypoints);
}

vector<int> MapsMerge::DbscanRegionsSelector::findClusters(vector<KeyPoint> keypoints) {
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
