#include "indiceprimario.h"

//Getter de la direccion
int IndicePrimario::getDireccionBytes() const{
    return direccionBytes;
}
//Setter de la direccion
void IndicePrimario::setDireccionBytes(const int& value){
    direccionBytes = value;
}
//Getter de la llave primaria
std::string IndicePrimario::getPrimaryKey() const{
    return primaryKey;
}

//Setter de la llave primaria
void IndicePrimario::setPrimaryKey(const std::string &value){
    primaryKey = value;
}

//Guarda los elementos del indice primario
void IndicePrimario::save(std::fstream &out){
    if(!out.is_open()){
        std::cout<<"No se pudo crear el archivo. IndicePrimario::Save"<<std::endl;
        return;
    }
    //Almacena la llave primaria, seguida de un delimitador y la direccion en bytes
    out << primaryKey;
    out << "♣";
    out << direccionBytes<<std::endl;
}

//Carda desde el archivo, el indice primario
void IndicePrimario::load(std::fstream &in){
    std::string auxString;
    if(!in.is_open()){
        std::cout<<"No se pudo crear el archivo. IndicePrimario::load"<<std::endl;
        return;
    }
    //Caracter auxiliar para almacenar el delimitador
    char auxChar('♣');
    //Por cada linea, se lee hasta el delimitador y se almacena en una cadena auxliar
    getline(in, auxString, auxChar);
    if(auxString.size() > 0){
        //Se elimina los datos basura que deja el delimitador
        auxString.pop_back();
        auxString.pop_back();
        //almacena la cadena auxiliar en la llave primaria
        primaryKey = auxString;
        //Lee lo que resta de la linea y se almacena en la direccion en bytes
        getline(in, auxString);
        direccionBytes = stoi(auxString); //Convierte la cadena a flotante
    }
}

int IndicePrimario::getCLSID() const{
    return CLSID_PRIMARY_INDEX;
}

IndicePrimario::IndicePrimario(){

}
