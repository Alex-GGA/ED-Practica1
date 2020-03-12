#ifndef CNODO_H
#define CNODO_H

#include "cSerializable.h"

///Declaration of class CNode
class CNode{
private:
    friend class CList;
    friend class CIterator;

    CNode* pNext;
    CNode* pPrev;
    CSerializable* data;

    void insertFront(CSerializable* data);
    CSerializable* deleteNext();

public:
    CNode();
    virtual ~CNode();
};




#endif // CNODO_H
