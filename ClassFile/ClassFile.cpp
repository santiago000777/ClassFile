// ClassFile.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "Common.h"
#include "File.h"
#include "Class.h"

#define MODE    0
                //  0 -> dva stringy
                //  1 -> int a string
                //  2 -> vector


#if MODE == 0
class TClass1 {
public:
    int x;
    std::string s1;
    std::string s2;

    TClass1() {
        this->x = 0;
        this->s1 = "";
        this->s2 = "";


    }
    TClass1(int x, std::string s1, std::string s2) {
        this->x = x;
        this->s1 = s1;
        this->s2 = s2;
    }

    ~TClass1() {
        this->x = 0;
        this->s1 = "";
        this->s2 = "";

    }

    int GetSize() const {
        int size = sizeof(x);
        size += sizeof(std::string) + s1.size();
        size += sizeof(std::string) + s2.size();

        return size;
    }
};
#elif MODE == 1
class TClass2 {
public:
    int x;
    std::string s1;

    TClass2() {
        this->x = 0;
        this->s1 = "";


    }
    TClass2(int x, std::string s1) {
        this->x = x;
        this->s1 = s1;
    }

    ~TClass2() {
        this->x = 0;
        this->s1 = "";

    }

    int GetSize() const {
        int size = sizeof(x);
        size += sizeof(std::string) + s1.size();

        return size;
    }
};
#elif MODE == 2
class TClass3 {
public:
    std::vector<int> iVec;

    TClass3() {
    }
    TClass3(const std::vector<int>& v) {
        this->iVec = v;
    }

    ~TClass3() {
    }

    int GetSize() const {
        int size = 0;

        size += sizeof(std::vector<int>) + iVec.size() * sizeof(int);

        return size;
    }
};
#endif



int main()
{
    TFile file1((std::string)"ahoj1.bin", TFile::eMode::BINW);

#if MODE == 0
    TClass1* cls1a = new TClass1(2, "ahoj", "AHOJ");
    file1.Write<TClass1>(cls1a, cls1a->GetSize());
#elif MODE == 1
    TClass2* cls1a = new TClass2(2, "Ahoj");
    file1.Write<TClass2>(cls1a, cls1a->GetSize());
#elif MODE == 2
    TClass3 *cls1a = new TClass3({ 1,2 }); // normalne bez *
    file1.Write<TClass3>(cls1a, cls1a->GetSize()); //.
#endif


    file1.Close();

    TFile file2((std::string)"ahoj1.bin", TFile::eMode::BINR);
    
    file2.Read();


#if MODE == 0
    TClass1 cls1b;
    cls1b = *file2.GetData<TClass1>(0);
#elif MODE == 1
    TClass2 cls1b;
    cls1b = *file2.GetData<TClass2>(0);
#elif MODE == 2
    TClass3 cls1b;
    cls1b = *file2.GetData<TClass3>(0);
#endif



    //file2.Close();
    __debugbreak();
    std::cout << std::endl << "Hello World!\n";
}




// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
