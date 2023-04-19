Trabajo Practico nº1: La misión de La'ebb


decidi hacerlo con objetos aunq creo que quedo bastante extenso, por eso prefiero hacer aclaraciones

objeto Mundial 

ATRIBUTOS:
    Equipo** lista_equipos: en cada elemento del array hay un puntero a un objeto Equipo

    int cantidad_equipos: mientras le el archivo "equipos.txt" va sumando una unidad

    int tamanio: es la cantidad de elementos en lista_equipos[tamanio] se inicia con una constante y se redimensiona si es nesesario
    
    int podio[4]: cuando en el archivo lee "semifinales" guarda con un metodo la posicion del equipo en el array lista_equipos
    
    Equipo* cuartos[8]: array de equipo si en octavos tuvo 2 o mas puntos se guarda 

    Equipo* octavos[16]: array de equipo recorre fase_grupos y de cada grupo saca los primeros 2

    int** fase_grupos: array que tiene fase_grupos[ GRUPO][POSICION_EN_EL_GRUPO] mediante funciones se guarda y ordena

    int cantidad_por_grupo[CANTIDAD_GRUPOS]: array para ordenar los grupos y sabiendo que puede haber
                                         un archivo incompleto se guarda en la fase y suma en la posiscion del grupo
                                         ejem: {A , B , C , D , E , F , G , H} en el archivo de prueba serian la cantidades 
                                               {4 , 4 , 4 , 4 , 4 , 4 , 0 , 0}


