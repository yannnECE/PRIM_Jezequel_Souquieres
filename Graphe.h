#ifndef GRAPHE_H_INCLUDED
#define GRAPHE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "fifo.h"

/* Structure d'un arc*/
struct Arc
{
    int depart;
    int sommet; // num�ro de sommet d'un arc adjacent au sommet initial
    int poids;
    struct Arc* arc_suivant;

};

/* Alias de pointeur sur un Arc */
typedef struct Arc* pArc;

/* Structure d'un sommet*/
struct Sommet
{
    struct Arc* arc;
    int valeur;
    char couleur;
    int distance;
};


/* Alias de pointeur sur un Sommet */
typedef struct Sommet* pSommet;

/* Alias d'un Graphe */
typedef struct Graphe
{
    int taille;
    int ordre;
    pSommet* pSommet;
    pArc* pArc;

} Graphe;

typedef struct edge_list {
    pArc *data;
    int n;
} edge_list;

struct Subset
{
    int Parent;
    int Rank;
};



// cr�er le graphe
Graphe* CreerGraphe(int ordre);

/* La construction du r�seau peut se faire � partir d'un fichier dont le nom est pass� en param�tre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier);

// Ajouter l'ar�te entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1, int s2, int poids);

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num);

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe);


void prim(struct Graphe* graph, int depart, edge_list *ListeMST);

#endif // GRAPHE_H_INCLUDED
