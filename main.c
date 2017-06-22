#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "simulated_annealing.h"
#include "graph_lib.h"
#include "k_opt.h"
#include "nearest_neighbour.h"
#include "language.h"
#include "type.h"
#include "utility.h"

void startmenu(item_language* language,coordinates** graph, int* graphsize, char* graphtitle, int** thisgraph_sol,double*** dist_square_matrix);
int* algomenu(bool opti,item_language* language,coordinates* graph, int* graphsize, char* graphtitle, double** dist_square_matrix);

int main()
{
    coordinates* thisgraph=NULL;
    coordinates** p_thisgraph=&thisgraph;
    item_language language;
    int thisgraph_size;
    char graphtitle[FILENAME_MAX];
    int* thisgraph_sol=NULL;
    double** dist_square_matrix=NULL;
    int** p_thisgraph_sol=&thisgraph_sol;
    double*** p_dist_square_matrix= &dist_square_matrix;
    sprintf(graphtitle,"_Random");
    language_choice(&language);
    startmenu(&language,p_thisgraph,&thisgraph_size,graphtitle,p_thisgraph_sol,p_dist_square_matrix);
    free(thisgraph);
    thisgraph=NULL;
    free_matrix(dist_square_matrix,thisgraph_size);
    dist_square_matrix = NULL;
    free(thisgraph_sol);
    thisgraph_sol=NULL;
    return 0;
}
void startmenu(item_language* language,coordinates** graph, int* graphsize, char* graphtitle, int** thisgraph_sol, double*** dist_square_matrix)
{

    int i,choice=0;
    char enter_k;
    coordinates* temp;

    /* ------------------------------------------
       |    Probleme du voyageur de commerce    |
       ------------------------------------------ */
    printf("%s",language->menu[0].line);
    printf("%s",language->menu[1].line);
    printf("%s\n\n",language->menu[0].line);
    /* Generer un dataset aleatoire
       Charger un dataset */
    printf("1. %s",language->menu[2].line);
    printf("2. %s",language->menu[3].line);

    if(*graph==NULL)
    {
        /* Quitter */
        printf("3. %s\n",language->menu[8].line);
        scanf("%d",&choice);
        clear();
        clear_buffer();
        switch(choice)
        {
        case 1:
            *graph=new_graph(language,graphsize);
            /* Un graphe est maintenant en memoire
               Appuyez sur entree pour revenir au menu */
            printf("%s%s",language->dataset[2].line,language->menu[9].line);
            scanf("%c",&enter_k);
            clear_buffer();
            break;
        case 2:
            *graph=import_dataset(language,graphsize);
            /* Un graphe est maintenant en memoire
               Appuyez sur entree pour revenir au menu */

            printf("%s%s",language->dataset[2].line,language->menu[9].line);
            scanf("%c",&enter_k);
            clear_buffer();
            break;
        case 3:
            return;
        default:
            printf("%s",language->errors[0].line);
            break;
        }
    }
    else
    {
        /* Exporter les donnees du dataset */
        printf("3. %s",language->menu[4].line);
        /* Trouver une solution pour le probleme actuel */
        printf("4. %s",language->menu[5].line);
        /* Optimiser la solution actuelle */
        printf("5. %s",language->menu[6].line);
        /* Quitter */
        printf("6. %s",language->menu[7].line);
        scanf("%d",&choice);
        clear();
        clear_buffer();
        switch(choice)
        {
        case 1:
            free(*graph);
            *graph=NULL;
            if (dist_square_matrix!=NULL){
                free_matrix(*dist_square_matrix,*graphsize);}
            *graph=new_graph(language,graphsize);
            /* Un graphe est maintenant en memoire
               Appuyez sur entree pour revenir au menu */
            printf("%s%s",language->dataset[2].line,language->menu[9].line);
            scanf("%c",&enter_k);
            clear_buffer();
            break;
        case 2:
            free(*graph);
            *graph=NULL;
            if (*dist_square_matrix!=NULL){
                free_matrix(*dist_square_matrix,*graphsize);
            }
            *graph=import_dataset(language,graphsize);
            /* Un graphe est maintenant en memoire
               Appuyez sur entree pour revenir au menu */
            printf("%s%s",language->dataset[2].line,language->menu[9].line);
            scanf("%c",&enter_k);
            clear_buffer();
            break;
        case 3:
            export_dataset(language,*graph,graphtitle,*graphsize,*thisgraph_sol);
            /* Le set de donnees a bien ete exporte
               Appuyez sur entree pour revenir au menu */
            printf("%s%s",language->dataset[3].line,language->menu[9].line);
            scanf("%c",&enter_k);
            clear_buffer();
            break;
        case 4:
            *thisgraph_sol = algomenu(false,language,*graph,graphsize,graphtitle,*dist_square_matrix);
            break;
        case 5:
            temp = malloc((*graphsize+1) * sizeof(*temp));
            for(i=0;i<=*graphsize;i++)
            {
                temp[i].x=graph[0][i].x;
                temp[i].y=graph[0][i].y;
            }
            for(i=0;i<=*graphsize;i++)
            {
                graph[0][i].x=temp[thisgraph_sol[0][i]].x;
                graph[0][i].y=temp[thisgraph_sol[0][i]].y;
            }
            free(temp);
            *thisgraph_sol = algomenu(true,language,*graph,graphsize,graphtitle,*dist_square_matrix);

            break;
        case 6:
            return;
        default:
            printf("%s",language->errors[0].line);
            break;
        }
    }
    clear();
    startmenu(language,graph,graphsize,graphtitle,thisgraph_sol,dist_square_matrix);
}


int* algomenu(bool opti,item_language* language,coordinates* graph, int* graphsize, char* graphtitle, double** dist_square_matrix)
{
    clear();
    free_matrix(dist_square_matrix,*graphsize);
    dist_square_matrix = distancesquare_matrix(language,*graphsize,graph);
    int* thisgraph_init ;

    int choice=0;
    char enter_k;
    /* ------------------------------------------
       |    Probleme du voyageur de commerce    |
       ------------------------------------------ */
    printf("%s",language->menu[0].line);
    printf("%s",language->menu[1].line);
    printf("%s\n\n",language->menu[0].line);

    printf("1. %s",language->algos[0].line);
    printf("2. %s",language->algos[1].line);
    printf("3. %s",language->algos[2].line);
    scanf("%d[^\n]",&choice);
    clear_buffer();
    thisgraph_init = malloc((*graphsize+1) * sizeof(*thisgraph_init));
        for (int i=0;i<*graphsize;i++)
        {
            thisgraph_init[i]=i;
        }
        thisgraph_init[*graphsize]=0;
    switch(choice)
    {
    case 1:
        thisgraph_init=nearest_neighbour(opti,language,dist_square_matrix,*graphsize,graphtitle);
        break;
    case 2:
        thisgraph_init = simulated_annealing(opti,language,dist_square_matrix,*graphsize,thisgraph_init,graphtitle,6);
        break;
    case 3:
        thisgraph_init=opt2_menu(opti,language,dist_square_matrix,*graphsize,thisgraph_init,graphtitle);
        break;
    default:
        printf("%s",language->errors[1].line);
        printf("%s",language->menu[9].line);
        scanf("%c",&enter_k);
        clear_buffer();
        algomenu(opti,language,graph,graphsize,graphtitle,dist_square_matrix);
    }
    thisgraph_init[*graphsize]=thisgraph_init[0];
    for (int k=0;k<*graphsize;k++)
    {
        printf("%d;",thisgraph_init[k]);
    }
    printf("\n");
    scanf("%c",&enter_k);
    clear_buffer();
    return thisgraph_init;
}
