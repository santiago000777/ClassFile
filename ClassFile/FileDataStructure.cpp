#include "FileDataStructure.h"

TFileDataStructure::TFileDataStructure(int id, int posInFile, size_t size, std::string type) {
	this->iID = id;
	this->iPosInFile = posInFile;
	this->size = size;
	this->sType = type;
}



