#pragma once
#include "Common.h"

class TFileDataStructure
{
public:
	int iID;
	int iPosInFile;
	size_t size;
	std::string sType;
public:
	TFileDataStructure() = default;
	TFileDataStructure(int id, int posInFile, size_t size, std::string type);
private:

};

