all: entrada_saida.o lista.o heap.o mst.o
	gcc -g -ggdb3 entrada_saida.o lista.o heap.o grafo.h mst.o -o mst
entrada_saida.o: entrada_saida.c
	gcc -g -c entrada_saida.c
lista.o: lista.c
	gcc -g -c lista.c
heap.o: heap.c
	gcc -g -c heap.c
mst.o: mst.c
	gcc -g -c mst.c