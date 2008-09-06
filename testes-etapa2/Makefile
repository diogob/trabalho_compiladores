## OBJ_DIR e INC_DIR sao atualizados pelo Makefile principal, assim como
## CC e CFLAGS.

# Lista todos os arquivos ./test*.c e cria a lista dos .o equivalentes.
# Vai-se querer compilador todos os $(objects).
objects := $(patsubst %.c,%.o,$(wildcard test*.c))
# Cada um dos .o in $(objects) devera ser compilado em um executavel cujo
# nome sera o basename. Todos esses executaveis devem ser compilados.
alvos   := $(basename $(objects))

all: $(alvos)

# Cada um dos .o em $(objects) depende de de seu .c, de pico.c e de tokens.h
# e eh compilador a partir do .c tranquilamente:
# (Inserir um -I PICO_DIR/include...)
$(objects): %.o : %.c 
	$(CC) -c $(CFLAGS) -I../src/Etapa2/ -I../include/ $< -o $@

# regra usada para compilar o executavel a partir do .o
$(alvos): % : %.o
	$(CC) $(LDFLAGS) -o $@ ../objects/symbol_table.o $<

clean:
	rm -f $(objects) $(alvos)
