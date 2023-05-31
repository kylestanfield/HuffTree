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

    // Read in the frequency table
    map<char, int> frequencies;
    char element;
    int frequency;
    int numElements = 0;
    
    string tableLine;
    getline(fin, tableLine);
    istringstream elemStream(tableLine);
    elemStream >> numElements;
    long charCount = 0;
    
    for (int i = 0; i < numElements; i++) {
        fin >> noskipws >> element;
        getline(fin, tableLine);
        istringstream tableStream(tableLine);
        
        tableStream >> noskipws >> frequency;
        charCount += frequency;
        frequencies[element] = frequency;
    }

    // Build the encoding table from the frequency table
    MinHeap<HuffTree> heap;

    for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
        HuffTree temp = HuffTree(it->first, it->second);
        heap.add(temp);
    }
    HuffTree tree = HuffTree::buildTree(heap);
    map<vector<bool>, char> huffmanTable = tree.reverseTable();
    
    cout << "Enter the filename output should be written to:\n";
    string outFile;
    cin >> outFile;
    ofstream out;
    out.open(outFile);


    char buffer = 0;
    long readChars = 0;
    vector<bool> code;
    while (fin >> noskipws >> buffer) {
        for (int i = 7; i >= 0; i--) {
            code.push_back(buffer & (1 << i));
            if (huffmanTable.find(code) != huffmanTable.end()) {
                out << huffmanTable[code];
                code.clear();
                readChars += 1;
            }
            if (readChars == charCount) {
                fin.close();
                out.close();
                return 0;
            }
        }
    }
    fin.close();
    out.close();
    return 0;
}
