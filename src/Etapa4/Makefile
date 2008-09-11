# a chamar a partir de ../..

# 'make' sem argumento vai resolver a depencia abaixo, e compilar pico:
all: pico
#
# o comando yacc -d gera tanto y.tab.c como y.tab.h. Apos ter criado
# y.tab.c, renomea-o para pico.c.
pico.c: pico.y
	yacc -d pico.y ;\
	mv y.tab.c pico.c

# o comando flex gera lex.yy.c (#included por pico.c)
lex.yy.c: scanner.l
	flex scanner.l

# 'pico' depende de pico.c, y.tab.h  e lex.yy.c
pico: pico.c y.tab.h lex.yy.c
	gcc -o pico pico.c -lfl

# o 'install' soh copia 'pico' em Tests/, mas primeiro ele deve ter sido
# compilador, por isso a dependencia.
install: pico
	cp pico $(PICO_DIR)/Tests
