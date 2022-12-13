/*Declaraciones en C*/
%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "TablaDeSimbolos.h"
#include "Definiciones.h"
#include "flex.yy.h"
#include "Errores.h"

extern int yylex();
void yyerror(char* s);
void imprimir_ayuda();
%}

/*Declaraciones en Bison*/

%union {
    float valor;
    char *lex;
}

%token <valor> NUM  //Numero simple
%token <lex> VARIABLE //Identificador
%token <lex> ARCHIVO //Archivo que se lee con LOAD

%destructor{free($$);}<lex>

%token HELP
%token CLEAN
%token LOAD
%token WORKSPACE

%type <valor> exp 
%type <valor> comparacion 

%right OPERATOR_ASIG
%left '-' '+' OPERATOR_SUMA_CMPX OPERATOR_RESTA_CMPX OPERATOR_SUMA_DOS OPERATOR_RESTA_DOS
%left '*' '/' OPERATOR_MULT_CMPX OPERATOR_DIV_CMPX
%left '%'

%start input

%%

input: 
    linea
    | input linea
    ;

linea:
    '\n'
    | exp '\n'                      {if(!isnan($1))
                                        printf("\x1b[33m""%.2f\n""\033[0m", $1);}
    | exp ';' '\n'                  {printf("\n");}
    | comparacion '\n'              {if(!isnan($1)) printf("\n");}
    | HELP '\n'                     {imprimir_ayuda();}
    | CLEAN '\n'                    {eliminarVariables();}
    | LOAD ARCHIVO '\n'             {abrirArchivo($2); free($2);}
    | WORKSPACE '\n'                {imprimirEspacioTrabajo();}
    | error                         {yyerror("Error de sintaxis");}
    ;

