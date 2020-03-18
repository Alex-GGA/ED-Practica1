#include "cIterator.h"

CIterator::CIterator(){
    pCurrent = nullptr;
}

CIterator::~CIterator(){
    //dtor
}

void CIterator::advance(){
    pCurrent = pCurrent->pNext;
}

void CIterator::toBackUp(){
    pCurrent = pCurrent->pPrev;
}

void CIterator::initialize(const CIterator& ciAuxIt){
    this->pCurrent = ciAuxIt.pCurrent;
}

bool CIterator::isEqual(const CIterator& ciAuxIt){
    return this == &ciAuxIt;
}

CSerializable* CIterator::readContent() const{
    return this->pCurrent->data;
}

void CIterator::insertFront(CSerializable* data){
    pCurrent->insertFront(data);
}

CSerializable* CIterator::deleteThisData() const{
    CSerializable* newData;
    newData = pCurrent->data;

    pCurrent->pNext->pPrev = pCurrent->pPrev;
    pCurrent->pPrev->pNext = pCurrent->pNext;
    delete pCurrent;

    return newData;
}

void CIterator::modifyContent(CSerializable* data){
    pCurrent->data = data;
}

CSerializable *CIterator::getPrev(){
    return this->pCurrent->pPrev->data;
}

CSerializable *CIterator::getNext(){
    return this->pCurrent->pNext->data;
}


///Operadores que sustituyen todos los metodos del iterador
void CIterator::operator++(){
    this->pCurrent = pCurrent->pNext;
}

void CIterator::operator--(){
    this->pCurrent = pCurrent->pPrev;
}

void CIterator::operator = (const CIterator& ciAuxIt){
    this->pCurrent = ciAuxIt.pCurrent;
}

bool CIterator::operator == (const CIterator& ciAuxIt){
    return this->pCurrent == ciAuxIt.pCurrent;
}

bool CIterator::operator!=(const CIterator& ciAuxIt){

    return this->pCurrent != ciAuxIt.pCurrent;
}

CSerializable* CIterator::operator * ()const{
    return this->pCurrent->data;
}



