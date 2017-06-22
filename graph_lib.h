#ifndef GRAPH_LIB_H_INCLUDED
#define GRAPH_LIB_H_INCLUDED

#include "language.h"
#include "type.h"
#include "utility.h"

#define MAXR 100
#define TMAX 32
#define FBUF 25

coordinates* new_graph(item_language* language, int* sizeofgraph);
double random_nb();
void export_dataset(item_language* language,coordinates* graph, char* algo, int graph_size, int* graph_mini);
coordinates* import_dataset(item_language* language,int* size_after_import);
double** distancesquare_matrix (item_language* language,int nb_vertex,coordinates* graph);
void free_matrix(double **matrix,int nb_vertex);

#endif // GRAPH_LIB_H_INCLUDED
