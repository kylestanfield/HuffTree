#include "HuffTree.h"
#include <iostream>

int BaseNode::weight() {
    return w;
}

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

int HuffTree::Compare(HuffTree* t) {
    if (weight() < t->weight()) {
        return -1;
    } else if (weight() == t->weight()) {
        return 0;
    } else {
        return 1;
    }
}

bool HuffTree::operator==(HuffTree* t) {
    return Compare(t) == 0;
}

bool HuffTree::operator<(HuffTree* t) {
    return Compare(t) < 0;
}

bool HuffTree::operator>(HuffTree* t) {
    return Compare(t) > 0;
}

HuffTree* HuffTree::buildTree(std::vector<HuffTree*>& heap) {
    std::cout << "Building Tree:\n";

    while (heap.size() > 1) {
        std::pop_heap(heap.begin(), heap.end());
        HuffTree* tmp1 = heap.back();
        heap.pop_back();

        std::pop_heap(heap.begin(), heap.end());
        HuffTree* tmp2 = heap.back();
        heap.pop_back();

        HuffTree* tmp3 = new HuffTree(tmp2->root(), tmp1->root(), tmp1->weight() + tmp2->weight());
        heap.push_back(tmp3);
        std::push_heap(heap.begin(), heap.end());
    }
    return heap.back();
}
