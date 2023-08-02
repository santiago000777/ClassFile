#include "DataSize.h"


// PUBLIC

TDataSize::TDataSize() {

}

int TDataSize::GetSize(std::fstream& file, eUnit unit) {
	this->unit = unit;
	CalculateSize(file);
	return this->DS_size;
}



// PRIVATE



void TDataSize::Init(std::streampos beggin, std::streampos end) {
	this->beggin = beggin;
	this->end = end;

	
}

void TDataSize::DevalueVar() {
	this->beggin = -1;
	this->end = -1;
	this->DS_size = -1;
	this->unit = eUnit::NONE;
}


void TDataSize::CalculateSize(std::fstream& file) {
	file.seekg(0, std::ios::beg);
	beggin = file.tellg();

	file.seekg(0, std::ios::end);
	end = file.tellg();

	int byte = end - beggin;

	switch (this->unit) {
		case eUnit::BIT: {
			DS_size = byte * 8;
			break;
		}
		case eUnit::BYTE: {
			DS_size = byte;
			break;
		}
		case eUnit::KB: {
			DS_size = byte / 1000;
			break;
		}
		case eUnit::MB: {
			DS_size = byte / 1048576;
			break;
		}
		case eUnit::GB: {
			DS_size = byte / 1073741824;
			break;
		}
	}
}
