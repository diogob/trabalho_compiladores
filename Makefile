export
# Localizacao do diretorio principal de Pico
PICO_DIR   = /Users/diogo/Desktop/Pico-Denys-Diogo-etapa1

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
all: etapa3 etapa2 etapa1 

############# ETAPA 1 ##########################
DIR1    = $(SRC_DIR)/Etapa1
etapa1: $(DIR1)/stack.h $(DIR1)/symbol_table.h
	cd $(DIR1) && $(MAKE) -w install

test1: etapa1
	cd $(PICO_DIR)/Tests && $(MAKE) -w

DIR2    = $(SRC_DIR)/Etapa2
etapa2: $(DIR2)/tokens.h $(DIR2)/scanner.l
	cd $(DIR2) && $(MAKE) -w install

test2: etapa2
	cd $(PICO_DIR)/Tests && $(MAKE) -w

DIR3    = $(SRC_DIR)/Etapa3
etapa3: $(DIR3)/pico.c
	cd $(DIR3) && $(MAKE) -w install

DIR_TESTE2    = $(PICO_DIR)/testes-etapa2
teste2: $(PICO_DIR)/testes-etapa2/pico.c
	cd $(DIR_TESTE2) && $(MAKE)

DIR4    = $(SRC_DIR)/Etapa4
etapa4: $(DIR4)/tokens.h $(DIR4)/scanner.l
	cd $(DIR4) && $(MAKE) -w install

test4: etapa4
	cd $(PICO_DIR)/Tests && $(MAKE) -w

clean:
	rm -f $(INC_DIR)/* $(OBJ_DIR)/* ; \
	cd $(DIR1) && $(MAKE) -w clean ; \
	cd $(PICO_DIR)/Tests && $(MAKE) -w clean ; \
