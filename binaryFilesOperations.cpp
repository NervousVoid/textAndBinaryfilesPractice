#include "binaryFilesOperations.h"

int textToBin(const string& nametf, string namebf) {
    ifstream tf(nametf);
    if (tf) {
        ofstream bf (namebf, ios::out | ios::binary);
        Reader r;
        while(!tf.eof()) {
            tf >> r.key;
            tf.get(); // remove whitespace between key and value
            tf >> r.lastname;
            tf.get();
            tf >> r.name;
            tf.get();
            tf >> r.middlename;
            tf.get();
            tf.getline(r.address, 100, '\n');
            // cout << r.key << ' ' << r.lastname << r.name << r.middlename << ' ' << r.address << endl;
            bf.write((char *) &r, sizeof(Reader));
        }
        tf.close();
        bf.close();
        return 0;
    }
    return 1;
}

int binToText(const string& namebf, string nametf ) {
    ifstream bf(namebf, ios::binary);
    if (bf) {
        ofstream tf(nametf, ios::out);
        Reader r;
        bf.read((char *)&r, sizeof(Reader));
        while (!bf.eof())
        {
            tf << r.key << ' ' << r.lastname <<  ' ' << r.name << ' ' << r.middlename << ' ' << r.address << endl;
            bf.read((char *)&r, sizeof(Reader));
        }
        bf.close();
        tf.close();
        return 0;
    }
    return 1;
}

int printBinFile(const string& namebf) {
    ifstream bf(namebf, ios::binary);
    if (bf) {
        Reader r;
        bf.read((char *)&r, sizeof(Reader));
        while (!bf.eof())
        {
            cout << r.key << ' ' << r.lastname <<  ' ' << r.name << ' ' << r.middlename << ' ' << r.address << endl;
            bf.read((char *)&r, sizeof(Reader));
        }
        bf.close();
        return 0;
    }
    return 1;
}

int removeReaderByKey(const string& namebf, int key) {
    ifstream bf(namebf, ios::binary);
    string copy_namebf = namebf;
    copy_namebf.insert((namebf.length() - 4), "_temp");
    ofstream copy_bf(copy_namebf, ios::binary);

    if (bf) {
        Reader r;
        bf.read((char *)&r, sizeof(Reader));
        while (!bf.eof())
        {
            if (r.key != key) {
                copy_bf.write((char*)&r, sizeof(Reader));
            }
            bf.read((char *) &r, sizeof(Reader));
        }
        bf.close();
        copy_bf.close();
        remove(namebf.c_str());
        rename(copy_namebf.c_str(), namebf.c_str());
        return 1;
    }
    return 0;
}

int getReaderByNumber(const string& namebf, int n) {
    ifstream bf(namebf, ios::binary);
    if (bf){
        Reader r;
        bf.seekg((n - 1) * sizeof(Reader));
        bf.read((char *)&r, sizeof(Reader));
        cout << r.key << ' ' << r.lastname <<  ' ' << r.name << ' ' << r.middlename << ' ' << r.address << endl;
        bf.close();
        return 1;
    }
    return 0;
}

int substituteForLastReaderByKey(const string& namebf, int key) {
    ifstream bf(namebf, ios::binary);
    string copy_namebf = namebf;
    copy_namebf.insert((namebf.length() - 4), "_temp");
    ofstream copy_bf(copy_namebf, ios::binary);


    if (bf){
        bf.seekg(0, ios::end);
        int bf_size = bf.tellg();
        int readers_amount = bf_size / sizeof(Reader);
        Reader r_last, r;
        bf.seekg((readers_amount - 1) * sizeof(Reader));
        bf.read((char *)&r_last, sizeof(Reader));
        bf.seekg(0);
        bf.read((char *)&r, sizeof(Reader));
        while (!bf.eof())
        {
            if (r.key == key) {
                copy_bf.write((char*)&r_last, sizeof(Reader));
            } else {
                copy_bf.write((char*)&r, sizeof(Reader));
            }
            bf.read((char *) &r, sizeof(Reader));
        }

        bf.close();
        copy_bf.close();
        remove(namebf.c_str());
        rename(copy_namebf.c_str(), namebf.c_str());
        return 1;
    }
    return 0;
}

int getReaderByKey(const string& namebf, int key){
    ifstream bf(namebf, ios::binary);
    if (bf) {
        Reader r;
        bf.read((char *)&r, sizeof(Reader));
        while (!bf.eof())
        {
            if (r.key == key) {
                cout << r.key << ' ' << r.lastname <<  ' ' << r.name << ' ' << r.middlename << ' ' << r.address << endl;
                bf.close();
                return 1;
            }
            bf.read((char *) &r, sizeof(Reader));
        }
        bf.close();
        return -1;
    }
    return 0;
}

string getBinaryFileName(){
    string name;
    cout << "Input binary file name: ";
    cin >> name;
    return name;
}

string getTextFileName() {
    string name;
    cout << "Input text file name: ";
    cin >> name;
    return name;
}

int getReaderKey(){
    int key;
    cout << "Input reader's key: ";
    cin >> key;
    return key;
}

int getReaderPosition() {
    int pos;
    cout << "Input reader's position: ";
    cin >> pos;
    return pos;
}

namespace binaryfiles {
    void menu(){
        cout << "--* Working with binary files *--\n";
        string nametf = getTextFileName(), namebf = getBinaryFileName();
        while (true) {
            int choice;
            cout << "1 - Create .dat file from .txt\n";
            cout << "2 - Create .txt file from .dat\n";
            cout << "3 - Print binary file\n";
            cout << "4 - Remove reader by key value\n";
            cout << "5 - Get reader by number in list\n";
            cout << "6 - Get reader by key value\n";
            cout << "7 - Substitute last reader for given reader by it's key value\n";
            cout << "0 - Exit\n";
            cin >> choice;

            switch (choice) {
                case 0: exit(0);
                case 1: textToBin(nametf, namebf); break;
                case 2: binToText(namebf, nametf); break;
                case 3: printBinFile(namebf); break;
                case 4: removeReaderByKey(namebf, getReaderKey()); break;
                case 5: getReaderByNumber(namebf, getReaderPosition()); break;
                case 6: getReaderByKey(namebf, getReaderKey()); break;
                case 7: substituteForLastReaderByKey(namebf, getReaderKey()); break;
                default: menu(); break;
            }
        }
    }
}
