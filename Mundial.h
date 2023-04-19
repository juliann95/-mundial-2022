#ifndef MUNDIAL_H
#define MUNDIAL_H

#include "Equipo.h"
#include "constantes.h"

enum NOMBRE_GRUPOS {
    FASE_GRUPOS,
    OCTAVOS_FINAL,
    CUARTOS_FINAL,
    SEMI_FINAL,
    FINAL
};

enum PUNTAJES {
    EMPATE =1,
    VICTORIA = 3,
    VICTORIA_PENALES = 2,
    DERROTA_PENALES= 1
};

class Mundial{
private:
    Equipo** lista_equipos;
    int cantidad_equipos;
    int tamanio; 
    int podio[4];
    Equipo* cuartos[8];
    Equipo* octavos[16];
    int** fase_grupos;
    int cantidad_por_grupo[CANTIDAD_GRUPOS];// ayuda para no leer vectores sin datos por falta de inf en resultados

 
    //pre:
    //pos:
    void leer_equipos(std::ifstream &Archivo);
    //pre:archivo abierto y int que indica a que fase pertenece
    //pos:
    std::string cargar_fase_grupos(std::ifstream &Archivo  ); 
    //pre:
    //pos:
    std::string cargar_fases(std::ifstream &Archivo, int fase); 
    //pre:
    //pos:
    void redimensionar(); 
    //pre:
    //pos:
    void sumar_puntos_grupos( std::string equipo1, std::string  equipo2, int resultado1, int resultado2);
    //pre:fase:ultima lectura ,equipo 1 y 2 
    //pos:
    void sumar_puntos_fases(int fase, std::string equipo1, std::string  equipo2, int resultado1, int resultado2 , int penales1 , int penales2);
    //pre:
    //pos:con el
    void definir_podio(std::string equipo1,std::string equipo2);
    //pre:
    //pos:compara lista_equipos[podio[i]] i=3,4. ordena podio[i] del 3er puesto
    void definir_tercero();
    //pre: int posicion del objeto Equipo en la lista_equipo
    //guarda en el podio[] la posicion del equipo en la lista_equiepo
    void guardar_en_podio(int posicion);
    //pre:
    //pos:
    void ordenar_podio();
public:
    //pre:
    //pos:
    Mundial();  
    //pre:
    //pos:
    void cargar_datos();
    //pre:direccion del archivo a leer
    //pos:
    void leer_partidos(std::ifstream &Archivo);
    //pre:
    //pos:muestra los equipos en la lista con su grupo
    void listar_equipos();
    //pre:nombre a comprar con los objetos de la lista_equipos[]
    //pos: int indicando la poscion donde se encontro el nombre
    int posicion_equipo(std::string nombre);
    //pre:
    //pos: muestra los dos equipos que llegaron a la final y el 3ro por puntos
    void mostrar_podio();
    //pre:
    //pos:recorre la lista hasta encontrar el nombre
    void buscar_equipo_menu();
    //pre:
    //pos:(CON METODO DE INSECION)
    void ordenar_lista();
    //pre:
    //pos:
    std::string cambiar_carracter(std::string nombre);
    //pre: string nombre a buscar
    //pos:devuelve int hace referencia al la posicion en lista_equipo
    int posicion_en_lista_equipos(std::string nombre1 );

    //pre:resive string 
    //pos:devuelve el mismo string todo en minuscula
    std::string devolver_nombre_minuscula(std::string nombre_equipo);

    //pre: 
    //pos:
    Equipo* devolver_equipo(int posicion);
    //pre: posicion i en listar_equipos[i]
    //pos: mustra nombre, fase hasta la que llego y titulo si tiene
    void mostrar_resultado_busqueda(int posicion);
    //pre:
    //pos:(**CONDICIONES DEL TRABAJO**)
    void mostrar_fixtur_completo();
    //pre:
    //pos:recoore 0-7 array y ordena los grupos por insecion
    void ordenar_fase_grupos( );
    //pre:
    //pos:carga el arra fase_grupos[] recorriendo lista_equipos[]
    void generar_fases_grupos( );
    //pre:
    //pos:entra a mostrar_fase
    void menu_mostrar_fases_grupos();
    //pre:
    //pos:pone punteros en nulo carga_octavos ordena_octavos y muestra
    void mostrar_octavos();
    //pre:
    //pos:recorre la lista de octavos y los que tienen puntaje >=2 los muestra
    void mostrar_cuartos();
    //pre:
    //pos:ordena lista octavos por insercion
    void ordenar_octavos();
    //pre:
    //pos:carga los elemento de fase_grupos[i][0,2] i=0,7 
    void cargar_octavos();
    //pre:
    //pos:si en puntaje[CUARTOS] tienen >=2 IMPRIME
    void mostrar_semifinal();
    //pre:
    //pos:muestra los paices por grupos con sus respectivos puntajes
    void mostrar_fases_grupos();

    ~Mundial();
};
#endif