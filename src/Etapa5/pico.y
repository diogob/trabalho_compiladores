%{
  /* Aqui, pode-se inserir qualquer codigo C necessario ah compilacao
   * final do parser. Sera copiado tal como esta no inicio do y.tab.c
   * gerado por Yacc.
   */
	#include <stdio.h>
	#include <stdlib.h>
	#include <string.h>

	/* este include eh importante... */
	#include "tokens.h"
	#include "symbol_table.h"
	/* Globais para valores de literais encontradas */
	int VAL_INT;
	double VAL_DOUBLE;
	symbol_t stable = NULL;

%}

%token IDF 
%token VAZIO 
%token OPEN_PAR
%token CLOSE_PAR
%token MUL
%token ADD
%token SUB
%token DIV
%token F_LIT
%token INT_LIT
%token DIG
%token OPCMP
%token INT
%token DOUBLE
%token FLOAT
%token CHAR
%token QUOTE
%token DQUOTE
%token LE
%token GE
%token EQ
%token NE
%token AND
%token OR
%token NOT
%token IF
%token THEN
%token ELSE
%token WHILE
%token BRANCO
%token END
%token TRUE
%token FALSE

%union {
   char* name;
}

%type<name> ident

%left ADD SUB
%left MUL DIV
%left OR
%left AND
%left NOT

 /* A completar com seus tokens - compilar com 'yacc -d' */

%%

/* area de definicao de gramatica */

code:			decls action |
				action
				;

decls: 			decl |
				decls ';' decl
				;	


/*----Declarations----*/

decl:			ident types {
								entry_t *idf;
								idf = malloc(sizeof(entry_t));
								idf->name = malloc(sizeof(char) * (strlen($1.name) + 1));
								strcpy(idf->name, $1.name);
								insert(&stable, idf);
								printf("DECL: %i", $1.name);
							}
		
ident:			IDF ',' ident |
				IDF ':'
				;
		
types:			type |
				type '[' type_array
				;
		
type:			INT |
				DOUBLE |
				FLOAT |
				CHAR
				;
		
type_array:		INT_LIT ':' INT_LIT ',' type_array |
				INT_LIT ':' INT_LIT ']'
				;

/*----END Declarations----*/		
			
/*----Actions----*/			
action:			command |
				command ';' action |
				simple_enun action 
				;
		
command:		attr |
				simple_enun
				;
		
attr:			lvalue '=' expr
				;

lvalue:			IDF |
				IDF '[' expr_list
				;
		
expr_list:		expr ',' expr_list |
				expr ']'
				;
			
expr:			expr ADD expr |
				expr SUB expr |
				expr MUL expr |
				expr DIV expr |
				OPEN_PAR expr CLOSE_PAR |
				INT_LIT |
				F_LIT |
				lvalue |
				proc_call
				;
		
proc_call:		IDF OPEN_PAR expr_list2
				;

expr_list2:		expr ',' expr_list2 |
				expr CLOSE_PAR
				;
			
simple_enun:	expr |
				control_instr
				;
				
control_instr:	if_expr |
				while_expr
				;
				
if_expr:		IF OPEN_PAR bool_expr CLOSE_PAR THEN action if_end
				;

if_end:			ELSE action END |
				END
				;
				
while_expr:		WHILE OPEN_PAR bool_expr CLOSE_PAR '{' action '}'
				;

bool_expr:		TRUE |
				FALSE |
				OPEN_PAR bool_expr CLOSE_PAR |
				bool_expr AND bool_expr |
				bool_expr OR bool_expr |
				expr '<' expr |
				expr '>' expr |
				expr LE expr |
				expr GE expr |
				expr EQ expr |
				expr NE expr |
				NOT bool_expr
				;

/*----END Actions----*/




%%
 /* A partir daqui, insere-se qlqer codigo C necessario.
  */
  #include "lex.yy.c"   /* Para poder usar o scanner */

char* progname;
int lineno;
int yydebug=0;

int main(int argc, char* argv[]) {
   progname = argv[0];

   init_table(&stable);

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

