 /* Secao das declaracoes */

%option noyywrap
  /* Sera copiado no .c final */
%{
    #include <stdlib.h>
    #include <string.h>
   
    /* este include eh importante... */
    #include "tokens.h"
	#include "symbol_table.h"
	#include "stack.h"
	/* Globais para valores de literais encontradas */
	int VAL_INT;
	double VAL_DOUBLE;
	symbol_t stable = NULL;
%}
 
  /* Definicoes regulares */
digito		[0-9]
letra		[A-Za-z]
alphanum	[A-Za-z0-9_]
branco		[ \t\n]
%%

 /* Secao das Regras de traducao */
 /* O que consta aqui eh puramente ilustrativo... 
  * Ver tambem "tokens.h" para a definicao de DIG e OPCMP
  */
"if"					{ return( IF ) ; }
"then"					{ return( THEN ) ; }
"else"					{ return( ELSE ) ; }
"while"					{ return( WHILE ) ; }
"int"		 			{ return( INT ); }
"double"		 		{ return( DOUBLE ); }
"float"			 		{ return( FLOAT ); }
"char"			 		{ return( CHAR ); }
{branco}+				{ }
"*"						{ return( MUL ) ; }
"+"						{ return( ADD ) ; }
"-"						{ return( SUB ) ; }
"/"						{ return( DIV ) ; }
","						{ return( ',' ) ; }
";"						{ return( ';' ) ; }
"'"						{ return( QUOTE ) ; }
"\""					{ return( DQUOTE ) ; }
"("						{ return( OPEN_PAR ) ; }
")"						{ return( CLOSE_PAR ) ; }
"["						{ return( '[' ) ; }
"]"						{ return( ']' ) ; }
"{"						{ return( '{' ) ; }
"}"						{ return( '}' ) ; }
"<"						{ return( '<' ) ; }
">"						{ return( '>' ) ; }
"="						{ return( '=' ) ; }
"<="					{ return( LE ) ; }
">="					{ return( GE ) ; }
"=="					{ return( EQ ) ; }
"!="					{ return( NE ) ; }
"&&"					{ return( AND ) ; }
"||"					{ return( OR ) ; }
"!"						{ return( NOT ) ; }
{letra}{alphanum}*		{
							entry_t *idf;
							idf = malloc(sizeof(entry_t));
							idf->name = malloc(sizeof(char) * (strlen(yytext) + 1));
							strcpy(idf->name, yytext);
							insert(&stable, idf);
							return( IDF ); 
						}
{digito}+				{ VAL_INT = (int)strtol(yytext, (char **)NULL, 10); return(INT_LIT); }
({digito}*\.{digito}+([Ee][+-]{digito}+)?)	{ VAL_DOUBLE = strtod(yytext, (char **)NULL); return(F_LIT); }
.                     	{ printf("Erro lexical - caractere nao reconhecido: %c.\n", yytext[0]); /* exit(-1); */ }

%%

 /* Secao dos  Procedimentos auxiliares  */

/* Para redefinir a entrada padrao do LEX. */
extern FILE *yyin;

int main(int argc, char* argv[])
{
	/*
	Criamos constantes para podermos usar ponteiros para os valores
	*/
	const int E = -1, X = -2, START = E, TVAZIO = VAZIO, TOPEN_PAR = OPEN_PAR, TCLOSE_PAR = CLOSE_PAR, TMUL = MUL, TADD = ADD, TSUB = SUB, TDIV = DIV, TF_LIT = F_LIT, TIDF = IDF, TINT_LIT = INT_LIT;
	int* simbolo = NULL;

	/*
	A tabela de parse LL1 foi codificada como um array bidimensional
	*/
	int tabela[2][11] = {{1, 0, 0, 0, 0, 0, 4, 2, 3, 0},{0, TVAZIO, 7, 5, 6, 8, 0, 0, 0, TVAZIO}};
	stack pilha;

	int token, producao;
	init_table(&stable);
	yyin = fopen(argv[1], "r");
	if (!yyin) 
	{
		printf("Uso: %s <input_file>. Could not find %s. Try again!\n", 
		argv[0], argv[1]);
		exit(-1);
	}
	
	//printf("Iniciando dados.\n");
	init_stack(&pilha);
	//printf("Push.\n");
	push(&pilha, (void *) &START);
	//printf("Le o primeiro token.\n");
	token = yylex();
	if(token)
	{
		while(!empty(pilha))
		{
			simbolo = (int *) pop(&pilha);
			//printf("Desempilhando: %i\n", *simbolo);
			/* Caso seja um simbolo nao terminal */
			if(*simbolo == E || *simbolo == X)
			{
				/* 
				Mapeamos o valor do simbolo e do token para enderecos no array 
				e buscamos a producao que tambem eh codificada com um inteiro
				*/
				producao = tabela[(abs(*simbolo) - 1)][(token - 1)];
				//printf("tabela[%i][%i] = %i\n", (abs(*simbolo) - 1), (token - 1), producao);
				if(producao)
				{
					//printf("Empilha producao %i\n", producao);
					/* empilha cada elemento da producao */
					switch(producao)
					{
					case 1:
						//) E -> ’(’ E ’)’ X
						push(&pilha, (void *) &X);
						push(&pilha, (void *) &TCLOSE_PAR);
						push(&pilha, (void *) &E);
						push(&pilha, (void *) &TOPEN_PAR);

						break;
					case 2:
						//) E -> IDF X
						push(&pilha, (void *) &X);
						push(&pilha, (void *) &TIDF);
						break;
					case 3:
						//) E -> INT_LIT X
						push(&pilha, (void *) &X);
						push(&pilha, (void *) &TINT_LIT);
						break;
					case 4:
						//) E -> F_LIT X
						push(&pilha, (void *) &X);
						push(&pilha, (void *) &TF_LIT);
						break;
					case 5:
						//) X -> ’+’ E
						push(&pilha, (void *) &E);
						push(&pilha, (void *) &TADD);
						break;
					case 6:
						//) X -> ’-’ E
						push(&pilha, (void *) &E);
						push(&pilha, (void *) &TSUB);
						break;
					case 7:
						//) X -> ’*’ E
						push(&pilha, (void *) &E);
						push(&pilha, (void *) &TMUL);
						break;
					case 8:
						//) X -> ’/’ E
						push(&pilha, (void *) &E);
						push(&pilha, (void *) &TDIV);
						break;
					case 9:
						//) X ->  &
						push(&pilha, (void *) &TVAZIO);
						break;
					}
				}
				else
				{
					printf("ERROR");
					exit(-1);
				}
			}
			else
			{
				/* Quando o simbolo da pilha foi lido da entrada avancamos a leitura */
				if(*simbolo == token)
				{
					token = yylex();
					if(!token)
					{
						/* Sinaliza o fim do arquivo quando o yylex nao encontrar nada */
						token = TEOF;
					}
				}
				else
				{
					printf("ERROR");
					exit(-1);
				}
			}
		}
	}
	else
	{
		printf("ERROR");
		exit(-1);
	}
	if(!yylex())
	{
		printf("OKAY");
	}
	return(0);
}

