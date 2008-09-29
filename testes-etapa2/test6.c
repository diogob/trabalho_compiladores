/**  numeros com virgula, casos menos simples */
#include <stdio.h>
#include <stdlib.h>
#include "symbol_table.h"
#include "tokens.h"
symbol_t stable;
#include "pico.c"

int main(int argc, char** argv) {
   int token;

   int okay = 1;
   init_table( &stable );
   yyin = fopen("test6-input.txt", "r");
   token=yylex();
   if (token != F_LIT) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != F_LIT) {
      printf("ERROR.\n");
      okay = 0;
   }
   if (okay) printf("OKAY.");
   return(0);
}
