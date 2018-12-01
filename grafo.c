#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lista.h"
#include "grafo.h"


/* Escolhe o no que fica na posicao zero baseado na sua lista de adjacencia.
Se o no tiver o menor peso de aresta aparecendo mais de uma vez na sua lista de adjacencia,
ele eh desconsiderado como opcao de posicao inicial.*/
void escolheInicio(TipoNo* Heap, TipoGrafo* Grafo, int* Posicao){
    int i, menor, sinal;
    Apontador p;
    TipoNo* Auxp, AuxHeap;

    for(i=0; i<Grafo->numeroNos; i++){
        p = Grafo->ListaAdjacencia[i]->inicio->proximo;
        Auxp = p->item;
        menor = INT_MAX;
        sinal = 0;
        while(p != NULL){
            Auxp = p->item;
            if(Auxp->peso == menor){   
                sinal++;
            }
            if(Auxp->peso < menor){    
                menor = Auxp->peso;
                sinal = 0;
            }
            p = p->proximo;
        }
        if(!sinal){
            AuxHeap = Heap[i];  
            Heap[i] = Heap[0];
            Heap[0] = AuxHeap;

            Posicao[0] = i;
            Posicao[i] = 0;

            return;
        }
    }
}