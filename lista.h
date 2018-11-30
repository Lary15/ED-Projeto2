#ifndef LISTA_H
#define LISTA_H

#include <stdio.h>
#include <stdlib.h>

/*Tipos de variável*/

typedef struct Celula* Apontador;

/*Celulas da Lista*/
typedef struct Celula{
	void* item;
	Apontador proximo;
}TipoCelula;

/*Lista*/
typedef struct{
	Apontador inicio, fim;
}TipoLista;

/*Protótipo das funções*/

Apontador alocaCelula(); /*Aloca uma célula dinamicamente*/
TipoLista* alocaLista(); // Aloca uma lista dinamicamente
TipoLista* criaListaVazia(); /*Cria uma lista vazia*/
TipoLista** criaVetorLista(int tamanho); /*Cria um vetor de listas vazias*/
int vazia(TipoLista* Lista); /*Verifica se a lista está vazia*/
void adicionaCelula(void* item, TipoLista* Lista); /*Adiciona uma célula ao final da lista*/
void* removeCelula(TipoLista* Lista); /*Remove uma célula no início da lista*/
void freeLista(TipoLista* Lista); // Libera o espaço de memória de toda a lista
void freeVetorLista(TipoLista** vetorLista, int tamanho); // Libera o espaço de memória de um vetor de listas

#endif