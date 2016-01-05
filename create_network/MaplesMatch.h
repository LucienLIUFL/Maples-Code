#ifndef MAPLES_MATCH_H_
#define MAPLES_MATCH_H_
#include "Map.h"
#include "Nodes.h"
namespace MaplesMatch {
    const int NODES_SIZE = 24702;
    const int EDGES_SIZE = 33532;
    Map initMap(const char * nodespath, const char * edgespath);
    Node * getNodeInput(const char * inputfile, size_t nodeSize);
}

#endif