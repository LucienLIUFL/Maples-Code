#ifndef EDGES_H_
#define EDGES_H_


class Edge {
public:
    size_t begin;
    size_t end;
    long weight;
};

class Edges {
public:
    Edge * edges = nullptr;
    size_t size;
    Edges(const size_t & size);
    Edges(const Edges & edges);
    virtual ~Edges();
};

#endif