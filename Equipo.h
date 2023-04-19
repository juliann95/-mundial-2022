#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>

enum GRUPOS{
    A=0,B,C,D,E,F,G,H
};

class Equipo{

private:
    std::string nombre;
    char grupo;
    int puntajes[5]; 
    std::string  titulo;

public:
    Equipo(){};
    //pre:
    //pos:
    Equipo( std::string equipo , char grupo); 
    //pre:
    //pos:devuelve el atributo nombre
    std::string devolver_nombre();
    //pre:
    //pos:devuel el atributo char grupo como numero p
    int devolver_grupo_enum();
    //pre:-
    //pos:devuel el atributo char grupo
    char devolver_grupo_letra();
    //pre:
    //pos:suma puntos puntaje[grupos,octavos,cuartos,semi,final] dependiendo donde se le indique
    void sumar_puntos(int puntos, int fase); 
    //pre:-
    //pos:devuelve la primera letra del nombre 
    char devolver_letra();    
    //pre:posicion en el array del dato que se quiere averiguar
    //pos: puntaje[grupos,octavos,cuartos,semi,final] devuelve int puntaje de la fase correspondiente
    int devolver_puntaje(int fase); 
    ~Equipo(){};

};
#endif