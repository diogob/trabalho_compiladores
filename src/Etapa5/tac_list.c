#include <stdlib.h>
#include <stdio.h>

#include "tac_list.h"

int init_list(tac_list* l)
{
	*l = (struct tac_list*) malloc(sizeof(struct tac_list));
	(*l)->tac = NULL;
	(*l)->next = NULL;
	return 0;
} 

void free_tac_list(tac_list* l)
{
	if((*l)->next != NULL)
		free_tac_list(&(*l)->next);

	free((*l)->tac);
	free(*l);
} 

int empty_list(tac_list l)
{
	return (l->tac == NULL ? -1 : 0);
}

tac_list last(tac_list l)
{
	tac_list last = l;
	for(last = l; last->tac != NULL; last = last->next);
	return last;
}

int append(tac_list l, tac_instruction* i)
{
	tac_list lasti = NULL;
	tac_list new = NULL;
	lasti = last(l);
	lasti->tac = i;	
	init_list(&new);
	// Em caso de falha na alocacao saimos com -1
	if(new == NULL)
		return -1;
	lasti->next = new;
	return 0;
}

tac_list concat_tac(tac_list l1, tac_list l2)
{

	tac_list before_last = NULL, last = NULL;
	tac_list new = NULL;
	for(last = before_last = l1; last->tac != NULL; before_last = last, last = last->next);

	// Se a primeira lista esta vazia retornamos a segunda 
	if(last == l1)
		return l2;
	before_last->next = l2;
	return l1;
}

tac_list first(tac_list l)
{
	if(empty_list(l))
		return NULL;
	return l->next;
}


