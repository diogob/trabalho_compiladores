#include <stdlib.h>
#include <stdio.h>

#include "tokens.h"
#include "tac_list.h"

const char* str_add = "ADD";
const char* str_sub = "SUB";
const char* str_mul = "MUL";
const char* str_div = "DIV";
const char* str_print = "PRINT";
const char* str_fadd = "FADD";
const char* str_fsub = "FSUB";
const char* str_fmul = "FMUL";
const char* str_fdiv = "FDIV";
const char* str_fprint = "FPRINT";
const char* str_error = "UNKNOWN";
const char* str_rdef = "RDEF";
const char* str_ldef = "LDEF";
const char* str_goto = "GOTO";
const char* str_and = "AND";
const char* str_or = "OR";


const char* str_eq = "==";
const char* str_ne = "!=";
const char* str_ge = ">=";
const char* str_le = "<=";
const char* str_gt = ">";
const char* str_lt = "<";


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
	if(i == NULL)
	{
		printf("INSTRUCAO NULA NO APPEND\n");
		return -2;
	}
	tac_list lasti = NULL;
	tac_list new = NULL;
	lasti = last(l);
	lasti->tac = i;	
	init_list(&new);
	// Em caso de falha na alocacao saimos com -1
	if(new == NULL)
	{
		printf("ERRO NO INIT\n");
		return -1;
	}
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
		case PRINT:
			return str_print;
		case FADD:
			return str_fadd;
		case FSUB:
			return str_fsub;
		case FMUL:
			return str_fmul;
		case FDIV:
			return str_fdiv;
		case FPRINT:
			return str_fprint;
		case RDEF:
			return str_rdef;
		case LDEF:
			return str_ldef;
		case GOTO:
			return str_goto;
		case EQ:
			return str_eq;
		case NE:
			return str_ne;
		case GE:
			return str_ge;
		case LE:
			return str_le;
		case '>':
			return str_gt;
		case '<':
			return str_lt;
		case AND:
			return str_and;
		case OR:
			return str_or;
		default:
			return str_error;
	}
}

void debug_tac(tac_list l)
{
	int i = 0;
	tac_list lasti;

	for(lasti = l; lasti->next != NULL; lasti = lasti->next, i++)
	{
		printf("%03i: OP: %s RES: %03i(%s) ARG1: %03i(%s) ARG2: %03i(%s) LIT1: %s LIT2: %s\n", i, get_op(lasti->tac->op), abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"), lasti->tac->literal1, lasti->tac->literal2);
	}
}

void print_tac(tac_list l)
{
	int i = 0;
	tac_list lasti;

	for(lasti = l; lasti->next != NULL; lasti = lasti->next, i++)
	{
		if(lasti->tac->op == RDEF)
		{
			printf("%03i:   %03i(%s) := %03i(%s)(%03i(%s))\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"));
		}
		else if(lasti->tac->op == LDEF)
		{
			if(lasti->tac->arg2)
				printf("%03i:   %03i(%s)(%03i(%s)) := %03i(%s)\n", i, abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"));
			else
				printf("%03i:   %03i(%s)(%03i(%s)) := %s\n", i, abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), lasti->tac->literal2);
		}
		else if(lasti->tac->op == GOTO)
		{
				printf("%03i:   GOTO %s\n", i, lasti->tac->literal1);
		}
		else if(lasti->tac->op == LABEL)
		{
			printf("%s:\n", lasti->tac->literal1);
			i--;
		}
		else if(lasti->tac->op == NOT)
		{
				printf("%03i:   %03i(%s) := NOT %03i(%s)\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"));
		}
		else if(lasti->tac->op == '<' || lasti->tac->op == '>' || lasti->tac->op == GE || lasti->tac->op == LE || lasti->tac->op == EQ || lasti->tac->op == NE)
		{
			if(lasti->tac->arg1 && lasti->tac->arg2)
				printf("%03i:   IF %03i(%s) %s %03i(%s) GOTO %s\n", i, abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), get_op(lasti->tac->op), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"), lasti->tac->literal3);
			else if(lasti->tac->arg1 && lasti->tac->literal2 != NULL)
				printf("%03i:   IF %03i(%s) %s %s GOTO %s\n", i, abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), get_op(lasti->tac->op), lasti->tac->literal2, lasti->tac->literal3);
			else if(lasti->tac->arg2 && lasti->tac->literal1 != NULL)
				printf("%03i:   IF %s %s %03i(%s) GOTO %s\n", i, lasti->tac->literal1, get_op(lasti->tac->op), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"), lasti->tac->literal3);
			else if(lasti->tac->literal1 != NULL && lasti->tac->literal2 != NULL)
				printf("%03i:   IF %s %s %s GOTO %s\n", i, lasti->tac->literal1, get_op(lasti->tac->op), lasti->tac->literal2, lasti->tac->literal3);
			else
				printf("%03i:   UNKNOW IF ERROR\n", i, lasti->tac->literal1, get_op(lasti->tac->op), lasti->tac->literal2, lasti->tac->literal3);
		}
		else
		{
			if(lasti->tac->arg1 && lasti->tac->arg2)
				printf("%03i:   %03i(%s) := %03i(%s) %s %03i(%s)\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), get_op(lasti->tac->op), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"));
			else if(lasti->tac->arg1 && lasti->tac->literal2 != NULL)
				printf("%03i:   %03i(%s) := %03i(%s) %s %s\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"), get_op(lasti->tac->op), lasti->tac->literal2);
			else if(lasti->tac->arg2 && lasti->tac->literal1 != NULL)
				printf("%03i:   %03i(%s) := %s %s %03i(%s)\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), lasti->tac->literal1, get_op(lasti->tac->op), abs(lasti->tac->arg2) - 1, (lasti->tac->arg2 < 0 ? "Rx" : "SP"));
			else if(lasti->tac->arg1)
				if(lasti->tac->op != PRINT && lasti->tac->op != FPRINT)
					printf("%03i:   %03i(%s) := %03i(%s)\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"));
				else
					printf("%03i:   %s %03i(%s)\n", i, get_op(lasti->tac->op), abs(lasti->tac->arg1) - 1, (lasti->tac->arg1 < 0 ? "Rx" : "SP"));
			else if(lasti->tac->op)
				printf("%03i:   %03i(%s) := %s %s %s\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), lasti->tac->literal1, get_op(lasti->tac->op), lasti->tac->literal2);
			else
				printf("%03i:   %03i(%s) := %s\n", i, abs(lasti->tac->res) - 1, (lasti->tac->res < 0 ? "Rx" : "SP"), lasti->tac->literal1);
		}
	}
}

