#include <stdlib.h>
#include <stdio.h>
#include "graphe.h"



node *creer_node(int id)
{
    node* n=(node*)malloc(sizeof(node));
    if (n == NULL ) return NULL;
    n->id=id;
    n->next=NULL;
    return n;
}

/*----------------------*/

void suprimer_node(node *n)
{
    free(n);
}


/*------------------------*/


graphe *graph_init(int N)
{
    graphe *g=(graphe*)malloc(sizeof(graphe));
    if (g == NULL)return NULL;

    g->nb_sommets=N;
    g->adj=(adjList*)malloc(N*sizeof(adjList));

    if(g == NULL ) return NULL;
    for (int i=0;i<N;++i) 
        g->adj[i].head=NULL;
    

    return g;    
}

void suprimer_graphe(graphe *g)
{
    free(g->adj);
    free(g);
}


int ajouter_arete(graphe *g ,int v ,int w) ///v : v     source w
{
    node* V=creer_node(v);
    node *W=creer_node(w);
    if (V == NULL || W == NULL || v >= g->nb_sommets || w >= g->nb_sommets ){puts("sommet invalide");return -1;}

    
    node* newNode = creer_node(v); 
    newNode->next = g->adj[w].head; 
    g->adj[w].head = newNode; 
  
    // Since graph is undirected, add an edge from 
    // v to w also 
    newNode = creer_node(w); 
    newNode->next = g->adj[v].head; 
    g->adj[v].head = newNode; 

    return 0;

}



void DFS_recursif(graphe *g,int id,int* visited)
{
        if(!visited[id])
        {
            visited[id]=1;
            printf("%d ",id);
            node *n=g->adj[id].head;
            
            // appel DFS sur les voisins de ' id '
    
            while (n!=NULL)
            {
                DFS_recursif(g,n->id ,visited);
                n=n->next;
            }
        }
    
    
}





void write_dot(const char *file,graphe *g)
{
    FILE *f = fopen(file,"w");
    if (f == NULL){puts("file error");exit(0);}
    fputs("graph{",f);

    for (int i=0; i < g->nb_sommets ;++i)
        fprintf(f,"%d;\n",i);

    for (int i=0; i <= g->nb_sommets;++i)
    {
        node* n=g->adj[i].head;
        while(n!=NULL)
        {
            fprintf(f,"\t%d--%d;\n",i,n->id);
            n=n->next;
        }
    }
    fputc('}',f);
}



void affichier_graphe(graphe *g){
    int n=g->nb_sommets;
    for(int i=0;i<n;++i)
    {
        printf("%d : [",i);
        node *n=g->adj[i].head;
        while (n!=NULL)
        {
            printf("%d ",n->id);n=n->next;
        }
        puts("]");

    }
}



int main()
{
    graphe *g=graph_init(6);
    int visited[g->nb_sommets];
    for (int i=0 ;i<g->nb_sommets;++i)visited[i]=0;
    ajouter_arete(g,0,1);
    ajouter_arete(g,1,2);
    ajouter_arete(g,1,3);
    ajouter_arete(g,0,3);
    ajouter_arete(g,4,5);
    ajouter_arete(g,2,5);
    //affichier_graphe(g);

    DFS_recursif(g,0,visited);
    write_dot("g.dot",g);
}
