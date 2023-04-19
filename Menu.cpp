
#include <iostream>
#include <stdexcept>
#include <cctype>
#include "Menu.h"
#include "Mundial.h"
#include "clear_screen.h"  

/*
1. Listar equipos.
2. Mostrar los equipos en primer segundo y tercer lugar.
3. Buscar equipo por nombre.
4. Mostrar por fase los países ordenados por puntaje.
5. Salir.
*/

void menu(Mundial* fixtur){ 

    int opcion  ;
    while (opcion != 5 ){    
        switch (seleccionar_opcion())
        {
            case 1: fixtur -> listar_equipos() ;break;
            case 2: fixtur -> mostrar_podio() ;break;
            case 3: fixtur -> buscar_equipo_menu() ;break;
            case 4: fixtur -> mostrar_fixtur_completo() ;break;
            case 5: opcion  = 5;break; 
        }
        
        limpiar(); 
    } 

}

void mostrar_menu(){

    std::cout<< "1. Listar equipos." <<std::endl;
    std::cout<< "2. Mostrar los equipos en primer segundo y tercer lugar." <<std::endl;
    std::cout<< "3. Buscar equipo por nombre." <<std::endl;
    std::cout<< "4. Mostrar por fase los países ordenados por puntaje." <<std::endl;
    std::cout<< "5. Salir." <<std::endl;
}

int seleccionar_opcion(){
    int opcion = 0;
    mostrar_menu();
    while (opcion < 1 || opcion > 5)
    {
        /*vuelve a pedir la opccion si no estata entre [1;5] */ 
        std::cout<< "ingrese un numero entre 1 y 5:  ";
        std::cin>>opcion;
         
        if (std::cin.fail()) { 
            throw std::runtime_error("Error: se ingreso un valor no valido.");   
        }   
    }
    return opcion;
    
}
void limpiar(){
    int respuesta =1;
    while(respuesta != 0){
        std::cout<<"introdusca '0' (cero) para continuar... Se borrara la pantalla ";
        std::cin>>respuesta;
    }
    system(CLR_SCREEN);
}
 