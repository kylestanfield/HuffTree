#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
#include "HuffTree.h"

using namespace std;

int main() {

    //read in file name
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

    vector<HuffTree*> heap;
    for (auto it = frequencies.begin(); it != frequencies.end(); it++) {
        heap.push_back(new HuffTree(it->first, it->second));
    }
    for (auto it = heap.begin(); it < heap.end(); it++) {
        cout << (*it)->r->w << " ";
    }
    cout << endl;
    make_heap(heap.begin(), heap.end());
    HuffTree* tree = HuffTree::buildTree(heap);

    return 0;
}
