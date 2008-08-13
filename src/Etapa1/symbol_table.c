#include <stdlib.h>

#include "symbol_table.h"


int init_table(symbol_t* table)
{
	*table = malloc(sizeof(symbol_list) * 101);
	if(*table == NULL)
		return -1;
    return 0;
}

//mapeia char para int... peguei no pdf q o carlos mandou, e o prof aconselha se basear nessa função(vide symbol_table.h,l53)
/*****************************************************************************
*                                                                            *
* -------------------------------- hashpjw ------------------------------- *
*                                                                            *
*****************************************************************************/
int hashpjw(const void *key) {
	char	*ptr;
	int		val = 0;
	/*****************************************************************************
	*                                                                            *
	* Hash the key by performing a number of bit operations on it.               *
	*                                                                            *
	*****************************************************************************/
	ptr = key;
	while (*ptr != '\0') 
	{
		int tmp;
		val = (val << 4) + (*ptr);
		if ((tmp = (val & 0xf0000000)))
		{
			val = val ^ (tmp >> 24);
			val = val ^ tmp;
		}
		ptr++;
	}
	return val;
}


entry_t* lookup(symbol_t table, char* name)
{
    // aplica função hash -> valor recebido em int % tamanho do array (q valor definir de tamanho?? de preferencia um primo o mais distante possivel de duas potencias de 2, ex: 2^4=16, 2^5=32, um bom valor entre os dois seria 23)
    // percorre a lista na posição do array que a função hash retornar
    // retorna ponteiro para entrada ou NULL
    return NULL;
}

int insert(symbol_t* table, entry_t* entry)
{
    // lookup no valor -> retorna negativo se não consegue inserir
    // senão
    // aplica função hash
    // insere valor na ultima posição da fila da posição do array
    return 0;
}

int print_table(symbol_t table)
{
    // laço imprimindo
    return 0;
}
int print_file_table(FILE* out, symbol_t table)
{
    return 0;
}


