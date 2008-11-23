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
	stack idents = NULL;
	/*
	Comeamos a contar o deslocamento a partir de 1 para SP
	e a partir de -1 para Rx
	0 eh reservado para indicar que o argumento nao foi passado
	na impressao subtraimos um do endereco para obter zero
	*/
	int deslocamento = 1;
	int desloc_temp = -1;
	int proximo_rotulo = 0;
	tac_list codigo_tac = NULL;

	char* gera_rotulo()
	{
		char* rotulo = malloc(10 * sizeof(char));
		sprintf(rotulo, "Label%03i", proximo_rotulo++);
		return rotulo;
	}

	tac_list gera_if( int op, int arg1, int arg2, char* literal1, char* literal2, char* literal3)
	{
		tac_list new;
		tac_instruction* taci;
		init_list(&new);
		taci = malloc(sizeof(tac_instruction));
		taci->op = op;
		taci->arg1 = arg1;
		taci->arg2 = arg2;
		taci->res = 0;
		taci->literal1 = literal1;
		taci->literal2 = literal2;
		taci->literal3 = literal3;
		append(new, taci);
		return new;
	}
	
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
		return -1;
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

// Marcedores para deferenciar ponteiros a direita (RDEF) e a esquerda (LDEF) de uma atribuicao
%token RDEF
%token LDEF

// Operadores extra
%token GOTO
%token LABEL

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
		void* stable_e;
		char* labelt;
		char* labelf;
	} einfo;
	char* double_val;
}

%type<name> ident
%type<name> IDF
%type<tinfo> types
%type<tinfo> type_array
%type<linfo> INT_LIT
%type<linfo> F_LIT
%type<einfo> lvalue
%type<einfo> expr
%type<einfo> expr_list
%type<einfo> expr_list2
%type<einfo> bool_expr
%type<einfo> proc_call
%type<einfo> action
%type<einfo> attr
%type<einfo> command
%type<einfo> simple_enun
%type<einfo> control_instr
%type<einfo> if_expr
%type<einfo> while_expr
%%

/* area de definicao de gramatica */

code:			decls action 
					{
						codigo_tac = $2.codigo;
					}
					| action
					{
						codigo_tac = $1.codigo;
					}
				;

decls: 			decl 
					| decls ';' decl
				;	


/*----Declarations----*/

decl:			ident types {
								entry_t *idf;
								char* id;								
								while(1)
								{
									id = (char*) pop(&idents);
									if(id == NULL)
										break;
									idf = malloc(sizeof(entry_t));
									idf->name = malloc(sizeof(char) * (strlen(id) + 1));
									strcpy(idf->name, id);
									idf->type = $2.type;
									idf->size = get_size($2.type) * ($2.size ? $2.size : 1);
									idf->desloc = deslocamento;
									deslocamento += idf->size;
								
									if($2.extra != NULL)
									{
										idf->extra = $2.extra;
									}
									insert(&stable, idf);
								}
							}

ident:			IDF ',' ident
				{
					push(&idents, $1);
				}
				| IDF ':'
				{
					push(&idents, $1);
				}
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
					{
						$$.codigo = $1.codigo;
					}
					| command ';' action
					{
						$$.codigo = concat_tac($1.codigo, $3.codigo);
					}
					| simple_enun action
					{
						$$.codigo = concat_tac($1.codigo, $2.codigo);
					}
				;
		
command:		attr 
						{
							$$.codigo = $1.codigo;
						}
						| simple_enun
						{
							$$.codigo = $1.codigo;
						}
				;
		
attr:			lvalue '=' expr
				{
					tac_list cod_gerado;
					if($1.stable_e == NULL && $3.stable_e == NULL)
						cod_gerado = gera_codigo(0, $3.desloc, 0, $1.desloc, $3.literal, NULL);
					else
						cod_gerado = gera_codigo(LDEF, $1.desloc, $3.desloc, ((entry_t*) $1.stable_e)->desloc, NULL, $3.literal);
					$$.codigo = concat_tac($1.codigo, concat_tac($3.codigo, cod_gerado));
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
					$$.type = idf->type;
					$$.desloc = idf->desloc;
					$$.stable_e = NULL;
				}
				| expr_list ']' 
				{
					int tmp = gera_temp(INT);
					char* num_w = (char*) malloc(sizeof(char) * 6);

					$$.desloc = gera_temp(INT);
					$$.type = $1.type;
					$$.stable_e = $1.stable_e;
					sprintf(num_w, "%i", get_size(((entry_t*) $1.stable_e)->type));
					$$.codigo = concat_tac($1.codigo,
											concat_tac(gera_codigo(MUL, $1.desloc, 0, tmp, $1.literal, num_w), 
												gera_codigo(ADD, ((entry_t*) $1.stable_e)->desloc, tmp, $$.desloc, $1.literal, NULL)));
				}
				;
		
