#include <fstream>
#include <iostream>  
#include <sstream>

#include "constantes.h" 
#include "Equipo.h"
#include "Mundial.h"  

//----------------------------------------------------------------------------
Mundial::Mundial(){
    this -> lista_equipos = new Equipo*[MAX_EQUIPOS];
    for (int i= 0; i< MAX_EQUIPOS;i++){
        this -> lista_equipos[i] = nullptr;
    } 
    for(int i = 0 ; i < 4 ; i++){
        this->podio[i] = -1;
    }
    this -> cantidad_equipos = 0;
    this -> tamanio = MAX_EQUIPOS; 
    cargar_datos();
}
//----------------------------------------------------------------------------
void Mundial::cargar_datos(){
    std::ifstream Archivo_equipos(ARCHIVO_EQUIPOS);
    leer_equipos(Archivo_equipos);
    Archivo_equipos.close(); 

    ordenar_lista(); 
    
    std::ifstream Archivo_partidos(ARCHIVO_RESULTADOS);
    leer_partidos(Archivo_partidos);
    Archivo_partidos.close(); 
} 
//----------------------------------------------------------------------------
std::string Mundial::cargar_fase_grupos(std::ifstream &Archivo  ){
    std::string  equipo1 , equipo2 , resultado1 , resultado2 , linea ; 
    std::stringstream  cortar_linea  ;
    getline(Archivo , linea );
    while ( linea != "octavos" && linea != "cuartos" && linea != "final" && linea != "semifinales")
    {   
        std::stringstream  cortar_linea(linea); 
        getline(cortar_linea,equipo1,SEPARACION_PUNTO);
        getline(cortar_linea,resultado1,SEPARACION_PUNTO);
        getline(cortar_linea,equipo2,SEPARACION_PUNTO);
        getline(cortar_linea,resultado2,SEPARACION_PUNTO); 
        sumar_puntos_grupos(equipo1 , equipo2 , int(resultado1[0]) , int(resultado2[0]));
        getline(Archivo , linea ) ;
    }
    return linea;
}
std::string Mundial::cambiar_carracter(std::string nombre){
    for (unsigned int e  = 0; e < nombre.length(); e ++) {
	    if(nombre[e] == 95){
            nombre[e] = SEPARACION_ESPACIO;
        }
    }
    return nombre;
}
  
//----------------------------------------------------------------------------
std::string Mundial::devolver_nombre_minuscula(std::string nombre_equipo){
    for (unsigned int e  = 0; e < nombre_equipo.length(); e ++) {
		nombre_equipo[e] = char(tolower(nombre_equipo[e]));
    }
    return nombre_equipo;
}
//----------------------------------------------------------------------------
std::string Mundial::cargar_fases(std::ifstream &Archivo, int fase){
    std::string  equipo1, equipo2, resultado1, resultado2, resultado_penales_2,resultado_penales_1, linea;     
    std::stringstream  cortar_linea;   
    getline(Archivo , linea );
    while (linea != "grupos" && linea != "octavos" && linea != "cuartos" &&
     linea != "final" && linea != "semifinales" && linea != "tercer puesto" && linea != ""){ 
        std::stringstream  cortar_linea(linea); 
        getline(cortar_linea,equipo1,SEPARACION_PUNTO);
        getline(cortar_linea,resultado1,SEPARACION_PUNTO);
        getline(cortar_linea,resultado_penales_1,SEPARACION_PUNTO);
        getline(cortar_linea,equipo2,SEPARACION_PUNTO);
        getline(cortar_linea,resultado2,SEPARACION_PUNTO);
        getline(cortar_linea,resultado_penales_2); 
        if(fase == SEMI_FINAL ){
            definir_podio(equipo1,equipo2);
        }

        sumar_puntos_fases( fase, equipo1 , equipo2 , int(resultado1[0]) , int(resultado2[0]),int(resultado_penales_1[0]) , int(resultado_penales_2[0]));
        getline(Archivo , linea ); 
    } 
    return linea;
}
//----------------------------------------------------------------------------
void Mundial::sumar_puntos_fases(int fase, std::string equipo1, std::string  equipo2, int resultado1, int resultado2 , int penales1 , int penales2){
    if( resultado1 > resultado2 ){
        this->lista_equipos[posicion_equipo(equipo1)] -> sumar_puntos(VICTORIA,fase);
        //gano equipo1
    }else if( resultado1 < resultado2 ){
        this-> lista_equipos[posicion_equipo(equipo2)]-> sumar_puntos(VICTORIA,fase);
    }else{
        //empate
        if(penales1 > penales2){ 
            this -> lista_equipos[posicion_equipo(equipo1)] -> sumar_puntos(VICTORIA_PENALES,fase) ;
            this -> lista_equipos[posicion_equipo(equipo2)] -> sumar_puntos(DERROTA_PENALES,fase) ;
        }else{
            this -> lista_equipos[posicion_equipo(equipo2)] -> sumar_puntos(VICTORIA_PENALES,fase) ;
            this -> lista_equipos[posicion_equipo(equipo1)] -> sumar_puntos(DERROTA_PENALES,fase) ;
        }
    }
    }
