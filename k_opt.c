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

int* opt2_menu(bool opti,item_language* language, double** matrix, int nb_vertex, int* cycle, char* title)
{
    clear();
    int choice;
    /*
    1. Utiliser 2-opt complet
    2. Utiliser 2-opt seulement sur les arretes ascendentes (recommande lorsque le nombre de sommet est grand et que le graphe a ete genere aleatoirement)
    */
    printf("1. %s2. %s",language->algos[3].line,language->algos[4].line);
    scanf("%d^\n",&choice);
    getchar();
    switch (choice)
    {
    case 1:
        return opt2(opti,language,matrix,nb_vertex,cycle,title);
    case 2:
        return opt2_quicker(opti,language,matrix,nb_vertex,cycle,title);
    default :
        return opt2_menu(opti,language,matrix,nb_vertex,cycle,title);
    }
}
int* opt2(bool opti,item_language* language, double **matrix, int nb_vertex, int* cycle, char* title)
{

    int improve=1,i,j,temp;
    printf("%s",language->algos[6].line);
    switch(opti)
    {
        case false:
        sprintf(title,"graph_%d_2opt",nb_vertex);
        break;
        case true:
        sprintf(title,"%s_2opt",title);
        break;
    }
    while (improve)
    {
        improve=0;
        for (i=0;i<nb_vertex-1;i++)
        {
            for (j=0;j<nb_vertex-1;j++)
            {
                if (j==i||j==(i-1)||j==(i+1))
                {
                    continue;
                }
                else
                {
                    if((matrix[cycle[i]][cycle[i+1]]+matrix[cycle[j]][cycle[j+1]])>(matrix[cycle[i]][cycle[j]]+matrix[cycle[i+1]][cycle[j+1]]))
                    {
                        temp = cycle[i+1];
                        cycle[i+1] = cycle[j+1];
                        cycle[j+1] = temp;
                        improve=1;

                    }
                }
            }
        }
        printf("%s\n",language->algos[5].line);
    }
    return cycle;
}

int* opt2_quicker(bool opti,item_language* language, double** matrix, int nb_vertex, int* cycle, char* title)
{
    bool improve=true,i,j,temp;
    printf("%s",language->algos[6].line);
    switch(opti)
    {
        case false:
        sprintf(title,"graph_%d_2opt_quick",nb_vertex);
        break;
        case true:
        sprintf(title,"%s_2opt_quick",title);
        break;
    }
    while(improve)
    {
        improve=false;
        for (i=0;i<nb_vertex-4;i++)
        {
            for (j=i+2;j<nb_vertex-2;j++)
            {
                if((matrix[cycle[i]][cycle[i+1]]+matrix[cycle[j]][cycle[j+1]])>(matrix[cycle[i]][cycle[j]]+matrix[cycle[i+1]][cycle[j+1]]))
                {
                    temp = cycle[i+1];
                    cycle[i+1] = cycle[j+1];
                    cycle[j+1] = temp;

                    temp=cycle[i+2];
                    cycle[i+2]=cycle[j-1];
                    cycle[j-1]=temp;
                    improve=true;
                }
            }
        }
    }
    printf("%s",language->algos[5].line);
    return cycle;
}
