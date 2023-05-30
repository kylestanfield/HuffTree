#include <bitset>
#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>

#ifndef HUFFTREE
#define HUFFTREE
#include "HuffTree.h"
#endif

#ifndef MINHEAP
#define MINHEAP
#include "Minheap.cpp"
#endif

using namespace std;

int main() {
    cout << "Enter the filename to be read:\n";
    string s;
    cin >> s;
    ifstream fin;
    
    // Check if file exists
    if (filesystem::exists(s)) {
        fin.open(s);
    } else {
        cout << "File not found.\n";
        return 1;
    }


    string line;
    map<char, int> frequencies;
    
    // Get frequency of each ch in corpus
    while (getline(fin, line)) {
        int n = line.length();
        for (int i = 0; i < n; i++) {
            frequencies[line[i]]++;
        }
    }

    // Use frequencies to build a MinHeap of Huffman Trees
    MinHeap<HuffTree> heap;
    for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
        HuffTree temp = HuffTree(it->first, it->second);
        heap.add(temp);
    }
    // Continuously combine smallest weight trees until all are combined
    HuffTree tree = HuffTree::buildTree(heap);

    // Use Huffman Tree to make a table from element to binary code
    map<char, vector<bool>> huffmanTable = tree.buildTable();

    // Next, write a header for the output file
    // Write the tree or frequency table
    // Then use a symbol to mark the end of the header and the start of compressed data

    return 0;
}
