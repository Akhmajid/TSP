#ifndef SIMULATED_ANNEALING_H_INCLUDED
#define SIMULATED_ANNEALING_H_INCLUDED
#include <stdio.h>
#include "type.h"
#include "graph_lib.h"
#include "language.h"
void swap(int* cycle,int el1,int el2);
void def_best_swap(int* cycle, int* better_swap,int curs,double* better_dist,double **matrix, int sup, int inf, int deep);
int* simulated_annealing(bool opti,item_language* language, double** matrix, int nb_vertex, int* cycle_h, char* title,int deep);

#endif // SIMULATED_ANNEALING_H_INCLUDED
