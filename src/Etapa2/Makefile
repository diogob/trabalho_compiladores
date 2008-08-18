install: pico
	cp pico $(PICO_DIR)/Tests ; cp pico.c $(PICO_DIR)/Tests ;\
	cp tokens.h $(PICO_DIR)/include

pico: scanner.l tokens.h
	flex -o pico.c scanner.l; \
	gcc -o pico pico.c 

clean:
	/bin/rm -f pico pico.c
