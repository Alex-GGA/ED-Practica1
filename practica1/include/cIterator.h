#ifndef CITERATOR_H
#define CITERATOR_H

#include <iostream>

#include "cNode.h"
#include "cSerializable.h"

class CIterator{
private:
    friend class CList;
    CNode* pCurrent;
public:
    CIterator();
    virtual ~CIterator();

    void advance();
    void toBackUp();
    void initialize(const CIterator &);
    bool isEqual(const CIterator &);
    CSerializable* readContent()const;
    void insertFront(CSerializable* data);
    CSerializable* deleteThisData()const;
    void modifyContent(CSerializable* data);
    CSerializable *getPrev();
    CSerializable* getNext();

    void operator ++();
    void operator --();
    void operator = (const CIterator& ciAuxIt);
    bool operator == (const CIterator& ciAuxIt);
    bool operator != (const CIterator& ciAuxIt);
    CSerializable* operator * ()const;

};

#endif // CITERATOR_H
