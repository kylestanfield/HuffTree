#include "HuffTree.h"
#include <map>
#include <iostream>

InternalNode::InternalNode(BaseNode* ln, BaseNode* rn, int we) {
    l = ln;
    r = rn;
    w = we;
}

BaseNode* InternalNode::left() {
    return (BaseNode*) l;
}
BaseNode* InternalNode::right() {
    return (BaseNode*) r;
}
int InternalNode::weight() {
    return w;
}
bool InternalNode::isLeaf() {
    return false;
}


LeafNode::LeafNode(int we, char v) {
    w = we;
    element = v;
}

char LeafNode::value() {
    return element;
}
int LeafNode::weight() {
    return w;
}
bool LeafNode::isLeaf() {
    return true;
}

HuffTree::HuffTree(char elem, int weight) {
    r = new LeafNode(weight, elem);
}

HuffTree::HuffTree(BaseNode* le, BaseNode* ri, int weight) {
    r = new InternalNode(le, ri, weight);
}

BaseNode* HuffTree::root() {
    return r;
}

int HuffTree::weight() {
    return r->weight();
}

int HuffTree::Compare(HuffTree t) {
    if (weight() < t.weight()) {
        return -1;
    } else if (weight() == t.weight()) {
        return 0;
    } else {
        return 1;
    }
}

bool HuffTree::operator==(HuffTree t) {
    return Compare(t) == 0;
}

bool HuffTree::operator<(HuffTree t) {
    return Compare(t) < 0;
}

bool HuffTree::operator>(HuffTree t) {
    return Compare(t) > 0;
}

HuffTree HuffTree::buildTree(MinHeap<HuffTree>& heap) {
    while (heap.getSize() > 1) {
        HuffTree tmp1 = heap.extractMin();
        HuffTree tmp2 = heap.extractMin();
        int newWeight = 0;
        if (tmp1.root()->isLeaf()) {
            newWeight += ((LeafNode*) tmp1.root())->weight();
        } else {
            newWeight += ((InternalNode*) tmp1.root())->weight();
        }
        if (tmp2.root()->isLeaf()) {
            newWeight += ((LeafNode*) tmp2.root())->weight();
        } else {
            newWeight += ((InternalNode*) tmp2.root())->weight();
        }
        HuffTree tmp3 = HuffTree(tmp1.root(), tmp2.root(), newWeight);
        heap.add(tmp3);
    }
    return heap.peek();
}

std::vector<bool> convertStr(std::string enc) {
    std::vector<bool> bits;

    for (int i = 0; i < enc.size(); i++) {
        if (enc[i] == '1') {
            bits.push_back(1);
        } else {
            bits.push_back(0);
        }
    }
    return bits;
}

std::map<char, std::vector<bool>> HuffTree::buildTable() {
    std::map<char, std::vector<bool>> table;
    BaseNode* cur = r;
    std::vector<std::pair<BaseNode*, std::string>> dfsQueue;
    dfsQueue.push_back(std::make_pair(cur, ""));

    while (dfsQueue.size() > 0) {
        std::pair<BaseNode*, std::string> p = dfsQueue.back();
        dfsQueue.pop_back();

        cur = p.first;
        std::string encoding = p.second;
        
        if (cur->isLeaf()) {
            table[((LeafNode*) cur)->value()] = convertStr(encoding);
        } else {
            dfsQueue.push_back(std::make_pair(((InternalNode*) cur)->left(), encoding + "1"));
            dfsQueue.push_back(std::make_pair(((InternalNode*) cur)->right(), encoding + "0"));
        }
    }
    return table;
}

std::map<std::vector<bool>, char> HuffTree::reverseTable() {
    std::map<std::vector<bool>, char> table;
    BaseNode* cur = r;
    std::vector<std::pair<BaseNode*, std::string>> dfsQueue;
    dfsQueue.push_back(std::make_pair(cur, ""));

    while (dfsQueue.size() > 0) {
        std::pair<BaseNode*, std::string> p = dfsQueue.back();
        dfsQueue.pop_back();

        cur = p.first;
        std::string encoding = p.second;
        
        if (cur->isLeaf()) {
            table[convertStr(encoding)] = ((LeafNode*) cur)->value();
        } else {
            dfsQueue.push_back(std::make_pair(((InternalNode*) cur)->left(), encoding + "1"));
            dfsQueue.push_back(std::make_pair(((InternalNode*) cur)->right(), encoding + "0"));
        }
    }
    return table;
}
