install: pico
	cp pico_ll1 $(PICO_DIR)/Tests ; cp pico_ll1.c $(PICO_DIR)/Tests ;\

pico: pico_ll1.c $(INC_DIR)/pico.c
	gcc $(CFLAGS) -I$(INC_DIR) -o pico_ll1 pico_ll1.c $(OBJ_DIR)/symbol_table.o $(OBJ_DIR)/stack.o

clean:
	/bin/rm -f pico pico.c
