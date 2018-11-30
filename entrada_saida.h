#ifndef ENTRADASAIDA_H
#define ENTRADASAIDA_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"

TipoGrafo* LeGrafo(char* nomeArquivo, int* custoGrafoTodo); /*Le a matriz de adjacencia e transforma em grafo*/
void ImprimeGrafo(TipoLista** ListaAdjacencia, int numeroNos); /*Imprime um grafo*/
void ImprimeMst(char* nomeArquivo, TipoNo* Heap, int tamanhoHeap, int* custoMst);
void insertionSortPai(TipoNo* Heap, int tamanhoHeap);
void insertionSortFilho(TipoNo* Heap, int tamanhoHeap);
void ImprimeMst2(char* nomeArquivo, TipoNo* Heap, int tamanhoHeap, int* custoMst);
#endif