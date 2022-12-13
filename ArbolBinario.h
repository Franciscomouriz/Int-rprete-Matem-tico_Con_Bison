#ifndef ABB_H
#define ABB_H

/**
 * Tipo de dato abstracto para arbol binario con clave de
 * ordenacion y elemento de celda.
 */

///////////////////////////////////////INICIO PARTE MODIFICABLE
typedef char* tipoclave;

typedef struct{
    char* lexema;  //Nombre de la variable/constante/funcion
    int componente;
    union Data{
        float valor;
        double (*fnc)();
    }data;
}tipoelem;

//////////////////////////////////////////FIN PARTE MODIFICABLE
		
typedef struct celda * abb;//tipo opaco

/////////////////////////////// FUNCIONES

//FUNCIONES DE CREACIÓN Y DESTRUCCIÓN DEL ÁRBOL
/**
 * Crea el arbol vacio.
 * @param A Puntero al arbol. Debe estar inicializado.
 */
void crear(abb *A);

/**
 * Destruye el arbol recursivamente
 * @param A El arbol que queremos destruir
 */
void destruir(abb *A);

//FUNCIONES DE INFORMACIÓN
/**
 * Comprueba si el arbol esta vacio
 * @param A El arbol binario
 */
unsigned es_vacio(abb A);

/**
 * Devuelve el subarbol izquierdo de A
 * @param A - Arbol original
 */
abb izq(abb A);
/**
 * Devuelve el subarbol derecho de A
 * @param A - Arbol original
 */
abb der(abb A);

/**
 * Comprueba si el elemento <E> existe en el arbol <A>
 * @param A
 * @param E
 */
unsigned es_miembro(abb A, tipoelem E);

/**
 * Comprueba si el elemento <E> existe en el arbol <A>
 * Devuelve el tipo de componente
 * @param A
 * @param E
 */
int verComponente(abb A, tipoelem E);

/**
 * Busca un nodo con clave <cl> en el arbol y, si existe
 * modifica el puntero <nodo> para que lo apunte.
 * @param A Arbol binario en el que se busca el nodo.
 * @param cl Clave que se buscara.
 * @param nodo Puntero a un tipoelem.
 */
void buscar_nodo(abb A, tipoclave cl, int *nodo);

//FUNCIONES DE MODIFICACIÓN
/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * del que toma su clave. Esta clave no debe existir en
 * el arbol.
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo.
 */
void insertarVarConst(abb *A, tipoelem E);
/**
 * Modifica un nodo del tipo variable.
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo.
 */
void actualizarVariable(abb *A, tipoelem E);
/**
 * Inserta un nuevo nodo en el arbol para el elemento E
 * del que toma su clave. Esta clave no debe existir en
 * el arbol.
 * @param A Arbol binario
 * @param E Informacion del nuevo nodo.
 */
void insertarFuncion(abb *A, tipoelem E);

/**
 * Funciones que recuperan los datos del arbol
 * @param A Arbol binario
 * @param E Tipoelem que se quiere recuperar
 */

float recuperarValor(abb *A, tipoelem E);
void recuperarFuncion(abb *A, tipoelem *E);

/*Función que ejecuta una función*/
float ejecutaFuncion(abb *A, tipoelem *E, float valor);
float ejecutaFuncion2(abb *A, tipoelem *E, float valor1, float valor2);

/**
 * Suprime el nodo del arbol <A>
 * @param A
 * @param E
 */
void suprimir(abb *A,tipoelem E);

/**
 * Suprime todos los nodos del tipo VARIABLE <A>
 * @param A
 * @param E
 */
void eliminarNodosVariables(abb *A);

/**
 * Imprime todos los elementos del arbol
 * @param A
 */
void imprimirArbol(abb *A);
/**
 * Imprime las variables del arbol
 * @param A
 */
void imprimirVariables(abb *A);

#endif	// ABB_H

