#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "graphe.h"
#include "liste.h"


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
/*------------------------*/


void read_graph(graphe **g)
{

    printf("Voulez-vous :\n");
    printf("1 :Continuez avec le graphe fournit dans le sujet de devoir\n");
    printf("2 :Testez un nouveau graphe avec une nouvelle matrice d'adjacence\n");
    printf("1 ou 2 : ");
    int choix=0;
    scanf("%d",&choix);
    if(choix == 1)return;
    

    int n;
    printf("Entrez la taille de matrice d'adjacence : ");
    scanf("%d",&n);
    
    while(n <= 0)
    {
        printf("Entrez une taille valide : ");
        scanf("%d",&n);
    }
    *g=graph_init(n);

    int matrice[n][n];
    printf("copier votre matrice ici : \n");
    for (int i=0; i<n;++i)
        for (int j=0;j<n;++j)
            scanf("%d",&matrice[i][j]);

    for (int i=0; i<n-1; ++i)
    {
        for (int j=i+1; j<n;++j)
        {
            if(matrice[i][j] >= 1){
                ajouter_arete(*g,i,j);
            }
        }
    }
    
}






/*----------------------*/



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


     // add W --> V
    V->next = g->adj[w].head; 
    g->adj[w].head = V; 
  
    
    // add V --> W
    W->next = g->adj[v].head; 
    g->adj[v].head = W; 

    return 0;

}



void DFS_recursif_helper(graphe *g,int id,int* visited,liste *M,liste *N,int *pere)
{       
      
           
            visited[id]=1;
            node *n=g->adj[id].head;
        
            liste_ajouter_fin(M,id);
            
            // appel DFS sur les voisins de ' id '
            while (n!=NULL)
            {
                if(!visited[n->id])
                {
                    pere[n->id]=id;
                    DFS_recursif_helper(g,n->id ,visited,M,N,pere);
                    
                }  
            n=n->next;
            }

            //Back-track après qu'il ne reste aucun sommet à visiter
            // ajouter le sommet à la liste "SUFFIX" si tous ces voisins ont étés visités 
            int explored=1;
            node *tmp=g->adj[id].head;
            while(tmp != NULL)
            {
                if(!liste_contient_element(M,tmp->id))
                {
                    explored=0;break;
                }
                tmp=tmp->next;
            }
            // si tous ces voisin on étés visités 
            if(explored)liste_ajouter_fin(N,id);
            
}


void DFS_recursif(graphe *g,int start_node)
{
    int n=g->nb_sommets;
    liste *M=liste_construire(n);
    liste *N=liste_construire(n);
    int pere[n];
    pere[start_node]=-1;
    
    int visited[n];
    for (int i=0;i<n;++i) visited[i]=0;
    DFS_recursif_helper(g,start_node,visited,M,N,pere);
    
    putchar('\n');
    printf("\tM : ");liste_afficher(M);
    printf("\tN : ");liste_afficher(N);

    
    int *m=liste_get_debut(M);
    int *n_=liste_get_debut(N);


    /*********************/ 


    puts("Trace :\n");
    printf("sommet  prefix  suffix  pere\n");

    for (int i=0 ;i< n ;++i)
    {
        printf("%5d  %5d  %5d",i,*m,*n_);
        if(i == start_node) printf("     -");
        else printf("  %5d",pere[i]);

        m=liste_get_suivant(M,m);
        n_=liste_get_suivant(N,n_);
        puts("");
    }
   
}



void DFS_iteratif(graphe *g,int start)
{
    //printf("DFS : iteratif : \n");
    int n=g->nb_sommets;
    int visited[n];
    int pere[n];
    pere[start]=-1;

    pere[start]=pere[start];

    for(int i=0; i<n ; ++i) visited[i]=0;

    liste *M=liste_construire(n);
    liste *N=liste_construire(n);
    liste *stack=liste_construire(n);

    liste_ajouter_fin(stack,start);
    liste_ajouter_fin(M,start);
    visited[start]=1;

    // tant que la pile n'est pas vide

    while(!liste_est_vide(stack))
    {
        int *x=liste_get_fin(stack);
        int explored=1;
        node *tmp=g->adj[*x].head;
        while(tmp!=NULL)
        {
            if(!visited[tmp->id])
            {
                explored=0;
                visited[tmp->id]=1;
                pere[tmp->id]=*x;
                liste_ajouter_fin(stack,tmp->id);
                liste_ajouter_fin(M,tmp->id);
                liste_ajouter_fin(stack,tmp->id);break;
            }
            tmp=tmp->next;
        }
        if(explored){
            x=malloc(sizeof(int));
            liste_supprimer_fin(stack,x);
            liste_ajouter_fin(N,*x);
            free(x);
        }

    }
    printf("\tM : ");liste_afficher(M);
    printf("\tN : ");liste_afficher(N);

    
    int *m=liste_get_debut(M);
    int *n_=liste_get_debut(N);


    /*********************/ 


    puts("Trace :\n");
    printf("sommet  prefix  suffix  pere\n");

    for (int i=0 ;i< n ;++i)
    {
        printf("%5d  %5d  %5d",i,*m,*n_);
        if(i == start) printf("     -");
        else printf("  %5d",pere[i]);

        m=liste_get_suivant(M,m);
        n_=liste_get_suivant(N,n_);
        puts("");
    }

}







void write_dot(const char *file,graphe *g)
{
    FILE *f = fopen(file,"w");
    if (f == NULL)  {puts("file error");exit(0);}
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
    printf("\n\n*** Liste d'adjacence ***\n\n");
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
    putchar('\n');
}

// add parent and make sure to add it once  like 2->0 2->3

int main()
{
        clock_t start,end;
        double cpu_time;

        graphe *g=graph_init(8);
    
        ajouter_arete(g,0,2);
        ajouter_arete(g,0,1);
        ajouter_arete(g,1,4);
        ajouter_arete(g,3,4);
        ajouter_arete(g,1,3);
        ajouter_arete(g,2,3);
        ajouter_arete(g,4,6);
        ajouter_arete(g,4,5);
        ajouter_arete(g,5,6);
        ajouter_arete(g,6,7);

        read_graph(&g);

        affichier_graphe(g);
        
        printf("DFS iteratif : \n");

        start=clock();
        DFS_iteratif(g,0);
        end=clock();
        cpu_time=((double)(end - start))/CLOCKS_PER_SEC;
        printf("temps d'execusion : %fs\n",cpu_time);

        printf("\n\n/********************************/\n\n");
        printf("DFS recursif : \n");

        start=clock();
        DFS_recursif(g,0);
        end=clock();
        cpu_time=((double)(end - start))/CLOCKS_PER_SEC;
        printf("temps d'execusion : %fs\n",cpu_time);

        
    

        write_dot("g.dot",g);
}
// dfs visited // 