//----------------------------------------------------------------------------
void Mundial::leer_partidos(std::ifstream &Archivo){
    //grupos. octavos. cuartos. semis. final. 
    std::string linea;
    getline(Archivo , linea );
    while (linea != ""){
        
        if (linea == "grupos"){
            linea = cargar_fase_grupos(Archivo ) ;  
        }else if(linea == "octavos"){
            linea = cargar_fases(Archivo, OCTAVOS_FINAL);
        }else if(linea == "cuartos"){  
            linea = cargar_fases(Archivo, CUARTOS_FINAL);
        }else if(linea == "semifinales" ){
            linea = cargar_fases(Archivo, SEMI_FINAL); 
        }else{//si es FINAL O TERCER PUESTO LO GUARDA EN FINAL. YA QUE TIENE TENER PTOS<2 EN SEMIFINAL EN EL 3RO
            linea = cargar_fases(Archivo, FINAL); 
        }
    }
}
//----------------------------------------------------------------------------
void Mundial::leer_equipos(std::ifstream &Archivo){
    int i = 0;
    std::string nombre , grupo, linea; 
    std::stringstream  cortar_linea ;  
    Equipo* nuevo;
    while( getline(Archivo , linea )){
        std::stringstream  cortar_linea(linea);
        getline(cortar_linea , nombre, SEPARACION_ESPACIO ); 
        nombre = cambiar_carracter(nombre);
        getline(cortar_linea , grupo );  
        nuevo = new Equipo(nombre, grupo[0]);
        this -> lista_equipos[i] = nuevo;
        i++;  
        this->cantidad_equipos ++;
        if( i == this -> tamanio-1 )
            redimensionar(); 
    } 
    
}
//----------------------------------------------------------------------------
int Mundial::posicion_equipo(std::string nombre){
    int posicion =0 ;
    while (this->lista_equipos[posicion]->devolver_nombre() 
    != nombre && this->lista_equipos[posicion] )
    {
        posicion++;
    }
    //suponemos que no hay equipos errores en el primer archivo
    return posicion;
}
//----------------------------------------------------------------------------
void Mundial::redimensionar(){   
    this -> tamanio =  tamanio + 4;
    Equipo** nueva = new Equipo*[this -> tamanio]; 
    for(int i= 0; i < this -> cantidad_equipos; i++){
        nueva[i] = this -> lista_equipos[i];
        }
    delete[] this -> lista_equipos;
    this -> lista_equipos = nueva;
}
//----------------------------------------------------------------------------
void Mundial::sumar_puntos_grupos( std::string  equipo1, std::string  equipo2, int resultado1, int resultado2){
    if( resultado1 > resultado2 ){ 
        this->lista_equipos[posicion_equipo(equipo1)] -> sumar_puntos(VICTORIA,FASE_GRUPOS);
        //gano equipo1
    }else if( resultado1 < resultado2 ) {
        this-> lista_equipos[posicion_equipo(equipo2)]-> sumar_puntos(VICTORIA,FASE_GRUPOS);
    } else {
        //empate
        this -> lista_equipos[posicion_equipo(equipo2)] -> sumar_puntos(EMPATE,FASE_GRUPOS) ;
        this -> lista_equipos[posicion_equipo(equipo2)] -> sumar_puntos(EMPATE,FASE_GRUPOS) ;
    }
    } 
