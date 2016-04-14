#include "../../image_matches/ImagesMatches.h"
#include "GaleShapleyMatcherStrategy.h"
#include "../regions_selector/RegionsSelector.h"
#include "../../utils/Utils.h"

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

	Utils::printMatrix("Matrix 1", matrix1);
	Utils::printMatrix("Matrix 2", matrix2);

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

void MapsMerge::GaleShapleyMatcherStrategy::matchRegions(ImagesMatches& imgsMatches) {	
	
	// Create matrices with matches quantity
	vector<vector<vector<int>>> numMatchesMatrices = createNumMatchesMatrices(imgsMatches);

	// Some test transformations
	vector<vector<int>> matchesMatrix = Utils::sumMatrices(numMatchesMatrices[0], Utils::transpose(numMatchesMatrices[1]));
	numMatchesMatrices[0] = matchesMatrix;
	numMatchesMatrices[1] = Utils::transpose(matchesMatrix);

	// Build preferences matrices
	for (int i = 0; i < imgsMatches.imgFeatures1.regions.size(); i++) {
		numMatchesMatrices[0][i] = findPreferences(numMatchesMatrices[0][i]);
		numMatchesMatrices[1][i] = findPreferences(numMatchesMatrices[1][i]);
	}

	// Match regions by Gale-Shapley 
	vector<int> regionsMatches = algGaleShapley(numMatchesMatrices[0], numMatchesMatrices[1]);

	// Set regions according to matches
	vector<Rect> copyRects1(imgsMatches.imgFeatures1.regions);
	for (int i = 0; i < copyRects1.size(); i++) {
		imgsMatches.imgFeatures1.regions[i] = copyRects1[regionsMatches[i]];
	}
}
