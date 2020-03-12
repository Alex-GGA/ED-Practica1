#include "indiceprimario.h"

int IndicePrimario::getDireccionBytes() const{
    return direccionBytes;
}

void IndicePrimario::setDireccionBytes(const int& value){
    direccionBytes = value;
}

std::string IndicePrimario::getPrimaryKey() const{
    return primaryKey;
}

void IndicePrimario::setPrimaryKey(const std::string &value){
    primaryKey = value;
}

void IndicePrimario::save(std::fstream &out){
    if(!out.is_open()){
        std::cout<<"No se pudo crear el archivo. IndicePrimario::Save"<<std::endl;
        return;
    }

    out << primaryKey;
    out << "|";
    out << direccionBytes<<std::endl;
}

void IndicePrimario::load(std::fstream &in){
    std::string auxString;
    if(!in.is_open()){
        std::cout<<"No se pudo crear el archivo. IndicePrimario::load"<<std::endl;
        return;
    }
    getline(in, auxString, '|');
    if(auxString.size() > 0){
        primaryKey = auxString;
        getline(in, auxString);
        direccionBytes = stoi(auxString);
    }
}

int IndicePrimario::getCLSID() const
{
    return CLSID_PRIMARY_INDEX;
}

IndicePrimario::IndicePrimario(){

}
