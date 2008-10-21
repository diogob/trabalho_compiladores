## Todas as variaveis nao-declaradas aqui estao definidas em Pico/Makefile
## ('cat ../../Makefile'  para jogar seu conteudo na tela.)
all: stack.o symbol_table.o

OBJ1     = symbol_table.o stack.o
HEAD1    = symbol_table.h stack.h

symbol_table.o: symbol_table.c symbol_table.h
	$(CC) $(CFLAGS) -c symbol_table.c

lista.o: lista.h lista.c
	$(CC) $(CFLAGS) -c lista.c

stack.o: stack.c
	$(CC) $(CFLAGS) -g -c stack.c

install: $(OBJ1) $(HEAD1) doc
	cp $(OBJ1) $(OBJ_DIR) ; cp $(HEAD1) $(INC_DIR) ;\

doc: Doxyfile $(HEAD1)
	doxygen Doxyfile

clean:
	rm -f $(OBJ1)
