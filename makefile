CC = gcc
CFLAGS = -Wall -ansi -pedantic
OBJS = assembler.o pre_assembler.o mcro_check.o firstPass.o coding.o propriety.o second_pass.o reference_tables.o

assembler: $(OBJS)
	$(CC) $(CFLAGS) -o assembler $(OBJS)

assembler.o: assembler.c mcro_check.h pre_assembler.h propriety.h coding.h reference_tables.h firstPass.h second_pass.h
	$(CC) $(CFLAGS) -c assembler.c

pre_assembler.o: pre_assembler.c pre_assembler.h mcro_check.h firstPass.h
	$(CC) $(CFLAGS) -c pre_assembler.c

mcro_check.o: mcro_check.c assembler.h pre_assembler.h propriety.h firstPass.h
	$(CC) $(CFLAGS) -c mcro_check.c

firstPass.o: firstPass.c propriety.h coding.h second_pass.h reference_tables.h mcro_check.h
	$(CC) $(CFLAGS) -c firstPass.c

coding.o: coding.c firstPass.h propriety.h reference_tables.h
	$(CC) $(CFLAGS) -c coding.c

propriety.o: propriety.c firstPass.h reference_tables.h mcro_check.h
	$(CC) $(CFLAGS) -c propriety.c

second_pass.o: second_pass.c reference_tables.h assembler.h pre_assembler.h mcro_check.h propriety.h
	$(CC) $(CFLAGS) -c second_pass.c

reference_tables.o: reference_tables.c assembler.h pre_assembler.h mcro_check.h firstPass.h
	$(CC) $(CFLAGS) -c reference_tables.c

clean:
	rm -f *.o assembler
