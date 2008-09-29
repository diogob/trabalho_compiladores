#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "symbol_table.h"

int main(int argc, char** argv)
{
	symbol_t tab = NULL;
	entry_t* e = NULL;
	entry_t teste, teste2, teste3, teste4;
	int status;
	FILE *out;
    
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

	// Esse insert deve funcionar
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

	// Esse insert deve funcionar
	printf("Testando insert2:");
	teste3.name = malloc(sizeof(char) * 6);
	strcpy((teste3.name), "teste1");
	status = insert(&tab, &teste3);
	if(!status)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	// Esse insert deve falhar pois temos itens duplicados
	printf("Testando insert2 duplicado:");
	teste4.name = malloc(sizeof(char) * 6);
	strcpy((teste4.name), "teste1");
	status = insert(&tab, &teste4);
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

	// Devem existir dois itens na tabela
	printf("Testando print_table:");
	status = print_table(tab);
	if(status == 2)
		printf(" OK\n");
	else
		printf(" ERROR\n");

    if ((out = fopen("/tmp/teste.txt", "w"))) 
    {
		// Devem existir dois itens na tabela
		printf("Testando print_file_table:");
        status = print_file_table(out, tab);
		if(status == 2)
			printf(" OK\n");
		else
			printf(" ERROR\n");

        fclose(out);
    }

	printf("Testando free_table:");
	free_table(&tab);
	status = print_table(tab);
	if(status == 0)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	return 0;
		
}
