#pragma once
#include "Common.h"
#include "DataSize.h"
//#include "VecDataStructure.h"
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
	std::vector<TFileDataStructure> dataStruct;  /////
	
	std::fstream pomFile;
	

public:
	TFile() = default;

	TFile(std::string path, eMode mode, bool saveMode = 1);

	void Close();
	bool IsOpen();

	void Rewrite(std::string s);
	

	template<typename T> 
	void Rewrite(T* var, int varSize) { //
		if (pomFile.is_open() && mode == eMode::BINW) {

				// nastaveni parametru dat do file dataStruct...
			TFileDataStructure pomDS(0, 0, varSize, (std::string)typeid(T).name());
			dataStruct.push_back(pomDS);
			DSFile.open(sDataStrucPath.c_str(), std::ios::out | std::ios::binary);
			DSFile.write((const char*)&dataStruct, sizeof(dataStruct));	// nepise
			DSFile.close();

				// vepsani dat do hlavni slozky
			pomFile.clear();
			pomFile.write((const char*)var, varSize); //
		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
		
	}
	
	
	void Write(std::string s);
								
	template<typename T>
	void Write(T* var, int varSize) { // pridano *
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::app | std::ios::binary);
		if (pomFile.is_open() && mode == eMode::BINW) {
			
			DSFile.open(sDataStrucPath.c_str(), std::ios::out | std::ios::binary);

				// tvorba (parametru dat) struktury slozky	
			if (pocitadloTrid == 0) {
					
				TFileDataStructure pomDS(0, 0, varSize , (std::string)typeid(T).name());//
				dataStruct.push_back(pomDS);
				sizeBinFile += pomDS.size;
			}
			else {
				TFileDataStructure pomDS(pocitadloTrid, dataStruct.at(pocitadloTrid-1).iPosInFile + dataStruct.at(pocitadloTrid - 1).size, varSize/*sizeof(var)*/, (std::string)typeid(T).name());//
				dataStruct.push_back(pomDS);
				sizeBinFile += pomDS.size;
			}
			
			pocitadloTrid++;
			/*int SFsize = sizeof(std::vector<TFileDataStructure>) + sizeof(TFileDataStructure) * dataStruct.size();*/
			int SFsize = sizeof(std::vector<TFileDataStructure>);
			for (int i = 0; i < pocitadloTrid; i++) {
				SFsize += sizeof(int) + sizeof(int) + sizeof(size_t) + dataStruct.at(i).sType.size();
			}
			



			DSFile.write((const char*)&dataStruct, SFsize);
			DSFile.close();


				// vepsani dat do hlavni slozky
			
			pomFile.write((const char*)var, varSize); // &
		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
	}

	void Read() {

		if (pomFile.is_open() && mode == eMode::READ) {
			std::string* sPom = new std::string;
			while (std::getline(pomFile, *sPom))
				sFileText += *sPom + "\n";
			delete sPom;
		}
		else if (pomFile.is_open() && mode == eMode::BINR) {
			DSFile.open(sDataStrucPath.c_str(), std::ios::in, std::ios::binary);


			DSFile.seekg(0, std::ios::beg);
			std::streampos begin = DSFile.tellg();
			DSFile.seekg(0, std::ios::end);
			std::streampos end = DSFile.tellg();
			int size = end - begin;

			DSFile.seekg(0, std::ios::beg);


			DSFile.read((char*)&dataStruct, size);
			this->mode = eMode::BINR;
			DSFile.close();


			pomFile >> sFileText;
			pomFile.close();

		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
	}


	template<typename T>
	T* GetData(int index) {
		
			// zjisteni typu pomoci dataStruct
		
		pomFile.open(sPath.c_str(), std::ios::in | std::ios::binary);

		if ((dataStruct.at(index).sType == (std::string)typeid(T).name() && typeSaveMode == true) || (dataStruct.at(index).sType != (std::string)typeid(T).name() && typeSaveMode == false)) { // kontrola kompatibility typu pres dataStruct
			if (pomFile.is_open() && mode == eMode::BINR) {
				

				pomFile.seekg(dataStruct.at(index).iPosInFile, std::ios::beg);	// nastaveni pozice cteni pomoci dataStruct
				T* pomT = new T;
				pomFile.read((char*)pomT, dataStruct.at(index).size);
				pomFile.close();
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
	std::string sDataStrucPath;
	std::fstream DSFile;

	std::string sFileText;
	std::streampos begin, end;

	std::string binDataType;

	bool typeSaveMode;
	std::string typeID;

	int pocitadloTrid;
	int sizeBinFile;

private:
	void AddTypeName_toFile(std::string s);
	void ZjisteniTypeName();
protected:
	
	
};

