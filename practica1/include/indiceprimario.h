#ifndef INDICEPRIMARIO_H
#define INDICEPRIMARIO_H

#include <string>

#include "cSerializable.h"

class IndicePrimario : public CSerializable{
private:
    std::string primaryKey;
    int direccionBytes;
public:
    IndicePrimario();

    int getDireccionBytes() const;
    void setDireccionBytes(const int& value);
    std::string getPrimaryKey() const;
    void setPrimaryKey(const std::string &value);

    void save(std::fstream& out);
    void load(std::fstream& in);
    int getCLSID()const;
};

#endif // INDICEPRIMARIO_H
