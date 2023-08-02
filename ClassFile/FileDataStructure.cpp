#include "FileDataStructure.h"

TFileDataStructure::TFileDataStructure(int id, int posInFile, std::string type) {
	this->iID = id;
	this->iPosInFile = posInFile;
	this->sType = type;
}
