#include "../../image_matches/ImagesMatches.h"
#include "GaleShapleyMatcherStrategy.h"

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


void MapsMerge::GaleShapleyMatcherStrategy::matchRegions(ImagesMatches& imgsMatches) {
	// TODO: Needs implementation
}
