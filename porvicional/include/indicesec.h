#ifndef INDICESEC_H
#define INDICESEC_H
#include "cSerializable.h"
#include <string>
//Herencia de la clase CSerializable para poder serializar el indice secundario
class IndiceSec : public CSerializable{
private:
   std::string primaryKey;
   std::string referencia[5]; //Referencias limitadas a solo 5

public:
    IndiceSec();
    virtual ~IndiceSec();
    //Getters y Setters de la llave primaria y las referencias
    std::string getPrimaryKey() const;
    void setPrimaryKey(const std::string &value);
    std::string getReferencia(const int& pos);
    /*Dos maneras para insertar las referencias, una cuando el
    programa recien abre y no hay un archivo y otra cuando se inserta un nuevo proyecto*/
    void setReferenciasInit(const std::string&, const int&);
    void setReferencia(const std::string&,int);

    //Metodos implementados en indicesec.cpp
    void sortReferencias();

    void save(std::fstream & out);
    void load(std::fstream & in);
    int getCLSID()const;


};

#endif // INDICESEC_H
