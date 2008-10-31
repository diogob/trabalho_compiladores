#include <stdio.h>
#include <stdlib.h>

#include "array_data.h"

int main(int argc, char** argv)
{
	stack adata = NULL;
	int c1, c2, c3;

	printf("Testando append_dim:");
	append_dim(&adata, 7);
	if(adata != NULL && *((int*) adata->next->element) == 7)
		printf(" OK\n");
	else
		printf(" ERROR\n");

	printf("Testando count_dim:");
	c1 = count_dim(adata);
	append_dim(&adata, 112);
	c2 = count_dim(adata);

	if(c1 == 1 && c2 == 2)
		printf(" OK\n");
	else
		printf(" ERROR wrong count: c1=%i c2=%i\n", c1, c2);

	printf("Testando len_dim:");
	c1 = len_dim(adata, 2);
	if(c1 == 7)
		printf(" OK\n");
	else
		printf(" ERROR wrong length: %i\n", c1);

	printf("Testando desloc_dim:");
	append_dim(&adata, 10);
	c1 = desloc_dim(adata, 1);
	c2 = desloc_dim(adata, 2);
	c3 = desloc_dim(adata, 3);

	if(c1 == 0 && c2 == 10 && c3 == 1120)
		printf(" OK\n");
	else
		printf(" ERROR wrong desloc: c1=%i c2=%i\n", c1, c2);


	return 0;
}
