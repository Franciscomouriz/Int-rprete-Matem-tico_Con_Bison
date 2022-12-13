#include "ArbolBinario.h"
#include "Definiciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

///////////////////////// ESTRUCTURAS DE DATOS

struct celda {
    tipoelem info;
    struct celda *izq, *der;
};

//////////////////////// FUNCIONES


/////////////////////////////////////////////////////////////
/////////////////////////// INICIO PARTE MODIFICABLE

/*Extraer la clave de una celda */
tipoclave _clave_elem(tipoelem *E) {
    return E->lexema;
}

/* Esta funcion puente nos permite modificar el tipo de
 * de datos del TAD sin tener que cambiar todas las 
 * comparaciones del resto de la biblioteca y en su lugar
 * cambiando solo esta. */
int _comparar_claves(tipoclave cl1, tipoclave cl2) {
    if(strcmp(cl1,cl2)==0)
        return 0;
    else if(strcmp(cl1,cl2)>0)
        return 1;
    else
        return -1;
}

/* Si tipoelem tiene alguna estructura que necesite 
 * destruirse ha de hacerse aqui. El uso de esta funcion
 * permite hacer mas eficiente la destruccion del arbol.*/
void _destruir_elem(tipoelem *E) {
    //free(E);
    free(E->lexema);
    E=NULL;
}

/////////////////////////// FIN PARTE MODIFICABLE
/////////////////////////////////////////////////////////////

//OPERACIONES DE CREACIÓN Y DESTRUCCIÓN

void crear(abb *A) {
    *A = NULL;
}

void destruir(abb *A) {
    if (*A != NULL) {
        destruir(&(*A)->izq);
        destruir(&(*A)->der);
        _destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    }
}

//OPERACIONES DE INFORMACIÓN

unsigned es_vacio(abb A) {
    return A == NULL;
}

abb izq(abb A) {
    return A->izq;
}

abb der(abb A) {
    return A->der;
}
// Función privada para comparar las claves

int _comparar_clave_elem(tipoclave cl, tipoelem E) {
    return _comparar_claves(cl, _clave_elem(&E));
}
//Función privada para informar si una clave está en el árbol
unsigned _es_miembro_clave(abb A, tipoclave cl) {
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { //cl == A->info
        return 1;
    }
    if (comp > 0) { //cl > A->info
        return _es_miembro_clave(der(A), cl);
    }
    //cl < A->info
    return _es_miembro_clave(izq(A), cl);
}

//Función privada para informar si una clave está en el árbol
//Devuelve el tipo de componente
int _ver_componente(abb A, tipoclave cl){
    if (es_vacio(A)) {
        return 0;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { //cl == A->info
        return A->info.componente;
    }
    if (comp > 0) { //cl > A->info
        return _ver_componente(der(A), cl);
    }
    //cl < A->info
    return _ver_componente(izq(A), cl);
}

//Funciones públicas

unsigned es_miembro(abb A, tipoelem E) {
    return _es_miembro_clave(A, _clave_elem(&E));
}

int verComponente(abb A, tipoelem E){
    return _ver_componente(A, _clave_elem(&E));
}

void buscar_nodo(abb A, tipoclave cl, int *nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);

    if (comp == 0) { // cl == A->info
        *nodo = A->info.componente;
    } else if (comp < 0) { // cl < A->info
        buscar_nodo(A->izq, cl, nodo);
    } else { // cl > A->info
        buscar_nodo(A->der, cl, nodo);
    }
}
//OPERACIONES DE MODIFICACIÓN

/* Funciones recursivas para insertar un nuevo nodo 
   en el arbol. Se presupone que no existe un nodo
   con la misma clave en el arbol. */
void insertarVarConst(abb *A, tipoelem E) {
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(sizeof (char) * (strlen(E.lexema) + 1));
        strcpy((*A)->info.lexema, E.lexema);
        (*A)->info.lexema[strlen(E.lexema)] = '\0';
        (*A)->info.componente = E.componente;
        (*A)->info.data.valor = E.data.valor;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp > 0) {
        insertarVarConst(&(*A)->der, E);
    } else {
        insertarVarConst(&(*A)->izq, E);
    }
}

void actualizarVariable(abb *A, tipoelem E){
    if (strcmp(E.lexema,(*A)->info.lexema)==0 && (*A)->info.componente==_VARIABLE){
        (*A)->info.data.valor = E.data.valor;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp > 0) {
        actualizarVariable(&(*A)->der, E);
    } else {
        actualizarVariable(&(*A)->izq, E);
    }
}

void insertarFuncion(abb *A, tipoelem E){
    if (es_vacio(*A)) {
        *A = (abb) malloc(sizeof (struct celda));
        (*A)->info.lexema = (char*)malloc(sizeof (char) * (strlen(E.lexema) + 1));
        strcpy((*A)->info.lexema, E.lexema);
        (*A)->info.lexema[strlen(E.lexema)] = '\0';
        (*A)->info.componente = _FUNCION;
        (*A)->info.data.fnc = E.data.fnc;
        (*A)->izq = NULL;
        (*A)->der = NULL;
        return;
    }
    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp > 0) {
        insertarFuncion(&(*A)->der, E);
    } else {
        insertarFuncion(&(*A)->izq, E);
    }
}

