#ifndef MAPLES_GRAPH_H_
#define MAPLES_GRAPH_H_

#include <vector>
#include "MaplesList.h"

class MaplesGraph {
public:
    MaplesGraph(size_t size);
    virtual ~MaplesGraph();

    size_t getSize() const;
    double getWeight(size_t tail, int head);
    
    void init(const char * filepath);
    size_t * getShortestPath(size_t begin, size_t end);

private:
    const size_t size;
    MaplesList<int> * graph;
    void setOuts(size_t index, int node, double weight);
};

#endif