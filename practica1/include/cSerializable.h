#ifndef CSERIALIZABLE_H
#define CSERIALIZABLE_H

#include <fstream>
#include <iostream>
#include <sstream>

#define CLSID_PRIMARY_INDEX 420
#define CLSID_SECONDARY_INDEX 840

class CSerializable{
private:
public:
    CSerializable();
    virtual ~CSerializable();

    virtual void save(std::fstream & out) = 0;

    virtual void load(std::fstream & in) = 0;

    virtual int getCLSID()const = 0;
};

#endif // CSERIALIZABLE_H