exp:
    NUM                             {$$ = $1;}
    | VARIABLE                      {   if (esMiembro($1, _VARIABLE) || esMiembro($1, _CONSTANTE)){
                                            $$ = obtenerValor($1);
                                        }
                                        else{
                                            $$ = NAN;
                                            yyerror("Error: Variable no declarada");
                                        }
                                        free($1);
                                    }
    | '(' exp ')'                   {$$ = $2;}
    | '-' exp                       {$$ = -$2;}
    | VARIABLE OPERATOR_ASIG exp    
            {
                if(!isnan($3)){
                    if(componenteMiembro($1) != _CONSTANTE && componenteMiembro($1) != _FUNCION){
                        insertarElemento($1, $3);
                        free($1);
                        $$ = $3;
                    }
                    else{
                        $$ = NAN;
                        yyerror("Error: No se puede modificar el valor de una constante");
                    }
                }
                else{
                    $$ = NAN;
                    yyerror("Error: No se puede asignar un valor nulo");
                }
            }
    | NUM OPERATOR_ASIG exp
            {
                $$ = NAN;
                yyerror("Error: No se puede asignar valor a un numero");
            }
    | VARIABLE OPERATOR_SUMA_CMPX exp
            {
                if(componenteMiembro($1) == _VARIABLE){
                    $$ = obtenerValor($1) + $3;
                    insertarElemento($1, $$);
                    free($1);
                }
                else if(componenteMiembro($1) == _CONSTANTE){
                    $$ = NAN;
		            yyerror("Error: No se puede modificar el valor de una constante");
		        }
                else{
                    $$ = NAN;
                    yyerror("Error: Todavía no se declaró la variable");
                }
            }
    | VARIABLE OPERATOR_SUMA_DOS
            {
                if(componenteMiembro($1) == _VARIABLE){
                    $$ = obtenerValor($1) + 1;
                    insertarElemento($1, $$);
                    free($1);
                }
                else if(componenteMiembro($1) == _CONSTANTE){
                    $$ = NAN;
                    yyerror("Error: No se puede modificar el valor de una constante");
                }
                else{
                    $$ = NAN;
                    yyerror("Error: Todavía no se declaró la variable");
                }
            }
    | VARIABLE OPERATOR_RESTA_CMPX exp
            {
                if(componenteMiembro($1) == _VARIABLE){
                    $$ = obtenerValor($1) - $3;
                    insertarElemento($1, $$);
                    free($1);
                }
                else if(componenteMiembro($1) == _CONSTANTE){
                    $$ = NAN;
                    yyerror("Error: No se puede modificar el valor de una constante");
               	}
                else{
                    $$ = NAN;
                    yyerror("Error: Todavía no se declaró la variable");
                }
            }
    | VARIABLE OPERATOR_RESTA_DOS
            {
                if(componenteMiembro($1) == _VARIABLE){
                    $$ = obtenerValor($1) - 1;
                    insertarElemento($1, $$);
                    free($1);
                }
                else if(componenteMiembro($1) == _CONSTANTE){
                    $$ = NAN;
                    yyerror("Error: No se puede modificar el valor de una constante");
                }
                else{
                    $$ = NAN;
                    yyerror("Error: Todavía no se declaró la variable");
                }
            }
    | VARIABLE OPERATOR_MULT_CMPX exp
            {
                if(componenteMiembro($1) == _VARIABLE){
                    $$ = obtenerValor($1) * $3;
                    insertarElemento($1, $$);
                    free($1);
                }
                else if(componenteMiembro($1) == _CONSTANTE){
                    $$ = NAN;
                    yyerror("Error: No se puede modificar el valor de una constante");
                }
                else{
                    $$ = NAN;
                    yyerror("Error: Todavía no se declaró la variable");
                }
            }
    | VARIABLE OPERATOR_DIV_CMPX exp
            {
                if(componenteMiembro($1) == _VARIABLE){
                    $$ = obtenerValor($1) / $3;
                    insertarElemento($1, $$);
                    free($1);
                }
                else if(componenteMiembro($1) == _CONSTANTE){
                    $$ = NAN;
		            yyerror("Error: No se puede modificar el valor de una constante");
		        }
                else{
                    $$ = NAN;
                    yyerror("Error: Todavía no se declaró la variable");
                }
            }
    | exp '+' exp
            {
                $$ = $1 + $3;
            }
    | exp '-' exp
            {
                $$ = $1 - $3;
            }
    | exp '*' exp
            {
                $$ = $1 * $3;
            }
    | exp '/' exp
            {   if($3 != 0){
                    $$ = $1 / $3;
                }
                else{
                    $$ = NAN;
                    yyerror("Error: Division por cero");
                }
                $$ = $1 / $3;
            }
    | exp '%' exp
            {
                $$ = (int)$1 % (int)$3;
            }
    | VARIABLE '(' exp ')'
		{   
			if(componenteMiembro($1) == _FUNCION){
				$$ = ejecutarFuncion($1, $3);
			}
			else{
                $$ = NAN;
				yyerror("Error: La función no está definida");
			}
            free($1);
		}
    
    | VARIABLE '(' exp ',' exp ')'
        {
            if(componenteMiembro($1) == _FUNCION){
                $$ = ejecutarFuncion2($1, $3, $5);
            }
            else{
                $$ = NAN;
                yyerror("Error: La función no está definida");
            }
            free($1);
        }        
    ;

comparacion:
    exp '>' exp
            {
                if($1 > $3){
                    printf("\tVerdadero\n");
                }
                else{
                    printf("\tFalso\n");
                }
            }
    | exp '<' exp
        {
            if($1 < $3){
                printf("\tVerdadero\n");
            }
            else{
                printf("\tFalso\n");
            }
        }
    ;

%%

void imprimir_ayuda(){
  FILE *fichero;
  if((fichero = fopen("Ayuda.txt", "r")) == NULL){
    imprimir_error("Error: No se pudo abrir el fichero de ayuda");
  }
  else{
    char c;
    while((c = fgetc(fichero)) != EOF){
      printf("%c", c);
    }
    printf("\n");
    fclose(fichero);
  }
}

void yyerror(char* s){
  imprimir_error(s);
}