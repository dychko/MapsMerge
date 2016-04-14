#ifndef __STATISTICS_H_INCLUDED__
#define __STATISTICS_H_INCLUDED__

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

namespace MapsMerge {
	class Statistics {

	private:
		ofstream fout;
		int numFields;
		int fieldsCounter;

		void setFileName(string fileName);
		void setNumFields(int numFields);

	public:
		Statistics(string fileName, int numFields);
		Statistics& addField(string value);
		Statistics& addField(int value);
		Statistics& addField(double value);
		void closeFile();
	};
}

#endif
