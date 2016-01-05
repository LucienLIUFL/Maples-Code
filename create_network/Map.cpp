#include <fstream>
#include <iostream>
#include <iomanip>
#include "Map.h"
#include "MaplesUtil.h"

Map::Map() {
    this->nodes = nullptr;
    this->edges = nullptr;
}

Map::Map(const Map & map) {
    this->edges = new Edges(*map.edges);
    this->nodes = new Nodes(*map.nodes);
}

Map::~Map() {
    delete[] this->edges;
    this->edges = nullptr;
    delete[] this->nodes;
    this->nodes = nullptr;
}

size_t Map::getIndexByNode(Node node) {
    double minDistance = 10000000.0;
    size_t minIndex = -1;
    for (size_t i = 0; i < this->nodes->size; ++i) {
        if (MaplesUtil::getDistance(this->nodes->nodes[i], node) < minDistance) {
            minDistance = MaplesUtil::getDistance(this->nodes->nodes[i], node);
            minIndex = i;
        }
    }
    std::cout << minIndex << std::endl;
    return minIndex;
}

void Map::updateNodesWeight(Node node) {
    MaplesUtil::assert(this->getIndexByNode(node) < this->nodes->size, "index out of range");
    ++this->nodes->nodes[this->getIndexByNode(node)].weight;
}

void Map::updataEdgesWeight() {
    for (size_t i = 0; i < this->edges->size; ++i) {
        this->edges->edges[i].weight = this->nodes->nodes[this->edges->edges[i].begin].weight 
                                       + this->nodes->nodes[this->edges->edges[i].end].weight;
    }
}

void Map::dump(const char * edgespath, const char * nodespath) {
    std::ofstream edgesfile(edgespath);
    std::ofstream nodesfile(nodespath);
    MaplesUtil::assert(edgesfile.is_open(), "The edgesfile is not be correct opened");
    MaplesUtil::assert(nodesfile.is_open(), "The nodesfile is not be correct opened");
    
    for (size_t i = 0; i < this->edges->size; ++i) {
        edgesfile << i << " " << this->edges->edges[i].begin << " ";
        edgesfile << this->edges->edges[i].end << " " << this->edges->edges[i].weight << std::endl;
    }

    nodesfile << std::setiosflags(std::ios::fixed);
    for (size_t i = 0; i < this->nodes->size; ++i) {
        nodesfile << i << " " << this->nodes->nodes[i].longitude << " ";
        nodesfile << this->nodes->nodes[i].latitude << " " << this->nodes->nodes[i].weight << std::endl;
    }
    nodesfile.close();
    edgesfile.close();
}