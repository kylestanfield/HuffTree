#include "HuffTree.h"

InternalNode::InternalNode(BaseNode ln, BaseNode rn, int we) {
    l = ln;
    r = rn;
    w = we;
}

BaseNode InternalNode::left() {
    return left;
}
BaseNode InternalNode::right() {
    return right;
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
HuffTree::HuffTree(BaseNode l, BaseNode r, int weight) {
    r = new InternalNode(l, r, weight);
}
BaseNode HuffTree::root() {
    return r;
}
int HuffTree::weight() {
    return r.weight();
}
