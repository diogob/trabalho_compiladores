 /* Secao das declaracoes */

%option noyywrap
  /* Sera copiado no .c final */
%{
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
{branco}+				{ return( BRANCO ); }
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
		case OPEN_PAR:
			strcpy(buffer, "OPEN_PAR");
			break;
		case CLOSE_PAR:
			strcpy(buffer, "CLOSE_PAR");
			break;
		case MUL: 		
			strcpy(buffer, "MUL");
			break;
		case ADD: 		
			strcpy(buffer, "ADD");
			break;
		case SUB: 		
			strcpy(buffer, "SUB");
			break;
		case DIV: 		
			strcpy(buffer, "DIV");
			break;
		case BRANCO: 		
			strcpy(buffer, "BRANCO");
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
	int token;
	char buff[10];
	init_table(&stable);
	yyin = stdin;
	if (!yyin) 
	{
		printf("Uso: %s <input_file>. Could not find %s. Try again!\n", 
		argv[0], argv[1]);
		exit(-1);
	}
	while ((token=yylex())) 
	{
		get_token_name(token, buff);
		printf("  %s: %s\n", buff, yytext);
	}
	print_table(stable);
	return(0);
}

