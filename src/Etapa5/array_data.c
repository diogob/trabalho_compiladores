#include <stdlib.h>
#include <stdio.h>

#include "array_data.h"


stack append_dim(stack* adata, int dim_size)
{
	int* new_size;
	if(*adata == NULL)
		init_stack(adata);

	new_size = (int*) malloc(sizeof(int));
	*new_size = dim_size;
	push(adata, (void *) new_size);
	return (*adata);
}

int count_dim(stack adata)
{
	int ndims = 0;
	stack el;
	for(el = adata; el->next != NULL; el = el->next,ndims++);
	return ndims;
}

int len_dim(stack adata, int dim)
{
	int ndims = 0;
	stack el;
	if(empty(adata))
		return -1;

	for(el = adata; el != NULL; el = el->next,++ndims)
		if(dim == ndims && el->element != NULL)
			return *((int*) el->element);
	return -1;
}

int desloc_dim(stack adata, int dim)
{
	int ndims = 0, desloc = 1;
	stack el;
	if(empty(adata))
		return -1;
	if(dim == 1)
		return 0;

	for(el = adata; el != NULL; el = el->next,++ndims)
	{
		if(dim == ndims)
			return desloc;
		if(el->element != NULL)
			desloc = desloc * *((int*) el->element);
	}
	return -1;
}

void print_array_data(stack adata)
{
	stack el;
	int ndims = 0;
	if(empty(adata))
		printf("ARRAY VAZIA\n");

	for(el = adata; el != NULL; el = el->next,++ndims)
		if(el->element != NULL)
			printf("Dim: %i - Tamanho: %i\n", ndims, *((int*) el->element));
}
