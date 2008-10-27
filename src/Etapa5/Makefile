# Makefile chamado pelo Makefile principal de Pico/

# 'make' sem argumento vai resolver a depencia abaixo, e compilar pico:
#   sem fazer a instalacao.
#
all: pico tac
#
# 'pico' depende de pico.c (codigo fonte do parser) e lex.yy.c (codigo fonte
# do scanner).
pico: pico.c lex.yy.c tac adata
	gcc -o pico -I$(INC_DIR) $(OBJ_DIR)/stack.o $(OBJ_DIR)/array_data.o $(OBJ_DIR)/symbol_table.o $(OBJ_DIR)/tac_list.o pico.c -lfl
#
# 'pico.c' eh gerado pelo Yacc a partir de pico.y.
# o comando yacc -d gera tanto y.tab.c como y.tab.h. 
# Apos ter criado y.tab.c, renomea-o para pico.c - nota que nessa etapa, 
#    pico.c passa a ser o parser e nao mais o scanner.
# Apos ter criado y.tab.h, renomea-o para tokens.h (que sera usado pelo 
#    scanner).
#
pico.c: pico.y
	yacc --debug --verbose -d pico.y ;\
	mv y.tab.c pico.c ; mv y.tab.h tokens.h

# o scanner 'lex.yy.c' eh gerado pelo flex
# O flex usa como entrada 'scanner.l' encontrado em Etapa2/src, porem alterando
# o nome do procedimento "main" encontrado nele para que passe a se chamar
# 'main-etapa2'. Dessa forma, nao tera conflito com o main de pico.c.
# OBSERVACAO: QUALQUER ALTERACAO EFETUADA NO SCANNER DEVE SER FEITA
# EM src/Etapa2/scanner.h !!
#
lex.yy.c: scanner.l
	flex scanner.l

tac: tac_list.c tac_list.h
	gcc -c -o tac_list.o tac_list.c
	cp tac_list.o $(OBJ_DIR)/
	cp tac_list.h $(INC_DIR)/

adata: array_data.c array_data.h
	gcc -c -o array_data.o -I$(INC_DIR) $(OBJ_DIR)/stack.o array_data.c
	cp array_data.o $(OBJ_DIR)/
	cp array_data.h $(INC_DIR)/

# o 'install' soh copia 'pico' em Tests/, mas primeiro ele deve ter sido
# compilado, por isso a dependencia.
#
install: pico tac
	cp tokens.h $(INC_DIR)/
	cp pico $(PICO_DIR)/Tests

clean:
	rm pico.c lex.yy.c tokens.h pico
