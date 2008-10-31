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
	#include "array_data.h"
	
	/* Definicao de constantes de erros */
	#define UNDEFINED_SYMBOL_ERROR -21
	#define TYPE_MISMATCH_ERROR -20

	/* Definicao de macro com erro de type mismatch */
	#define DISPARA_TYPE_MISMATCH() printf("ERRO DE COMPATIBILIDADE DE TIPO. Quem te ensinou a programar?\n"); return TYPE_MISMATCH_ERROR;
	#define DISPARA_UNDEFINED_SYMBOL(varref) printf("UNDEFINED SYMBOL. A variavel %s nao foi declarada.\n", varref); return UNDEFINED_SYMBOL_ERROR;

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

	tac_list gera_codigo( int op, int arg1, int arg2, int res, char* literal1, char* literal2)
	{
		tac_list new;
		tac_instruction* taci;
		init_list(&new);
		taci = malloc(sizeof(tac_instruction));
		taci->op = op;
		taci->arg1 = arg1;
		taci->arg2 = arg2;
		taci->res = res;
		taci->literal1 = literal1;
		taci->literal2 = literal2;
		append(new, taci);
//		printf("APPEND: %i %i %i %i %s %s\n", taci->op, taci->arg1, taci->arg2, taci->res, taci->literal1, taci->literal2);
		return new;
	}

	int gera_codigo_aritmetico( int op, struct einfo* arg1, struct einfo* arg2, struct einfo* res)
	{

		tac_list cod_gerado;
		int fop;

		if(arg1->type == CHAR || arg2->type == CHAR)
			return -1;

		switch(op)
		{
			case ADD:
				fop = FADD;
				break;
			case SUB:
				fop = FSUB;
				break;
			case MUL:
				fop = FMUL;
				break;
			case DIV:
				fop = FDIV;
				break;
			// Nunca deve chegar no default (soh em caso de erro)
			default:
				fop = op;
		}

		if(arg1->type == INT && arg2->type == INT)
		{
			res->type = INT;
			res->desloc = gera_temp(INT);
			cod_gerado = gera_codigo(op, arg1->desloc, arg2->desloc, res->desloc, arg1->literal, arg2->literal);
		}
		else if(arg1->type == arg2->type)
		{
			res->type = (arg1->type == FLOAT ? FLOAT : DOUBLE);
			res->desloc = gera_temp(res->type);
			cod_gerado = gera_codigo(fop, arg1->desloc, arg2->desloc, res->desloc, arg1->literal, arg2->literal);
		}
		else
		{
			struct einfo* arg_upcast;
			struct einfo* arg;
			int upcast_tmp;
			
			/*
			Escolhemos o maior tipo envolvido para o tipo do resultado
			*/
			if(arg1->type == DOUBLE || arg2->type == DOUBLE)
				res->type = DOUBLE;
			else
				res->type = FLOAT;

			upcast_tmp = gera_temp(res->type);
			res->desloc = gera_temp(res->type);

			if((arg1->type == FLOAT && arg2->type == INT) || (arg1->type == DOUBLE))
			{
				arg = arg1;
				arg_upcast = arg2;
			}
			else
			{
				arg = arg2;
				arg_upcast = arg1;
			}
			cod_gerado = gera_codigo(0, arg_upcast->desloc, 0, upcast_tmp, arg_upcast->literal, NULL);
			cod_gerado = concat_tac(cod_gerado, gera_codigo(fop, arg->desloc, upcast_tmp, res->desloc, arg->literal, NULL));
		}
		res->codigo = (void*) concat_tac(concat_tac((tac_list) arg1->codigo, (tac_list) arg2->codigo), cod_gerado);
		
		return 0;
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
%token FMUL
%token FADD
%token FSUB
%token FDIV

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

%token PRINT
%token FPRINT

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
		void* extra;
	} tinfo;
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
		int ndim;
		void* ar;
	} einfo;
	char* double_val;
	void* stable_entry;
}

%type<name> ident
%type<name> IDF
%type<tinfo> types
%type<tinfo> type_array
%type<linfo> INT_LIT
%type<linfo> F_LIT
%type<stable_entry> lvalue
%type<einfo> expr
%type<einfo> expr_list
%type<einfo> expr_list2
%%

/* area de definicao de gramatica */

code:			decls action 
					| action
				;

decls: 			decl 
					| decls ';' decl
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
								
								if($2.extra != NULL)
								{
									/*
									printf("==== Inicio de decl de array. Dimensoes: %03i =====\n", count_dim((stack) $2.extra));
									print_array_data((stack) $2.extra);
									printf("=================== Fim de array ==================\n");
									*/
									idf->extra = $2.extra;
								}
								insert(&stable, idf);
								/*
								printf("Decl da var %s tipo: %i tamanho: %i desloc: %i el: %i\n", $1, $2.type, idf->size, idf->desloc, $2.size);
*/
							}
		
