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
	

	template<typename T> 
	void Rewrite(T* var, int varSize) { // problem zde
		if (pomFile.is_open() && mode == eMode::BINW) {

				// nastaveni parametru dat do file dataStruct...
			TFileDataStructure pomDS(0, 0, varSize, (std::string)typeid(T).name());
			dataStruct.push_back(pomDS);
			sizeStruct = sizeof(std::vector<TFileDataStructure>) + sizeof(int) + sizeof(int) + sizeof(size_t) + /*/*/sizeof(std::string)/*/*/ + dataStruct.at(0).sType.size();

			char* pSizeStruct = (char*)&sizeStruct;
			for (int i = 0; i < sizeof(int); i++) {
				sStruct += *pSizeStruct;
				pSizeStruct++;
			}

			char* pDataStruct = (char*)&dataStruct;
			for (int i = 0; i < sizeStruct; i++) {
				sStruct += *pDataStruct;
				pDataStruct++;
			}
			
			char* pVar = (char*)var;
			for (int i = 0; i < varSize; i++) {
				sData += *pVar;
				pVar++;
			}

			sFile = sStruct + sData;


			
				// vepsani dat do hlavni slozky
			
			pomFile.close();

			pomFile.open(sPath.c_str(), std::ios::out | std::ios::beg);
			pomFile << sFile;

			pomFile.close();
		}
		else {
			std::cout << "MODE ERROR!" << std::endl;
			__debugbreak();
		}
		
	}
	
	
	void Write(std::string s);
			


	template<typename T> 
	void Write(T* var, int varSize) {
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::in | std::ios::beg);
		if (pomFile.is_open() && mode == eMode::BINW) {

			std::string* sPom = new std::string;
			while (std::getline(pomFile, *sPom))
				sFile += *sPom;
			pomFile.close();

			char* pSizeStruct = (char*)&sizeStruct;

			if (sFile.empty()) {
				TFileDataStructure pomDS(0, 0, varSize, (std::string)typeid(T).name());//
				dataStruct.push_back(pomDS);
				sizeBinFile += pomDS.size;

				pocitadloTrid++;

				sizeStruct = sizeof(std::vector<TFileDataStructure>) + sizeof(int) + sizeof(int) + sizeof(size_t) + /*/*/sizeof(std::string)/*/*/ + dataStruct.at(0).sType.size();
			}
			else {
				
					// cteni velikosti struktury (cislo na zacatku souboru) a zvetsovani o jeden element vektoru dataStruct
				pSizeStruct = (char*)&sizeStruct;
				for (int i = 0; i < sizeof(int); i++) {
					*pSizeStruct = sFile.at(i);
					pSizeStruct++;
				}

				char* pDataStruct = (char*)&dataStruct;
				for (int i = 4; i < sizeStruct + 4; i++) {
					*pDataStruct = sFile.at(i);
					pDataStruct++;
				}

				
				pocitadloTrid = dataStruct.size();
				

				//pocitadloTrid = (sizeStruct - sizeof(std::vector<TFileDataStructure>)) / (sizeof(int) + sizeof(int) + sizeof(size_t) + dataStruct.at(i/*!*/).sType.size());

				TFileDataStructure pomDS(pocitadloTrid, dataStruct.at(pocitadloTrid - 1).iPosInFile + dataStruct.at(pocitadloTrid - 1).size, varSize, (std::string)typeid(T).name());//
				dataStruct.push_back(pomDS);
				sizeBinFile += pomDS.size;

				pocitadloTrid++;

				for (int i = 1; i < pocitadloTrid; i++) {
					sizeStruct += sizeof(int) + sizeof(int) + sizeof(size_t) + dataStruct.at(i).sType.size();
				}
			}

				// prepsani velikosti struktury, ktera je na zacatku souboru vyjadrena cislem v bajtech
			pSizeStruct = (char*)&sizeStruct;
			for (int i = 0; i < sizeof(int); i++) {
				sFile.at(i) = *pSizeStruct;
				pSizeStruct++;
			}



				// rozdeleni stringu s hodnotami lele slozky (sFile) pomoci substr -> sStruct a sData
			sStruct = sFile.substr(0, sizeof(int) + sizeStruct);
			sData = sFile.substr(sizeof(int) + sizeStruct + 1, sFile.size());

				// pridani hodnot struktury noveho elementu z vektrou dataStruct do sStruct pomoci prepsanim ze starych dat na nove
			char* pDataStruct = (char*)&dataStruct;
			for (int i = sizeof(int); i < sizeStruct + sizeof(int); i++) {
				sStruct.at(i) = *pDataStruct;
				pDataStruct++;
			}

				// pridani hodnot dat noveho elementu pomoci pridani na konec sData
			char* pVar = (char*)var;
			for (int i = 0; i < varSize; i++) {
				sData += *pVar;
				pVar++;
			}



				// spojeni sStruct + sData do sFile
			sFile = sStruct + sData;

				// zapsani stringu s daty cele slozky (sFile) do slozky
			pomFile.open(sPath.c_str(), std::ios::out | std::ios::beg);
			pomFile << sFile;
			pomFile.close();
			
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
				sFile += *sPom + "\n";
			delete sPom;
		}
		else if (pomFile.is_open() && mode == eMode::BINR) {
			pomFile.close();
			pomFile.open(sPath.c_str(), std::ios::in | std::ios::beg);


			std::string* sPom = new std::string;
			while (std::getline(pomFile, *sPom))
				sFile += *sPom;
			delete sPom;

			char* pSizeStruct = (char*)&sizeStruct;
			for (int i = 0; i < sizeof(int); i++) {
				*pSizeStruct = sFile.at(i);
				pSizeStruct++;
			}
			
			char* pDataStruct = (char*)&dataStruct;
			for (int i = sizeof(int); i < sizeStruct + sizeof(int); i++) {
				*pDataStruct = sFile.at(i);
				pDataStruct++;
			}

			int end = 0;
			for (int i = 0; i < dataStruct.size(); i++) {
				end += dataStruct.at(i).size;
			}

			for (int i = sizeStruct + 4; i < end + sizeStruct + 4; i++) {
				sData += sFile.at(i);
			}

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
		pomFile.close();
		pomFile.open(sPath.c_str(), std::ios::in | std::ios::binary);

		if ((dataStruct.at(index).sType == (std::string)typeid(T).name() && typeSaveMode == true) || (dataStruct.at(index).sType != (std::string)typeid(T).name() && typeSaveMode == false)) { // kontrola kompatibility typu pres dataStruct
			if (pomFile.is_open() && mode == eMode::BINR) {
				
				T* pomT = new T;
				char* pPomT = (char*)pomT;
				for (int i = dataStruct.at(index).iPosInFile; i < dataStruct.at(index).iPosInFile + dataStruct.at(index).size; i++) {
					*pPomT = sData.at(i);
					pPomT++;
				}
				
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

	
	std::streampos begin, end;

	std::string binDataType;

	bool typeSaveMode;
	std::string typeID;

	int sizeStruct;
	int pocitadloTrid;
	int sizeBinFile;

	std::string sStruct, sData, sFile;

private:
	void AddTypeName_toFile(std::string s);
	void ZjisteniTypeName();
protected:
	
	
};

