#ifndef __UTILS_H_INCLUDED__
#define __UTILS_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>

using namespace std;

namespace MapsMerge {
	class Utils {

	public:
		static vector<vector<int>> getTuples4Vector(int maxSize);
		static void printMatrix(string name, vector<vector<int>> matrix);

	};
}

#endif
