#include <stdio.h>
#include <stdlib.h>

#include "tac_list.h"

int main(int argc, char** argv)
{
	tac_list l = NULL;
	tac_list l2 = NULL;
	tac_list l3 = NULL;

	tac_list lasti = NULL;
	tac_instruction tac1;
	tac_instruction tac2;
	
	tac1.op = 1;
	tac1.arg1 = 2;
	tac1.arg2 = 3;
	tac1.res = 4;

	tac2.op = 5;
	tac2.arg1 = 6;
	tac2.arg2 = 7;
	tac2.res = 8;

	printf("Testando init_list:");
	init_list(&l);
	if(l != NULL)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando empty_list:");
	if(empty_list(l))
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando last com lista vazia:");
	lasti = last(l);
	if(lasti == l)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando append:");
	append(l, &tac1);
	if(((int) l->tac->op) == 1 && ((int) l->tac->arg1) == 2 && ((int) l->tac->arg2) == 3 && ((int) l->tac->res) == 4 && !empty_list(l))
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando last com 2 elementos:");
	append(l, &tac2);
	lasti = last(l);
	if( lasti != NULL && lasti->tac == NULL )
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando concat (1,5,5,1):\n");
	init_list(&l2);
	append(l2, &tac2);
	append(l2, &tac1);
	concat_tac(l, l2);

	init_list(&l3);
	l3 = concat_tac(l3, l);
	for(lasti = l3; lasti->next != NULL; lasti = lasti->next)
		printf("Elemento: %i\n", lasti->tac->op);

	return 0;
}
