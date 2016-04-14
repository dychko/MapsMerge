#include "Utils.h"

vector<vector<int>> MapsMerge::Utils::getTuples4Vector(int maxSize) {
	vector<vector<int>> regionsIndexes;
	vector<int> regionsTemp;

	for(int iRegion1 = 0; iRegion1 < maxSize; iRegion1++ ) {
		for(int iRegion2 = iRegion1 + 1; iRegion2 < maxSize; iRegion2++ ) {
			for(int iRegion3 = iRegion2 + 1; iRegion3 < maxSize; iRegion3++ ) {
				for(int iRegion4 = iRegion3 + 1; iRegion4 < maxSize; iRegion4++ ) {
					// 4 regions
					regionsTemp.push_back(iRegion1);
					regionsTemp.push_back(iRegion2);
					regionsTemp.push_back(iRegion3);
					regionsTemp.push_back(iRegion4);
					regionsIndexes.push_back(regionsTemp);
					regionsTemp.clear();
				}
			}
		}
	}
	return regionsIndexes;
}

void MapsMerge::Utils::printMatrix(string name, vector<vector<int>> matrix) {
	cout << name << endl;
	for (int i = 0; i < matrix.size(); i++) {
		cout << "[ ";
		for (int j = 0; j < matrix[i].size(); j++) {
			cout << matrix[i][j] << ((matrix[i].size() - 1 != j) ? (", ") : (""));
		}
		cout << " ]" << endl;
	}
}

vector<vector<int>> MapsMerge::Utils::transpose(vector<vector<int>> matrix) {
	vector<vector<int>> transposedMatrix(matrix.size(), vector<int>(matrix[0].size()));
	for (int i = 0; i < matrix.size(); i++) {
		for (int j = 0; j < matrix[i].size(); j++) {
			transposedMatrix[i][j] = matrix[j][i];
		}
	}
	return transposedMatrix;
}

vector<vector<int>> MapsMerge::Utils::sumMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2) {
	vector<vector<int>> sumResult(matrix1.size(), vector<int>(matrix1[0].size()));
	for (int i = 0; i < matrix1.size(); i++) {
		for (int j = 0; j < matrix1[i].size(); j++) {
			sumResult[i][j] = matrix1[i][j] + matrix2[i][j];
		}
	}
	return sumResult;
}

string MapsMerge::Utils::getTimeStr() {
	time_t t = time(0);   // get time now
    struct tm * now = localtime(&t);
    string time = to_string((now->tm_year + 1900)) + '-' + 
                  to_string((now->tm_mon + 1)) + '-' + 
				  to_string(now->tm_mday) + '-' +
				  to_string(now->tm_hour) + '_' +
				  to_string(now->tm_min) + '_' + 
				  to_string(now->tm_sec);
	return time;
}
