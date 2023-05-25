#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
#include "HuffTree.h"
#ifndef MINHEAP
#define MINHEAP
#include "Minheap.cpp"
#endif

using namespace std;

int main() {

    //read in file name
    cout << "Enter the filename to be read:\n";
    string s;
    cin >> s;
    ifstream fin;
    
    //check if file exists
    if (filesystem::exists(s)) {
        fin.open(s);
    } else {
        cout << "File not found.\n";
        return 1;
    }
    string line;

    //declare a map from char to int
    map<char, int> frequencies;

    //get frequency of each ch in corpus
    while (getline(fin, line)) {
        int n = line.length();
        for (int i = 0; i < n; i++) {
            frequencies[line[i]]++;
        }
    }

    MinHeap<HuffTree> heap;
    for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
        HuffTree temp = HuffTree(it->first, it->second);
        heap.add(temp);
    }
    HuffTree tree = HuffTree::buildTree(heap);
    return 0;
}