/*Funciones para recuperar los datos de la tabla*/
float recuperarValor(abb *A, tipoelem E){
    float resultado; 
    if (strcmp(E.lexema, (*A)->info.lexema) == 0 && ((*A)->info.componente == _VARIABLE || (*A)->info.componente == _CONSTANTE))
    {
        resultado = (*A)->info.data.valor;
        return resultado;
    }
    else if (strcmp(E.lexema,(*A)->info.lexema)<0){
        return (recuperarValor(&(*A)->izq, E));
    }
    else{
        return (recuperarValor(&(*A)->der, E));
    }
}

float ejecutaFuncion(abb *A, tipoelem *E, float valor){
    if (strcmp(E->lexema,(*A)->info.lexema)==0 && (*A)->info.componente==_FUNCION){
        return (*A)->info.data.fnc(valor);
    }
    else if (strcmp(E->lexema,(*A)->info.lexema)<0){
        return (ejecutaFuncion(&(*A)->izq, E, valor));
    }
    else{
        return (ejecutaFuncion(&(*A)->der, E, valor));
    }
}

float ejecutaFuncion2(abb *A, tipoelem *E, float valor1, float valor2){
    if (strcmp(E->lexema,(*A)->info.lexema)==0 && (*A)->info.componente==_FUNCION){
        return (*A)->info.data.fnc(valor1,valor2);
    }
    else if (strcmp(E->lexema,(*A)->info.lexema)<0){
        return (ejecutaFuncion2(&(*A)->izq, E, valor1, valor2));
    }
    else{
        return (ejecutaFuncion2(&(*A)->der, E, valor1, valor2));
    }
}

/* Funcion privada que devuelve mínimo de subárbol dcho */
tipoelem _suprimir_min(abb * A) {//Se devuelve el elemento más a la izquierda
    abb aux;
    tipoelem ele;
    if (es_vacio((*A)->izq)) {//Si izquierda vacía, se devuelve valor nodo actual A
        ele = (*A)->info;
        aux = *A;
        *A = (*A)->der;
        free(aux);
        return ele;
    } else {
        return _suprimir_min(&(*A)->izq); //se vuelve a buscar mínimo rama izquierda
    }
}

/* Funcion que permite eliminar un nodo del arbol */
void suprimir(abb *A, tipoelem E) {
    abb aux;
    if (es_vacio(*A)) {
        return;
    }

    tipoclave cl = _clave_elem(&E);
    int comp = _comparar_clave_elem(cl, (*A)->info);
    if (comp < 0) { //if (E < (*A)->info) {
        suprimir(&(*A)->izq, E);
    } else if (comp > 0) { //(E > (*A)->info) {
        suprimir(&(*A)->der, E);
    } else if (es_vacio((*A)->izq) && es_vacio((*A)->der)) {
        _destruir_elem(&((*A)->info));
        free(*A);
        *A = NULL;
    } else if (es_vacio((*A)->izq)) { // pero no es vacio derecha
        aux = *A;
        *A = (*A)->der;
        _destruir_elem(&aux->info);
        free(aux);
    } else if (es_vacio((*A)->der)) { //pero no es vacio izquierda
        aux = *A;
        *A = (*A)->izq;
        _destruir_elem(&aux->info);
        free(aux);
    } else { //ni derecha ni izquierda esta vacio, busco mínimo subárbol derecho
        _destruir_elem(&(*A)->info); //elimino la info pero no libero el nodo,
        //pues en su sitio voy a poner el mínimo del subárbol derecho
        (*A)->info = _suprimir_min(&(*A)->der);
    }
}

/*Función que recorre el arbol eliminando todos los nodos del tipo VARIABLE*/
void eliminarNodosVariables(abb *A){
    if (es_vacio(*A)){
        return;
    }
    eliminarNodosVariables(&(*A)->izq);
    eliminarNodosVariables(&(*A)->der);
    if ((*A)->info.componente == _VARIABLE){
        suprimir(A, (*A)->info);
    }
}

/* Funcion privada para pasar la clave y no tener que
   extraerla del nodo en las llamadas recursivas.*/
void _modificar(abb A, tipoclave cl, tipoelem nodo) {
    if (es_vacio(A)) {
        return;
    }
    int comp = _comparar_clave_elem(cl, A->info);
    if (comp == 0) {
        A->info = nodo;
    } else if (comp < 0) {
        _modificar(A->izq, cl, nodo);
    } else {
        _modificar(A->der, cl, nodo);
    }
}

void imprimirArbol(abb *A){
    if(!es_vacio(*A)){
        if(&(*A)->izq != NULL)
            imprimirArbol(&(*A)->izq);
        printf("Lexema: %s", (*A)->info.lexema);
        for(size_t i = 0; i < 20 - strlen((*A)->info.lexema); i++){
            printf(" ");
        }
        if((*A)->info.componente == _VARIABLE){
            printf("Componente: Variable\n");
        }
        else if((*A)->info.componente == _FUNCION){
            printf("Componente: Función\n");
        }   
        else if((*A)->info.componente == _CONSTANTE){
            printf("Componente: Constante\n");
        }  

        if(&(*A)->der != NULL)
            imprimirArbol(&(*A)->der);
    }
}

void imprimirVariables(abb *A){
    if(!es_vacio(*A)) {
        if (&(*A)->izq != NULL)
            imprimirVariables(&(*A)->izq);
        if ((*A)->info.componente == _VARIABLE) {
            printf("Nombre: %s", (*A)->info.lexema);
            for (size_t i = 0; i < 20 - strlen((*A)->info.lexema); i++) {
                printf(" ");
            }
            printf("Valor: %f\n", (*A)->info.data.valor);
        }
        if (&(*A)->der != NULL)
            imprimirVariables(&(*A)->der);
    }
}