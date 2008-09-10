install: pico
	cp pico_ll1 $(PICO_DIR)/Tests ; cp pico_ll1.c $(PICO_DIR)/Tests ;\

pico: scanner.l tokens.h
	gcc $(CFLAGS) -I$(INC_DIR) -I -o pico $(OBJ_DIR)/symbol_table.o pico.c 

clean:
	/bin/rm -f pico pico.c