ident:			IDF ',' ident 
					| IDF ':'
				;

types:			type 
				{ 
					$$.size = 0;
					$$.extra = NULL;
				}
				| type '[' type_array 
				{
					$$.size = $3.size; 
					$$.extra = $3.extra;
				}
				;
		
type:		INT 
				| DOUBLE 
				| FLOAT 
				| CHAR
				;
		
type_array:		INT_LIT ':' INT_LIT ',' type_array
						{
							$$.size = ($3.int_val - $1.int_val) + 1 + $5.size;
							$$.extra = (void*) append_dim((stack*) &($5.extra), ($$.size - $5.size));
						}
						| INT_LIT ':' INT_LIT ']'
						{
							$$.size = ($3.int_val - $1.int_val) + 1;
							stack adata = NULL;
							append_dim(&adata, $$.size);
							$$.extra = (void*) adata;
							adata = NULL;
						}
						;

/*----END Declarations----*/		
			
/*----Actions----*/			
action:			command 
					| command ';' action 
					| simple_enun action 
				;
		
command:		attr 
						| simple_enun
				;
		
attr:			lvalue '=' expr
				{
					tac_list cod_gerado = gera_codigo(0, $3.desloc, 0, ((entry_t *) $1)->desloc, $3.literal, NULL);
					codigo_tac = concat_tac(codigo_tac, concat_tac($3.codigo, cod_gerado));
				}
				;

lvalue:		IDF 
				{
					entry_t *idf = NULL;
					idf = lookup(stable, $1);
					if( idf == NULL )
					{
						DISPARA_UNDEFINED_SYMBOL($1)
					}
					$$ = idf;
				}
				| expr_list ']' 
				{
				}
				;
		
expr_list:		expr_list ',' expr
					{
						if($3.type != INT)
						{
							DISPARA_TYPE_MISMATCH()
						}
					}
					| IDF '[' expr
					{
						entry_t *idf = NULL;
						idf = lookup(stable, $1);
						if( idf == NULL )
						{
							DISPARA_UNDEFINED_SYMBOL($1)
						}
						$$.ar = (void*) idf;
						$$.desloc = $3.desloc;
						$$.ndim = 1;

						if($3.type != INT)
						{
							DISPARA_TYPE_MISMATCH()
						}
					}
					;
			
expr:		expr ADD expr
				{
					if(gera_codigo_aritmetico(ADD, &$1, &$3, &$$) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
				| expr SUB expr 
				{
					if(gera_codigo_aritmetico(SUB, &$1, &$3, &$$) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
				| expr MUL expr
				{
					if(gera_codigo_aritmetico(MUL, &$1, &$3, &$$) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				} 
				| expr DIV expr
				{
					if(gera_codigo_aritmetico(DIV, &$1, &$3, &$$) < 0)
					{
						DISPARA_TYPE_MISMATCH()
					}
				}
				| OPEN_PAR expr CLOSE_PAR
				{
					$$.type = $2.type;
					$$.desloc = $2.desloc;
					$$.codigo = $2.codigo;
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
					{
						if(!strcmp($1, "print"))
						{
							if($3.type == FLOAT || $3.type == DOUBLE)
							{
								concat_tac(codigo_tac, gera_codigo(FPRINT, $3.desloc, 0, 0, NULL, NULL));
							}
							else if($3.type == INT)
							{
								concat_tac(codigo_tac, gera_codigo(PRINT, $3.desloc, 0, 0, NULL, NULL));
							}
							else
							{
								DISPARA_TYPE_MISMATCH()
							}
						}
					}
					;

expr_list2:		expr ',' expr_list2 { $$.type = $1.type; }
						| expr CLOSE_PAR { $$.type = $1.type; }
				;
			
simple_enun:	expr 
						| control_instr
				;
				
control_instr:	if_expr 
						| while_expr
				;
				
if_expr:		IF OPEN_PAR bool_expr CLOSE_PAR THEN action if_end
				;

if_end:			ELSE action END 
					| END
				;
				
while_expr:		WHILE OPEN_PAR bool_expr CLOSE_PAR '{' action '}'
				;

bool_expr:	TRUE 
					| FALSE 
					| OPEN_PAR bool_expr CLOSE_PAR 
					| bool_expr AND bool_expr 
					| bool_expr OR bool_expr 
					| expr '<' expr 
					| expr '>' expr 
					| expr LE expr 
					| expr GE expr 
					| expr EQ expr 
					| expr NE expr 
					| NOT bool_expr
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
	return(0);

}

yyerror(char* s) {
  fprintf(stderr, "%s: %s", progname, s);
  fprintf(stderr, "line %d\n", lineno);
}

