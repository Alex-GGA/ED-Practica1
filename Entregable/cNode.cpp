#include "cNode.h"
///Implementation of class CNode

//Inserta al frente
void CNode::insertFront(CSerializable* auxData){
    CNode* pNew(nullptr);
    pNew = new CNode; //Crea un nodo auxiliar
    pNew->pNext = this->pNext; //Coloca al siguiente del nodo nuevo
    this->pNext->pPrev = pNew; //Coloca el nuevo nodo
    pNew->pPrev = this; //Coloca a this el el anterior del nuevo nodo
    this->pNext = pNew; //Coloca al siguiente de this el nuevo nodo
    pNew->data = auxData; //Asigna el dato del nuevo nodo
}

//Elimina el siguiente elemento
CSerializable* CNode::deleteNext(){
    CSerializable* auxData;

    auxData = this->pNext->data; //Salva el dato del nodo a elminar

    this->pNext = this->pNext->pNext; //Mueve la cabecera del siguiente, hacia el sguiente de ese
    delete this->pNext->pPrev; //Elimina el nodo siguiente de this
    this->pNext->pPrev = this; //Coloca la cabecera anterior a this.

    return auxData; //Devuelve el dato eliminado
}

CNode::CNode(){

}

CNode::~CNode(){

}
