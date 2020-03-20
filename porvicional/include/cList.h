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

//Hereda los metodos para poder serializar la lista
class CList : public CSerializable{
private:
    //Nodos para establecer el inicio y el final de la lista
    CNode start;
    CNode nEnd;
public:
    CList();
    virtual ~CList();
    //Métodos de la lista que están implementados en cList.cpp
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
    //Métodos declarados de la la clase heredada
    void save(std::fstream& out);
    void load(std::fstream& in);
    int getCLSID()const;

};




#endif // CLISTA_H
