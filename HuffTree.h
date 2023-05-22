#ifndef HUFFTREE
#define HUFFTREE


class BaseNode {
    public:
        int weight();
        bool isLeaf();
};

class InternalNode : public BaseNode {
    int w;
    BaseNode l;
    BaseNode r;

    public:
        InternalNode(BaseNode ln, BaseNode rn, int we);
        BaseNode left();
        BaseNode right();
        int weight();
        bool isLeaf();
};

class LeafNode : public BaseNode {
    char element;
    int w;

    public:
        LeafNode(int we, char v);
        char value();
        int weight();
        bool isLeaf();
    
};


class HuffTree {
    private:
        BaseNode r;

    public:
        HuffTree(char elem, int weight);
        HuffTree(BaseNode l, BaseNode r, int weight);

        BaseNode root();

        int weight();
        int Compare(const HuffTree& t);        
};
#endif
