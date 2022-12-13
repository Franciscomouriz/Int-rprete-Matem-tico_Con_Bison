#include <string.h>
#include "flex.yy.h"
#include "TablaDeSimbolos.h"
#include "Errores.h"
#include "bison.tab.h"


void _liberarMemoria(){
    borrarTablaSimbolos();
}

void _iniciarInterprete(){
    inicializarTablaSimbolos();
    imprimirTablaSimbolos();
    /* Se inicializa el analizador sintáctico */
    yyparse();
    imprimirTablaSimbolos();
}

void _finalizarInterprete(){
    cerrarArchivo();
    _liberarMemoria();
}

int main(int argc, char *argv[]) {
    /* Se inicializa la estructura de datos */
    //Si hay parámetro por línea de comandos abre el archivo
    if(argc > 2){
        imprimir_error("Error: No se aceptan tantos argumentos");
        return 1;
    }
    else if(argc == 2){
        /* Si el argumento es -h o --help, muestra la ayuda */
        if(strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--help") == 0){
            imprimir_ayuda();
        }
        else{
            abrirArchivo(argv[1]);
            //abrirArchivo("../concurrentSum.go");
        }
    }
    _iniciarInterprete();

    /* Se cierra el programa y se libera memoria*/
    _finalizarInterprete();
    return 0;
}
