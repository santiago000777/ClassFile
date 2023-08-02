#pragma once

#include "Common.h"
//#include "File.h"

struct TDataSize
{
public:
	enum class eUnit {
		NONE = -1,
		BIT,
		BYTE,
		KB,
		MB,
		GB
	};
public:
	TDataSize();

	int GetSize(std::fstream& file, eUnit unit);	// jedine s WRITE (out)

	void Init(std::streampos beggin, std::streampos end);
	void DevalueVar();
private:
	
	eUnit unit;
	int DS_size;
	std::streampos beggin, end;

private:
	void CalculateSize(std::fstream& file);

protected:
	
};

