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
    int GetSize() const {
        int size = sizeof(x);
        return size;
    }
};



int main()
{

    

    TFile file1((std::string)"ahoj1.bin", TFile::eMode::BINW);

    TClass cls1a(1, 2, 8.5446);
    //char c = 'j';
    file1.Write<TClass>(cls1a, cls1a.GetSize());

    TClass2 cls2a(4);
    file1.Write<TClass2>(cls2a, cls2a.GetSize());

    TClass cls3a(2, 8, 19.54);
    file1.Write<TClass>(cls3a, cls3a.GetSize());

    TClass cls4a(7, 8, 12.89);
    file1.Write<TClass>(cls4a, cls4a.GetSize());

    TClass2 cls5a(8);
    file1.Write<TClass2>(cls5a, cls5a.GetSize());

    TClass2 cls6a(9);
    file1.Write<TClass2>(cls6a, cls6a.GetSize());

    TClass cls7a(88, 77, 9.994);
    file1.Write<TClass>(cls7a, cls7a.GetSize());



    file1.Close();



    TFile file2((std::string)"ahoj1.bin", TFile::eMode::BINR);
    file2.Read<char>();


    TClass cls1b(0, 0, 0.0);
    //char h = '\0';
    cls1b = file2.GetData<TClass>(0);

    TClass2 cls2b(0);
    cls2b = file2.GetData<TClass2>(1);

    TClass cls3b(0, 0, 0.0);
    cls3b = file2.GetData<TClass>(2);

    TClass cls4b(0, 0, 0.0);
    cls4b = file2.GetData<TClass>(3);

    TClass2 cls5b(0);
    cls5b = file2.GetData<TClass2>(4);

    TClass2 cls6b(0);
    cls6b = file2.GetData<TClass2>(5);

    TClass cls7b(0, 0, 0.0);
    cls7b = file2.GetData<TClass>(6);

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
