#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

int main(int argc, char** argv)
{
	symbol_t tab = NULL;
	entry_t* e = NULL;
	entry_t teste, teste2;
	int status;

	printf("Testando hashpjw:");
	if(hashpjw("teste") == 8047269 && hashpjw("teste1") == 128756353)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando init_table:");
	init_table(&tab);
	if(tab != NULL)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando lookup:");
	e = lookup(tab, (char *) "teste");
	if(e == NULL)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	// Esste insert deve funcionar
	printf("Testando insert:");
	teste.name = malloc(sizeof(char) * 5);
	strcpy((teste.name), "teste");
	status = insert(&tab, &teste);
	if(!status)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	// Esse insert deve falhar pois temos itens duplicados
	printf("Testando insert duplicado:");
	teste2.name = malloc(sizeof(char) * 5);
	strcpy((teste2.name), "teste");
	status = insert(&tab, &teste2);
	if(status)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	// Agora temos que encontrar
	printf("Testando lookup novamente:");
	e = lookup(tab, (char *) "teste");
	if(e == NULL)
		printf(" ERROR\n");
	else
		printf(" OK\n");

	return 0;
	
	
}
