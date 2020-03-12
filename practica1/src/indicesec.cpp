#include "indicesec.h"

std::string IndiceSec::getPrimaryKey() const
{
    return primaryKey;
}

void IndiceSec::setPrimaryKey(const std::string &value)
{
    primaryKey = value;
}

std::string IndiceSec::getReferencia(const int & pos){
    return referencia[pos];
}

void IndiceSec::setReferencia(const std::string &data, const int &pos){
    referencia[pos] = data;
}

void IndiceSec::save(std::fstream &out){
    if(!out.is_open()){
        std::cout<<"No se pudo crear el archivo. IndiceSec::save"<<std::endl;
        return;
    }

    out << primaryKey<<"|";
    for(int i(0); i < 5; i++){
        out<<referencia[i]<<"|";
    }
    out<<std::endl;
}

void IndiceSec::load(std::fstream &in){
    std::string auxStr;
    if(!in.is_open()){
        std::cout<<"No se pudo crear el archivo. IndiceSec::load"<<std::endl;
        return;
    }
    getline(in, auxStr, '|');
    if(auxStr.size() > 0){
        primaryKey = auxStr;
        for(int i(0); i < 5; i++){
            getline(in, auxStr, '|');
            referencia[i] = auxStr;
        }
        getline(in, auxStr);
    }
}

int IndiceSec::getCLSID() const
{
    return CLSID_SECONDARY_INDEX;
}

IndiceSec::IndiceSec(){

}

IndiceSec::~IndiceSec()
{

}
