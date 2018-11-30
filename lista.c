#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*Aloca uma célula dinamicamente*/
Apontador alocaCelula(){
	return(TipoCelula*)malloc(sizeof(TipoCelula));
}

/*Aloca uma lista dinamicamente*/
TipoLista* alocaLista(){
	return (TipoLista*)malloc(sizeof(TipoLista));
}

/*Cria uma lista vazia*/
TipoLista* criaListaVazia(){
	TipoLista* Lista;
	Lista = alocaLista();
	Lista->inicio = alocaCelula();
	Lista->fim = Lista->inicio;
	Lista->inicio->proximo = NULL;
	return Lista;
}

/*Cria um vetor de listas vazias*/
TipoLista** criaVetorLista(int tamanho){
	TipoLista** vetorLista;
	int i;
	vetorLista = (TipoLista**) malloc(sizeof(TipoLista*) * tamanho);
	for(i = 0; i < tamanho; i++){
		vetorLista[i] = criaListaVazia();
	}
	return vetorLista;
}

/*Verifica se a lista está vazia*/
int vazia(TipoLista* Lista){
	return (Lista->inicio == Lista->fim);
}

/*Adiciona um elemento ao final da lista*/
void adicionaCelula(void* item, TipoLista* Lista){
	Apontador novaCelula;
	novaCelula = alocaCelula();
	Lista->fim->proximo = novaCelula;
	Lista->fim = novaCelula;
	Lista->fim->item = item;
	Lista->fim->proximo = NULL;	
}

/*Remove o primeiro elemento na lista e atribui um novo primeiro elemento*/
void* removeCelula(TipoLista* Lista){
	void* item;
	Apontador cel;
	if(vazia(Lista)){
		return NULL;
	}
	cel = Lista->inicio;
	Lista->inicio = Lista->inicio->proximo;
	item = Lista->inicio->item;
	free(cel);

	return item;
}

// Libera o espaço de memória de toda a lista
void freeLista(TipoLista* Lista){
	void* lixo;
	while(!vazia(Lista)){
		lixo = removeCelula(Lista);
		free(lixo);
	}
	free(Lista->inicio);
	free(Lista);
}

// Libera o espaço de memória de um vetor de listas
void freeVetorLista(TipoLista** vetorLista, int tamanho){
	int i;
	for(i = tamanho - 1; i >= 0; i--){
		freeLista(vetorLista[i]);
	}
	free(vetorLista);
}
