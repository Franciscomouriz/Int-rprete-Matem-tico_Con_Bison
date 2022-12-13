%{
#include "TablaDeSimbolos.h"
#include "Errores.h"
#include "Definiciones.h"
#include "bison.tab.h"

void abrirArchivo(char* nombreArchivo);
void cerrarArchivo();
%}

/* Para contar las líneas. */
%option yylineno
%option noyywrap

/*Expresiones regulares del intérprete matemático*/

/*Caracteres*/
NEWLINE                 \n
UNICODE_LETTER          [A-Za-z]
UNICODE_DIGIT           [0-9]

/*Letras y dígitos*/
LETTER                  {UNICODE_LETTER}|_
DECIMAL_DIGIT           {UNICODE_DIGIT}
BINARY_DIGIT            [01]
OCTAL_DIGIT             [0-7]
HEX_DIGIT               [0-9a-fA-F]

/*Separadores*/
WHITESPACE              [ ]
HORIZONTAL_TAB          \t
CARRIAGE_RETURN         \r
SEPARATOR               ({WHITESPACE}|{HORIZONTAL_TAB}|{CARRIAGE_RETURN})+

SEMICOLON               ;
COLON                   ,

IDENTIFIER              {LETTER}({LETTER}|{UNICODE_DIGIT})*

ARCHIVE                 {IDENTIFIER}\..+

/*Operadores y puntuación*/
OPERATOR_PUNC           [+*/%^,.!><()-]|{SEMICOLON}|{COLON}
OPERATOR_ASIG           =
OPERATOR_SUMA_CMPX      \+=
OPERATOR_RESTA_CMPX     -=
OPERATOR_MULT_CMPX      \*=
OPERATOR_DIV_CMPX       \/=
OPERATOR_SUMA_DOS       \+\+
OPERATOR_RESTA_DOS      --

/*Enteros*/
DECIMAL_DIGITS          {DECIMAL_DIGIT}(_?{DECIMAL_DIGIT})*
INT_LIT                 0|([1-9]|(_?{DECIMAL_DIGITS})?)

/*Flotantes*/
DECIMAL_EXPONENT        [eE][+-]?{DECIMAL_DIGITS}
FLOAT_LIT               ({DECIMAL_DIGITS}\.{DECIMAL_DIGITS}?{DECIMAL_EXPONENT}?)|({DECIMAL_DIGITS}{DECIMAL_EXPONENT})|(\.{DECIMAL_DIGITS}{DECIMAL_EXPONENT}?)

/*Numero*/
NUM                     {INT_LIT}|{FLOAT_LIT}


%%

"QUIT"                    {yyterminate();}
"HELP"                    {return (HELP);}
"LOAD"                    {return (LOAD);}
"WORKSPACE"               {return (WORKSPACE);}
"CLEAN"                   {return (CLEAN);}

{IDENTIFIER}              {yylval.lex = strdup(yytext);
                            return (VARIABLE);}

{ARCHIVE}                 {yylval.lex = strdup(yytext);
                            return (ARCHIVO);}

{NUM}                     { yylval.valor = atof(yytext);
                            return (NUM);}
{SEPARATOR}
{NEWLINE}                 return ((int) *yytext);
{OPERATOR_PUNC}           return ((int) *yytext);
{OPERATOR_ASIG}           return (OPERATOR_ASIG);
{OPERATOR_SUMA_CMPX}      return (OPERATOR_SUMA_CMPX);
{OPERATOR_RESTA_CMPX}     return (OPERATOR_RESTA_CMPX);
{OPERATOR_MULT_CMPX}      return (OPERATOR_MULT_CMPX);
{OPERATOR_DIV_CMPX}       return (OPERATOR_DIV_CMPX);
{OPERATOR_SUMA_DOS}       return (OPERATOR_SUMA_DOS);
{OPERATOR_RESTA_DOS}      return (OPERATOR_RESTA_DOS);
.                         {error_lexico(yylineno);}
<<EOF>>                   {cerrarArchivo(); yyrestart(stdin);}

%%

void abrirArchivo(char* nombreArchivo){
    yyin = fopen(nombreArchivo, "r");
    if(yyin == NULL){
        imprimir_error("No se pudo abrir el archivo\n");
        yyin = stdin;
    }
}

void cerrarArchivo(){
    fclose(yyin);
}