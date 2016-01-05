#ifndef MAPLES_UTIL_H_
#define MAPLES_UTIL_H_
#include "Nodes.h"

namespace MaplesUtil {
    void assert(bool condition, const char * errstr);
    double getDistance(Node begin, Node end);
}

#endif