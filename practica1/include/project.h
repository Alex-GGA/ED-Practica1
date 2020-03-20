#ifndef PROJECT_H
#define PROJECT_H

#include <iostream>
#include <string>
#include <sstream>

#include "cSerializable.h"

class Project : public CSerializable{

private:
    std::string folio; /*Llave principal con la forma canónica:
                                                -Tres primeras letras del nombre
                                                -guion medio
                                                -Número aleatorío*/
    std::string name;
    std::string area;
    std::string speciality;
    float economicAmount;
    std::string responsible;



public:
    Project();
    Project(const std::string& ss);
    virtual ~Project();

    //Encapsulamiento de datos para evitar anomalias directas en los atributos de cada proyecto
    void setFolio(const std::string&);
    std::string getFolio();
    void setName(const std::string&);
    std::string getName()const;
    void setArea(const std::string&);
    std::string getArea()const;
    void setSpeciality(const std::string&);
    std::string getSpeciality()const;
    void setEconomicAmount(const float&);
    float getEconomicAmount()const;
    void setResponsible(const std::string&);
    std::string getResponsible();

    //Devuelve una cadena con todo y delimitadores
    std::string toFile();
    //Muestra el proyecto
    std::string toString();

    //Sobrecarga de operadores de entrada y salida, para poder hacer cada proyecto flujeable
    void save(std::fstream&out);
    void load(std::fstream&in);
    int getCLSID()const;
};

#endif // PROJECT_H
