#include <stdio.h>
#include <stdlib.h>
#include "Errores.h"

/*Función que indica la existencia de un error léxico*/
void error_lexico(int linea){
    printf("\033[31m""Error lexico en la linea %d\n""\033[0m", linea);
}

/*Función que imprime un mensaje de error grave y cierra el programa*/
void imprimir_error(char *mensaje){
    printf("\033[31m""%s\n""\033[0m", mensaje);
}