#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "lista.h"

/*
Estrutura no, que participa da lista de adjacencia: 
    id: o numero do vertice;
    peso: peso da aresta;
    chave: utilizada durante o algoritmo para guardar a menor aresta associada;
    pai: utilizado durante o algoritmo para guardar o no associado da aresta da mst;
    contador_chave: inteiro necessario para testar unicidade da mst;
*/

typedef struct{ 
    int id;
    int peso;
    int chave;
    int pai;
    int contador_chave;
} TipoNo;

typedef struct{
    int numeroNos;
    TipoLista** ListaAdjacencia;
} TipoGrafo;

/*Funcao que determina qual no vai estar na posicao zero do heap e, consequentemente, ser o inicio da mst*/
void escolheInicio(TipoNo* Heap, TipoGrafo* Grafo, int* Posicao);
#endif