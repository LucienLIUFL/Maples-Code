#include "Nodes.h"

Nodes::Nodes(const size_t & size) : size(size) {
    this->nodes = new Node[this->size];
}

Nodes::Nodes(const Nodes & nodes) {
    this->nodes = new Node[nodes.size];
    for (size_t i = 0; i < nodes.size; ++i) {
        this->nodes[i] = nodes.nodes[i];
    }
    this->size = nodes.size;
}

Nodes::~Nodes() {
    delete[] this->nodes;
    this->nodes = nullptr;
}
