#ifndef MAPLES_LIST_H_
#define MAPLES_LIST_H_

#include <cstdlib>
#include "MaplesNode.h"

template <class MaplesType>
class MaplesList {
public:
    MaplesList();
    virtual ~MaplesList();

    void append(MaplesType node, double weight);
    void remove(MaplesType index);
    double getWeight(MaplesType index);
    void destroy();
    size_t getSize();
    MaplesType * show();

private:
    MaplesNode<MaplesType> * head;
    size_t size;
};

template <class MaplesType>
MaplesList<MaplesType>::MaplesList() : size(0) {
    this->head = new MaplesNode<MaplesType>;
    this->head->next = nullptr;
}

template <class MaplesType>
MaplesList<MaplesType>::~MaplesList() {
    this->destroy();
    delete this->head;
    this->head = nullptr;
}

template <class MaplesType>
void MaplesList<MaplesType>::destroy() {
    MaplesNode<MaplesType> * workptr = this->head;
    MaplesNode<MaplesType> * workfront = workptr;

    while (head->next) {
        while (workptr->next) {
            workfront = workptr;
            workptr = workptr->next;
        }

        delete workptr;
        --this->size;
        workfront->next = nullptr;
        workptr = this->head;
        workfront = workptr;
    }

    this->size = 0;
    workptr = nullptr;
    workfront = nullptr;
}

template <class MaplesType>
void MaplesList<MaplesType>::append(MaplesType index, double weight) {
    MaplesNode<MaplesType> * workptr = this->head;
    

    while (workptr->next && (workptr->next->index != index)) {
        workptr = workptr->next;
    }
    
    if (!workptr->next) {
        MaplesNode<MaplesType> * tempNode = new MaplesNode<MaplesType>;
        tempNode->index = index;
        tempNode->weight = weight;
        workptr->next = tempNode;
        ++this->size;
        workptr->next->next = nullptr;
        workptr = nullptr;
    }
}

template <class MaplesType>
void MaplesList<MaplesType>::remove(MaplesType index) {
    MaplesNode<MaplesType> * workptr = this->head;
    MaplesNode<MaplesType> * tempptr = nullptr;
    if (head->next) {
        while (workptr->next && (workptr->next->index != index)) {
            workptr = workptr->next;
        }

        if (workptr->next) {
            tempptr = workptr->next;
            workptr->next = tempptr->next;
            tempptr->next = nullptr;
            delete tempptr;
            tempptr = nullptr;
            --this->size;
        }
    }

    workptr = nullptr;
}

template <class MaplesType>
double MaplesList<MaplesType>::getWeight(MaplesType index) {
    MaplesNode<MaplesType> * workptr = this->head;
    if (head->next) {
        while (workptr->next && (workptr->next->index != index)) {
            workptr = workptr->next;
        }

        if (workptr->next) {
            return workptr->next->weight;
        }
    }

    workptr = nullptr;
    return -1;
}

template <class MaplesType>
size_t MaplesList<MaplesType>::getSize() {
    return this->size;
}

template <class MaplesType>
MaplesType * MaplesList<MaplesType>::show() {
    MaplesType * indexArray = new MaplesType[this->size];
    MaplesNode<MaplesType> * workptr = this->head->next;
    if (head->next) {
        for (size_t i = 0; workptr; ++i) {
            indexArray[i] = workptr->index;
            workptr = workptr->next;
        }
    }
    return indexArray;
}
#endif