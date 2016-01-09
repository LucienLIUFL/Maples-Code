#include <iostream> 
#include <fstream>

#include "MaplesGraph.h"

const int GRAPHS_SIZE = 6;
const char * GRAPH_FILE_PATH = "C:\\Users\\admin\\Desktop\\edges.txt";

int main(int argc, char * argv[]) {
    
    MaplesGraph graph(GRAPHS_SIZE);
    graph.init(GRAPH_FILE_PATH);

    graph.getShortestPath(0, 5);
    return 0;
}