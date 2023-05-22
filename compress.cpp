#include <bits/stdc++.h>
#include <fstream>
#include <filesystem>
#include "HuffTree.h"

using namespace std;

int main() {

    string s;
    cin >> s;
    ifstream fin;
    

    if (filesystem::exists(s)) {
        fin.open(s);
    } else {
        cout << "File not found.\n";
        return 1;
    }
    string line;

    //declare a map from char to int
    map<char, int> frequencies;

    while (getline(fin, line)) {
        int n = line.length();
        for (int i = 0; i < n; i++) {
            frequencies[line[i]]++;
        }
    }

    return 0;
}
