#include "HuffTree.h"
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
    std::cout << "Building Tree:\n";

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