//----------------------------------------------------------------------------
void Mundial::ordenar_lista(){
    Equipo* auxiliar;
    int comparacion;
    for(int i = 1; i< this -> cantidad_equipos ; i++){ 
        comparacion = i-1;  
        while (comparacion >= 0 && this->lista_equipos[comparacion]->devolver_letra() >=  this->lista_equipos[comparacion+1]->devolver_letra() )
            { 
                auxiliar =  this->lista_equipos[comparacion+1] ;
                this->lista_equipos[comparacion+1] = this->lista_equipos[comparacion];
                this->lista_equipos[comparacion] = auxiliar; 
                comparacion -= 1;
            }
    } 
}
//----------------------------------------------------------------------------
void Mundial::listar_equipos(){
    int posicion =0;
    while(this ->lista_equipos[posicion] != nullptr && posicion < this -> cantidad_equipos)
    {
        std::cout<<posicion+1<<"-"<<this->lista_equipos[posicion]->devolver_nombre()<<std::endl; 
        posicion++;
    }
}
//----------------------------------------------------------------------------
void Mundial::ordenar_podio(){
    int aux;
    for(int i = 0; i < 3 ; i++ ){
        if(this-> lista_equipos[podio[i]] -> devolver_puntaje( SEMI_FINAL) >=2 &&
            this-> lista_equipos[podio[i]] -> devolver_puntaje( FINAL) >= 2 ){
                aux = podio[0] ;
                podio[0] = podio[i];
                podio[i] = aux;
        }else if(this-> lista_equipos[podio[i]] -> devolver_puntaje( SEMI_FINAL) >=2 ){
                aux = podio[1] ;
                podio[1] = podio[i];
                podio[i] = aux;
        }else if(this-> lista_equipos[podio[i]] -> devolver_puntaje( FINAL) >=2 ){
                aux = podio[2] ;
                podio[2] = podio[i];
                podio[i] = aux;
        }
    }
}
//----------------------------------------------------------------------------
void Mundial::mostrar_podio(){ 
    ordenar_podio();
    std::cout<<"Primer puetro:    \t"<< this->lista_equipos[this->podio[0]]->devolver_nombre() <<std::endl ;
    std::cout<<"segundo puetro: \t"<<this->lista_equipos[this->podio[1]]->devolver_nombre()<<std::endl;
    std::cout<<"tercero puetro: \t"<<this->lista_equipos[this->podio[2]]->devolver_nombre()<<std::endl;
}
//----------------------------------------------------------------------------
 
 
void Mundial::guardar_en_podio(int posicion){
    int i = 0 ; 
    while(i < 4 && this -> podio[i] != -1 ){ 
        i++;
    }
    this -> podio[i] = posicion;
}
//----------------------------------------------------------------------------
void Mundial::definir_podio(std:: string equipo1 ,std:: string equipo2) {  

int posicion1 = posicion_en_lista_equipos(equipo1); 
    guardar_en_podio(posicion1); 
int posicion2 = posicion_en_lista_equipos(equipo2);  
    guardar_en_podio(posicion2); 

}

