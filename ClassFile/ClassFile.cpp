// ClassFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"
#include "File.h"
#include "Class.h"

class TClass2 {
public:
    int x;
    TClass2() = default;
    TClass2(int x) {
        this->x = x;
    }
};

int main()
{
    TFile file1((std::string)"FileBin.bin", TFile::eMode::BINW);  //string prepsat
    TClass cls1(1, 2, 8.5446);
    file1.Rewrite<TClass>(cls1);
    file1.Close();

    TFile file2((std::string)"FileBin.bin", TFile::eMode::BINR);
    TClass cls2(0, 0, 0.0);
    file2.Read<TClass>();  // prepsat
    cls2 = file2.GetData<TClass>();


    std::cout << std::endl << "Hello World!\n";
}


/*TFile file("mojeSlozka.txt", TFile::eMode::WRITE);
    file.Write((std::string)"Ahoj, jmenuji se Jakub Veit.\n");  // v souboru je vzdy jen to co je napsano v main() i kdyz v ni bylo neco puvodne pred buildem napsano

    std::cout << file.size.GetSize(file.pomFile, TDataSize::eUnit::BYTE) << " bytes";
    
    file.Close();*/



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
