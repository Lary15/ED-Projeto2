#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "grafo.h"

/*Funcao le a matriz de adjacencia e constroi um grafo criando um 
array de lista de adjacencias*/
TipoGrafo* LeGrafo(char* nomeArquivo, int* custoGrafoTodo){
    FILE* ponteiroArquivo;
    int i, j, peso;
    TipoGrafo* Grafo = malloc(sizeof(TipoGrafo));    
    TipoNo* no;

    ponteiroArquivo = fopen(nomeArquivo, "r");
    fscanf(ponteiroArquivo, "%d", &Grafo->numeroNos); 
    Grafo->ListaAdjacencia = criaVetorLista(Grafo->numeroNos);

    for(i=0; i<Grafo->numeroNos; i++){
        for(j=0; j<Grafo->numeroNos; j++){
            fscanf(ponteiroArquivo, "%d", &peso);
            if(peso){ 
                no = (TipoNo*) malloc(sizeof(TipoNo));
                no->id = j;
                no->peso = peso;
                adicionaCelula(no, Grafo->ListaAdjacencia[i]);

                /*Calcula-se o custo do grafo todo conexo com a soma dos pesos diferentes 
                de zero da matriz triangular superior*/
                if(j>i)
                    *custoGrafoTodo += peso;
            }    
        }
    }   

    fclose(ponteiroArquivo);
    return Grafo;
}

/*Funcao auxiliar para melhor vizualizacao do grafo*/
void ImprimeGrafo(TipoLista** ListaAdjacencia, int numeroNos){
    Apontador p;
    TipoNo* Auxp;
    int i, j;

    for(i=0; i<numeroNos; i++){
        printf("NO #%d\n", i);
        p = ListaAdjacencia[i]->inicio->proximo;
        while(p!=NULL){
            Auxp = p->item;
            printf("\tLigado a :%d por aresta de peso: %d\n", Auxp->id, Auxp->peso);
            p = p->proximo;
        }
    }
}

/*As duas funcoes de insertionSort sao para a ordenacao da saida. 
A filho eh feita baseada no id do no e a pai baseada no pai do no*/
void insertionSortFilho(TipoNo* Heap, int tamanhoHeap){
    int  i, j;
    TipoNo aux;

    for (i = 1; i < tamanhoHeap; i++) {
		aux = Heap[i];
		j = i - 1;
		while ((j >= 0) && (Heap[j].id > aux.id)) {
			Heap[j + 1] = Heap[j];
			j--;
		}
		Heap[j + 1] = aux;
	}
}

void insertionSortPai(TipoNo* Heap, int tamanhoHeap){
    int i, j;
    TipoNo aux;

    for (i = 1; i < tamanhoHeap; i++) {
		aux = Heap[i];
		j = i - 1;
		while ((j >= 0) && (Heap[j].pai > aux.pai)) {
			Heap[j + 1] = Heap[j];
			j--;
		}
		Heap[j + 1] = aux;
	}
}

/*Funcao imprime a MST com arestas ordenadas e calcula seu custo.
O Newheap eh um array de nos sem o no com o pai igual a -1, que significa a aresta "pai,id" nao pertencer a mst, 
e com valores de pai certamente maiores que de id*/ 
void ImprimeMst(char* nomeArquivo, TipoNo* Heap, int tamanhoHeap, int* custoMst){
    FILE* ponteiroArquivo;
    int i;
    TipoNo* newHeap;

    newHeap = (TipoNo*)malloc(sizeof(TipoNo)*(tamanhoHeap-1));
    ponteiroArquivo = fopen(nomeArquivo, "w");

    for(i=0; i < tamanhoHeap; i++){
        if(Heap[i].pai != -1){
            if(Heap[i].pai < Heap[i].id){
                newHeap[i].id = Heap[i].pai;
                newHeap[i].pai = Heap[i].id;
                *custoMst += Heap[i].peso;
            }
            else{
                newHeap[i].id = Heap[i].id;
                newHeap[i].pai = Heap[i].pai;
                *custoMst += Heap[i].peso;
            }
        }
    }
    
    insertionSortPai(newHeap, tamanhoHeap-1);
    insertionSortFilho(newHeap, tamanhoHeap-1);

    for(i=0; i < tamanhoHeap-1; i++){
        fprintf(ponteiroArquivo, "%d,%d\n", newHeap[i].id, newHeap[i].pai);
    }

    free(newHeap);
    fclose(ponteiroArquivo);
}

