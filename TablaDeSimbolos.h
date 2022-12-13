#include "ArbolBinario.h"

/* Función que crea la tabla de símbolos y inserta las palabras reservadas del lenguaje */
void inicializarTablaSimbolos();

/* Función que imprime la tabla de símbolos */
void imprimirTablaSimbolos();

/*Función que imprime el espacio de trabajo*/
void imprimirEspacioTrabajo();

/* Función que libera la memoria eliminando los datos de la tabla de símbolos */
void borrarTablaSimbolos();

/*Función que inserta una variable en la tabla de símbolos*/
void insertarElemento(char* lexema , float valor);

/*Función que inserta una función en la tabla de símbolos*/
void insertaFunc(char *lexema, void *fnc);

/*Función que comprueba un componente lexico en la tabla de símbolos*/
short esMiembro(char* lexema,int componente);

/*Función que devuelve el componente*/
short componenteMiembro(char* lexema);

/*Función que devuelve el valor de una variable o constante*/
float obtenerValor(char* lexema);

/*Función que ejecuta una función de la tabla de símbolos*/
float ejecutarFuncion(char* lexema, float parametro);
float ejecutarFuncion2(char* lexema, float parametro1, float parametro2);

/*Función que elimina todas las variables de la tabla de símbolos*/
void eliminarVariables();

