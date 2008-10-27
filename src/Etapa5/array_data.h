/** @file tac_list.h
 */
#ifndef _ARRAY_DATA_H_
#define _ARRAY_DATA_H_

#include <stdio.h>
#include "stack.h"

/** \brief Inserir uma dimensao no array.
 *
 * @param adata uma lista de dimensoes ou um valor nulo para criar uma nova lista de dimensoes.
 * @param dim_size o tamanho da dimensao.
 * @return um numero negativo se nao se conseguiu efetuar a insercao, zero se
 *   deu certo.
 */
stack append_dim(stack* adata, int dim_size) ;
int count_dim(stack adata) ;
int len_dim(stack adata, int dim) ;
void print_array_data(stack adata);
int desloc_dim(stack adata, int dim) ;


#endif
