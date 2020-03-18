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
        counter -= ((IndicePrimario*)(aux))->getDireccionBytes();
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
    //Ordenamiento final, solo para asegurar de que guardara el archivo ordenado con forme a la llave primaria
    indicePrimarioL.sortList(false);
    //Guarda en el archivo el indice primario
    fstream archivoIndiceP(filePrimaryIndex, fstream::out);
    //Identificador para indicarle a la lista que al momento de cargar, cargara un indice primario
    archivoIndiceP << CLSID_PRIMARY_INDEX<<endl;
    //manda a llamar su propio metodo para guardar
    indicePrimarioL.save(archivoIndiceP);
    archivoIndiceP.close();
    //Guarda en su respectivo archivo, el indice secundario
    fstream fSecondaryIndex(fileSecondaryIndex, fstream::out);
    //Identificador para indicarle a la lista que al momento de cargar, cargara un indice secundario
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
        system("pause");
        system("clear||cls");
    }while(option != EXIT);
}

void MainMenu::insertNewProject(){
    system("cls");

    //Variables auxiliares para agregar nuevos proyectos y establecerles un dato a cada campo
    std::string auxStr;
    float auxFloat;

    int opcion;
    cout<<"---AGREGAR UN NUEVO PROYECTO---"<<endl;

    Project newProject;
    //Puntero a objeto de la clase IndicePrimario para agregarlo a la lista que contiene ese indice
    IndicePrimario* newIndice = new IndicePrimario;

    cin.ignore();
    cout<<" Nombre del proyecto: ";
    getline(cin, auxStr);
    newProject.setName(auxStr); //Se le agrega el nombre al proyecto

    newProject.setFolio(Folio(auxStr)); //Mnada a llamar el metodo Folio para establecer el folio al proyecto
    cout << " Folio generado: " << newProject.getFolio() << endl<<endl;

    cout<<"\t\t\t--AREAS--"<<endl;
    cout <<AREA_I<<") AREA I: FISICO MATEMATICAS Y CIENCIAS DE LA TIERRA." <<endl
         <<AREA_II<<") AREA II: BIOLOGIA Y QUIMICA." <<endl
         <<AREA_III<<") AREA III: CIENCIAS MEDICAS Y DE LA SALUD." <<endl
         <<AREA_IV<<") AREA IV: HUMANIDADES Y CIENCIA DE LA CONDUCTA" <<endl
         <<AREA_V<<") AREA V: CIENCIAS SOCIALES." <<endl
         <<AREA_VI<<") AREA VI: BIOTECNOLOGIAS Y CIENCIAS AGROPECUARIAS." <<endl
         <<AREA_VII<<") AREA VII: INGENIERIAS" <<endl
         <<"  Opcion: ";
    cin >> opcion;
    if(opcion < 0 || opcion > 6){
        cout<<"Area invalida..."<<endl
            <<"SE ESTABLECERA EL AREA VII"<<endl;
        newProject.setArea(areas[6]);
    }else{
        newProject.setArea(areas[opcion]); //Accede a un elemento del arreglo areas y lo establece
    }
    cin.ignore();

    cout <<endl<< " Especialidad: ";
    getline(cin,auxStr);
    newProject.setSpeciality(auxStr);

    cout <<endl<< " Monto economico: ";
    cin >> auxFloat;
    cin.ignore();
    newProject.setEconomicAmount(auxFloat);

    cout <<endl<< " Responsable: ";
    getline(cin,auxStr);
    newProject.setResponsible(auxStr);

    newIndice->setPrimaryKey(newProject.getFolio()); //Captura el folio del proyecto y lo añade al indice primario

    //En caso de que este vacia la lista, se establece la direccion de 0 y el contador aumenta en razon a la longitud
    if(indicePrimarioL.isEmpty()){
        newIndice->setDireccionBytes(0);
        //Longitud sacada del proyecto incluyendo el delimitador, restando 6 bytes por el peso extra del delimitador
        counter += newProject.toFile().size()-6;
    }else{
        //Se establece el contador desde la ultima posicion
        newIndice->setDireccionBytes(counter);
        counter += newProject.toFile().size()-6;
    }

    //Recorrido para ingresar al indice secundario
    for (CIterator indSecIt = indiceSecundario.beginList();
        indSecIt != indiceSecundario.endList();
        ++indSecIt){
        /*Vrifica en cada elemento del indice secundario, si su llave
        priamaria es igual al area seleccionada del proyecto, se agrega el folio en uno d elos campos referencia*/
        if(((IndiceSec*)(indSecIt.readContent()))->getPrimaryKey() == areas[opcion]){

            ((IndiceSec*)(indSecIt.readContent()))->setReferencia(newProject.getFolio(), DEFAULT_POS);
        //Ordena las referencias del indice secundario, pero solo de la posicion actual.
            ((IndiceSec*)(indSecIt.readContent()))->sortReferencias();
        }
    }
    //Agrega el objeto de tipo IndicePrimario a la lista
    indicePrimarioL.insertAtTheStart(newIndice);
    //Ordenara la lista de manera descendente con forme a las llaves primarias
    indicePrimarioL.sortList(false);
    //Metodo que guarda el proyecto al archivo
    GuardarProyecto(newProject,*newIndice);
    cout<<endl<<endl<<"Nuevo proyecto agregado con exito :)"<<endl;

}

