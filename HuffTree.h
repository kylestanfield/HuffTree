#ifndef HUFFTREE
#define HUFFTREE


class BaseNode {
    public:
        int weight();
        bool isLeaf();
};

class InternalNode : public BaseNode {
    int weight;
    BaseNode l;
    BaseNode r;

    public:
        InternalNode(BaseNode l, BaseNode r, int w);
        BaseNode left();
        BaseNode right();
        int weight();
        bool isLeaf();
}

class LeafNode : public BaseNode {
    char element;
    int weight;

    public:
        char value();
        int weight();
        bool isLeaf();
    
}


class HuffTree {
    private:
        Node root;

    public:
        HuffTree(char elem, int weight);
        HuffTree(BaseNode l, BaseNode r, int weight);

        BaseNode root();

        int weight();
        int Compare(const HuffTree& t);        
};
#endif
