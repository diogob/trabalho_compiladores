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
all: etapa1

############# ETAPA 1 ##########################
DIR1    = $(SRC_DIR)/Etapa1
etapa1: $(DIR1)/stack.h $(DIR1)/symbol_table.h
	cd $(DIR1) && $(MAKE) -w install

test1: etapa1
	cd $(PICO_DIR)/Tests && $(MAKE) -w

clean:
	rm -f $(INC_DIR)/* $(OBJ_DIR)/* ; \
	cd $(DIR1) && $(MAKE) -w clean ; \
	cd $(PICO_DIR)/Tests && $(MAKE) -w clean ; \
