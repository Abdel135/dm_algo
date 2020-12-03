#include "liste.h"

/*
    Représentation du graph par la liste d'adjacence 
*/

#ifndef GRPAHE_H
#define GRAPHE_H

/*
 Structure d'un nœud
*/ 

typedef struct node{
    int id;
    struct node* next;
}node;

/*
    Liste d'adjacence 
*/

typedef struct adjList{
    node *head;
}adjList;
/* 
    Structure du graphe : lsite des nœuds 
*/

typedef struct graphe{
    int nb_sommets;
    adjList* adj;
}graphe;

/*
    Creation d'un nœud avec id comme valeur 
    @return NULL en cas d'echec si non l'adresse du nœud
*/
node *creer_node(int id);

/*
    Supression d'un nœud
*/
void suprimer_node(node* n);


/*
    intitalisation d'un nouveau graphe de degre N
    @return NULL en cas d'echec si non 0
*/
graphe* graph_init(int N);


/*
    Supression du graphe
*/
void suprimer_graphe(graphe *g);


/*
    ajout d'une arrete V<--->W
    @return -1 en cas d'echec si non 0
*/
int ajouter_arete(graphe *g ,int v,int w );


/*
    Parcours DFS recursive 
*/
void DFS_recursif(graphe *g,int id,int*visited);


/*
    DFS itératif
*/
void DFS_iteratif(graphe *g);

/*
    affichage du graphe 
*/
void afficher_grpahe(graphe *g);

#endif 