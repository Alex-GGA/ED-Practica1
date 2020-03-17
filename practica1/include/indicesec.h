#ifndef INDICESEC_H
#define INDICESEC_H
#include "cSerializable.h"
#include <string>
class IndiceSec : public CSerializable
{
private:
   std::string primaryKey;
   std::string referencia[5];
public:
    IndiceSec();
    virtual ~IndiceSec();
    std::string getPrimaryKey() const;
    void setPrimaryKey(const std::string &value);

    std::string getReferencia(const int& pos);

    void setReferenciasInit(const std::string&, const int&);
    void setReferencia(const std::string&,int);

    void sortReferencias();
    void swapReferencias(std::string&, std::string&);

    void save(std::fstream & out);
    void load(std::fstream & in);
    int getCLSID()const;


};

#endif // INDICESEC_H
