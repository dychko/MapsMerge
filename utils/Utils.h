#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <algorithm>

using namespace std;

namespace MapsMerge {
	class Utils {

	public:
		static vector<vector<int>> getTuples4Vector(int maxSize);
		static void printMatrix(string name, vector<vector<int>> matrix);
		static vector<vector<int>> transpose(vector<vector<int>> matrix);
		static vector<vector<int>> sumMatrices(vector<vector<int>> matrix1, vector<vector<int>> matrix2);
		static string getTimeStr();
		static int maxElement(vector<int>& vec);

	};
}

#endif
