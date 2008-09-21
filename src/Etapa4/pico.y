%{
  /* Aqui, pode-se inserir qualquer codigo C necessario ah compilacao
   * final do parser. Sera copiado tal como esta no inicio do y.tab.c
   * gerado por Yacc.
   */
  #include <stdio.h>
%}

%token IDF
 /* A completar com seus tokens - compilar com 'yacc -d' */

%%
code: declaracoes acoes

declaracoes:

acoes: comando
    | comando ';' acoes
    ;

comando:

%%
 /* A partir daqui, insere-se qlqer codigo C necessario.
  */
#include "lex.yy.c"   /* Para poder usar o scanner */

char* progname;
int lineno;

int main(int argc, char* argv[]) {
   progname = argv[0];
   if (!yyparse()) 
      printf("OKAY.\n");
   else 
      printf("ERROR.\n");
   return(0);
}

yyerror(char* s) {
  fprintf(stderr, "%s: %s", progname, s);
  fprintf(stderr, "line %d\n", lineno);
}