//-------------------------------<<<<<--------->>>>>-------------------------
void Mundial::mostrar_resultado_busqueda(int posicion){
    std::cout<<"Equipo encontrado: "<< this->lista_equipos[posicion]->devolver_nombre()<< 
    "\t Grupo "<< this->lista_equipos[posicion]->devolver_grupo_letra() <<std::endl;
    //std<<"ultima fase: "<<this->lista_equipos[posicion] -> ultima_fase()<<std::endl;
    for( int c : this->podio){
        if(podio[c] == posicion ){
            switch (c){
            case 0: std::cout<<"\nTitulo: CAMPEON"       ; break;
            case 1: std::cout<<"\nTitulo: SUBCAMPEON"    ; break;
            case 2: std::cout<<"\nTitulo: TERCER PUESTO" ; break;
            case 3: std::cout<<"\nTitulo: CUARTO PUESTO" ; break; 
            }
        }
    }

}
//----------------------------------------------------------------------------
int Mundial::posicion_en_lista_equipos(std::string nombre_buscado){
    int i =0;
    nombre_buscado = devolver_nombre_minuscula(nombre_buscado) ;
    while( i < this -> cantidad_equipos  && 
    devolver_nombre_minuscula(this -> lista_equipos[i] -> devolver_nombre()) != nombre_buscado){ 
        i++;
    }
    return devolver_nombre_minuscula(this -> lista_equipos[i] -> devolver_nombre()) == nombre_buscado ? i : -1 ;
}
//----------------------------------------------------------------------------
void Mundial::buscar_equipo_menu(){
    std::string nombre_ingresado  , nombre_equipo; 
    std::cout<<"introdusca nombre del equipo: ";
    std::cin>>nombre_ingresado;  
    
    int posicion = posicion_en_lista_equipos(nombre_ingresado) ;

    if( posicion != -1){
        mostrar_resultado_busqueda(posicion);
    }else{
        std::cout<<"no se a enctrado coincidencia"<<std::endl;
    }
}
//----------------------------------------------------------------------------
void Mundial::generar_fases_grupos(){ 
    for (int i = 0; i < CANTIDAD_GRUPOS; i++){ 
        this -> cantidad_por_grupo[i] = 0 ;
    }
    for(int i =0  ; i != this -> cantidad_equipos ; i++ ){
        fase_grupos[this -> lista_equipos[i] -> devolver_grupo_enum()]// 0-7 enum FASE_GRUPOS
        [this -> cantidad_por_grupo[this -> lista_equipos[i] -> devolver_grupo_enum()]] = i;// posicion en urna y suma 
        this -> cantidad_por_grupo[this -> lista_equipos[i] -> devolver_grupo_enum()] += 1 ;  
     } 
}
//----------------------------------------------------------------------------
void Mundial::mostrar_fases_grupos( ){ 
    for(int i =0 ; i < CANTIDAD_GRUPOS ; i++){
        if(this->cantidad_por_grupo[i] != 0){
            std::cout<<"grupo: "<< 
            this -> lista_equipos[fase_grupos[i][0]] ->devolver_grupo_letra() <<std::endl;
            for(int e =0 ;  e < this->cantidad_por_grupo[i] ;  e++){
            std::cout<<"equipo: "<< this -> lista_equipos[fase_grupos[i][e]] ->devolver_nombre() 
            <<"\t\t  puntos"<< lista_equipos[fase_grupos[i][e]] ->devolver_puntaje(FASE_GRUPOS) <<std::endl;
            }      
        }
    }
       
}
//----------------------------------------------------------------------------
void Mundial::menu_mostrar_fases_grupos(){
    int  columnas = 4; 
    this -> fase_grupos = new int*[CANTIDAD_GRUPOS];
    for(int i = 0 ; i < CANTIDAD_GRUPOS ; i++){
        fase_grupos[i] = new int[columnas];
    }
    generar_fases_grupos( ) ;
    ordenar_fase_grupos(  );
    mostrar_fases_grupos( );
    

}
//----------------------------------------------------------------------------
void Mundial::ordenar_fase_grupos(  ){
    int aux  , comparacion   ;
    for(int  i = 0 ; i < CANTIDAD_GRUPOS ; i++){
        for (int e  = 1 ; e < this->cantidad_por_grupo[i] ; e++){
            comparacion = e;
            while(comparacion != 0 &&  
            lista_equipos[ fase_grupos[i][comparacion - 1 ]] ->devolver_puntaje(FASE_GRUPOS) < 
            lista_equipos[ fase_grupos[i][comparacion] ] ->devolver_puntaje(FASE_GRUPOS)){
                aux = fase_grupos[i][comparacion];
                fase_grupos[i][comparacion] = fase_grupos[i][comparacion-1];
                fase_grupos[i][comparacion-1] = aux;
                comparacion--;
            }
        } 
    }
    std::cout<<"ordenar_fase_grupo\n  ";
}
//----------------------------------------------------------------------------
void Mundial::mostrar_octavos(){
    for(int i =0 ; i < 16; i++){
        this->octavos[i] = nullptr;
    }
    cargar_octavos();
    ordenar_octavos(); 
    std::cout<< "-------------Octavos-------------" <<std::endl;
    for(Equipo* equipo: octavos){
        if(equipo != nullptr){
            std::cout<<"Nombre:"<<equipo->devolver_nombre()
            <<"\t puntos: "<< equipo->devolver_puntaje(OCTAVOS_FINAL)<<std::endl;
        }
    }
}
//----------------------------------------------------------------------------
void Mundial::cargar_octavos(){int cargar = 0;
    for(int i = 0 ; i < this->cantidad_por_grupo[i] ; i++){ //cantidad_por_grupo
        for(int e = 0 ; e < 2 ; e++){
            this->octavos[cargar] = this -> lista_equipos[fase_grupos[i][e]];
            cargar++;
        }
    }}
