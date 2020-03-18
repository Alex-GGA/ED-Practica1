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

void IndiceSec::setReferenciasInit(const std::string &data, const int& pos){
    referencia[pos] = data;
}

void IndiceSec::setReferencia(const std::string &data, int pos){
    for(int i(0); i < 5; i++){
        if(referencia[pos] == "0"){
            referencia[pos] = data;
            break;
        }
        pos++;
    }
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

int IndiceSec::getCLSID() const{
    return CLSID_SECONDARY_INDEX;
}

void IndiceSec::sortReferencias(){
    int i(4), j;
    bool flag;
    do{
        flag = false;
        j = 0;

        while(j < i){
            if (referencia[j] > referencia[j+1]){

                //Intercambiar
                referencia[j].swap(referencia[j+1]);
                flag = true;
            }
            j++;
        }
        i--;
    }while(flag);

    i = 4;
    std::string auxStr;
    do{
        flag = false;
        j = 0;

        while(j < i){
            if (referencia[j] == "0"){
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

void IndiceSec::swapReferencias(std::string& r1, std::string& r2){
    std::string auxR;
    auxR = r1;
    r1 = r2;
    r2 = auxR;
}



IndiceSec::IndiceSec(){

}

IndiceSec::~IndiceSec(){

}
