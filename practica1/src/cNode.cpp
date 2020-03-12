#include "cNode.h"
///Implementation of class CNode

void CNode::insertFront(CSerializable* auxData){
    CNode* pNew(nullptr);
    pNew = new CNode;
    pNew->pNext = this->pNext;
    this->pNext->pPrev = pNew;
    pNew->pPrev = this;
    this->pNext = pNew;
    pNew->data = auxData;
}

CSerializable* CNode::deleteNext(){
    CSerializable* auxData;

    auxData = this->pNext->data;

    this->pNext = this->pNext->pNext;
    delete this->pNext->pPrev;
    this->pNext->pPrev = this;

    return auxData;
}

CNode::CNode(){

}

CNode::~CNode(){

}
