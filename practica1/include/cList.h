#ifndef CLISTA_H
#define CLISTA_H

#define CLSID_LIST 7
#include <iostream>

#include "cIterator.h"
#include "cNode.h"
#include "cSerializable.h"
#include "indiceprimario.h"
#include "indicesec.h"
///Declaration of the list

class CList : public CSerializable{
private:
    CNode start;
    CNode nEnd;
public:
    CList();
    virtual ~CList();

    void insertAtTheStart(CSerializable* data);
    void insertAtTheEnd(CSerializable* data);

    CSerializable* deleteAtTheStart();
    CSerializable* deleteAtTheEnd();

    bool isEmpty();
    bool isFull();
    int sizeOfTheList();

    void sortList(const bool&);

    void print();

    void listEmpty();

    CIterator beginList()const;
    CIterator endList()const;
    CIterator findData(CSerializable* data);

    void save(std::fstream& out);
    void load(std::fstream& in);
    int getCLSID()const;

};




#endif // CLISTA_H
