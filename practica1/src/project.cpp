#include "project.h"
using namespace std;
Project::Project(){
    //ctor
}

Project::~Project(){
    //dtor
}

void Project::setFolio(const string& auxFolio){
    folio = auxFolio;
}

string Project::getFolio(){
    return folio;
}


void Project::setName(const string& auxName){
    name = auxName;
}

string Project::getName() const{
    return name;
}

void Project::setArea(const string& auxArea){
    area = auxArea;
}

string Project::getArea() const{
    return area;
}

void Project::setSpeciality(const string& auxSpec){
    speciality = auxSpec;
}

string Project::getSpeciality() const{
    return speciality;
}

void Project::setEconomicAmount(const float& auxEcon){
    economicAmount = auxEcon;
}

float Project::getEconomicAmount() const{
    return economicAmount;
}

void Project::setResponsible(const string& auxResp){
    responsible = auxResp;
}

string Project::getResponsible(){
    return responsible;
}

string Project::toFile(){
    string ss;
    ss = folio + "♣" + name + "♣" + area + "♣"
            + speciality + "♣" +
            to_string(economicAmount) + "♣" + responsible + "♣";
    return ss;
}


void Project::save(std::fstream& out){

    if(!out.is_open()){
        std::cout<<"No fue posible abrir el archivo. Prohject::save()"<<std::endl;
    }
    /*Creando un objeto de la clase Project, se consiguen todos sus atributos
        por medio del getter, para poder ingresarlos al archivo con un fstream,
        añadiendo su delimitador. Esto es logrado gracias a la herencia de la clase CSerializable
    */

    out<<getFolio()<< "♣"
          <<getName()<<"♣"
          <<getArea()<<"♣"
          <<getSpeciality()<<"♣"
          <<getEconomicAmount()<<"♣"
         <<getResponsible()<<"♣"<<endl;
}

int Project::getCLSID()const{
    return 0;
}


/*istream& operator >> (istream& input, Project& project){
    Cuando algo sale de un archivo, sale en forma de string, por ello
        se crea auxStr, que recibirá atributo tras atributo, hasta el delimitador.
        Metiendo esos atributos a un objeto de la clase Project
    string auxStr;
    //Se requiere de tener un character auxiliar para almacenar el delimitador, para que el getline lo pueda leer
    const char FIELD_DELIMITER = '♣';

    getline(input, auxStr, FIELD_DELIMITER);
    if(auxStr.size() > 0){
        project.setFolio(auxStr);
        getline(input, auxStr, FIELD_DELIMITER);
        project.setName(auxStr);
        getline(input, auxStr, FIELD_DELIMITER);
        project.setArea(auxStr);
        getline(input, auxStr, FIELD_DELIMITER);
        project.setSpeciality(auxStr);
        getline(input, auxStr, FIELD_DELIMITER);
        project.setEconomicAmount(stof(auxStr)); //Convertir a flotante antes de pasarlo
        getline(input, auxStr, FIELD_DELIMITER);
        project.setResponsible(auxStr);
    }
    return input;
}*/
void Project::load(std::fstream& in){

}



