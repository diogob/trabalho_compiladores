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
	#include "tac_list.h"
	
	/* Globais para valores de literais encontradas */
	int VAL_INT;
	double VAL_DOUBLE;
	symbol_t stable = NULL;
	/*
	Comeamos a contar o deslocamento a partir de 1 para SP
	e a partir de -1 para Rx
	0 eh reservado para indicar que o argumento nao foi passado
	na impressao subtraimos um do endereco para obter zero
	*/
	int deslocamento = 1;
	int desloc_temp = -1;
	tac_list codigo_tac = NULL;

	tac_list gera_codigo( int op, int arg1, int arg2, int res, char* literal)
	{
		tac_list new;
		tac_instruction* taci;
		init_list(&new);
		taci = malloc(sizeof(tac_instruction));
		taci->op = op;
		taci->arg1 = arg1;
		taci->arg2 = arg2;
		taci->res = res;
		taci->literal = literal;
		append(new, taci);
		return new;
	}

	int gera_temp(int type)
	{
		int tmp = desloc_temp;
		desloc_temp -= get_size(type);
		return tmp;
	}

	int get_size(int type)
	{
		switch(type)
		{
			case INT:
				return 4;
				break;
			case DOUBLE:
				return 8;
				break;
			case FLOAT:
				return 4;
				break;
			case CHAR:
				return 1;
				break;
		}
	}

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

%left ADD SUB
%left MUL DIV
%left OR
%left AND
%left NOT

%union {
	char* name;
	struct tinfo{ 
		int type;
		int size;
	} tinfo;
	int nelements;
	struct linfo {
		char* text;
		int int_val;
		double double_val;
	} linfo;
	struct einfo {
		int type;
		int desloc;
		char* literal;
		void* codigo;
	} einfo;
	char* double_val;
	void* stable_entry;
}

%type<name> ident
%type<name> IDF
%type<tinfo> types
%type<nelements> type_array
%type<linfo> INT_LIT
%type<linfo> F_LIT
%type<stable_entry> lvalue
%type<einfo> expr
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
								idf->name = malloc(sizeof(char) * (strlen($1) + 1));
								strcpy(idf->name, $1);
								idf->type = $2.type;
								idf->size = get_size($2.type) * ($2.size ? $2.size : 1);
								idf->desloc = deslocamento;
								deslocamento += idf->size;
								insert(&stable, idf);
								printf("Decl da var %s tipo: %i tamanho: %i desloc: %i el: %i\n", $1, $2.type, idf->size, idf->desloc, $2.size);
							}
		
ident:			IDF ',' ident |
				IDF ':'
				;
		
types:			type { $$.size = 0; }
				| type '[' type_array { $$.size = $3; }
				;
		
type:			INT |
				DOUBLE |
				FLOAT |
				CHAR
				;
		
type_array:		INT_LIT ':' INT_LIT ',' type_array
				{
					$$ = $3.int_val - $1.int_val + $5;
				}
				| INT_LIT ':' INT_LIT ']'
				{
					$$ = $3.int_val - $1.int_val;
				}
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
				{
					codigo_tac = concat_tac(codigo_tac, concat_tac($3.codigo, gera_codigo('=', $3.desloc, 0, ((entry_t *) $1)->desloc, $3.literal)));
				}
				;

lvalue:			IDF {
						entry_t *idf = NULL;
						idf = lookup(stable, $1);
						if( idf == NULL )
						{
							printf("Erro de sintaxe. Variavel %s nao declarada.\n", $1);
							return -1;
						}
						$$ = idf;
					}
				| IDF '[' expr_list {
										
									}
				;
		
expr_list:		expr ',' expr_list |
				expr ']'
				;
			
expr:			expr ADD expr
				{
					if($1.type == CHAR || $3.type == CHAR)
					{
						printf("Erro de tipo. Tentativa de somar um char\n");
						return -1;
					}
					//printf("Gerando codigo para soma: %i = %i + %i");
					$$.desloc = gera_temp($1.type);
					$$.codigo = (void*) concat_tac(concat_tac((tac_list) $1.codigo, (tac_list) $3.codigo), gera_codigo(ADD, $1.desloc, $3.desloc, $$.desloc, NULL));
				}
				| expr SUB expr 
				{
					if($1.type == CHAR || $3.type == CHAR)
					{
						printf("Erro de tipo. Tentativa de subtrair um char\n");
						return -1;
					}
					$$.desloc = gera_temp($1.type);
				}
				| expr MUL expr
				{
					if($1.type == CHAR || $3.type == CHAR)
					{
						printf("Erro de tipo. Tentativa de multiplicar um char\n");
						return -1;
					}
					$$.desloc = gera_temp($1.type);
				} 
				| expr DIV expr
				{
					if($1.type == CHAR || $3.type == CHAR)
					{
						printf("Erro de tipo. Tentativa de dividir um char\n");
						return -1;
					}
					$$.desloc = gera_temp($1.type);
				} 
				| OPEN_PAR expr CLOSE_PAR
				{
					$$.type = $2.type;
					$$.desloc = $2.desloc;
				}
				| INT_LIT
				{
					$$.type = INT;
					$$.codigo = NULL;
					$$.literal = $1.text;
					$$.desloc = 0;
				}
				| F_LIT
				{
					$$.type = FLOAT;
					$$.codigo = NULL;
					$$.literal = $1.text;
					$$.desloc = 0;
				}
				| lvalue 
				{
					$$.type = ((entry_t *) $1)->type;
					$$.desloc = ((entry_t *) $1)->desloc;
				}
				| proc_call
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
	init_list(&codigo_tac);

	if (!yyparse())
	{
		/*
		Subtraimos 1 do deslocamento pois ele deve comecar no endereco 0
		No delocamento dos temporarios subtraimos 1 do valor absoluto, pois estavamos contando numeros negativos
		*/
		printf("%i\n", deslocamento - 1);
		printf("%i\n", abs(desloc_temp) - 1);
		print_tac(codigo_tac);
	}
	else 
		printf("ERROR.\n");

	return(0);
}

yyerror(char* s) {
  fprintf(stderr, "%s: %s", progname, s);
  fprintf(stderr, "line %d\n", lineno);
}

