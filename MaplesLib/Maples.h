#ifndef MAPLES_H_
#define MAPLES_H_

#include <iostream>
#include <string>

//Maples Type
typedef size_t mint;

//Basic Object
class Object {
public:
    virtual ~Object() {}
};

class MaplesString {
public:
    MaplesString(const char* cstr): str(cstr) {}
    MaplesString(const MaplesString& string): str(string.str) {}
    MaplesString& operator=(const MaplesString& string) {
        this->str = string.str;
        return *this;
    }
    
    MaplesString& operator+(const MaplesString& string) {
        std::string temp(string.str);
        this->str.append(temp);
        return *this;
    }
    
    std::string toString() {
        return this->str;
    }
private:
    std::string str;
};

//Debug part
void assert(bool condition, const char* errMessage) {
    if (!condition) {
        std::cerr << errMessage << std::endl;
        exit(1);
    }
}

void print(std::string str) {
    std::cout << str << std::endl;
}

#endif
