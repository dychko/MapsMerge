#include "../../image_matches/ImagesMatches.h"
#include "GaleShapleyMatcherStrategy.h"
#include "../regions_selector/RegionsSelector.h"

bool MapsMerge::GaleShapleyMatcherStrategy::prefers(vector<vector<int>> matrix2, int w, int m, int m1) {
	for (int i = 0; i < matrix2[0].size(); i++) {
		if (matrix2[w][i] == m1)
			return true;
		
		if (matrix2[w][i] == m)
			return false;
	}
}

vector<int> MapsMerge::GaleShapleyMatcherStrategy::algGaleShapley(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
	if (matrix1.size() != matrix2.size()) {
		cerr << "Incompatible dimensions of matrices" << endl;
		return vector<int>(0, 0);
	}

	int N = matrix1.size();
	vector<int> wMatch(N, -1);
	vector<bool> mMatched(N, false);
	int freeCount = N;

	while (freeCount > 0) {
		int m;
		for (m = 0; m < N; m++)
			if (mMatched[m] == false)
				break;
		for (int i = 0; i < N && !mMatched[m]; i++) {
			int w = matrix1[m][i];

			if (wMatch[w] == -1) {
				wMatch[w] = m;
				mMatched[m] = true;
				freeCount--;
			} else {
				int m1 = wMatch[w];

				if (!prefers(matrix2, w, m, m1)) {
					wMatch[w] = m;
					mMatched[m] = true;
					mMatched[m1] = false;
				}
			}
		}
	}

	// Returns a vector with values corresponding to matrix1 and indices - to matrix2

	return wMatch;
}

void MapsMerge::GaleShapleyMatcherStrategy::testGaleShapleyAlgorithm() {

	// Initialization
	const int dimension = 4;
	    int prefer[2 * dimension][dimension] = { 
		{7, 5, 6, 4},
        {5, 4, 6, 7},
        {4, 5, 6, 7},
        {4, 5, 6, 7},
    
		{0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
        {0, 1, 2, 3},
    };
	vector<vector<int>> matrix1(dimension, vector<int>(dimension));
	vector<vector<int>> matrix2(dimension, vector<int>(dimension));
	
	cout << "Before initialization" << endl;

	//for (int i = 0; i < dimension; i++) {
	//	matrix1[i].assign(&prefer[i][0], &prefer[i][dimension]);
	//	matrix1[i + dimension].assign(&prefer[i + dimension][0], &prefer[i + dimension][dimension]);
	//}

	matrix1[0][0] = 3; matrix1[0][1] = 1; matrix1[0][2] = 2; matrix1[0][3] = 0;
	matrix1[1][0] = 1; matrix1[1][1] = 0; matrix1[1][2] = 2; matrix1[1][3] = 3;
	matrix1[2][0] = 0; matrix1[2][1] = 1; matrix1[2][2] = 2; matrix1[2][3] = 3;
	matrix1[3][0] = 0; matrix1[3][1] = 1; matrix1[3][2] = 2; matrix1[3][3] = 3;
	matrix2[0][0] = 0; matrix2[0][1] = 1; matrix2[0][2] = 2; matrix2[0][3] = 3;
	matrix2[1][0] = 0; matrix2[1][1] = 1; matrix2[1][2] = 2; matrix2[1][3] = 3;
	matrix2[2][0] = 0; matrix2[2][1] = 1; matrix2[2][2] = 2; matrix2[2][3] = 3;
	matrix2[3][0] = 0; matrix2[3][1] = 1; matrix2[3][2] = 2; matrix2[3][3] = 3;

	cout << "Matrix 1" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "[ ";
		for (int j = 0; j < 4; j++) {
			cout << matrix1[i][j] << ((j!=3)?(", "):(""));
		}
		cout << " ]\n";
	}

	cout << "Matrix 2" << endl;
	for (int i = 0; i < 4; i++) {
		cout << "[ ";
		for (int j = 0; j < 4; j++) {
			cout << matrix2[i][j] << ((j!=3)?(", "):(""));
		}
		cout << " ]\n";
	}

	cout << "After initialization" << endl;
	
	// Algorithm
	vector<int> result = algGaleShapley(matrix1, matrix2);

	cout << "After algorithm" << endl;

	// Print results
	cout << "Results: " << endl;
	for (int i = 0; i < result.size(); i++) {
		cout << result[i] << ", ";
	}
}

