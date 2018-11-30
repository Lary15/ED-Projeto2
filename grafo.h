#ifndef GRAFO_H
#define GRAFO_H

#include <stdio.h>
#include <stdlib.h>
#include "lista.h"

/*
Estrutura no, que participa da lista de adjacencia: 
    id: o numero do vertice;
    peso: peso da aresta;
    chave: utilizada durante o algoritmo para guardar a menor aresta associado;
    pai: utilizado durante o algoritmo para guardar o no associado dentro d mst; 
*/

typedef struct{ 
    int id;
    int peso;
    int chave;
    int pai;
} TipoNo;

typedef struct{
    int numeroNos;
    TipoLista** ListaAdjacencia;
} TipoGrafo;

#endif