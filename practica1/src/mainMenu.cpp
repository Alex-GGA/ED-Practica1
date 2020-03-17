#include "mainMenu.h"
using namespace std;

MainMenu::MainMenu() : counter(0) {
    /*Carga desde los dos archivos todo lo referente a ambos indices*/
    fstream input(filePrimaryIndex, fstream::in);
    indicePrimarioL.load(input);
    input.close();

    fstream input2(fileSecondaryIndex, fstream::in);
    indiceSecundario.load(input2);
    CSerializable* aux;
    input2.close();
    if(!indicePrimarioL.isEmpty() && !indiceSecundario.isEmpty()){
        /*En caso de que los indices esten vacios, no podra eliminar el registro "basura"
        que es generado, esto se hace para evitar que el programa busque una posicion invalida*/
        aux = indicePrimarioL.deleteAtTheEnd();
        aux = indiceSecundario.deleteAtTheEnd();
        delete aux;
    }
    /*Esto solo ocurre al inicio del programa, ya que necesita verificar si el archivo de indice
     secundario esta creado o no, en caso de que no esté creado, se llena el indice secundario
     con las areas especificadas y con los cinco campos en "0" para dejar disponibles anuevas inserciones*/
    if(indiceSecundario.isEmpty()){
        for(int i(0); i < 7; i++){
            IndiceSec* auxIndice = new IndiceSec;
            auxIndice->setPrimaryKey(areas[i]);
            for(int j(0); j < 5; j++){
                auxIndice->setReferenciasInit("0", j);
            }
            indiceSecundario.insertAtTheEnd(auxIndice);
        }
    }
    /*El contador ira en aumento, dando un recorrido por eel indice primario para poder conseguir
        la ultima posicion del archivo*/
    for(CIterator primaryIndexIt = indicePrimarioL.beginList();
        primaryIndexIt != indicePrimarioL.endList();
        ++primaryIndexIt){
            counter += ((IndicePrimario*)(primaryIndexIt.readContent()))->getDireccionBytes();
        }
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
    system("clear||cls");
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
        counter += newProject.toFile().size()-6;
    }else{
        newIndice->setDireccionBytes(counter);
        counter += newProject.toFile().size()-6;
    }

    for (CIterator indSecIt = indiceSecundario.beginList();
        indSecIt != indiceSecundario.endList();
        ++indSecIt){
        if(((IndiceSec*)(indSecIt.readContent()))->getPrimaryKey() == areas[opcion]){
            ((IndiceSec*)(indSecIt.readContent()))->setReferencia(newProject.getFolio(), DEFAULT_POS);
            ((IndiceSec*)(indSecIt.readContent()))->sortReferencias();
        }
    }

    indicePrimarioL.insertAtTheStart(newIndice);
    indicePrimarioL.sortList(false);
    GuardarProyecto(newProject,*newIndice);

}

void MainMenu::showProjectsByFolio(){
    int i(1), option;
    CIterator it;
    for(it = indicePrimarioL.beginList(); it != indicePrimarioL.endList(); ++it, ++i){
        cout<<i<<") "<<((IndicePrimario*)(it.readContent()))->getPrimaryKey()<< endl;
    }
    cout<<"--> ";
    cin>> option;
    it = indicePrimarioL.beginList();
    for(int j(1); j < option; ++j){
        ++it;
    }

    readByPrimaryIndex(it);

}

void MainMenu::showProjectsByArea(){
    int i(1), option;
    CIterator it;
    for(it = indiceSecundario.beginList(); it != indiceSecundario.endList();++it, ++i){
        cout<<i<<") "<<((IndiceSec*)(it.readContent()))->getPrimaryKey()<<endl;
    }
    cout<<"--> ";
    cin >> option;

    it = indiceSecundario.beginList();
    for(int j(1); j < option; ++j){
        ++it;
    }

    for(int k(0); k < 5; k++){

        for(CIterator it2 = indicePrimarioL.beginList(); it2 != indicePrimarioL.endList();++it2){
            if(((IndiceSec*)(it.readContent()))->getReferencia(k)
               == ((IndicePrimario*)(it2.readContent()))->getPrimaryKey()){
                    readByPrimaryIndex(it2);
            }
        }
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

void MainMenu::readByPrimaryIndex(const CIterator& auxIt){
    fstream lecturaIndice;
    CIterator it;
    it = auxIt;
    int pesoBytes(0);
    lecturaIndice.open(fileData);

    if(it.getNext() == indicePrimarioL.endList().readContent()){
        pesoBytes = counter - ((IndicePrimario*)(it.readContent()))->getDireccionBytes();

    }else{
        pesoBytes = ((IndicePrimario*)(it.getNext()))->getDireccionBytes()
                        - ((IndicePrimario*)(it.readContent()))->getDireccionBytes();
    }


    char* auxStr =  new char[pesoBytes];
    string auxStr2;
    lecturaIndice.seekp(((IndicePrimario*)(it.readContent()))->getDireccionBytes()+1);
    lecturaIndice.read(auxStr, pesoBytes);
    auxStr2 = auxStr;
    Project auxProject(auxStr2);

    auxProject.print();

    lecturaIndice.close();
}



