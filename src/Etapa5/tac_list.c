#include <stdlib.h>
#include <stdio.h>

#include "tokens.h"
#include "tac_list.h"

const char* str_add = "ADD";
const char* str_sub = "SUB";
const char* str_mul = "MUL";
const char* str_div = "DIV";
const char* str_error = "UNKNOWN";

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
	// Se a segunda lista eh nula retornamos a primeira e vice-versa
	if(l2 == NULL)
		return l1;
	if(l1 == NULL)
		return l2;

	for(last = before_last = l1; last->tac != NULL; before_last = last, last = last->next);

	// Se a primeira lista esta vazia retornamos a segunda 
	if(last == l1)
		return l2;
		
	// Caso nenhuma das duas esteja vazia apontamos o proximo elemento da primeira para o primeiro da segunda
	before_last->next = l2;
	return l1;
}

tac_list first(tac_list l)
{
	if(empty_list(l))
		return NULL;
	return l->next;
}

const char* get_op(int op)
{
	switch(op)
	{
		case ADD:
			return str_add;
		case SUB:
			return str_sub;
		case MUL:
			return str_mul;
		case DIV:
			return str_div;
		default:
			return str_error;
	}
}

void print_tac(tac_list l)
{
	int i = 0;
	tac_list lasti;

	for(lasti = l; lasti->next != NULL; lasti = lasti->next, i++)
	{
		if(lasti->tac->arg2)
			printf("%03i:   %03i(%s) := %03i(%s) %s %03i(%s)\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), get_op(lasti->tac->op), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"));
		else if(lasti->tac->arg1)
			printf("%03i:   %03i(%s) := %03i(%s)\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"));
		else
			printf("%03i:   %03i(%s) := %s\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), lasti->tac->literal);
	}
}