expr_list:		expr_list ',' expr
					{
						int tmp = gera_temp(INT);
						int dim = $1.ndim + 1;
						char* num = (char*) malloc(sizeof(char) * 6);
						sprintf(num, "%i", len_dim((stack) ((entry_t*) $1.stable_e)->extra, dim));
						$$.codigo = concat_tac($3.codigo,
											concat_tac(gera_codigo(MUL, $1.desloc, 0, tmp, $1.literal, num),
																	gera_codigo(ADD, tmp, $3.desloc, tmp, NULL, $3.literal)));
						$$.stable_e = $1.stable_e;
						$$.desloc = tmp;
						$$.ndim = dim;
						if($3.type != INT)
						{
							DISPARA_TYPE_MISMATCH()
						}
					}
					| IDF '[' expr
					{
						tac_list cod_gerado = NULL;
						entry_t *idf = NULL;
						idf = lookup(stable, $1);
						if( idf == NULL )
						{
							DISPARA_UNDEFINED_SYMBOL($1)
						}
						$$.stable_e = (void*) idf;
						$$.desloc = $3.desloc;
						$$.literal = $3.literal;
						$$.ndim = 1;
						$$.type = idf->type;
						if($3.type != INT)
						{
							DISPARA_TYPE_MISMATCH()
						}
						$$.codigo = $3.codigo;
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
					$$.literal = $2.literal;
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
					tac_list cod_gerado = NULL;
					$$.type = $1.type;
					$$.desloc = $1.desloc;
					if($1.stable_e != NULL)
					{
						cod_gerado = gera_codigo(RDEF, $1.desloc, ((entry_t*) $1.stable_e)->desloc, $1.desloc, NULL, NULL);
						$$.codigo = cod_gerado;
					}
					$$.stable_e = NULL;
				}
				| proc_call
				{
					$$.codigo = $1.codigo;
				}
				;

proc_call:		IDF OPEN_PAR expr_list2
					{
						if(!strcmp($1, "print"))
						{
							int var_print = $3.desloc;
							if($3.stable_e != NULL)
							{
								var_print = gera_temp($3.type);
								$$.codigo = gera_codigo(RDEF, $3.desloc, ((entry_t*) $3.stable_e)->desloc, var_print, NULL, NULL);
							}
							if($3.type == FLOAT || $3.type == DOUBLE)
							{
								$$.codigo = gera_codigo(FPRINT, var_print, 0, 0, NULL, NULL);
							}
							else if($3.type == INT)
							{
								$$.codigo = gera_codigo(PRINT, var_print, 0, 0, NULL, NULL);
							}
							else
							{
								DISPARA_TYPE_MISMATCH()
							}
						}
					}
					;

expr_list2:		expr ',' expr_list2 
				{ 
					$$.type = $1.type;
					$$.desloc = $1.desloc;
					$$.stable_e = $1.stable_e;
				}
				| expr CLOSE_PAR 
				{ 
					$$.type = $1.type;
					$$.desloc = $1.desloc;
					$$.stable_e = $1.stable_e;
				}
				;
			
simple_enun:	expr
						{
							$$.codigo = $1.codigo;
						}
						| control_instr
						{
							$$.codigo = $1.codigo;
						}
				;
				
control_instr:	if_expr 
						{
							$$.codigo = $1.codigo;
						}
						| while_expr
						{
							$$.codigo = $1.codigo;
						}
				;
				
if_expr:		IF OPEN_PAR bool_expr CLOSE_PAR THEN action if_end
					{
						$3.labelt = gera_rotulo();
						$$.codigo = concat_tac($3.codigo, gera_codigo(LABEL, 0, 0, 0, $3.labelt, NULL));
					};

if_end:			ELSE action END 
					| END
				;
				
while_expr:		WHILE OPEN_PAR bool_expr CLOSE_PAR '{' action '}'
				;

bool_expr:	TRUE 
					{
						$$.codigo = gera_codigo(GOTO, 0, 0, 0, $$.labelt, NULL);
					}
					| FALSE 
					{
						$$.codigo = gera_codigo(GOTO, 0, 0, 0, $$.labelf, NULL);
					}
					| OPEN_PAR bool_expr CLOSE_PAR 
					{
						$$.codigo = $2.codigo;
					}
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
	init_stack(&idents);

	if (!yyparse())
	{
		/*
		Subtraimos 1 do deslocamento pois ele deve comecar no endereco 0
		No delocamento dos temporarios subtraimos 1 do valor absoluto, pois estavamos contando numeros negativos
		*/

		printf("%i\n", deslocamento - 1);
		printf("%i\n", abs(desloc_temp) - 1);
		print_tac(codigo_tac);
//		debug_tac(codigo_tac);
	}
	return(0);

}

yyerror(char* s) {
  fprintf(stderr, "%s: %s", progname, s);
  fprintf(stderr, "line %d\n", lineno);
}

