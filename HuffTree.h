#include <vector>
#include <algorithm>

#ifndef MINHEAP
#define MINHEAP
#include "Minheap.cpp"
#endif

#ifndef HUFFTREE
#define HUFFTREE


class BaseNode {
    public:
        virtual int weight() = 0;
        virtual bool isLeaf() = 0;
};

class InternalNode : public BaseNode {
    public:    
        int w;
        BaseNode* l;
        BaseNode* r;
        InternalNode(BaseNode* ln, BaseNode* rn, int we);
        BaseNode* left();
        BaseNode* right();
        int weight();
        bool isLeaf();
};

class LeafNode : public BaseNode {
    public:
        char element;
        int w;
        LeafNode(int we, char v);
        char value();
        int weight();
        bool isLeaf();
};


class HuffTree {
    public:
        BaseNode* r;
        HuffTree(char elem, int weight);
        HuffTree(BaseNode* l, BaseNode* r, int weight);

        static HuffTree buildTree(MinHeap<HuffTree>& heap);
        BaseNode* root();

        int weight();
        int Compare(HuffTree t);
        bool operator==(HuffTree t);
        bool operator<(HuffTree t);
        bool operator>(HuffTree t);
};
#endif