bool comparePair(const pair<int, int>  &p1, const pair<int, int> &p2) {
	return p1.second > p2.second;
}

vector<int> MapsMerge::GaleShapleyMatcherStrategy::findPreferences(const vector<int> numMatches) {
	int length = numMatches.size();
	vector<pair<int, int>> vecPairsNumMatches(length);
	for(int i = 0; i < length; i++) {
		vecPairsNumMatches[i] = pair<int,int>(i, numMatches[i]);
	}

	sort(vecPairsNumMatches.begin(), vecPairsNumMatches.end(), comparePair);	
	
	vector<int> preferences(length);
	for (int i = 0; i < length; i++) {
		preferences[i] = vecPairsNumMatches[i].first;
	}

	return preferences;
}

vector<vector<vector<int>>> MapsMerge::GaleShapleyMatcherStrategy::createNumMatchesMatrices(ImagesMatches& imgsMatches) {
	vector<vector<vector<int>>> numMatchesMatrices;

	// Build matrices with matches quantity

	const int numRegions1 = imgsMatches.imgFeatures1.regions.size();
	const int numRegions2 = imgsMatches.imgFeatures2.regions.size();

	vector<vector<int>> numMatchesRegions12(numRegions1, vector<int>(numRegions2));
	vector<vector<int>> numMatchesRegions21(numRegions2, vector<int>(numRegions1));

	for (int i = 0; i < numRegions1; i++) {
		vector<Rect> oneRegion1(1, imgsMatches.imgFeatures1.regions[i]);
		for (int j = 0; j  < numRegions2; j ++) {
			vector<Rect> oneRegion2(1, imgsMatches.imgFeatures2.regions[j]);
			numMatchesRegions12[i][j] = RegionsSelector::leaveRegionsMatches(imgsMatches, oneRegion1, oneRegion2).size();
			numMatchesRegions21[i][j] = RegionsSelector::leaveRegionsMatches(imgsMatches, oneRegion2, oneRegion1).size();			
		}
	}

	// Build preferences matrices

	for (int i = 0; i < numRegions1; i++) {
		numMatchesRegions12[i] = findPreferences(numMatchesRegions12[i]);
		numMatchesRegions21[i] = findPreferences(numMatchesRegions21[i]);
	}

	numMatchesMatrices.push_back(numMatchesRegions12);
	numMatchesMatrices.push_back(numMatchesRegions21);

	return numMatchesMatrices;
}

void MapsMerge::GaleShapleyMatcherStrategy::matchRegions(ImagesMatches& imgsMatches) {	
	
	// Create matrices of preferences
	vector<vector<vector<int>>> numMatchesMatrices = createNumMatchesMatrices(imgsMatches);


	// Start logging
	cout <<  "\n Matrices of preferences \n" << endl;
	cout << "Matrix 1" << endl;
	for (int i = 0; i < numMatchesMatrices[0].size(); i++) {
		cout << "[ ";
		for (int j = 0; j < numMatchesMatrices[0][0].size(); j++) {
			cout << numMatchesMatrices[0][i][j] << ((numMatchesMatrices[0][0].size()-1!=j)?(", "):(""));
		}
		cout << " ]\n";
	}


	cout << "Matrix 2" << endl;
	for (int i = 0; i < numMatchesMatrices[1].size(); i++) {
		cout << "[ ";
		for (int j = 0; j < numMatchesMatrices[1][0].size(); j++) {
			cout << numMatchesMatrices[1][i][j] << ((numMatchesMatrices[1][0].size()-1!=j)?(", "):(""));
		}
		cout << " ]\n";
	}
	// End logging


	// Match regions by Gale-Shapley 
	vector<int> regionsMatches = algGaleShapley(numMatchesMatrices[0], numMatchesMatrices[1]);

	// Set regions according to matches
	vector<Rect> copyRects1(imgsMatches.imgFeatures1.regions);
	for (int i = 0; i < copyRects1.size(); i++) {
		imgsMatches.imgFeatures1.regions[i] = copyRects1[regionsMatches[i]];
	}
}
