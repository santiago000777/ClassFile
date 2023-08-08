#include "File.h"

//		PUBLIC FUNCTIONS


TFile::TFile(std::string path, eMode mode, bool saveMode) {
	this->mode = mode;
	this->sPath = path;
	this->typeSaveMode = saveMode;
	this->pocitadloTrid = 0;
	this->sizeBinFile = 0;
	this->sDataStrucPath = "dataStructure.bin";
	//DSFile.open(sDataStrucPath.c_str(), std::ios::out | std::ios::binary);

	switch (mode) {
		
		case eMode::READ: {
			pomFile.open(path.c_str(), std::ios::in | std::ios::beg);
			break;
		}
		case eMode::WRITE: {
			pomFile.open(path.c_str(), std::ios::out | std::ios::app);
			break;
		}
		case eMode::BINR: {
			pomFile.open(path.c_str(), std::ios::in | std::ios::binary);
			break;
		}
		case eMode::BINW: {
			pomFile.open(path.c_str(), std::ios::out | std::ios::binary); // pridat App
			break;
		}
		default: {
			std::cout << "This mode is not defined!" << std::endl;
			this->mode = eMode::NONE;
		}
	}

	if (!pomFile.is_open()/* || !DSFile.is_open()*/) {
		std::cout << "ERROR!\n";
		__debugbreak();
	}
	size.Init(this->GetBeg(), this->GetEnd());
	
}



void TFile::Close() {
	if (pomFile.is_open()) {
		pomFile.close();
		this->mode = eMode::NONE;
		this->begin = -1;
		this->end = -1;
		this->sFileText = "\0";
		this->size.DevalueVar();
		this->sPath = "\0";
		//delete[] & dataStruct;
	}
}

bool TFile::IsOpen() {
	if(pomFile.is_open())
		return true;
	else
		return false;
}



void TFile::Rewrite(std::string s) {
	if (pomFile.is_open() && mode == eMode::WRITE) {
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::out);
		pomFile.clear();
		pomFile << s;
	}
	else {
		std::cout << "MODE ERROR!" << std::endl;
		__debugbreak();
	}
}


void TFile::Write(std::string s) {
	if (pomFile.is_open() && mode == eMode::WRITE) {
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::app);
		pomFile << s;
	}
	else {
		std::cout << "MODE ERROR!" << std::endl;
		__debugbreak();
	}
	
}


std::string TFile::GetText() {
	return sFileText;
}

std::streampos TFile::GetBeg() {
	return begin;
}
std::streampos TFile::GetEnd() {
	return end;
}


TFile::~TFile() {
	if(pomFile.is_open())
		Close();
	
}




//		PRIVATE FUNCTIONS



void TFile::AddTypeName_toFile(std::string s) {
	if (typeSaveMode) {
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::app);
		pomFile << "€" << s << "€";
	}
	

}

void TFile::ZjisteniTypeName() {
	pomFile.close();
	pomFile.open(sPath.c_str(), std::ios::in);

	std::string textFile;

	std::string* sPom = new std::string;
	while (std::getline(pomFile, *sPom))
		textFile += *sPom + "\n";
	delete sPom;

		// vyhledani a ulozeni typu ze souboru
	int typeOd = textFile.find("€");
	int typeDo = textFile.find("€", typeOd+1);
	char buffer[20];
	std::size_t len = textFile.copy(buffer, typeDo - typeOd - 1, typeOd + 1);
	buffer[len] = '\0';
	typeID = buffer;
}








//		PROTECTED FUNCTIONS





