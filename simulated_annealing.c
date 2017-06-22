#include <stdio.h>
#include <stdlib.h>
#include "type.h"
#include "language.h"
#include "utility.h"
#include "graph_lib.h"
#include "simulated_annealing.h"
#include <math.h>

#define STARTT pow(10,8)
#define STOPT .01
#define COOL 0.99
#define BK (1.38064852*pow(10,-12))


int* simulated_annealing(bool opti,item_language* language, double** matrix, int nb_vertex, int* cycle_h, char* title,int deep )
{
    switch(opti)
    {
        case false:
        sprintf(title,"graph_%d_SimulatedAnnealing",nb_vertex);
        break;
        case true:
        sprintf(title,"%s_SimulatedAnnealing",title);
        break;
    }
    opti=true;
    int i,j;
    printf("%s",language->algos[8].line);
    scanf("%d",&deep);
    printf("%s",language->algos[7].line);
    clear_buffer();
    int vertex;
    int* graph6=malloc(deep*sizeof(*graph6));
    int* best_g6=malloc(deep*sizeof(*graph6));
    double cost, curcost,best_cost,graph6_min;
    double graph6_cur=8*pow(MAXR,2);
    graph6_min=graph6_cur;
    cost=0;
    int* best_cycle=malloc(sizeof(*best_cycle)*(nb_vertex+1));

    printf("%s",language->algos[6].line);

    double t = STARTT;
    int nb_try = pow(nb_vertex/2,2);

    /* Cout initial */
    for (i=0;i<nb_vertex;i++)
    {
        best_cycle[i]=cycle_h[i];
        cost+= (matrix[cycle_h[i]][cycle_h[i+1]]);
    }

    best_cycle[nb_vertex]=cycle_h[0];
    best_cost=curcost=cost;
    /* RECUIT */
    while (t > STOPT)
    {
        /* Plus d'améliorations */
        if (!opti)
        {
            if ((curcost-best_cost) > 0)
            {
                for(i=0;i<nb_vertex;i++)
                {

                    cycle_h[i]=best_cycle[i];
                    break;
                }
            }

        }
        opti=false;

        /* Essai amélioration */
        for (i=1;i<nb_try;i++)
        {
            /* On tire un sommet dans l'intervalle [1; nb_vertex-deep[ */
            vertex=1+((int)(random_nb() *10* nb_vertex)) % (nb_vertex-deep);
            for(j=0;j<deep;j++)
            {
                graph6[j]= cycle_h[vertex+j];
                best_g6[j]=graph6[j];
            }
            curcost=cost;
            graph6_cur=curcost;
            /* On s'assure que la valeur de graph6_min ne soit pas inférieure à la longueur actuelle */
            graph6_min=2*deep*pow(MAXR,2);
            def_best_swap(graph6,best_g6,0,&graph6_cur,matrix,cycle_h[vertex+deep],cycle_h[vertex-1],deep);
            /* Cout de la nouvelle solution */
            curcost+=graph6_min;
            double boltzmann = exp(-(curcost-cost)/(t));
            if ((curcost-cost)<=0 || (random_nb()<boltzmann))
            {
                for (j=0;j<deep;j++)
                {
                    cycle_h[vertex+j]=best_g6[j];
                }

                cost = curcost;
                opti=true;
                /* Si la solution actuelle est la meilleure rencontree on la conserve en memoire */
                if (curcost<=best_cost)
                {
                    for (j=0;j<=nb_vertex;j++)
                    {
                        best_cycle[j]=cycle_h[j];
                    }
                    best_cost=curcost;
                }
            }
        }
        t*=COOL;
    }

    free(best_cycle);
    printf("%s",language->algos[5].line);
    cycle_h[nb_vertex]=cycle_h[0];
    return cycle_h;
}
void def_best_swap(int* cycle, int* better_swap,int curs,double* better_dist,double **matrix, int sup, int inf,int deep)
{
    int i;
    double cur_dist;
    if (deep-curs<=1)
    {
            cur_dist=0;
            /* Compare le cout de la permutation */
            for (i=0;i<(deep-1);i++)
            {
                    cur_dist+= (matrix[cycle[i]][cycle[i+1]]);
            }
        cur_dist+=matrix[cycle[deep-1]][sup];
        cur_dist+=matrix[inf][cycle[0]];
        if (cur_dist<*better_dist)
        {
            /* Enregistre le meilleur échange */
            *better_dist=cur_dist;
            for (i=0;i<deep;i++)
            {
                better_swap[i]=cycle[i];
            }
        }
    }
    else
    {
        for(i=curs;i<6;i++)
        {
            swap(cycle,i,curs);
            def_best_swap(cycle,better_swap,curs+1,better_dist,matrix,sup,inf,deep);
            swap(cycle,i,curs);
        }
    }
}
void swap(int* cycle,int el1,int el2)
{

    int tmp = cycle[el1];
    cycle[el1] = cycle[el2];
    cycle[el2] = tmp;
}

