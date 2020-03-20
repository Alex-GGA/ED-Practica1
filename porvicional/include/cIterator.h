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


    void advance(); //Coloca el iterador en la siugiente posicion
    void toBackUp(); //En la anterior posicion
    void initialize(const CIterator &); //Inicializa el iterador
    bool isEqual(const CIterator &); //Verifica si es igual a otro iterador
    CSerializable* readContent()const; //Recupera el contenido del iterador
    void insertFront(CSerializable* data); //Insera en la lista usando el iterador
    CSerializable* deleteThisData()const; //Elimina un dato en donde esta el iterador
    void modifyContent(CSerializable* data); //Permite modificar el dato del iterador
    CSerializable *getPrev(); //Recupera la posicion anterior
    CSerializable* getNext(); //Recupera la posicion siguiente

    //Sobre carga de operadores para el funcionamiento del iterador
    void operator ++();
    void operator --();
    void operator = (const CIterator& ciAuxIt);
    bool operator == (const CIterator& ciAuxIt);
    bool operator != (const CIterator& ciAuxIt);
    CSerializable* operator * ()const;

};

#endif // CITERATOR_H
