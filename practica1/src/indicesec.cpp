#include "indicesec.h"

//Implementacion de los Getters y Setters
std::string IndiceSec::getPrimaryKey() const{
    return primaryKey;
}

void IndiceSec::setPrimaryKey(const std::string &value){
    primaryKey = value;
}

std::string IndiceSec::getReferencia(const int & pos){
    return referencia[pos];
}

//Establece las referencias caundo inicia el programa (Sin un archivo generado)
void IndiceSec::setReferenciasInit(const std::string &data, const int& pos){
    referencia[pos] = data;
}

//Establece las referencias y va verificando que cada lugar disponible sea un "0"
void IndiceSec::setReferencia(const std::string &data, int pos){
    for(int i(0); i < 5; i++){
        if(referencia[pos] == "0"){
            referencia[pos] = data;
            break;
        }
        pos++;
    }
}

//Guarda al archivo los datos del indice secundario
void IndiceSec::save(std::fstream &out){
    if(!out.is_open()){
        std::cout<<"No se pudo crear el archivo. IndiceSec::save"<<std::endl;
        return;
    }
    //Almacena la llave primaria, seguida del delimitador
    out << primaryKey<<"♣";
    //Almacena referencia por referencia, seguido del delimitador
    for(int i(0); i < 5; i++){
        out<<referencia[i]<<"♣";
    }
    out<<std::endl;
}

//Carga los datos desde el archivo INDICE SECUNDARIO.txt
void IndiceSec::load(std::fstream &in){
    std::string auxStr;
    if(!in.is_open()){
        std::cout<<"No se pudo crear el archivo. IndiceSec::load"<<std::endl;
        return;
    }
    char auxChar('♣'); //Caracter auxiliar para almacenar el delimitador
    getline(in, auxStr, auxChar);
    //Se lee cada linea ahsta el delimitador, para ir almacenando en la llave primaria y despues en las referencias
    if(auxStr.size() > 0){
        auxStr.pop_back();
        auxStr.pop_back();
        //Se eliminan la basura que genera el delimitador
        primaryKey = auxStr;
        for(int i(0); i < 5; i++){
            getline(in, auxStr, auxChar);
            auxStr.pop_back();
            auxStr.pop_back();
            referencia[i] = auxStr;
        }
        getline(in, auxStr);
    }
}

int IndiceSec::getCLSID() const{
    return CLSID_SECONDARY_INDEX;
}

//Ordena las referencias por medio de un boobleSort mejorado
void IndiceSec::sortReferencias(){
    int i(4), j;
    bool flag;
    do{
        flag = false;
        j = 0;

        while(j < i){
            if (referencia[j] > referencia[j+1]){ //Criterio de ordenamiento, para acomodar de manera ascendente

                //Intercambiar
                referencia[j].swap(referencia[j+1]);
                flag = true; //El uso de la bandera es para verificar si seguir ordenando o no
            }
            j++;
        }
        i--;
    }while(flag);

    i = 4;
    std::string auxStr;
    //Vuelve a realizar un ordenamiento en burbuja para mandar los "0" hasta el final
    do{
        flag = false;
        j = 0;

        while(j < i){
            if (referencia[j] == "0"){ //El critero cambia  y ahora compara que sea igual a "0"
                auxStr = referencia[j];
                referencia[j] = referencia[j+1];
                referencia[j+1] = auxStr;
                flag = true;
            }
            j++;
        }
        i--;
    }while(flag);
}

IndiceSec::IndiceSec(){

}

IndiceSec::~IndiceSec(){

}
