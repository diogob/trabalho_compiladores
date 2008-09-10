#include "pico.c"
#include "stack.h"

/*
	Definicao de simbolos nao terminais
*/

int
main (int argc, char* argv[])
{
/*
const START = E
const CONJ_NAO_TERMINAIS = [ E, X ]
var pilha
var entrada[]
var index_entrada=0

empilha START; // produção start
while simbolo=pilha.POP()
{
	se simbolo in CONJ_NAO_TERMINAIS
	{
		// mapear os simbolos para nums? eg: tabela[ simbolo_da_linha, simbolo_da_coluna ]
		se tabela[ simbolo, entrada[index_entrada] ] != vazio
		{
			producao = tabela[ simbolo, entrada[index_entrada] ]
			empilha cada_elemento_da_producao // se produção for "(E)X", '(' é o elemento que fica no topo da pilha
		}else{
			"ERRO"
			break
		}
	}else{
		se (simbolo == entrada)
		{
			index_entrada++; // casa simbolo
		}else{
			"ERRO"
			break
		}
	}
}

if entrada[index_entrada]==vazio "ACEITA"

*/
	const int E = -1, X = -2, START = E;
	int* simbolo = NULL;
	int token = 0;
	int tabela[2][11] = {{0, 1, 0, 0, 0, 0, 0, 4, 2, 3, 0},{9, 0, 0, 7, 5, 6, 8, 0, 0, 0, 0}};
	stack pilha;
	yyin = fopen(argv[1], "r");
	if (!yyin) 
	{
		printf("Uso: %s <input_file>. Could not find %s. Try again!\n", argv[0], argv[1]);
		exit(-1);
	}

	init_stack(&pilha);
	push(&pilha, (void *) &START);
	token = yylex();
	if(token)
	{
		while(!empty(pilha))
		{
			simbolo = (int *) pop(&pilha);
			printf("Desempilhando: %i\n", *simbolo);
			if(*simbolo == E || *simbolo == X)
			{
				if(!tabela[(abs(*simbolo) - 1)][(token - 1)])
				{
					printf("Empilha %i\n", tabela[(abs(*simbolo) - 1)][(token - 1)]);
					// empilha cada_elemento_da_producao
				}
				else
				{
					printf("Erro sintatico.");
					exit(-1);
				}
			}
			else
			{
				if(*simbolo == token)
				{
					token = yylex();
				}
				else
				{
					printf("Erro sintatico.");
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
	while(*(simbolo = (int *) pop(&pilha)))
	{
		printf("Desempilhando: %i", *simbolo);
	}
	*/
	return 0;
}
