/** @file symbol_table.h
 */
#ifndef _SYMBOL_TABLE_H_
#define _SYMBOL_TABLE_H_

/** \brief Tamanho da tabela de simbolos utilizada.
 *
 */
#define TAMANHO_TABELA 101

#include <stdio.h>
/** \brief Encapsulamento das entradas na tabela hash
 *
 * Tipo abstrato das entradas na tabela de Hash. (Obs.: futuramente, os campos
 * dessa struct poderao vir a ser alterados em funcao das necessidades.)
 * Na Etapa 1, nao e necessario entender o conteudo desses campos.
 * Sempre vao ser inseridos na tabela, e recuperado dela, ponteiros sobre tais
 * estruturas de dados abstratas.
 */
typedef struct {
   char* name;  /**< um string que representa o nome de uma variavel. */
   int type;    /**< representacao do tipo da variavel. */
   int size;    /**< numero de Bytes necessarios para armazenamento. */
   int desloc;  /**< Endereco da proxima variavel. */
   void* extra; /**< qualquer informacao extra. */
} entry_t ;

/** \brief Encapsulamento da lista de elementos usada pela symbol_t
 *
 * Cada elemento da tabela hash e uma lista encadeada para tratamento de colisao
 *
 */
typedef struct symbol_list {
   entry_t* element;			/**< elemento da lista (entrada da tabela de hash). */
   struct symbol_list* next;	/**< proximo elemento da lista. */
} symbol_list;

/** \brief Encapsulamento de uma tabela de simbolos (uma tabela has)
 *
 * A tabela de simbolos e um array de listas de simbolos.
 * Implementamos dessa forma para tratar a colisao de hash com o encadeamento da lista.
 *
 */
typedef symbol_list* symbol_t;

/** \brief Inicializar a tabela de Hash.
 *
 * @param table uma referencia sobre uma tabela de simbolos.
 * @return o valor 0 se deu certo.
 */
int init_table(symbol_t* table) ;

/** \brief Retornar um ponteiro sobre a entrada associada a 'name'.
 *
 * Essa funcao deve consultar a tabela de simbolos para verificar se se encontra
 * nela uma entrada associada a um char* (string) fornecido em entrada. Para
 * a implementacao, sera necessario usar uma funcao que mapeia um char* a
 * um numero inteiro. Aconselha-se, por exemplo, consultar o livro do dragao
 * (Aho/Sethi/Ulman), Fig. 7.35 e a funcao HPJW.
 *
 * @param table uma tabela de simbolos.
 * @param name um char* (string).
 * @return um ponteiro sobre a entrada associada a 'name', ou NULL se 'name'
 *         nao se encontrou na tabela.
 */
entry_t* lookup(symbol_t table, char* name) ;

/** \brief Inserir uma entrada em uma tabela.
 *
 * @param table uma tabela de simbolos.
 * @param entry uma entrada.
 * @return um numero negativo se nao se conseguiu efetuar a insercao, zero se
 *   deu certo.
 */
int insert(symbol_t* table, entry_t* entry) ;

/** \brief Imprimir o conteudo de uma tabela.
 *
 * A formatacao exata e deixada a carga do programador. Deve-se listar todas
 * as entradas contidas na tabela atraves de seu nome (char*). Deve retornar
 * o numero de entradas na tabela.
 *
 * @param table uma tabela de simbolos.
 * @return o numero de entradas na tabela.
 */
int print_table(symbol_t table);

/** \brief Imprimir o conteudo de uma tabela em um arquivo.
 *
 * A formatacao exata e deixada a carga do programador. Deve-se listar todas
 * as entradas contidas na tabela atraves de seu nome (char*). Deve retornar
 * o numero de entradas na tabela. A saida deve ser dirigida para um arquivo,
 * cujo descritor e passado em parametro.
 *
 * @param out um descrito de arquivo (FILE*).
 * @param table uma tabela de simbolos.
 * @return o numero de entradas na tabela.
 */
int print_file_table(FILE* out, symbol_t table);

/**
 * \brief Mapeia char para int
 *
 * Faz um hash da chave executando uma serie de operacoes bitwise.
 *
 * @param key a chave a ser mapeada.
 * @return o inteiro resultante.
 */
int hashpjw(const void *key);

/**
 * \brief Libera a tabela de simbolos
 *
 * @param table ponteiro para tabela de simbolos.
 * @return nada (void).
 */
void free_table(symbol_t* table);

/**
 * \brief Libera uma lista encadeada
 *
 * @param list ponteiro para symbol_list.
 * @return nada (void).
 */
void free_list(symbol_t list);
#endif
