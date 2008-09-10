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
void get_token_name(int token, char *buffer)
{
	strcpy(buffer, "\0");
	switch(token)
	{
		case IDF:
			strcpy(buffer, "IDF");
			break;
		case INT:
			strcpy(buffer, "INT");
			break;
		case DOUBLE:
			strcpy(buffer, "DOUBLE");
			break;
		case FLOAT:
			strcpy(buffer, "FLOAT");
			break;
		case CHAR:
			strcpy(buffer, "CHAR");
			break;
		case QUOTE:
			strcpy(buffer, "QUOTE");
			break;
		case DQUOTE:
			strcpy(buffer, "DQUOTE");
			break;
		case LE:
			strcpy(buffer, "LE");
			break;
		case GE:
			strcpy(buffer, "GE");
			break;
		case EQ:
			strcpy(buffer, "EQ");
			break;
		case NE:
			strcpy(buffer, "NE");
			break;
		case AND:
			strcpy(buffer, "AND");
			break;
		case OR:
			strcpy(buffer, "OR");
			break;
		case NOT:
			strcpy(buffer, "NOT");
			break;
		case IF:
			strcpy(buffer, "IF");
			break;
		case THEN:
			strcpy(buffer, "THEN");
			break;
		case ELSE:
			strcpy(buffer, "ELSE");
			break;
		case WHILE:
			strcpy(buffer, "WHILE");
			break;
		case INT_LIT:
			strcpy(buffer, "INT_LIT");
			break;
		case F_LIT:
			strcpy(buffer, "F_LIT");
			break;
		default:
			buffer[0] = token;
			buffer[1] = '\0';
			break;
	}
}
/* Para redefinir a entrada padrao do LEX. */
extern FILE *yyin;

int main(int argc, char* argv[])
{
	const int E = -1, X = -2, START = E, TVAZIO = VAZIO, TOPEN_PAR = OPEN_PAR, TCLOSE_PAR = CLOSE_PAR, TMUL = MUL, TADD = ADD, TSUB = SUB, TDIV = DIV, TF_LIT = F_LIT, TIDF = IDF, TINT_LIT = INT_LIT;
	int* simbolo = NULL;
	int tabela[2][11] = {{1, 0, 0, 0, 0, 0, 4, 2, 3, 0},{0, TVAZIO, 7, 5, 6, 8, 0, 0, 0, TVAZIO}};
	stack pilha;

	int token, producao;
	char buff[10];
	init_table(&stable);
	yyin = fopen(argv[1], "r");
	if (!yyin) 
	{
		printf("Uso: %s <input_file>. Could not find %s. Try again!\n", 
		argv[0], argv[1]);
		exit(-1);
	}
	
	printf("Iniciando dados.\n");
	init_stack(&pilha);
	printf("Push.\n");
	push(&pilha, (void *) &START);
	printf("Le o primeiro token.\n");
	token = yylex();
	if(token)
	{
		while(!empty(pilha))
		{
			simbolo = (int *) pop(&pilha);
			printf("Desempilhando: %i\n", *simbolo);
			if(*simbolo == E || *simbolo == X)
			{
				producao = tabela[(abs(*simbolo) - 1)][(token - 1)];
				printf("tabela[%i][%i] = %i\n", (abs(*simbolo) - 1), (token - 1), producao);
				if(producao)
				{
					printf("Empilha producao %i\n", producao);
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
					// empilha cada_elemento_da_producao
				}
				else
				{
					printf("Erro sintatico 1.");
					exit(-1);
				}
			}
			else
			{
				if(*simbolo == token)
				{
					token = yylex();
					if(!token)
					{
						// Sinaliza o fim do arquivo
						token = TEOF;
					}
				}
				else
				{
					printf("Erro sintatico 2.");
					exit(-1);
				}
			}
		}
	}
	else
	{
		printf("Entrada vazia.\n");
	}
	if(!yylex())
	{
		printf("Aceita.\n");
	}

	/*
	while ((token=yylex())) 
	{
		get_token_name(token, buff);
		printf("  %s: %s\n", buff, yytext);
	}
	print_table(stable);
	*/
	return(0);
}

