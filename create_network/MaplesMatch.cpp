#include <fstream>
#include "Nodes.h"
#include "MaplesUtil.h"
#include "MaplesMatch.h"

Map MaplesMatch::initMap(const char * nodespath, const char * edgespath) {
    std::ifstream nodesfile(nodespath);
    std::ifstream edgesfile(edgespath);
   
    MaplesUtil::assert(nodesfile.is_open(), "The nodesfile is not be correct opened");
    MaplesUtil::assert(edgesfile.is_open(), "The edgesfile is not be correct opened");

    Nodes nodearr(MaplesMatch::NODES_SIZE);
    Edges edgearr(MaplesMatch::EDGES_SIZE);

    size_t index;
    for (size_t i = 0; i < nodearr.size && nodesfile >> index; ++i) {
        nodesfile >> nodearr.nodes[i].longitude;
        nodesfile >> nodearr.nodes[i].latitude;
        nodesfile >> nodearr.nodes[i].weight;
    }
    
    for (size_t i = 0; i < edgearr.size && edgesfile >> index; ++i) {
        edgesfile >> edgearr.edges[i].begin;
        edgesfile >> edgearr.edges[i].end;
        edgesfile >> edgearr.edges[i].weight;
    }

    edgesfile.close();
    nodesfile.close();

    Map map;

    map.edges = new Edges(edgearr);
    map.nodes = new Nodes(nodearr);
    return map;
}

Node * MaplesMatch::getNodeInput(const char * inputfile, size_t nodeSize) {
    std::ifstream infile(inputfile);
    MaplesUtil::assert(infile.is_open(), "The inputfile is not be correct opened");

    Node * nodes = new Node[nodeSize];
    for (size_t i = 0; i < nodeSize && infile.good(); ++i) {
        infile >> nodes[i].longitude;
        infile >> nodes[i].latitude;
    }

    return nodes;
}