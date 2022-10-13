#ifndef PR2_BINARYFILESOPERATIONS_H
#define PR2_BINARYFILESOPERATIONS_H
#include <iostream>
#include <fstream>

using namespace std;

struct Reader {
    int key;
    char name[30];
    char lastname[30];
    char middlename[30];
    char address[100];
};

int textToBin(const string& nametf, string namebf);
int binToText(const string& namebf, string nametf );
int printBinFile(const string& namebf);
int removeReaderByKey(const string& namebf, int key);
int getReaderByNumber(const string& namebf, int n);
int substituteForLastReaderByKey(const string& namebf, int key);
int getReaderByKey(const string& namebf, int key);
string getBinaryFileName();
string getTextFileName();
int getReaderKey();
int getReaderPosition();
namespace binaryfiles{
    void menu();
}

#endif
