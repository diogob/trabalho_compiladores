#include <stdlib.h>
#include <stdio.h>

#include "stack.h"

void init_stack(stack* s)
{
	*s = (struct stack*) malloc(sizeof(struct stack));
	(*s)->element = NULL;
	(*s)->next = NULL;
} 

void free_stack(stack* s)
{
	if((*s)->next != NULL)
		free_stack(&(*s)->next);

	free((*s)->element);
	free(*s);
} 

int empty(stack s)
{
	return (s->next == NULL ? -1 : 0);
}

int push(stack* s, void* item)
{
	stack new = NULL;
	(*s)->element = item;
	init_stack(&new);
	// Em caso de falha na alocacao saimos com -1
	if(new == NULL)
		return -1;

	new->element = NULL;
	new->next = (*s);
	*s = new;
	return 0;
}

void* pop(stack* s)
{
	void* 	ret;
	stack	newtop;
	if(empty(*s))
		return NULL;
	ret = (*s)->next->element;
	newtop = (*s)->next->next;
	free((*s)->next);
	(*s)->next = newtop;
	return ret;
}

void* top(stack s)
{
	if(empty(s))
		return NULL;
	return s->next->element;
}
