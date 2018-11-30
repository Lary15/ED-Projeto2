#ifndef HEAP_H
#define HEAP_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"

TipoNo* CriaHeap(int numeroNos, int* Posicao); /* Funcao cria um heap com itens TipoNo com todas as chaves iguais ao maior inteiro possivel*/
void Heapifica(TipoNo* Heap, int i, int max, int* Posicao); /* Garante a propriedade de min-heap*/
int RetiraMinimo(TipoNo* Heap, int* tamanhoHeap, int* Posicao); /* Retira o No da root e poe o ultimo em seu lugar */
void MudaChave(TipoNo* Heap, int* Posicao, int peso, int Id);
#endif 