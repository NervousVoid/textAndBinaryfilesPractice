#ifndef PR2_TEXTFILESOPERATIONS_H
#define PR2_TEXTFILESOPERATIONS_H

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

string removePunct(string &word);
int countNumbersInString(string word);
void printFile(fstream &f);
void appendFile(fstream &f);
void createFileASCII(fstream &f);
void getWordByNumber(fstream &f);
void getNumbersAmountInFile(fstream &f);
void removeStringByNumber(fstream &f, string file_name);
namespace textfiles {
    void menu();
}

#endif
