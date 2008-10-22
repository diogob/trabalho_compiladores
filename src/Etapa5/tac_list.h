/** @file tac_list.h
 */
#ifndef _TAC_LIST_H_
#define _TAC_LIST_H_


#include <stdio.h>
/** \brief Encapsulamento das entradas na lista de instrucoes TAC
 *
 * Tipo abstrato das entradas na lista TAC.
 */
typedef struct {
   int op;  /**< operador. */
   int arg1;    /**< argumento 1. */
   int arg2;    /**< argumento 2. */
   int res;  /**< resultado. */
} tac_instruction ;

/** \brief Encapsulamento da lista de instrucoes TAC
 *
 * 
 *
 */
typedef struct tac_list {
   tac_instruction* tac;		/**< elemento da lista TAC. */
   struct tac_list* next;	/**< proximo elemento da lista. */
} *tac_list;

/** \brief Inicializar lista TAC.
 *
 * @param table uma referencia sobre uma lista TAC.
 * @return o valor 0 se deu certo.
 */
int init_list(tac_list* tac) ;

/** \brief Inserir uma entrada em uma tabela.
 *
 * @param table uma tabela de simbolos.
 * @param entry uma entrada.
 * @return um numero negativo se nao se conseguiu efetuar a insercao, zero se
 *   deu certo.
 */
int append(tac_list tac, tac_instruction* i) ;

/** \brief Imprimir o conteudo de uma tabela.
 *
 * A formatacao exata e deixada a carga do programador. Deve-se listar todas
 * as entradas contidas na tabela atraves de seu nome (char*). Deve retornar
 * o numero de entradas na tabela.
 *
 * @param table uma tabela de simbolos.
 * @return o numero de entradas na tabela.
 */
int print_tac(tac_list tac);

/**
 * \brief Libera uma lista encadeada
 *
 * @param list tac_list.
 * @return nada (void).
 */
void free_list(tac_list* tac);
int empty_list(tac_list l);

tac_list last(tac_list l);
tac_list first(tac_list l);

#endif
