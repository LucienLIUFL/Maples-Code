#ifndef NODES_H_
#define NODES_H_
class Node {
public:
    double longitude;
    double latitude;
    long weight = 0;
};

class Nodes {
public:
    Node * nodes = nullptr;
    size_t size;
    Nodes(const size_t & size);
    Nodes(const Nodes & nodes);
    virtual ~Nodes();
};
#endif