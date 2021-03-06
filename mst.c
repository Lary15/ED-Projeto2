#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"
#include "entrada_saida.h"
#include "heap.h"

int main(int argc, char **argv)
{
    if (argc != 3)
    {
        printf("Erro na passagem de argumentos.\n");
        printf("Execucao do programa deve ser feita com ./mst <arquivo1_texto> <arquivo2_texto>.\n");
        printf("O esperado eh que o arquivo1 contenha o grafo a ser lido e arquivo2 armazene a mst resultante.\n");
        return 0;
    }

    int IdRetirado, tamanhoHeap, custoGrafoTodo=0, custoMst=0, unica=1;

    Apontador n; /* n e Auxn sao variaveis auxiliares utilizadas para percorrer pelas listas de adjacencias*/
    TipoNo* Auxn;
    
    int* Posicao; /*Vetor que guarda a posicao dos nos no heap baseado no seu id, necessario para MudaChave*/
    TipoNo* Heap; /*Um array que representa um heap*/
    TipoGrafo* Grafo; 

    /*Criacao do grafo, Heap e vetor Posicao*/
    Grafo = LeGrafo(argv[1], &custoGrafoTodo);
    tamanhoHeap = Grafo->numeroNos;
    Posicao = (int *)malloc(sizeof(int) * tamanhoHeap);
    Heap = CriaHeap(Grafo->numeroNos, Posicao);

    /*Funcao move para posicao zero um no com arestas minimas nao repetidas*/
    escolheInicio(Heap, Grafo, Posicao);

    /* Algoritmo de Prim*/
    Heap[0].chave = 0;
    while (tamanhoHeap){
        IdRetirado = RetiraMinimo(Heap, &tamanhoHeap, Posicao);

        n = Grafo->ListaAdjacencia[IdRetirado]->inicio->proximo;
        Auxn = n->item;

        while (n != NULL){
            Auxn = n->item;
            if (Posicao[Auxn->id] < tamanhoHeap && Auxn->peso == Heap[Posicao[Auxn->id]].chave){
                Heap[Posicao[Auxn->id]].contador_chave++;
            }
            if (Posicao[Auxn->id] < tamanhoHeap && Auxn->peso < Heap[Posicao[Auxn->id]].chave){
                Heap[Posicao[Auxn->id]].pai = IdRetirado;
                Heap[Posicao[Auxn->id]].peso = Auxn->peso;
                Heap[Posicao[Auxn->id]].contador_chave = 0;
                MudaChave(Heap, Posicao, Auxn->peso, Auxn->id);
            }
            n = n->proximo;
        }
    }

    /* Impressao no arquivo texto de saida e calculo do custo da Mst*/
    ImprimeMst(argv[2], Heap, Grafo->numeroNos, &custoMst);

    printf("Mst com custo: %d\n", custoMst);
    printf("Economia em relacao a malha toda conexa: %d\n", (custoGrafoTodo - custoMst));

    /* Verificando contadores de chave a fim de descobrir se a Mst eh unica*/
    for(int i = 0; i<Grafo->numeroNos; i++){
        if(Heap[i].contador_chave != 0){
            unica=0;
            break;
        }
    }
    if(unica){
        printf("Mst eh unica\n");
    }
    else{
        printf("Mst nao eh unica\n");
    }

    freeVetorLista(Grafo->ListaAdjacencia, Grafo->numeroNos);
    free(Grafo);
    free(Heap);
    free(Posicao);
    return 0;
}