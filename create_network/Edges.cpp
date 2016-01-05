#include "Edges.h"

Edges::Edges(const size_t & size) : size(size){
    this->edges = new Edge[this->size];
}

Edges::Edges(const Edges & edges) {
    this->edges = new Edge[edges.size];
    for (size_t i = 0; i < edges.size; ++i) {
        this->edges[i] = edges.edges[i];
    }
    this->size = edges.size;
}

Edges::~Edges() {
    delete[] this->edges;
    this->edges = nullptr;
}