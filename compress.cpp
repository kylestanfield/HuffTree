#include <fstream>
#include <filesystem>
#include <iostream>
#include <map>

#include "HuffTree.h"

#ifndef MINHEAP
#define MINHEAP
#include "Minheap.cpp"
#endif

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cout << "Usage: ./compress inFile outFile\n";
        return 1;
    }

    string inputFile = argv[1];
    ifstream fin;
    // Check if file exists
    if (filesystem::exists(inputFile)) {
        fin.open(inputFile);
    } else {
        cout << "File not found.\n";
        return 1;
    }


    string line;
    map<char, int> frequencies;
    
    // Get frequency of each ch in corpus
    char elem = 0;
    while (fin >> noskipws >> elem) {
        frequencies[elem]++;
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

    string outFile = argv[2];
    ofstream out;
    out.open(outFile);

    // Next, write a header for the output file
    // Write the frequency table
    out << frequencies.size() << endl;
    for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
        out << it->first << it->second << "\n";
    }
    // Encode the text using the code table
    fin.clear();
    fin.seekg(0);

    vector<bool> encoding;
    // Read the input again and turn it into a vector of bits

    while (fin >> noskipws >> elem) {
        vector<bool> bits = huffmanTable[elem];
        encoding.insert(encoding.end(), bits.begin(), bits.end());
    }
    fin.close();

    // We cannot write bit by bit so we write chars (8 bits).
    char buffer = 0;
    int bitCount = 0;
    for (auto it = encoding.begin(); it != encoding.end(); it++) {
        buffer <<= 1;
        buffer |= *it;
        bitCount += 1;

        if (bitCount == 8) {
            out << buffer;
            buffer = 0;
            bitCount = 0;
        }
    }
    // If we don't have a multiple of 8 bits, we pad the end with zeros
    // This will work because no code is a prefix of another code

    if (bitCount > 0) {
        while (bitCount < 8) {
            buffer <<= 1;
            bitCount += 1;
        }
        out << buffer;
    }
    out.close();
    return 0;
}
