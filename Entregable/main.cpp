#include <iostream>
/*
    Primera practica de Estrcuturas de datos 2
    Descricion: Programa que por medio de un menú se permite la carga de "proyectos"
    donde los cuales son ingresados a un archivo de texto, que despues puede ser consultado por medio
    de dos indices, uno donde se muestran los folios de cada proyecto y otro dodne se muestran los proyectos
    por area especificada.

    Programadores:
        -ORTIZ FRANCO CESAR ALEJANDRO
        -RAMÍREZ MIRANDA ALEJANDRO
        -GAYTAN GUTIERREZ ALEJANDRO
        */
#include "mainMenu.h"
using namespace std;


int main(){
    /*El programa se inicia a traves de un objeto creado desde MainMenu*/
    MainMenu main;
    main.menu();

    return 0;
}
