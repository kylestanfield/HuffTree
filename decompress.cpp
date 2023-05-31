#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>
#include <sstream>
#include "HuffTree.h"

#ifndef MINHEAP
#define MINHEAP
#include "Minheap.cpp"
#endif

using namespace std;

int main() {
    cout << "Enter the filename to be decompressed:\n";
    string inFile;
    cin >> inFile;
    ifstream fin;

    if (filesystem::exists(inFile)) {
        fin.open(inFile);
    } else {
        cout << "File not found.\n";
        return 1;
    }

    map<char, int> frequencies;
    char element;
    int frequency;
    int numElements = 0;
    
    string tableLine;
    getline(fin, tableLine);
    istringstream elemStream(tableLine);
    elemStream >> numElements;
    
    for (int i = 0; i < numElements; i++) {
        getline(fin, tableLine);
        istringstream tableStream(tableLine);
        
        tableStream >> noskipws >> element;
        tableStream >> noskipws >> frequency;
        frequencies[element] = frequency;
        cout << element << " " << frequency << "\n";
    }

    return 0;
}
