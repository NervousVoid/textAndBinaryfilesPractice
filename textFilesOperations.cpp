#include "textFilesOperations.h"

string removePunct(string &word){
    for (int i = 0; i < word.length(); i++){
        if(ispunct(word[i]))
            word.erase(i);
    }
    return word;
}

int countNumbersInString(string word) {
    int c = 0;
    bool flag = false;
    for (int i = 0; i < word.length(); i++) {
        if (isdigit(word[i])){
            if (!flag)
                flag = true;
        } else {
            if (flag) {
                flag = false;
                c++;
            }
        }
        if (flag && i == word.length() - 1)
            c++;
    }
    return c;
}

void printFile(fstream &f) {
    string line;
    while (getline(f, line))
        cout << line << endl;
}

void appendFile(fstream &f) {
    string str;
    cout << "String for appending: ";
    cin >> str;
    f << str << endl;
}

void createFileASCII(fstream &f) {
    cout << "Input your decimal ASCII values:\n";
    int ascii_numeric;
    do {
        cin >> ascii_numeric;
        char ch = ascii_numeric;
        f << ch;
    } while (cin && cin.peek() != '\n');
    f.close();
    printFile(f);
}

void getWordByNumber(fstream &f) {
    int n;
    string cur_word;
    cout << "Word number: ";
    cin >> n;
    for (int i = 1; i <= n; i++) {
        f >> cur_word;
        if (i == n)
            cout << removePunct(cur_word) << endl;
    }
}

void getNumbersAmountInFile(fstream &f) {
    string line;
    int c = 0;
    while (getline(f, line)) {
        c += countNumbersInString(line);
    }
    cout << c << " numbers in file\n";
}

void removeStringByNumber(fstream &f, string file_name) {
    fstream f_copy;
    string f_copy_name = file_name;
    f_copy_name.insert((file_name.length() - 4), "_temp");
    int str_num;
    int i = 1;
    string line;
    cout << "Enter what string to remove (number): ";
    cin >> str_num;

    f_copy.open(f_copy_name, ios::out | ios::trunc);
    while (getline(f, line)) {
        if (i != str_num)
            f_copy << line << endl;
        i++;
    }
    f_copy.close();
    f.close();
    remove(file_name.c_str());
    rename(f_copy_name.c_str(), file_name.c_str());

}

namespace textfiles {
    void menu(){
        cout << "--* Working with text files *--\n";
        string file_name;
        cout << "Input file name: ";
        cin >> file_name;

        while (true) {
            int choice;
            cout << "1 - Create .txt file from ASCII decimal numbers\n";
            cout << "2 - Print file text\n";
            cout << "3 - Append string to file\n";
            cout << "4 - Find word of given number in file\n";
            cout << "5 - Count numbers amount in file\n";
            cout << "6 - Remove string by number\n";
            cout << "0 - Exit\n";
            cin >> choice;

            fstream f;
            if (!f) {
                cout << "File stream error\n";
                menu();
            }

            switch (choice) {
                case 2: case 4: case 5: case 6: {
                    f.open(file_name, ios::in);
                    if (!f.is_open()) {
                        cout << "Error while opening the file\n";
                        menu();
                    }
                }; break;
                case 1: {
                    f.open(file_name, ios::out | ios::trunc);
                    if (!f.is_open()){
                        cout << "Error while opening the file\n";
                        menu();
                    }
                }; break;
                case 3: {
                    f.open(file_name, ios::app);
                    if (!f.is_open()){
                        cout << "Error while opening the file\n";
                        menu();
                    }
                }; break;
            }

            switch (choice) {
                case 0: f.close(); exit(0);
                case 1: createFileASCII(f); f.close(); break;
                case 2: printFile(f); f.close(); break;
                case 3: appendFile(f); f.close(); break;
                case 4: getWordByNumber(f); f.close(); break;
                case 5: getNumbersAmountInFile(f); f.close(); break;
                case 6: removeStringByNumber(f, file_name); f.close(); break;
                default: menu(); break;
            }
        }
    }
}
