VALGRIND_FLAGS=--leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 --show-leak-kinds=all --trace-children=yes
CFLAGS =-std=c99 -Wall -Wconversion -Wtype-limits -pedantic -Werror -O2 -g
CC = gcc

all: clean valgrind-tdas

valgrind-tdas: pruebas_tdas
	valgrind $(VALGRIND_FLAGS) ./pruebas_tdas

pruebas_tdas: *.c pruebas_tdas.c
	$(CC) $(CFLAGS) *.c -o pruebas_tdas

clean:
	rm -f pruebas_tdas
	rm -f a.out