#ifndef INDICEPRIMARIO_H
#define INDICEPRIMARIO_H

#include <string>

#include "cSerializable.h"

//Herencia de la clase CSerializable para poder serializar el indice primario
class IndicePrimario : public CSerializable{
private:
    std::string primaryKey;
    int direccionBytes;
public:
    IndicePrimario();
    //Metodos implementados en el idniceprimario.cpp
    int getDireccionBytes() const;
    void setDireccionBytes(const int& value);
    std::string getPrimaryKey() const;
    void setPrimaryKey(const std::string &value);
    //Declaracion de metodos heredados
    void save(std::fstream& out);
    void load(std::fstream& in);
    int getCLSID()const;
};

#endif // INDICEPRIMARIO_H
