#include "cList.h"
///Implementation of the list

CList::CList(){
    //Usa doble encabezado y mete la lista entre el inicio y el fin
    start.pNext = &nEnd;
    nEnd.pPrev = &start;
    start.pPrev = nullptr;
    nEnd.pNext = nullptr;
}

CList::~CList(){
    listEmpty();
}

//Manda a llamar el metodo del nodo para insertar
void CList::insertAtTheStart(CSerializable* data){
    start.insertFront(data);
}
//Manda a llamar el metodo del nodo apra insertar al final
void CList::insertAtTheEnd(CSerializable* data){
    nEnd.pPrev->insertFront(data);
}
//Manda a llamar el metodo del nodo para eliminar el inicio
CSerializable* CList::deleteAtTheStart(){
    return start.deleteNext();
}

//Manda a llamar el metodo del nodo para eliminar al final
CSerializable* CList::deleteAtTheEnd(){
    return nEnd.pPrev->pPrev->deleteNext();
}

//Verifica que la lista este vacia, preguntadno si el siguiente dle inicio es el final de la lista
bool CList::isEmpty(){
    return start.pNext == &nEnd;
}
//Verifica que este llena, sabiendoq ue existe algo antes del final de la lista
bool CList::isFull(){
    return nEnd.pPrev != &start;
}
//Devulve el tamaño de la lista
int CList::sizeOfTheList(){
    CNode* pAux(start.pNext);

    int iCounter(0);
    //Recorre todos los nodos y va aumentando el contador
    while(pAux != &nEnd){
        iCounter++;
        pAux = pAux->pNext;
    }
    return iCounter;
}

//Ordena la lista por medio del método de inserción
void CList::sortList(){
    //Iteradores para recorrer la lista
    CIterator it1;
    CIterator it2;
    //Dato auxiliar para poder hacer el ordenamiento
    IndicePrimario* auxData;

    //Inicia el iterador
    it1 = beginList();

    while(it1 != endList()){
        //En el dato auxiliar se recupera lo que haya en el primer iterador
        auxData = (IndicePrimario*)it1.pCurrent->data;
        it2 = it1;
        /*Verifica y recorre la lista con el segundo iterador hasta que sea el final y el la llave
        primaria del dato auxiliar sea menor que la llave primaria del segundo iterador*/
        while(it2 != beginList() &&
              auxData->getPrimaryKey() < ((IndicePrimario*)(it2.getPrev()))->getPrimaryKey()){

            //Captura en el dato del iterador 2 el dato de su anterior
            it2.pCurrent->data = it2.getPrev();
            //Decrementa el segundo iterador
            --it2;
        }
        //Verifica que ambos iteradores sean diferentes
        if(it1 != it2){
            //Cambia el dato del iterador 2 al dato auxiliar
            it2.pCurrent->data = (CSerializable*)auxData;
        }
        //Incrementa el priemr iterador
        ++it1;
    }

}

void CList::print(){
    //Recorre nodo a nodo, para imrpimir la lista y obtener todas las llaves primarias
    CNode* newNode(start.pNext);
    while(newNode != &nEnd){
        std::cout<<((IndicePrimario*)(newNode->data))->getPrimaryKey()<<std::endl;
        newNode = newNode->pNext;
    }
}

//Vacia la lista
void CList::listEmpty(){
    //Borra nodo con nodo hasta dejar los encabezados
    while(start.pNext != &nEnd){
        start.deleteNext();
    }
}

//Vrifica el inicio de la lista para establecerlo en un iterador
CIterator CList::beginList()const{
    CIterator listIterator;
    listIterator.pCurrent = start.pNext;

    return listIterator;
}

//Vrifica el fin de la lista (Hasta la cabecera final) para establecerlo al iterador
CIterator CList::endList()const{
    CIterator listIterator;
    listIterator.pCurrent = nEnd.pPrev->pNext;

    return listIterator;
}

//Serializa la lista usando el metodo heredado de la interfaz
void CList::save(std::fstream& out){
    ///Verifica que el archivo sí se haya abierto
    if(!out.is_open()){
        std::cout<<"No se pudo crear el archivo. CList::Save"<<std::endl;
        return;
    }
    //Usando un nodo, saca cada dato y manda a llamar su metodo apra poder guardar a un archivo
    CNode* auxNode(start.pNext);
    while(auxNode != &nEnd){
        auxNode->data->save(out);
        auxNode = auxNode->pNext;
    }
}

//Recupera la lista de un archivo en base al tipo de lista que se guardo
void CList::load(std::fstream& in){
    std::string auxStr;
    if(!in.is_open()){
        std::cout<<"No se pudo crear el archivo. CList::load"<<std::endl;
        return;
    }
    //Recupera el ID de uno de los archivos para posteriormente compararlo
    getline(in, auxStr);
    /*Si es el ID de la lista de tipo indice primario, buscará desde el archivo INDICE PRIAMRIO.TXT*/
    if(auxStr == std::to_string(CLSID_PRIMARY_INDEX)){
        while(!in.eof()){
            //Crea un puntero a objeto de tipo CSerializable, pero como IndicePriamrio
            CSerializable* primaryIndex = new IndicePrimario;
            //Manda a llamar su metodo heredado para cargar desde el archivo
            primaryIndex->load(in);
            insertAtTheEnd(primaryIndex);
        }
    //Si el ID es del indice secundario, se meterá al archivo INDICE SECUNDARIO.txt
    }else if (auxStr == std::to_string(CLSID_SECONDARY_INDEX)){
        while(!in.eof()){
            //Crea un puntero a objeto de tipo CSerializable, pero como IndiceSec
            CSerializable* secondaryIndex = new IndiceSec;
            //Manda a llamar su metodo heredado para cargar desde el archivo
            secondaryIndex->load(in);
            insertAtTheEnd(secondaryIndex);
        }
    }

}

int CList::getCLSID()const{
    return CLSID_LIST;
}




