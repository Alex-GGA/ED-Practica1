#ifndef CNODO_H
#define CNODO_H

#include "cSerializable.h"

///Declaration of class CNode
class CNode{
private:
    friend class CList;
    friend class CIterator;

    //Punteros a nodo, para usar la doble ligadura
    CNode* pNext;
    CNode* pPrev;
    CSerializable* data;
    //Métodos implementados en CNode.cpp
    void insertFront(CSerializable* data);
    CSerializable* deleteNext();

public:
    CNode();
    virtual ~CNode();
};




#endif // CNODO_H
