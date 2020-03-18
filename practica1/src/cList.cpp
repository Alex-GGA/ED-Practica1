#include "cList.h"
///Implementation of the list

CList::CList(){
    start.pNext = &nEnd;
    nEnd.pPrev = &start;
    start.pPrev = nullptr;
    nEnd.pNext = nullptr;
}

CList::~CList(){
    listEmpty();
}

void CList::insertAtTheStart(CSerializable* data){
    start.insertFront(data);
}

void CList::insertAtTheEnd(CSerializable* data){
    nEnd.pPrev->insertFront(data);
}

CSerializable* CList::deleteAtTheStart(){
    return start.deleteNext();
}

CSerializable* CList::deleteAtTheEnd(){
    return nEnd.pPrev->pPrev->deleteNext();
}

bool CList::isEmpty(){
    return start.pNext == &nEnd;
}

bool CList::isFull(){
    return nEnd.pPrev != &start;
}

int CList::sizeOfTheList(){
    CNode* pAux(start.pNext);

    int iCounter(0);

    while(pAux != &nEnd){
        iCounter++;
        pAux = pAux->pNext;
    }
    return iCounter;
}

void CList::sortList(const bool& flag){
    CIterator it1;
    CIterator it2;
    IndicePrimario* auxData;
    it1 = beginList();
    if(!flag){
        while(it1 != endList()){
            auxData = (IndicePrimario*)it1.pCurrent->data;
            it2 = it1;
            while(it2 != beginList() &&
                  auxData->getPrimaryKey() < ((IndicePrimario*)(it2.getPrev()))->getPrimaryKey()){
                it2.pCurrent->data = it2.getPrev();
                --it2;
            }
            if(it1 != it2){
                it2.pCurrent->data = (CSerializable*)auxData;
            }
            ++it1;
        }
    }else{
        while(it1 != endList()){
            auxData = (IndicePrimario*)it1.pCurrent->data;
            it2 = it1;
            while(it2 != beginList() &&
                  auxData->getDireccionBytes() < ((IndicePrimario*)(it2.getPrev()))->getDireccionBytes()){
                it2.pCurrent->data = it2.getPrev();
                --it2;
            }
            if(it1 != it2){
                it2.pCurrent->data = (CSerializable*)auxData;
            }
            ++it1;
        }

    }

}

void CList::print()
{
    CNode* newNode(start.pNext);
    while(newNode != &nEnd){
        std::cout<<((IndicePrimario*)(newNode->data))->getPrimaryKey()<<std::endl;
        newNode = newNode->pNext;
    }
}

void CList::listEmpty(){

    while(start.pNext != &nEnd){
        start.deleteNext();
    }
}

CIterator CList::beginList()const{
    CIterator listIterator;
    listIterator.pCurrent = start.pNext;

    return listIterator;
}

CIterator CList::endList()const{
    CIterator listIterator;
    listIterator.pCurrent = nEnd.pPrev->pNext;

    return listIterator;
}

CIterator CList::findData(CSerializable* data){
    CIterator listIterator;
    listIterator.initialize(beginList());
    CSerializable* auxData;
    auxData = listIterator.pCurrent->data;

    while(listIterator.pCurrent != &nEnd &&
          listIterator.pCurrent->data != data){

          listIterator.advance();

        if(listIterator.pCurrent != &nEnd){
            auxData = listIterator.pCurrent->data;
            listIterator.pCurrent->data = auxData;
        }else{
            listIterator.pCurrent->data = 0;
            break;
        }
    }

    return listIterator;
}

void CList::save(std::fstream& out){
    if(!out.is_open()){
        std::cout<<"No se pudo crear el archivo. CList::Save"<<std::endl;
        return;
    }

    CNode* auxNode(start.pNext);
    while(auxNode != &nEnd){
        auxNode->data->save(out);
        auxNode = auxNode->pNext;
    }
}

void CList::load(std::fstream& in){
    std::string auxStr;
    if(!in.is_open()){
        std::cout<<"No se pudo crear el archivo. CList::load"<<std::endl;
        return;
    }
    getline(in, auxStr);
    if(auxStr == std::to_string(CLSID_PRIMARY_INDEX)){
        while(!in.eof()){
            CSerializable* primaryIndex = new IndicePrimario;
            primaryIndex->load(in);
            insertAtTheEnd(primaryIndex);
        }
    }else if (auxStr == std::to_string(CLSID_SECONDARY_INDEX)){
        while(!in.eof()){
            CSerializable* secondaryIndex = new IndiceSec;
            secondaryIndex->load(in);
            insertAtTheEnd(secondaryIndex);
        }
    }

}

int CList::getCLSID()const{
    return CLSID_LIST;
}




