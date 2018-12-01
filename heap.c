#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "grafo.h"


/*Cria um Heap de vertices, colocando todos os valores de chaves como INT_MAX*/
TipoNo* CriaHeap(int numeroNos, int* Posicao){
    int i;
    TipoNo *Heap;
    Heap = (TipoNo*)malloc(sizeof(TipoNo) * numeroNos);

    for (i = 0; i < numeroNos; i++)
    {
        Heap[i].id = i;
        Heap[i].chave = INT_MAX;
        Heap[i].peso = 0;
        Heap[i].pai = -1;
        Heap[i].contador_chave = 0;
        Posicao[i] = i;
    }
    return Heap;
}

/* Garante a propriedade de min-heap*/
void Heapifica(TipoNo* Heap, int i, int max, int* Posicao){
    int indice, esquerda, direita, aux;
    TipoNo tmp; 

    while (i < max)
    {
        indice = i;
        esquerda = 2 * i + 1;
        direita = 2 * i + 2;

        if (esquerda < max && Heap[esquerda].chave < Heap[indice].chave)
            indice = esquerda;
        if (direita < max && Heap[direita].chave < Heap[indice].chave)
            indice = direita;
        if (indice == i)
            return;
        
        tmp = Heap[i];
        Heap[i] = Heap[indice];
        Heap[indice] = tmp;

        aux = Posicao[Heap[i].id];
        Posicao[Heap[i].id] = Posicao[Heap[indice].id];
        Posicao[Heap[indice].id] = aux;

        i = indice;
    }
}

/* Retira o No da root e poe o ultimo em seu lugar */
int RetiraMinimo(TipoNo* Heap, int* tamanhoHeap, int* Posicao){
    int aux;
    int Ultimo = *tamanhoHeap-1;
    TipoNo tmp;

    tmp = Heap[0];
    Heap[0] = Heap[Ultimo];
    Heap[Ultimo] = tmp;

    aux = Posicao[Heap[0].id];
    Posicao[Heap[0].id] = Posicao[Heap[Ultimo].id];
    Posicao[Heap[Ultimo].id] = aux;

    
    Heapifica(Heap, 0, Ultimo, Posicao);
    
    *tamanhoHeap -= 1;

    return Heap[Ultimo].id;
}

/* Troca o valor chave de um vertice, como isso pode quebrar a propriedade min-heap, 
verifica-se os nos pais de baixo para cima heapificando o que for necessario*/
void MudaChave(TipoNo* Heap, int* Posicao, int peso, int idFilho){
    int i, paiHeap;
    TipoNo tmp;

    i = Posicao[idFilho];
    Heap[i].chave = peso;
    paiHeap = (i - 1) / 2;

    while(paiHeap >= 0 && Heap[i].chave < Heap[paiHeap].chave){
        Posicao[idFilho] = paiHeap;
        Posicao[Heap[paiHeap].id] = i;

        tmp = Heap[i];
        Heap[i] = Heap[paiHeap];
        Heap[paiHeap] = tmp;

        i = paiHeap;
        paiHeap = (i - 1) / 2;
    }   
}