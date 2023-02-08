CC=gcc
CFLAGS=-O2 -Wall -pedantic -Iincludes `pkg-config --cflags glib-2.0`
LDFLAGS=`pkg-config --libs glib-2.0` -lm

SOURCES = $(filter-out src/main.c src/tests.c, $(wildcard src/*.c))
OBJECTS = $(SOURCES:src/%.c=obj/%.o)

BIN_PRINCIPAL = programa-principal
BIN_TESTES = programa-testes

.PHONY: all clean debug

all: $(BIN_PRINCIPAL) $(BIN_TESTES)

$(BIN_PRINCIPAL): $(OBJECTS) obj/main.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

$(BIN_TESTES): $(OBJECTS) obj/tests.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -o $@

debug: $(OBJECTS) obj/main.o
	$(CC) $^ $(CFLAGS) $(LDFLAGS) -g -o $(BIN_PRINCIPAL)
	#gdb ./programa-principal
	#valgrind ./programa-principal <dataset> <input.txt>

obj/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -fr $(BIN_PRINCIPAL) $(BIN_TESTES) obj/*.o Resultados/
