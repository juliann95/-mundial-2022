#include <iostream>
#include "Menu.h"
#include "Mundial.h"
#include "constantes.h"
#include "clear_screen.h"
//CONSTANTES despues poner en archivo aparte

int main(){
    //system(CLR_SCREEN);
 
    Mundial* fixtur = new Mundial;    
    //fixtur->mostrar_fixtur_completo();
    menu(fixtur);
    
    for(int i = 0 ; i < MAX_EQUIPOS ; i++){
        delete fixtur->devolver_equipo(i);
    }
    delete fixtur;
    return 0;    
}
/*
tp 1 fixtur del mundial

leer el archivo 1 ves. ordenar por insercion
equipo grupo

archivo "resultados.csv"
    grupos
    equipo1,goles,equipo2,goles
    .
    .
    .
    octavos
    equipo1 goles resultado_penales1 equipo2 goles resultado_penales
    ...
    cuartos
    semisfinal
    final
*/