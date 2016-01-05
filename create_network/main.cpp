#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

#include "MaplesUtil.h"
#include "MaplesMatch.h"
#include "Map.h"
#include "Nodes.h"



int main(int argc, char * argv[]) {
    MaplesUtil::assert(argc == 7, "Please enter path: main path");
  
    Map map(MaplesMatch::initMap(argv[1], argv[2]));
    map.updataEdgesWeight();
    
    std::istringstream insstream(argv[4]);
    size_t size;
    insstream >> size;
    Node * nodearr = MaplesMatch::getNodeInput(argv[3], size);
    
    for (size_t i = 0; i < size; ++i) {
        map.updateNodesWeight(nodearr[i]);
    }

    map.updataEdgesWeight();
    map.dump(argv[5], argv[6]);
    return 0;
}

