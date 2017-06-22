#ifndef NEAREST_NEIGHBOUR_H_INCLUDED
#define NEAREST_NEIGHBOUR_H_INCLUDED
#include "type.h"


#define TVAL 2*pow(MAXR,2)+1


int* nearest_neighbour(bool opti,item_language* language, double** matrix, int nb_vertex, char* title);
bool libre(int* liste ,int taille,int index_cherche);
#endif // NEAREST_NEIGHBOUR_H_INCLUDED
