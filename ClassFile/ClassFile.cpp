// ClassFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"
#include "File.h"
#include "Class.h"

class TClass2 {
public:
    int x;
    std::string s;


    TClass2() {
        this->x = 0;
        this->s = "";
    }
    TClass2(int x, std::string s) {
        this->x = x;
        this->s = s;
    }

    ~TClass2() {
        this->x = 0;
        this->s = "";
    }

    int GetSize() const {
        int size = sizeof(x);
        size += sizeof(std::string) + s.size();

        return size;
    }
};



int main()
{

    

    TFile file1((std::string)"ahoj1.bin", TFile::eMode::BINW);


    TClass2 cls1a(4, "Ahoj");
    file1.Write<TClass2>(cls1a, cls1a.GetSize());

    TClass2 cls2a(8, "Zdar");
    file1.Write<TClass2>(cls2a, cls2a.GetSize());

    


    file1.Close();



    TFile file2((std::string)"ahoj1.bin", TFile::eMode::BINR);
    
    file2.Read();


    TClass2 cls1b(0, "");
    cls1b = *file2.GetData<TClass2>(0);

    TClass2 cls2b(0, "");
    cls2b = *file2.GetData<TClass2>(1);



    //file2.Close();
    __debugbreak();
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
