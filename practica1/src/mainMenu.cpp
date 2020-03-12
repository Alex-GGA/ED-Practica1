#include "mainMenu.h"
using namespace std;

MainMenu::MainMenu() : counter(0) {

    fstream input(filePrimaryIndex, fstream::in);
    indicePrimarioL.load(input);
    input.close();
    fstream input2(fileSecondaryIndex, fstream::in);
    indiceSecundario.load(input2);
    CSerializable* aux;
    aux = indicePrimarioL.deleteAtTheEnd();
    aux = indiceSecundario.deleteAtTheEnd();
    input2.close();
    if(indiceSecundario.isEmpty()){
        for(int i(0); i < 7; i++){
            IndiceSec* auxIndice = new IndiceSec;
            auxIndice->setPrimaryKey(areas[i]);
            for(int j(0); j < 5; j++){
                auxIndice->setReferencia("0", j);
            }
            indiceSecundario.insertAtTheEnd(auxIndice);
        }
    }


    for(CIterator primaryIndexIt = indicePrimarioL.beginList();
        primaryIndexIt != indicePrimarioL.endList();
        ++primaryIndexIt){
            counter += ((IndicePrimario*)(primaryIndexIt.readContent()))->getDireccionBytes();
        }

    delete aux;
}

MainMenu::~MainMenu(){

    fstream archivoIndiceP(filePrimaryIndex, fstream::out);
    archivoIndiceP << CLSID_PRIMARY_INDEX<<endl;
    indicePrimarioL.save(archivoIndiceP);
    archivoIndiceP.close();

    fstream fSecondaryIndex(fileSecondaryIndex, fstream::out);
    fSecondaryIndex << CLSID_SECONDARY_INDEX<<endl;
    indiceSecundario.save(fSecondaryIndex);
    fSecondaryIndex.close();
}

void MainMenu::menu(){
    //system("clear||cls");
    int option;
    do{
        cout<<"----MENU PRINCIPAL----"<<endl
            <<INSERT_PROJECT<<") Insertar proyecto"<<endl
            <<SHOW_BY_FOLIO<<") Mostrar por folio"<<endl
            <<SHOW_BY_AREA<<") Mostrar por area"<<endl
            <<EXIT<<") Salir"<<endl
            <<"---> ";
        cin >> option;

        switch(option){
        case INSERT_PROJECT:
            insertNewProject();
            break;
        case SHOW_BY_FOLIO:
            showProjectsByFolio();
            break;
        case SHOW_BY_AREA:
            showProjectsByArea();
            break;
        case EXIT:
            cout<<"Saliendo..."<<endl<<endl;
            break;
        default:
            cout<<"Opcion errada, favor de elegir una de las mostradas en el menu"<<endl;
        }

    }while(option != EXIT);
}

void MainMenu::insertNewProject(){
    system("cls");
    std::string auxStr;
    float auxFloat;
    stringstream ss;
    int opcion;
    cout<<"---AGREGAR UN NUEVO PROYECTO---"<<endl;

    Project newProject;
    IndicePrimario* newIndice = new IndicePrimario;

    cin.ignore();
    cout<<" Nombre del proyecto: ";
    getline(cin, auxStr);
    newProject.setName(auxStr);
    newProject.setFolio(Folio(auxStr));
    cout << " Folio generado: " << newProject.getFolio() << endl;
    cout<<"--AREAS--"<<endl;
    cout <<AREA_I<<") AREA I: FISICO MATEMATICAS Y CIENCIAS DE LA TIERRA." <<endl
         <<AREA_II<<") AREA II: BIOLOGIA Y QUIMICA." <<endl
         <<AREA_III<<") AREA III: CIENCIAS MEDICAS Y DE LA SALUD." <<endl
         <<AREA_IV<<") AREA IV: HUMANIDADES Y CIENCIA DE LA CONDUCTA" <<endl
         <<AREA_V<<") AREA V: CIENCIAS SOCIALES." <<endl
         <<AREA_VI<<") AREA VI: BIOTECNOLOGIAS Y CIENCIAS AGROPECUARIAS." <<endl
         <<AREA_VII<<") AREA VII: INGENIERIAS" <<endl
         <<"  Opcion: ";
    cin >> opcion;
    newProject.setArea(areas[opcion]);


    cin.ignore();
    cout << " Especialidad: ";
    getline(cin,auxStr);
    newProject.setSpeciality(auxStr);
    cout << " Monto economico: ";
    cin >> auxFloat;
    cin.ignore();
    newProject.setEconomicAmount(auxFloat);
    cout << " Responsable: ";
    getline(cin,auxStr);
    newProject.setResponsible(auxStr);
    newIndice->setPrimaryKey(newProject.getFolio());
    if(indicePrimarioL.isEmpty()){
        newIndice->setDireccionBytes(0);
        counter += newProject.toFile().length();
    }else{
        newIndice->setDireccionBytes(counter);
        counter += newProject.toFile().length();
    }

    indicePrimarioL.insertAtTheStart(newIndice);
    indicePrimarioL.sortList(false);
    GuardarProyecto(newProject,*newIndice);

    /*LLenar el indice secundario por medio de iteradores que iteren sobre
     el indice primario, para poder ir asignando los folios en sus respectivas areas
     de manera ordenada*/
    //int auxCont;
    /*for(CIterator indSecIt = indiceSecundario.beginList();
        indSecIt != indicePrimarioL.endList();
        ++indSecIt){
        auxCont = 0;
        for (CIterator indPrimIt = indicePrimarioL.beginList();
             indPrimIt != indicePrimarioL.endList();
             ++indPrimIt) {
            if(((IndiceSec*)(indSecIt.readContent()))->getPrimaryKey()
                    == ((IndicePrimario*)(indPrimIt.readContent()))->get)
        }
    }*/
}

void MainMenu::showProjectsByFolio(){
    for(CIterator it = indicePrimarioL.beginList();it != indicePrimarioL.endList();++it){
        cout<<((IndicePrimario*)(it.readContent()))->getPrimaryKey()<< " - " <<
              ((IndicePrimario*)(it.readContent()))->getDireccionBytes() << endl;
    }
}

void MainMenu::showProjectsByArea(){
    for(CIterator it = indiceSecundario.beginList(); it != indiceSecundario.endList();++it){
        cout<<((IndiceSec*)(it.readContent()))->getPrimaryKey()<<endl;
    }
}

string MainMenu::Folio(string &nombre)
{
    stringstream folio_generado;
    srand(time(NULL));
    int num1 = rand()%100;
    for (int i = 0; i <= 2; i++){
        folio_generado << nombre[i];
    }
    folio_generado << '-' << num1;
    return folio_generado.str();
}

void MainMenu::GuardarProyecto(Project &nuevo_proyecto,IndicePrimario &newIndice)
{
    fstream archivo_proyecto(fileData,fstream::app);
    nuevo_proyecto.save(archivo_proyecto);
    archivo_proyecto.close();
}


