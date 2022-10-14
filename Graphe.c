#include <stdio.h>
#include <stdlib.h>
#include "Graphe.h"

/* affichage des successeurs du sommet num*/
void afficher_successeurs(pSommet * sommet, int num)
{

    //printf(" sommet %d :\n",num);


    pArc arc = sommet[num]->arc;
    while(arc!=NULL)
    {
        printf("%d -> %d poids: %d \n",num, arc->sommet, arc->poids);
        arc=arc->arc_suivant;
    }

}

// Ajouter l'arête entre les sommets s1 et s2 du graphe
pSommet* CreerArete(pSommet* sommet,int s1,int s2, int poids)
{
    if(sommet[s1]->arc==NULL)
    {
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->depart = s1;
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids = poids;
        sommet[s1]->arc=Newarc;
        return sommet;
    }

    else
    {
        pArc temp = sommet[s1]->arc;
        while( !(temp->arc_suivant==NULL))
        {
            temp=temp->arc_suivant;
        }
        pArc Newarc=(pArc)malloc(sizeof(struct Arc));
        Newarc->depart = s1;
        Newarc->sommet=s2;
        Newarc->arc_suivant=NULL;
        Newarc->poids = poids;

        if(temp->sommet>s2)
        {
            Newarc->arc_suivant=temp->arc_suivant;
            Newarc->sommet=temp->sommet;
            Newarc->poids = temp->poids;
            Newarc->depart = s1;
            temp->sommet=s2;
            temp->poids=poids;
            temp->arc_suivant=Newarc;
            return sommet;
        }

        temp->arc_suivant=Newarc;
        return sommet;
    }
}

// créer le graphe
Graphe* CreerGraphe(int ordre)
{

    Graphe * Newgraphe=(Graphe*)malloc(sizeof(Graphe));
    Newgraphe->pSommet = (pSommet*)malloc(ordre*sizeof(pSommet));

    for(int i=0; i<ordre; i++)
    {
        Newgraphe->pSommet[i]=(pSommet)malloc(sizeof(struct Sommet));
        Newgraphe->pSommet[i]->valeur=i;
        Newgraphe->pSommet[i]->arc=NULL;
    }
    return Newgraphe;
}

/* La construction du réseau peut se faire à partir d'un fichier dont le nom est passé en paramètre
Le fichier contient : ordre, taille,orientation (0 ou 1)et liste des arcs */
Graphe * lire_graphe(char * nomFichier)
{
    Graphe* graphe;
    FILE * ifs = fopen(nomFichier,"r");
    int taille, ordre, s1, s2, poids;

    if (!ifs)
    {
        printf("Erreur de lecture fichier\n");
        exit(-1);
    }


    fscanf(ifs,"%d",&ordre);
    graphe = CreerGraphe(ordre); // créer le graphe d'ordre sommets

    graphe->ordre = ordre;

    //fscanf(ifs,"%d",&orientation);
    //graphe->orientation=orientation;

    for(int i=0; i<graphe->ordre; i++)
    {
        fscanf(ifs, "%d", &graphe->pSommet[i]->valeur);
    }


    fscanf(ifs,"%d",&taille);
    graphe->taille=taille;

    // créer les arêtes du graphe
    for (int i=0; i<taille; ++i)
    {
        fscanf(ifs,"%d%d%d",&s1,&s2, &poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s1, s2, poids);
        graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);

        //if(!orientation)
            //graphe->pSommet=CreerArete(graphe->pSommet, s2, s1, poids);
    }

    return graphe;
}

/*affichage du graphe avec les successeurs de chaque sommet */
void graphe_afficher(Graphe* graphe)
{
    printf("graphe\n");

    printf("ordre = %d\n",graphe->ordre);
    //printf("listes d'adjacence :\n");

    for (int i=0; i<graphe->ordre; i++)
    {

        afficher_successeurs(graphe->pSommet, i);

    }
    printf("\n");
}


////////////////////////////////////////////////////////////////////


///L'algorithme suit exactement le même déroulé que cette vidéo : https://www.youtube.com/watch?v=3EYWgIiNm8M
void prim(struct Graphe* graph, int depart, edge_list *ListeMST)
{
    int V = graph->ordre;

    int dist[V];        ///tableau de distances pour choisir l'arc avec le poid minimum
    pArc minEdge[V];    ///tableau qui stock l'arrete adjacente au sommet u qui a le poids minimum
    int inMST[V];      ///Tableau qui sert de booléen, lorsque inMST[u] = 0 le sommet u ne fait pas partie de l'arbe courant

    struct TasMin* minHeap = createMinHeap(V); ///Création du tas qui est notre file de priorité

    for (int i = 0; i < V; i++) ///pour tous les sommets V = ordre du graphe
    {
        dist[i] = INT_MAX;  ///on met les distance à des valeurs "infinies", ici grandes valeurs
        minEdge[i] = NULL;
        inMST[i] = 0;      ///Aucun sommet n'est dans l'arbe pour le moment

        ///Initialisation du tas
        minHeap->array[i] = NouveauNoeudTas(i,dist[i], minEdge[i]);
        minHeap->pos[i] = i;
    }


    ///On rajoute le sommet de départ, sa distance est à 0 pour qu'il soit extrait en premier
    dist[depart] = 0;
    decreaseKey(minHeap, depart, dist[depart]); ///on met à jour la distance

    minHeap->size = V;  /// taille tas = ordre graphe
    struct NoeudtasMin* minHeapNode;


    while (minHeap->size > 0) ///tant que le tas n'est pas vide
    {
        ///On extrait le sommet qui a la distance minimum au sommet de départ
        minHeapNode = extractMin(minHeap);
        int u = minHeapNode->v;
        pArc Temparc = graph->pSommet[u]->arc;

        ///Si il existe une arrete adjacente de poids minimum au sommet u, on l'ajoute dans l'arbre
        ///Au départ minEdge[u] est vide, mais cela change dans la boucle while(Temparc!=NULL)
        if(minEdge[u] != NULL)
        {
            ListeMST->data[ListeMST->n] = minEdge[u];
            ListeMST->n ++;
            inMST[minEdge[u]->sommet]=1;
        }

        ///On parcourt toutes les arretes reliées au sommet de distance minimum
        ///Si le prochain sommet est toujours dans la file de priorité, que sa distance est supérieure au poids de l'arrete, et qu'il n'appartient pas à l'arbe couvrant
        while(Temparc!=NULL) ///Pour chaque noeud voisin
        {
            int prochainSommet = Temparc->sommet;
            if (isInMinHeap(minHeap, prochainSommet) && Temparc->poids <= dist[prochainSommet] && inMST[prochainSommet]==0)
            {
                    /// On met à jour la distance
                    dist[prochainSommet] = Temparc->poids;
                    decreaseKey(minHeap, prochainSommet, dist[prochainSommet]);
                    ///on lui assigne une arrete adjacente de poids minimum
                    minEdge[prochainSommet]=Temparc;
            }
            Temparc=Temparc->arc_suivant;

        }

    }


    ///On affiche toutes les arrêtes dans l'ordre
    ///On affiche le poids total de l'arbre
    int cost=0;
    for(int i=0;i<ListeMST->n;i++)
    {
        printf("\n%d --> %d , Poids : %d",ListeMST->data[i]->depart,ListeMST->data[i]->sommet,ListeMST->data[i]->poids);
        cost=cost+ListeMST->data[i]->poids;
    }

    printf("\n\nLe poids total de l'arbre couvrant est : %d \n\n",cost);




}
