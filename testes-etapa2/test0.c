/**  casos triviais */
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
   yyin = fopen("test0-input.txt", "r");
   token=yylex();
   if (token != INT) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != DOUBLE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != FLOAT) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != CHAR) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != QUOTE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != DQUOTE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != LE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != GE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != EQ) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != NE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != AND) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != OR) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != NOT) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != IF) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != THEN) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != ELSE) {
      printf("ERROR.\n");
      okay = 0;
   }
   token=yylex();
   if (token != WHILE) {
      printf("ERROR.\n");
      okay = 0;
   }
   if (okay) printf("OKAY.");
   return(0);
}
