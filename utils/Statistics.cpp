#include "Statistics.h"

MapsMerge::Statistics::Statistics(string fileName, int numFields) {
	this->fieldsCounter = 0;
	this->setFileName(fileName);
	this->setNumFields(numFields);
}
void MapsMerge::Statistics::setFileName(string fileName) {
	this->fout = ofstream(fileName.c_str());
}

void MapsMerge::Statistics::setNumFields(int numFields) {
	if (numFields <= 0) {
		cerr << "Numer of fileds must be greater than zero";
		return;
	}
	this->numFields = numFields;
}

MapsMerge::Statistics& MapsMerge::Statistics::addField(string value) {
	fout << value << ";";
	fieldsCounter++;
	if (fieldsCounter % numFields == 0) {
		fieldsCounter = 0;
		fout << endl;
	}	
	return *this;
}

MapsMerge::Statistics& MapsMerge::Statistics::addField(int value) {
	return addField(to_string(value));
}

MapsMerge::Statistics& MapsMerge::Statistics::addField(double value) {
	return addField(to_string(value));
}

void MapsMerge::Statistics::closeFile() {
	fout.close();
}
