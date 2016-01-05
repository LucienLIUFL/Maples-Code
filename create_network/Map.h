#ifndef MAP_H_
#define MAP_H_

#include "Nodes.h"
#include "Edges.h"

class Map {
public:
    Nodes * nodes = nullptr;
    Edges * edges = nullptr;
    Map();
    Map(const Map & map);
    virtual ~Map();
    size_t getIndexByNode(Node node);
    void updateNodesWeight(Node node);
    void updataEdgesWeight();
    void dump(const char * edgespath, const char * nodespath);
};

#endif