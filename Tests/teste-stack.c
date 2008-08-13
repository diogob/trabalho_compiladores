#include <stdio.h>
#include <stdlib.h>

#include "stack.h"

int main(int argc, char** argv)
{
	stack pilha = NULL;
	int* item = (int *) malloc(sizeof(int));
	*item = 5;

	printf("Testando init_stack:");
	init_stack(&pilha);
	if(pilha != NULL)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando empty:");
	if(empty(pilha))
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando push:");
	push(&pilha, item);
	if(*((int *) pilha->next->element) == 5 && pilha->element == NULL && !empty(pilha))
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando top:");
	if( *((int *) top(pilha)) == 5 )
		printf(" OK\n");
	else
		printf(" ERROR\n");

	item = (int *) malloc(sizeof(int));
	*item = 10;
	push(&pilha, item);
	printf("Testando pop:");
	if( *((int *) pop(&pilha)) == 10 && !empty(pilha) && *((int *) pop(&pilha)) == 5 && pilha->element == NULL && empty(pilha))
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando freestack:");
	free_stack(&pilha);
	printf(" OK\n");

	return 0;
}
