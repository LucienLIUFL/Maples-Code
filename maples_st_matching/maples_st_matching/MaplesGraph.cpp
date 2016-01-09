#include <iostream>
#include <fstream> 
#include <float.h>
#include "MaplesGraph.h"

#define MAX_DOUBLE 100000.0


MaplesGraph::MaplesGraph(size_t size) : size(size) {
    this->graph = new MaplesList<int>[size];
}

MaplesGraph::~MaplesGraph() {
    delete[] this->graph;
    this->graph = nullptr;
}

size_t MaplesGraph::getSize() const {
    return this->size;
}


void MaplesGraph::setOuts(size_t index, int node, double weight) {
    this->graph[index].append(node, weight);
}

double MaplesGraph::getWeight(size_t tail, int head) {
    return this->graph[tail].getWeight(head);
}

void MaplesGraph::init(const char * filepath) {
    std::ifstream infile(filepath);

    size_t index;
    int node;
    double weight;
    for (size_t i = 0; infile >> i; ++i) {
        infile >> index;
        infile >> node;
        infile >> weight;
        this->graph[index].append(node, weight);
    }

    infile.close();
}



size_t * MaplesGraph::getShortestPath(size_t begin, size_t end) {
    int SIZE = this->size;
    bool * flag = new bool[this->size];
    double * weightArray = new double[this->size];
    size_t * frontArray = new size_t[this->size];
    for (size_t i = 0; i < this->size; ++i) {
        flag[i] = true;
        weightArray[i] = -1;
        frontArray[i] = -1;
    }

    weightArray[begin] = 0;
    frontArray[begin] = begin;
    size_t tmpIndex = begin;
    int * tmpArray;
    for (size_t i = 0; i < this->size; ++i) {
        tmpArray = this->graph[tmpIndex].show();

        for (size_t k = 0; k < graph[tmpIndex].getSize(); ++k) {
            if (flag[tmpIndex]) {
                if (-1 == graph[tmpIndex].getWeight(tmpArray[k])) {
                    continue;
                } else if (-1 == weightArray[tmpArray[k]]) {
                    weightArray[tmpArray[k]] = graph[tmpIndex].getWeight(tmpArray[k]);
                    frontArray[tmpArray[k]] = tmpIndex;
                    continue;
                } else if (weightArray[tmpArray[k]] > (graph[tmpIndex].getWeight(tmpArray[k]) + weightArray[tmpIndex])) {
                    weightArray[tmpArray[k]] = (graph[tmpIndex].getWeight(tmpArray[k]) + weightArray[tmpIndex]);
                    frontArray[tmpArray[k]] = tmpIndex;
                }
            }
            frontArray[tmpArray[k]] = tmpIndex;
        }

        bool isDone = true;
        size_t minIndex = 0;
        double minWeight = MAX_DOUBLE;
        for (size_t j = 0; j < this->size; ++j) {
            if (flag[j] && (-1 == weightArray[j])) {
                if (weightArray[j] < minWeight) {
                    minIndex = j;
                    isDone = false;
                }
            }
        }

        tmpIndex = minIndex;

        delete[] tmpArray;
        if (isDone) {
            break;
        }
    }

    for (size_t i = 0; i < this->size; ++i) {
        std::cout << weightArray[i] << std::ends;
    }
    std::cout << std::endl;
    for (size_t i = 0; i < this->size; ++i) {
        std::cout << weightArray[i] << std::ends;
    }
    std::cout << std::endl;

    delete[] flag;
    delete[] weightArray;
    delete[] frontArray;
    return nullptr;
}