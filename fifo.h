#ifndef FIFO_H_INCLUDED
#define FIFO_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "Graphe.h"

struct _file {
    int longueur;
    Cellule tete;
    Cellule queue;
};

typedef struct _file* File;

struct NoeudtasMin {

    int v;
    int distance;
    struct Arc* minEdge;
};

struct TasMin
{
    // Number of heap nodes present currently
    int size;
    // Capacity of min heap
    int capacity;
    // This is needed for decreaseKey()
    int *pos;
    struct NoeudtasMin **array;
};

void swap(struct NoeudtasMin** a, struct NoeudtasMin** b);
void heapify(struct TasMin* tas, int index);
struct NoeudtasMin* extractMin(struct TasMin* tas);
struct TasMin* createMinHeap(int capacity);
struct NoeudtasMin* NouveauNoeudTas(int v,int dist, struct Arc* minEdge);
void decreaseKey(struct TasMin* minHeap,int v, int dist);
int isInMinHeap(struct TasMin *minHeap, int v);


    #endif // FIFO_H_INCLUDED