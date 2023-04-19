#include <iostream> 

#include "constantes.h" 
#include "Equipo.h"
 

Equipo::Equipo( std::string equipo,char grupo){
    this -> nombre = equipo;
    this -> grupo = grupo ;
    for(int i = 0 ;i <= 4 ; i++){
        this -> puntajes[i] = 0;
        } 
} 
std::string Equipo::devolver_nombre(){
    return this -> nombre;
}
void Equipo::sumar_puntos(int puntos, int fase){
        this -> puntajes[fase] += puntos;    
} 
//std:: string Equipo::ultima_fase(){}

int Equipo::devolver_grupo_enum(){ 
    int devolver;
    switch ( this -> grupo)
    {
    case 'A' : devolver = A ;break;
    case 'B' : devolver = B ;break;
    case 'C' : devolver = C ;break;
    case 'D' : devolver = D ;break;
    case 'E' : devolver = E ;break;
    case 'F' : devolver = F ;break;
    case 'G' : devolver = G ;break;
    case 'H' : devolver = H ;break;
    };
return devolver;
}
char Equipo::devolver_grupo_letra(){
    return  this -> grupo;
}
char Equipo::devolver_letra(){
    return this->nombre[0];
}
int Equipo::devolver_puntaje(int fase){
    return this -> puntajes[fase];
}

 