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
