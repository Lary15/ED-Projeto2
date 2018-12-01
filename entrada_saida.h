#ifndef ENTRADASAIDA_H
#define ENTRADASAIDA_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"

TipoGrafo* LeGrafo(char* nomeArquivo, int* custoGrafoTodo); /*Le a matriz de adjacencia e transforma em grafo*/
void ImprimeGrafo(TipoLista** ListaAdjacencia, int numeroNos); /*Função nao eh utilizada no algoritmo. Imprime um grafo para vizualização*/
void insertionSortPai(TipoNo* Heap, int tamanhoHeap);   /*Funcoes auxiliares da ImprimeMst*/
void insertionSortFilho(TipoNo* Heap, int tamanhoHeap);
void ImprimeMst(char* nomeArquivo, TipoNo* Heap, int tamanhoHeap, int* custoMst);/* Imprime as arestas da mst de forma ordenada*/
#endif