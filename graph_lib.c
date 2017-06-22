#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include "k_opt.h"
#include "nearest_neighbour.h"
#include "language.h"
#include "type.h"
#include "utility.h"



coordinates* new_graph(item_language* language, int* sizeofgraph)
{
    /*
    Renvoie un pointeur sur tableau de coordinates
    Il sera nécéssaire de libérer la mémoire avec free pour éviter les fuites de mémoire
    */

    int nb_vertex;
    coordinates *list_xy=NULL;
    printf("%s",language->dataset[0].line);
    scanf("%d", &nb_vertex);
    /* Allocation dynamique de mémoire pour la structure */
    list_xy = malloc(nb_vertex * sizeof(coordinates));
    if(list_xy == NULL)
    {
        /* Erreur lors de la tentative d'allocation de memoire */
        printf("%s",language->errors[1].line);
        exit(EXIT_FAILURE);
    }
    for (int i=0;i<nb_vertex;i++)
    {
        list_xy[i].x= random_nb();
        list_xy[i].y= random_nb();
    }
    *sizeofgraph=nb_vertex;
    return list_xy;
}

double random_nb()
{
    /* Générateur semi-aléatoire de nombres entre 0 et MAXR */
    static int first = 0;
    if (first == 0)
    {
        srand (time (NULL));
        first = 1;
    }
    return rand()/(double)RAND_MAX;
}

void export_dataset(item_language* language,coordinates* graph, char* algo, int graph_size, int* graph_mini)
{
    char title[TMAX];
    /* Fichier source du graph */
    sprintf(title,"graph_%d.csv",graph_size);
    FILE* filename = fopen(title,"w+");
    if (filename!=NULL)
    {
        fprintf(filename,"%2f,%2f,Graphe aleatoire,%d\n",graph[0].x,graph[0].y,graph_size);
        for (int i=1;i<graph_size;i++)
        {
            fprintf (filename,"%2f,%2f\n",graph[i].x,graph[i].y);
        }
        fclose(filename);
    }
    else
    {
        /* Erreur lors de la sauvegarde : aucun fichier n'a pu etre lu ou cree */
        printf("%s",language->errors[3].line);
    }
    if (graph_mini!=NULL)
    {
        /* Fichier solution avec algo */
        sprintf(title, "%s.csv",algo);
        filename=fopen(title,"w+");
        if (filename!=NULL)
        {
            fprintf(filename,"%2f,%2f,%s,%d,%2f,%2f\n",graph[graph_mini[0]].x,graph[graph_mini[0]].y,algo,graph_size,graph[0].x,graph[0].y);
            for (int i=1;i<=graph_size;i++)
            {
                fprintf (filename,"%2f,%2f,,,%2f,%2f\n",graph[graph_mini[i]].x,graph[graph_mini[i]].y,graph[i].x,graph[i].y);
            }
            fclose(filename);

        }
    }
    else
        {
            /* Aucune solution n'est disponible en memoire ! */
            printf("%s",language->errors[4].line);
        }
}

coordinates* import_dataset(item_language* language,int* size_after_import)
{
    /*
    Parsing du fichier dont le nom est demandé
    Renvoie un pointeur sur tableau de coordinates
    Il sera nécéssaire de libérer la mémoire avec free pour éviter les fuites de mémoire
    */

    char algo[FBUF];
    char filename[FILENAME_MAX];
    double cur_x;
    double cur_y;
    int graph_size;
    coordinates *graph=NULL;
    /* Quel est le nom du fichier *.csv que vous souhaiter importer ? */
    printf("%s",language->dataset[1].line);
    scanf("%s",filename);
    FILE* thisfile =NULL;
    sprintf(filename,"%s.csv",filename);
    thisfile = fopen(filename,"r");
    if(thisfile!=NULL)
    {
        if(fscanf(thisfile,"%lf,%lf,%[^','],%d",&cur_x,&cur_y,algo,&graph_size)==EOF)
        {
            /* TODO : Message d'erreur ouverture */
            printf("%s",language->errors[2].line);
        }
        else
        {
            /* Allocation de mémoire */
            graph = malloc(graph_size * sizeof(*graph));
            /* Assignation des données */
            graph[0].x=cur_x;
            graph[0].y=cur_y;
            for(int i=1;i<graph_size;i++)
            {
                fscanf(thisfile,"%lf,%lf,,",&cur_x,&cur_y);
                graph[i].x=cur_x;
                graph[i].y=cur_y;
            }
            *size_after_import=graph_size;
            char k;
            scanf("%c",&k);

        }
    }
    else
    {
        /* Impossible de trouver ce fichier
           Appuyez sur une touche pour revenir au menu */
        printf("%s, %s",language->errors[2].line,language->menu[9].line);
    }
    return graph;
}

double** distancesquare_matrix (item_language* language,int nb_vertex,coordinates* graph)
{
    int i,j;
    double distsq;
    double **matrix;
    char err;

    /* tableau dynamique de pointeurs sur pointeurs */
    matrix = malloc(nb_vertex * sizeof(*matrix));
    if(matrix == NULL)
    {
        /* Erreur lors de la tentative d'allocation de memoire
           Appuyez sur une touche pour revenir au menu */
        printf("%s%s",language->errors[1].line,language->menu[9].line);
        scanf("%c",&err);
        clear_buffer();
        return NULL;
    }

    for(i=0 ; i < nb_vertex ; i++)
    {
        /* tableau dynamique de pointeurs sur int */
        matrix[i] = malloc(nb_vertex * sizeof(**matrix) );
        if(matrix[i] != NULL)
        {
            for (j=0;j<nb_vertex;j++)
            {
                distsq=fabs(pow(graph[j].x-graph[i].x,2)+pow(graph[j].y-graph[i].y,2));
                matrix[i][j]=distsq;
            }
        }
        else
        {
            for (i=i-1;i>=0;i--)
            {
                free(matrix[i]);
            }
            free(matrix);
            /* Erreur lors de la tentative d'allocation de memoire
               Appuyez sur une touche pour revenir au menu */
            printf("%s%s",language->errors[1].line,language->menu[9].line);
            scanf("%c",&err);
            clear_buffer();
            return NULL;
        }
    }
    return matrix;
}
 void free_matrix(double** matrix,int nb_vertex)
 {
    if (matrix!=NULL)
    {
        for (int i=nb_vertex-1;i>=0;i--)
        {
            free(matrix[i]);
        }
        free(matrix);
        matrix=NULL;
    }
 }
