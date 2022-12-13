#include "ArbolBinario.h"
#include "Definiciones.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>

static abb arbol; //Tabla de símbolos creada como global

/* Función que crea la tabla de símbolos y inserta las palabras reservadas del lenguaje
 * La tabla se crea en forma de arbol y se insertan las palabras reservadas*/
void inicializarTablaSimbolos() {
    tipoelem elem;
    elem.lexema = (char*)malloc(50*sizeof(char));
    crear(&arbol);

    /*Array de constantes*/
    char* constantes[] = {"E", "PI"};
    char* valor[] = {"2.718281828459045", "3.141592653589793"};

    /*Bucle for que recorre el array de constantes*/
    for(int i=0; i<2; i++){
        /*Se crea una variable que almacena la constante*/
        strcpy(elem.lexema, constantes[i]);
        /*Se crea una variable que almacena el valor de la constante*/
        elem.data.valor = atof(valor[i]);
        elem.componente = _CONSTANTE;
        /*Se inserta la constante en la tabla de símbolos*/
        if (es_miembro(arbol, elem) == 0) {
            insertarVarConst(&arbol, elem);
        }
    }

    /*Array de funciones matemáticas*/
    char* funciones[] = {"sin", "cos", "tan", "sqrt", "exp", "ln"};
    char* funciones2[] = { "pow"};
    /*Lista de double (*fnc)() que almacena las funciones matemáticas*/
    double (*puntero[])(double) = {sin, cos, tan, sqrt, exp, log};
    double (*puntero2[])(double, double) = {pow};	

    /*Bucle for que recorre el array de funciones*/
    for(int i=0; i<6; i++){
        /*Se crea una variable que almacena la función*/
        strcpy(elem.lexema, funciones[i]);
        /*Se crea una variable que almacena el puntero a la función*/
        elem.data.fnc = (double (*)()) puntero[i];
        elem.componente = _FUNCION;
        /*Se inserta la función en la tabla de símbolos*/
        if (es_miembro(arbol, elem) == 0) {
            insertarFuncion(&arbol, elem);
        }
    }
    
    /*Bucle for que recorre el array de funciones con dos parametros*/
    for(int i=0; i<1; i++){
        /*Se crea una variable que almacena la función*/
        strcpy(elem.lexema, funciones2[i]);
        /*Se crea una variable que almacena el puntero a la función*/
        elem.data.fnc = (double (*)()) puntero2[i];
        elem.componente = _FUNCION;
        /*Se inserta la función en la tabla de símbolos*/
        if (es_miembro(arbol, elem) == 0) {
            insertarFuncion(&arbol, elem);
        }
    }

    /*Se libera memoria*/
    free(elem.lexema);
}

void imprimirTablaSimbolos(){
    printf("\n*-*-*Imprimiendo la tabla de símbolos*-*-*\n");
    imprimirArbol(&arbol);
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

void imprimirEspacioTrabajo(){
    printf("\n*-*-*Imprimiendo las variables declaradas*-*-*\n");
    imprimirVariables(&arbol);
    printf("*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*\n");
}

void borrarTablaSimbolos(){
    destruir(&arbol);
    printf("\n*-*-*Tabla de simbolos borrada*-*-*\n");
}

void insertarElemento(char* lexema , float valor) {
    tipoelem elem;
    //Reservo memoria para el lexema
    elem.lexema = (char*)malloc(sizeof(char) * 50);
    //Copio el contenido del lexema en el tipoelem
    strcpy(elem.lexema, lexema);
    elem.componente = _VARIABLE;
    elem.data.valor = valor;
    //Primero se comprueba que el lexema no esté ya en la tabla de simbolos
    if (es_miembro(arbol, elem) == 0) {
        insertarVarConst(&arbol, elem);
    }
    else{
        actualizarVariable(&arbol, elem);
    }
    //Libero la memoria reservada para el lexema
    free(elem.lexema);
}

void insertaFunc(char *lexema, void *fnc){
    tipoelem elem;
    //Reservo memoria para el lexema
    elem.lexema = (char*)malloc(sizeof(char) * 50);
    //Copio el contenido del lexema en el tipoelem
    strcpy(elem.lexema, lexema);
    elem.componente = _FUNCION;
    //Primero se comprueba que la función no esté ya en la tabla de simbolos
    if (es_miembro(arbol, elem) == 0) {
        elem.data.fnc = (double (*)()) fnc;
        insertarFuncion(&arbol, elem);
    }
}

short esMiembro(char* lexema,int componente){
    tipoelem elem;
    short resultado;

    elem.lexema = (char*)malloc(sizeof(char) * 50);
    strcpy(elem.lexema, lexema);
    elem.componente = componente;
    resultado = es_miembro(arbol, elem);

    free(elem.lexema);
    return resultado;
}

short componenteMiembro(char* lexema){
    tipoelem elem;
    short resultado;

    elem.lexema = (char*)malloc(sizeof(char) * 50);
    strcpy(elem.lexema, lexema);
    resultado = verComponente(arbol, elem);

    free(elem.lexema);
    return resultado;
}

float obtenerValor(char* lexema){
    tipoelem elem;
    float resultado;

    elem.lexema = (char*)malloc(sizeof(char) * 50);
    strcpy(elem.lexema, lexema);
    elem.componente = _VARIABLE;
    resultado = recuperarValor(&arbol, elem);

    free(elem.lexema);
    return resultado;
}

float ejecutarFuncion(char* lexema, float parametro){
    tipoelem elem;
    float resultado;
    elem.lexema = (char*)malloc(sizeof(char) * 50);
    strcpy(elem.lexema, lexema);
    elem.componente = _FUNCION;

    resultado = ejecutaFuncion(&arbol, &elem, parametro);

    free(elem.lexema);
    return resultado;
}

float ejecutarFuncion2(char* lexema, float parametro1, float parametro2){
    tipoelem elem;
    float resultado;
    elem.lexema = (char*)malloc(sizeof(char) * 50);
    strcpy(elem.lexema, lexema);
    elem.componente = _FUNCION;

    resultado = ejecutaFuncion2(&arbol, &elem, parametro1, parametro2);

    free(elem.lexema);
    return resultado;
}

void eliminarVariables(){
    eliminarNodosVariables(&arbol);
}
