#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "graph_lib.h"
#include "k_opt.h"
#include "nearest_neighbour.h"
#include "language.h"
#include "type.h"
#include "utility.h"


int* nearest_neighbour(bool opti,item_language* language, double** matrix, int nb_vertex, char* title)
{
	int k = 1;
	int j;
	int index=0;
	bool est_libre;
	int i = 0;
	double temp=TVAL;
    double dist;
    int *liste=malloc(sizeof(*liste)*(nb_vertex+1));

    for (i=1;i<nb_vertex;i++)
    {
        liste[i]=-1;
    }
    liste[0]= 0;
    i=0;

    switch(opti)
    {
        case false:
        sprintf(title,"graph_%d_NearestNeighbour",nb_vertex);
        break;
        case true:
        sprintf(title,"%s_NearestNeighbour",title);
        break;
    }
    printf("%s",language->algos[6].line);
	while ( k < nb_vertex)
	{

		for(j=0; j<nb_vertex;j++)
        {
            dist=matrix[i][j];
            est_libre = libre(liste,k,j);
			if(dist && (dist<temp)&& est_libre)
            {
                temp = dist;
                index = j;
            }
        }
		liste[k] = index;
		i = index;
		temp=TVAL;
        k++;
    }
liste[nb_vertex]= liste[0];
printf("%s", language -> algos[5].line);
return liste;

}

bool libre(int* liste ,int taille,int index_cherche)
{
    for (int i=0;i<=taille;i++)
    {
        if (index_cherche==liste[i])
        {
            return false;
        }
    }
    return true;
}
