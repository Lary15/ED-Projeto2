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

/*Funcao imprime a MST com arestas ordenadas e calcula seu custo.
O heap eh um array de nos. O id do no e seu pai formam uma aresta.
Caso o pai de um no seja igual a -1 essa aresta nao pertence a MST*/ 
void ImprimeMst(char* nomeArquivo, TipoNo* Heap, int tamanhoHeap, int* custoMst){
    FILE* ponteiroArquivo;
    int idFilho, idPai, k=0;

    ponteiroArquivo = fopen(nomeArquivo, "w");

    /*O primeiro loop procura pelos ids de nos em ordem crescente e o segundo percorre o heap
    em busca de arestas com esse id tambem em ordem crescente*/
    for(idFilho=0; idFilho < tamanhoHeap; idFilho++){
        for(idPai=idFilho+1; idPai < tamanhoHeap; idPai++){
            for(k=0; k < tamanhoHeap; k++){
                if(Heap[k].pai != -1){ 
                    if(Heap[k].pai == idFilho && Heap[k].id == idPai){
                        fprintf(ponteiroArquivo, "%d,%d\n", Heap[k].pai , Heap[k].id);
                        Heap[k].pai = -1;
                        *custoMst += Heap[k].peso;
                    }
                    if(Heap[k].id == idFilho && Heap[k].pai == idPai){
                        fprintf(ponteiroArquivo, "%d,%d\n", Heap[k].id , Heap[k].pai);
                        Heap[k].pai = -1;
                        *custoMst += Heap[k].peso;
                    }
                }       
            }
        }
    }
    fclose(ponteiroArquivo);
}

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

void ImprimeMst2(char* nomeArquivo, TipoNo* Heap, int tamanhoHeap, int* custoMst){
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

