#pragma once
#include "Common.h"
#include "DataSize.h"
#include "FileDataStructure.h"




class TFile
{
public:
	enum class eMode {
		NONE = -1,
		READ,
		WRITE,
		BINR,
		BINW
	};

	TDataSize size;		// jedine s WRITE (out)
	std::vector<TFileDataStructure> dataStruct;
	std::fstream pomFile;

public:
	TFile() = default;

	TFile(std::string path, eMode mode, bool saveMode = 1);

	void Close();
	bool IsOpen();

	void Rewrite(std::string s);
								// <- dat dohrmady
	template<typename T> 
	void Rewrite(T var) {
		if (pomFile.is_open() && mode == eMode::BINW) {
			pomFile.clear();
			AddTypeName_toFile((std::string)typeid(T).name());
			pomFile.close();
			pomFile.open(sPath.c_str(), /*std::ios::out*/std::ios::app | std::ios::binary);
			pomFile.write((const char*)&var, sizeof(T));
		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
		
	}
	

	template<typename T>
	void Read() {
		if (pomFile.is_open() && mode == eMode::READ) {
			std::string* sPom = new std::string;
			while (std::getline(pomFile, *sPom))
				sFileText += *sPom + "\n";
			delete sPom;
		}
		else if (pomFile.is_open() && mode == eMode::BINR) {

			ZjisteniTypeName();
			if ((typeID == (std::string)typeid(T).name() && typeSaveMode == true) || (typeID != (std::string)typeid(T).name() && typeSaveMode == false)) {
					// ulozeni do sFileText a pote zpristupnit s funkci GetData()
				T pomTRead;
				pomFile.seekg(typeID.length() + 2, std::ios::beg);
				pomFile.read((char*)&pomTRead, sizeof(T));
				char* pTRead = (char*)&pomTRead;
				for (int i = 0; i < sizeof(T); i++) {
					sFileText += *pTRead;
					pTRead++;
				}
			}
			else {
				std::cout << "CLASS/STRUCT TYPE ERROR!" << std::endl;
				__debugbreak();
			}
			
		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
	}


	void Write(std::string s);
								// <- dat dohrmady
	template<typename T>
	void Write(T var) {
		if (pomFile.is_open() && mode == eMode::BINW) {
			AddTypeName_toFile((std::string)typeid(T).name());
			pomFile.close();
			pomFile.open(sPath.c_str(), std::ios::app | std::ios::binary);
			pomFile.write((const char*)&var, sizeof(T));
		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
	}


	template<typename T>
	T& GetData() {
		
		ZjisteniTypeName();
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::in | std::ios::binary);
		if ((typeID == (std::string)typeid(T).name() && typeSaveMode == true) || (typeID != (std::string)typeid(T).name() && typeSaveMode == false)) {
			if (pomFile.is_open() && mode == eMode::BINR) {
				T pomT;
				pomFile.seekg(typeID.length() + 2, std::ios::beg);
				pomFile.read((char*)&pomT, sizeof(T));
				return pomT;
			}
			else {
				std::cout << "MODE ERROR!" << std::endl;
				__debugbreak();
			}
		}
		else {
			std::cout << "CLASS/STRUCT TYPE ERROR!" << std::endl;
			__debugbreak();
		}
	}

	std::string GetText();
	std::streampos GetBeg();
	std::streampos GetEnd();

	~TFile();
private:
	eMode mode;
	std::string sPath;

	std::string sFileText;
	std::streampos begin, end;

	std::string binDataType;

	bool typeSaveMode;
	std::string typeID;
private:
	void AddTypeName_toFile(std::string s);
	void ZjisteniTypeName();
protected:
	
	
};

