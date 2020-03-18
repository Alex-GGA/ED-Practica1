#ifndef MAINMENU_H
#define MAINMENU_H


#include <iostream>
#include <time.h>
#include <fstream>
#include <sstream>

#include "project.h"
#include "indiceprimario.h"
#include "cList.h"
#include "cIterator.h"
#include "indicesec.h"

#define DEFAULT_POS 0
//Clase principal que cargará y mostrará todos los proyectos que sean añadidos
class MainMenu{

private:
    //Constantes definidas para los archivos usados
    const std::string filePrimaryIndex = "INDICE PRIMARIO.txt";
    const std::string fileSecondaryIndex = "INDICE SECUNDARIO.txt";
    const std::string fileData = "DATOS.txt";
    /* Se crea una estructura del tipo enum, para evitar
        los números mágicos y así poder usar una lista de
        constantes para el menú principal*/
    enum OPT_MAINMENU{
        INSERT_PROJECT = 1,
        SHOW_BY_FOLIO,
        SHOW_BY_AREA,
        EXIT
    };

    /*Nuevamente para evitar numeros magicos, cada opcion de las areas
        sera representada por un elemento de la estructura enum*/
    enum AREAS_MENU{
        AREA_I,
        AREA_II,
        AREA_III,
        AREA_IV,
        AREA_V,
        AREA_VI,
        AREA_VII
    };

    /*Como el método "menu()" será el único que accedera a
        estos métodos (Cada uno pertenece a una opción), es mejor tenerlos privados*/
    void insertNewProject();
    void showProjectsByFolio();
    void showProjectsByArea();
    void readByPrimaryIndex(const CIterator&);

    //Método generador del folio
    std::string Folio(std::string &nombre);

    //Los indices
    CList indicePrimarioL;
    CList indiceSecundario;

    //Contador para saber las posiciones de cada proyecto
    int counter;
    //Guarda cada proyecto en el archivo de "DATOS.TXT"
    void GuardarProyecto(Project &nuevo_proyecto, IndicePrimario &newIndice);

    //Areas del proyecto
    std::string areas[7] = {"AREA I: FISICO MATEMATICAS Y CIENCIAS DE LA TIERRA",
                            "AREA II: BIOLOGIA Y QUIMICA",
                            "AREA III: CIENCIAS MEDICAS Y DE LA SALUD",
                           "AREA IV: HUMANIDADES Y CIENCIA DE LA CONDUCTA",
                           "AREA V: CIENCIAS SOCIALES",
                           "AREA VI: BIOTECNOOGIA Y CIENCIAS AGROPECUARIAS",
                           "AREA VII: INGENIERIAS"};

    void saveIndex();
public:
    MainMenu();
    virtual ~MainMenu();

    void menu();
};

#endif // MAINMENU_H
