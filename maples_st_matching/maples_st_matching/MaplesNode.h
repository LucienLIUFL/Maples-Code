#ifndef MAPLES_NODE_H_
#define MAPLES_NODE_H_

template <class MaplesNodeType>
class MaplesNode {
public:
    MaplesNodeType index;
    double weight;
    MaplesNode * next;

    MaplesNode();

    virtual ~MaplesNode();
};


template <class MaplesNodeType>
MaplesNode<MaplesNodeType>::MaplesNode() : weight(0.0), next(nullptr) {}

template <class MaplesNodeType>
MaplesNode<MaplesNodeType>::~MaplesNode() {
    delete this->next;
    this->next = nullptr;
}

#endif
