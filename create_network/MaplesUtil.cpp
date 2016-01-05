#include <iostream>
#include <cmath>
#include "MaplesUtil.h"

void MaplesUtil::assert(bool condition, const char * errstr) {
    if (condition)
        return;
    std::cerr << errstr << std::endl;
    exit(1);
}

double MaplesUtil::getDistance(Node begin, Node end) {
    return pow(begin.latitude - end.latitude, 2.0) + pow(begin.longitude - end.longitude, 2.0);
}