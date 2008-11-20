export
# Localizacao do diretorio principal de Pico
PICO_DIR   = /home/diogo/Desktop/compiladores

# Localizacao dos arquivos headers:
INC_DIR    = $(PICO_DIR)/include
# Localizacao dos arquivos fontes
SRC_DIR    = $(PICO_DIR)/src
# Localizacao dos arquivos objetos:
OBJ_DIR    = $(PICO_DIR)/objects
# Localizacao dos arquivos de documentação:
DOC_DIR    = $(PICO_DIR)/doc
# Localizacao do executavel
BIN        = $(PICO_DIR)/bin

# Compilador C:
CC         = gcc

# Opcoes de compilacao:
CFLAGS     = -Wall -g

# Alterar a linha abaixo para compilar outras etapas. 
#   Por exemplo, para compilar as tres primeiras etapas:
# all: etapa1 etapa2 etapa3
#   ou ainda, para compilar apenas a sexta etapa:
# all: etapa6
all: etapa5

############# ETAPA 1 ##########################
DIR1    = $(SRC_DIR)/Etapa1
# depois de 'make etapa1', include/ contem os .h e objects/ os .o de src/Etapa1.
etapa1: $(DIR1)/stack.h $(DIR1)/symbol_table.h
	cd $(DIR1) && $(MAKE) -w install

test: etapa1 etapa6
	cd $(PICO_DIR)/Tests && $(MAKE) -w

DIR2    = $(SRC_DIR)/Etapa2

# depois de 'make etapa2':
#    include/ contem uma copia de src/Etapa2/tokens.h
#    Tests/ contem uma copia de pico.c (que contem um main).
etapa2: etapa1
	cd $(DIR2) && $(MAKE) -w install

test2: etapa2
	cd $(PICO_DIR)/Tests && $(MAKE) -w

DIR4    = $(SRC_DIR)/Etapa4
# Depois de 'make etapa4', 'pico' eh copiado em Testes.
etapa4: etapa2 etapa1
	cd $(DIR4) && $(MAKE) -w install

test4: etapa4
	cd $(PICO_DIR)/Tests && $(MAKE) -w

DIR5    = $(SRC_DIR)/Etapa5
# Depois de 'make etapa5', 'pico' eh copiado em Testes.
etapa5: etapa2 etapa1
	cd $(DIR5) && $(MAKE) -w install

DIR6    = $(SRC_DIR)/Etapa6
# Depois de 'make etapa6', 'pico' eh copiado em Testes.
etapa6: etapa2 etapa1
	cd $(DIR6) && $(MAKE) -w install

test4: etapa4
	cd $(PICO_DIR)/Tests && $(MAKE) -w

clean:
	rm -f $(INC_DIR)/* $(OBJ_DIR)/* ; \
	cd $(DIR1) && $(MAKE) -w clean ; \
	cd $(DIR2) && $(MAKE) -w clean ; \
	cd $(DIR4) && $(MAKE) -w clean ; \
	cd $(PICO_DIR)/Tests && $(MAKE) -w clean ; \
