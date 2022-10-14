#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

void swap(struct NoeudtasMin** a, struct NoeudtasMin** b)
{
    struct NoeudtasMin* t = *a;
    *a = *b;
    *b = t;
}

// Function to heapify the tree
void heapify(struct TasMin* minHeap, int idx)
{

    int smallest, left, right;
    smallest = idx;
    left = 2 * idx + 1;
    right = 2 * idx + 2;

    if (left < minHeap->size &&
        minHeap->array[left]->distance <
        minHeap->array[smallest]->distance )
        smallest = left;

    if (right < minHeap->size &&
        minHeap->array[right]->distance <
        minHeap->array[smallest]->distance )
        smallest = right;

    if (smallest != idx)
    {
        // The nodes to be swapped in min heap
        struct NoeudtasMin *smallestNode =
                minHeap->array[smallest];
        struct NoeudtasMin *idxNode =
                minHeap->array[idx];

        // Swap positions
        minHeap->pos[smallestNode->v] = idx;
        minHeap->pos[idxNode->v] = smallest;

        // Swap nodes
        swap(&minHeap->array[smallest],
                        &minHeap->array[idx]);

        heapify(minHeap, smallest);
    }
}

struct NoeudtasMin* extractMin(struct TasMin* tas)
{
    if (tas->size == 0)
    {
        return NULL;
    }

    // Store the root node
    struct NoeudtasMin* root = tas->array[0];

    // Replace root node with last node
    struct NoeudtasMin* lastNode = tas->array[tas->size - 1];
    tas->array[0] = lastNode;

    // Update position of last node
    tas->pos[root->v] = tas->size-1;
    tas->pos[lastNode->v] = 0;

    // Reduce heap size and heapify root
    --tas->size;
    heapify(tas, 0);

    return root;
}

struct TasMin* createMinHeap(int capacity)
{
    struct TasMin* tas = (struct TasMin*)malloc(sizeof(struct TasMin));
    tas->pos = (int *)malloc(capacity * sizeof(int));
    tas->size = 0;
    tas->capacity = capacity;
    tas->array =(struct NoeudtasMin**)malloc(capacity *sizeof(struct NoeudtasMin*));
    return tas;
}

struct NoeudtasMin* NouveauNoeudTas(int v,int dist, struct Arc* minEdge)
{
    struct NoeudtasMin* minHeapNode =(struct NoeudtasMin*)malloc(sizeof(struct NoeudtasMin));
    minHeapNode->v = v;
    minHeapNode->distance = dist;
    minHeapNode->minEdge = minEdge;
    return minHeapNode;
}

void decreaseKey(struct TasMin* minHeap,int v, int dist)
{
    // Get the index of v in  heap array
    int i = minHeap->pos[v];

    //On met à jour la distance du noeud
    minHeap->array[i]->distance = dist;

    // Travel up while the complete
    // tree is not hepified.
    // This is a O(Logn) loop
    while (i && minHeap->array[i]->distance < minHeap->array[(i - 1) / 2]->distance)
    {
        // Swap this node with its parent
        minHeap->pos[minHeap->array[i]->v] =(i-1)/2;
        minHeap->pos[minHeap->array[(i-1)/2]->v] = i;
        swap(&minHeap->array[i],&minHeap->array[(i - 1) / 2]);
        // move to parent index
        i = (i - 1) / 2;
    }
}

int isInMinHeap(struct TasMin *minHeap, int v)
{
    if (minHeap->pos[v] < minHeap->size)
        return 1;
    return 100000;
}



