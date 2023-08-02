#pragma once
#include "Common.h"

class TFileDataStructure
{
public:
	int iID;
	int iPosInFile;
	std::string sType;
public:
	TFileDataStructure(int id, int posInFile, std::string type);
private:

};

