CC=gcc
CFLAGS= -O2 -Wall -ansi -pedantic

all: GestHiper clean
	@echo "Executavel \"GestHiper\" criado com sucesso!"


GestHiper: main.o compras.o contabilidade.o clientes.o produtos.o
	$(CC) $(CFLAGS) main.o compras.o contabilidade.o clientes.o produtos.o -o GestHiper


clientes.o: clientes.c clientes.h
	$(CC) -o clientes.o -c clientes.c $(CFLAGS)

produtos.o: produtos.c produtos.h
	$(CC) -o produtos.o -c produtos.c $(CFLAGS)

contabilidade.o: contabilidade.c contabilidade.h
	$(CC) -o contabilidade.o -c contabilidade.c $(CFLAGS)

compras.o: compras.c compras.h
	$(CC) -o compras.o -c compras.c $(CFLAGS)

main.o: main.c clientes.h compras.h produtos.h contabilidade.h main.h
	gcc -o main.o -c main.c $(CFLAGS)

clean:
	rm -rf *.o