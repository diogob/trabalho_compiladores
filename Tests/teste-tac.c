#include <stdio.h>
#include <stdlib.h>

#include "tokens.h"
#include "tac_list.h"

int main(int argc, char** argv)
{
	tac_list l = NULL;
	tac_list l2 = NULL;
	tac_list l3 = NULL;

	tac_list lasti = NULL;
	tac_instruction tac1;
	tac_instruction tac2;
	tac_instruction tac3;
	tac_instruction tac4;

	tac_instruction tac5;
	tac_instruction tac6;
	tac_instruction tac7;
	tac_instruction tac8;

	printf("ADD: %i DIV: %i", ADD, DIV);
	tac1.op = ADD;
	tac1.arg1 = 2;
	tac1.arg2 = 3;
	tac1.res = 4;

	tac2.op = DIV;
	tac2.arg1 = 6;
	tac2.arg2 = 7;
	tac2.res = 8;

	tac3.op = LABEL;
	tac3.arg1 = 0;
	tac3.arg2 = 0;
	tac3.res = 0;
	tac3.literal1 = (char *) malloc(10);
	sprintf(tac3.literal1, "TESTE");

	tac4.op = GOTO;
	tac4.arg1 = 0;
	tac4.arg2 = 0;
	tac4.res = 0;
	tac4.literal1 = (char *) malloc(10);
	sprintf(tac4.literal1, "TESTE");

	tac5.op = EQ;
	tac5.arg1 = -1;
	tac5.arg2 = 2;
	tac5.literal3 = (char *) malloc(10);
	sprintf(tac5.literal3, "TESTE");

	tac6.op = NE;
	tac6.arg1 = 3;
	tac6.arg2 = 0;
	tac6.literal2 = (char *) malloc(10);
	sprintf(tac6.literal2, "34");
	tac6.literal3 = (char *) malloc(10);
	sprintf(tac6.literal3, "TESTE");

	tac7.op = '>';
	tac7.arg1 = 0;
	tac7.arg2 = 2;
	tac7.literal1 = (char *) malloc(10);
	sprintf(tac7.literal1, "34");
	tac7.literal3 = (char *) malloc(10);
	sprintf(tac7.literal3, "TESTE");

	tac8.op = GE;
	tac8.arg1 = 0;
	tac8.arg2 = 0;
	tac8.literal1 = (char *) malloc(10);
	sprintf(tac8.literal1, "31");
	tac8.literal2 = (char *) malloc(10);
	sprintf(tac8.literal2, "32");
	tac8.literal3 = (char *) malloc(10);
	sprintf(tac8.literal3, "TESTE");

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
	if(((int) l->tac->op) == ADD && ((int) l->tac->arg1) == 2 && ((int) l->tac->arg2) == 3 && ((int) l->tac->res) == 4 && !empty_list(l))
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

	append(l3, &tac3);
	append(l3, &tac4);
	append(l3, &tac5);
	append(l3, &tac6);
	append(l3, &tac7);
	append(l3, &tac8);

	print_tac(l3);
	return 0;
}