void MainMenu::showProjectsByFolio(){
    system("clear||cls");

    int i(1), option;
    CIterator it;

    cout<<"---INDICE PRIMARIO---"<<endl;
    //Usando in iterador, se recorre la lista del indice primario y muestra todas las llaves primarias
    for(it = indicePrimarioL.beginList(); it != indicePrimarioL.endList(); ++it, ++i){
        cout<<i<<") "<<((IndicePrimario*)(it.readContent()))->getPrimaryKey()<< endl;
    }
    cout<<"--> ";
    cin>> option;

    //Mueve el iterado de inicio hasta la opcion seleccionada
    it = indicePrimarioL.beginList();
    for(int j(1); j < option; ++j){
        ++it;
    }
    //Valida que la opcion sea una de las mostradas
    if(option < 0 || option >= i){
        cout<<"Proyecto no encontrado..."<<endl;
    }else{
        cout<<endl<<"Proyecto encontrado: ";
        cout<<endl<<endl;
        //Método que muestra el proyecto que se haya encontrado
        readByPrimaryIndex(it);
        cout<<endl<<endl;
    }

}

void MainMenu::showProjectsByArea(){
    system("clear||cls");
    int i(1), option;
    CIterator it;

    cout<<"\t\t---INDICE SECUNDARIO---"<<endl;
    //Por medio de un iterador muestra las llaves primarias del indice secundario
    for(it = indiceSecundario.beginList(); it != indiceSecundario.endList();++it, ++i){
        cout<<i<<") "<<((IndiceSec*)(it.readContent()))->getPrimaryKey()<<endl;
    }
    cout<<"--> ";
    cin >> option;
    cout<<endl<<endl;

    //Valida que la opcion sea una de las mostradas
    if(option < 0 || option >= i){
        cout<<"Proyecto no encontrado..."<<endl;
    }else{
        cout<<"Proyectos del: "<<areas[option-1]<<": "<<endl<<endl;
        //Coloca el iterador en la opcion
        it = indiceSecundario.beginList();
        for(int j(1); j < option; ++j){
            ++it;
        }
        //Se mueve por todas las refencias de la opcions eleccionada
        for(int k(0); k < 5; k++){
            //De cada referencia saca un proyecto, conectando el indice secundario con el indice primario
            for(CIterator it2 = indicePrimarioL.beginList(); it2 != indicePrimarioL.endList();++it2){
                //En caso de encontrar, saca un proyecto
                if(((IndiceSec*)(it.readContent()))->getReferencia(k)
                   == ((IndicePrimario*)(it2.readContent()))->getPrimaryKey()){
                        cout<<"Proyecto No. "<<k+1<<endl;
                        readByPrimaryIndex(it2);
                        cout<<endl;
                }
            }
        }
    }
}

string MainMenu::Folio(string &nombre){
    stringstream folio_generado;
    srand(time(NULL));
    int num1 = rand()%100; //Genera un numero aleatorio de 0 - 99
    for (int i = 0; i <= 2; i++){
        folio_generado << nombre[i]; //Toma las tres primeras letras del nombre del proyecto
    }
    folio_generado << '-' << num1; //Concatena el guion seguido del numero generado
    return folio_generado.str();
}

void MainMenu::GuardarProyecto(Project &nuevo_proyecto,IndicePrimario &newIndice){
    //Abre un archivo en modo app, para agregar un nuevo proyecto al final del archivo
    fstream archivo_proyecto(fileData,fstream::app);
    //Llama a su metodo para guardar
    nuevo_proyecto.save(archivo_proyecto);
    archivo_proyecto.close();
}

void MainMenu::readByPrimaryIndex(const CIterator& auxIt){

    fstream lecturaIndice;
    CIterator it;
    it = auxIt;
    int pesoBytes(0);
    //Solo abre el archivo de los datos
    lecturaIndice.open(fileData);

    //Ordena la lista de manera ascendete con forme a las direcciones
    indicePrimarioL.sortList(true);

    //Si estamos en el ultimo elementod e la lista, solo va a restar el contador a la direccion del elemento buscado
    if(it.getNext() == indicePrimarioL.endList().readContent()){
        pesoBytes = counter - ((IndicePrimario*)(it.readContent()))->getDireccionBytes();

    }else{
        //Si estamos en cualquier otra posicion, se resta la direccion del siguiente a la direccion actual
        pesoBytes = ((IndicePrimario*)(it.getNext()))->getDireccionBytes()
                        - ((IndicePrimario*)(it.readContent()))->getDireccionBytes();
    } //Esto para poder saber el peso en bytes de cada proyecto a consultar

    char* auxStr =  new char[pesoBytes]; //Cadena de caracteres para capturar el proyecto
    string auxStr2;

    //Verifica que el proyecto a buscar sea el primero
    if(((IndicePrimario*)(it.readContent()))->getDireccionBytes() == DEFAULT_POS){
            //Si es el primero, coloca el puntero en la direccion del proyecto buscado
        lecturaIndice.seekp(((IndicePrimario*)(it.readContent()))->getDireccionBytes());
    }else{
        //SI no lo es, entonces Suma 1 a la direccion
        lecturaIndice.seekp(((IndicePrimario*)(it.readContent()))->getDireccionBytes()+1);
    }

    //Lee desde el archivo, almacena en la cadena caracteres la cantidad de pesoBytes
    lecturaIndice.read(auxStr, pesoBytes);
    //Conviente la cadena de caracteres a una cadena normal
    auxStr2 = auxStr;
    //Crea un proyecto auxiliar para poder mostrar su contenido recuperado
    Project auxProject(auxStr2);
    //Imprime sus datos
    auxProject.print();
    lecturaIndice.close();
}



