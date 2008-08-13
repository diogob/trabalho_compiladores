#include <stdio.h>
#include <stdlib.h>

#include "symbol_table.h"

int main(int argc, char** argv)
{
	symbol_t tab = NULL;
	printf("Testando init_table:");
	init_table(&tab);
	if(tab != NULL)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	return 0;
}
