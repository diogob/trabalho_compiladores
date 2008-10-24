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
		free_list(&(*l)->next);

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

tac_list first(tac_list l)
{
	if(empty_list(l))
		return NULL;
	return l->next;
}


