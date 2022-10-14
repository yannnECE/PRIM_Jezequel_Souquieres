#include "Graphe.h"

/// SOURCES
/// https://www.youtube.com/watch?v=3EYWgIiNm8M
///https://fr.wikipedia.org/wiki/Algorithme_de_Prim


int main()
{
    int depart;
    Graphe * g = lire_graphe("grapheDisjkstra.txt");             ///On lit le graphe selon les donn�es d'un fichier texte

    ///saisie du num�ro du sommet initial et du sommet d'arriv�e
    printf("numero du sommet initial : ");
    scanf("%d", &depart);


    ///ListeMST est une liste d'arr�tes qui repr�sente l'arbre de poids minimum (Minimum Spanning Tree)
    edge_list *ListeMST;
    ///on alloue dynamiquement ses param�tres car la taille de l'arbre est diff�rente selon le graphe
    ListeMST = (edge_list *) malloc(sizeof(edge_list));
    ListeMST->data = (pArc *) malloc(ListeMST->n * sizeof(pArc));///Le tableau d'arr�tes
    ListeMST->n = 0; ///la taille de l'arbe


    /// PRIM AVEC FILE DE PRIORITE
    prim(g, depart, ListeMST);



    return 0;
}
