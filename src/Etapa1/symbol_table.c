#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "symbol_table.h"


int init_table(symbol_t* table)
{
	*table = malloc(sizeof(symbol_list) * TAMANHO_TABELA);
	if(*table == NULL)
		return -1;

	// Zera toda a memoria alocada
	memset(*table, 0, sizeof(symbol_list) * TAMANHO_TABELA);
    return 0;
}

int hashpjw(const void *key)
{
	char	*ptr;
	int		val = 0;
	ptr = (char *) key;
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
	int indice = hashpjw(name) % TAMANHO_TABELA;
	entry_t* temp = table[indice].element;
	symbol_t list_item = &(table[indice]);

	if(temp == NULL)
		return NULL;

	while(1)
	{
		// Encontrou o item
		if(!strcmp(list_item->element->name, name))
			return list_item->element;
		if(list_item->next == NULL)
			break;
		list_item = list_item->next;
	}
	return NULL;
}

int insert(symbol_t* table, entry_t* entry)
{
	// lookup no valor -> retorna negativo se não consegue inserir
	// senão
	// aplica função hash
	// insere valor na ultima posição da fila da posição do array
	int indice = hashpjw(entry->name) % TAMANHO_TABELA;
	entry_t* temp = (*table)[indice].element;
	if(temp == NULL)
	{
		(*table)[indice].element = entry;
	}
	else
	{
		symbol_t list_item = &((*table)[indice]);
		symbol_t new_item;
		while(1)
		{
			// Elemento jah existe
			if(!strcmp(list_item->element->name, entry->name))
				return -1;
			if(list_item->next == NULL)
			{
				new_item = malloc(sizeof(symbol_list));
				new_item->element = entry;
				new_item->next = NULL;
				list_item->next = new_item;
				break;
			}
			list_item = list_item->next;
		}
	}
	return 0;
}

int print_table(symbol_t table)
{
	return print_file_table(stdout, table);
}

int print_file_table(FILE* out, symbol_t table)
{
	int indice;
	int contador = 0;
	entry_t* temp ;
	symbol_t list_item ;
	fprintf(out, "\nConteudo da tabela de symbolos:\n");
	for(indice=0; indice < TAMANHO_TABELA; indice++)
	{
		temp = table[indice].element;
		list_item = &(table[indice]);
		if(temp != NULL){
			fprintf(out, "--------------\nIndice: %d\n",indice);    
			while(1)
			{
				// Encontrou o item
				fprintf(out, "Elemento: %s\n",list_item->element->name);
				contador++;
				if(list_item->next == NULL)
					break;
				list_item = list_item->next;
			}
		}
	}
	fprintf(out, "\n");
	return contador;
}

void free_list(symbol_t list)
{
	if(list->next != NULL)
	{
		free_list(list->next);
		free(list->element);
	}
}

void free_table(symbol_t* table)
{
	int indice;
	int contador = 0;
	entry_t* temp ;
	symbol_t list_item;
	for(indice = 0; indice < TAMANHO_TABELA; indice++)
	{
		if((*table)[indice].element != NULL)
		{
			list_item = &((*table)[indice]);
			free_list(list_item);
		}
	}
	// Zera toda a memoria alocada
	memset(*table, 0, sizeof(symbol_list) * TAMANHO_TABELA);
	free(*table);
}