//----------------------------------------------------------------------------
void Mundial::ordenar_octavos(){
    int i = 1 ;
    Equipo* aux = 0;
    while (this -> octavos[i] != nullptr){
        int e = i;
        while (e > 0  &&  octavos[e]->devolver_puntaje(OCTAVOS_FINAL) > 
                            octavos[e-1]->devolver_puntaje(OCTAVOS_FINAL)){
                aux = octavos[e-1]; 
                octavos[e-1] = octavos[e];
                octavos[e] = aux;
        e--;
        }
        i++;
    }   
}
//----------------------------------------------------------------------------
void Mundial::mostrar_cuartos(){
    std::cout<< "-------------Cuartos-------------" <<std::endl;
    for(int i = 0 ; i < this->cantidad_equipos ; i++ ){
        if(this ->lista_equipos[i]->devolver_puntaje(OCTAVOS_FINAL) >= 2){
            std::cout<< "Nombre: "<< this ->lista_equipos[i]->devolver_puntaje(OCTAVOS_FINAL)
            << "\t Puntos: "<< this ->lista_equipos[i]->devolver_puntaje(OCTAVOS_FINAL)<<std::endl;
        }
    }
}
//----------------------------------------------------------------------------
void Mundial::mostrar_semifinal(){
    std::cout<< "-------------Semifimales-------------" <<std::endl;
    for(int i: this->podio ){ 
        std::cout<< "Nombre: "<< this ->lista_equipos[i]->devolver_puntaje(CUARTOS_FINAL)
        << "\t Puntos: "<< this ->lista_equipos[i]->devolver_puntaje(CUARTOS_FINAL)<<std::endl; 
    }
    
}
//----------------------------------------------------------------------------
void Mundial::mostrar_fixtur_completo(){
    //fases 
    menu_mostrar_fases_grupos();
    mostrar_octavos();
    mostrar_cuartos();
    mostrar_semifinal();
    for(int i = 0 ; i < CANTIDAD_GRUPOS ; i++){
        delete[] fase_grupos[i];
    }
    delete[] fase_grupos;

} 
//----------------------------------------------------------------------------
Equipo* Mundial::devolver_equipo(int posicion){
return this ->lista_equipos[posicion];
}
//----------------------------------------------------------------------------
Mundial::~Mundial(){
    delete[] lista_equipos;
}
