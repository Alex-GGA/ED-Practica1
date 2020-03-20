#include "project.h"
using namespace std;
Project::Project(){
    //ctor
}

//Constructor para poder almacenar en cada campo del proyecto, lo que provenga de un string
Project::Project(const string& ss){
    char FIELD_DELIMITER = '♣';
    stringstream auxSS;
    auxSS << ss;
    string auxStr;

    //Se leen lineas hasta el delimitador y se almacenan en cada campo respectivo desde un stringstream
    getline(auxSS, folio, FIELD_DELIMITER);
    getline(auxSS, name, FIELD_DELIMITER);
    getline(auxSS, area, FIELD_DELIMITER);
    getline(auxSS, speciality, FIELD_DELIMITER);
    getline(auxSS, auxStr, FIELD_DELIMITER);
    economicAmount = stof(auxStr);
    getline(auxSS, responsible, FIELD_DELIMITER);
}

Project::~Project(){
    //dtor
}

//Getters y Setters de cada campo del proyecto
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

//Devuelve una cadena de los datos del proyecto, incluyendo el delimitador
string Project::toFile(){
    string ss;
    char* auxSTR = new char[8];
    //El delimitador pesa 3 bytes
    sprintf(auxSTR, "%0.2f", economicAmount);
    ss = folio + "♣" + name + "♣" + area + "♣"
            + speciality + "♣" +
            auxSTR + "♣" + responsible + "♣";
    return ss;
}

//Imprime el proyecto sacando cada campo
string Project::toString(){
    for(int i(0); i < 2; i++){
        //Elimina la basura generada del delimitador
        folio.pop_back();
        name.pop_back();
        area.pop_back();
        responsible.pop_back();
        speciality.pop_back();
    }
    //Añade estetica a la impresion
    if(folio[0] == '\n'){
        folio[0] = ' ';
    }
    string strProject;
    char* auxSTR = new char[8];
    sprintf(auxSTR, "%0.2f", economicAmount);
    strProject += "Folio: " + folio + "\n"
                + "Nombre: " + name + "\n"
                + "Area: " + area + "\n"
                + "Especialidad: " + speciality + "\n"
                + "Monto Economico: " + auxSTR + "\n"
                + "Responsable: " + responsible + "\n";

    return strProject;
}

void Project::save(std::fstream& out){

    if(!out.is_open()){
        std::cout<<"No fue posible abrir el archivo. Prohject::save()"<<std::endl;
    }
    /*Creando un objeto de la clase Project, se consiguen todos sus atributos
        por medio del getter, para poder ingresarlos al archivo con un fstream,
        añadiendo su delimitador. Esto es logrado gracias a la herencia de la clase CSerializable
    */
    char* auxSTR = new char[8];
    sprintf(auxSTR, "%0.2f", economicAmount);

    out<<getFolio()<< "♣"
          <<getName()<<"♣"
          <<getArea()<<"♣"
          <<getSpeciality()<<"♣"
          <<auxSTR<<"♣"
         <<getResponsible()<<"♣"<<endl;
}

int Project::getCLSID()const{
    return 0;
}

void Project::load(std::fstream& in){

}




