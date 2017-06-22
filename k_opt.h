#ifndef K_OPT_H_INCLUDED
#define K_OPT_H_INCLUDED
#include "type.h"
#include "utility.h"

int* opt2_menu(bool opti,item_language* language, double** matrix, int nb_vertex, int* cycle, char* title);
int* opt2(bool opti,item_language* language_choice, double** distsquare_matrix, int nb_vertex,int* cycle,char* title);
int* opt2_quicker(bool opti,item_language* language_choice, double** distsquare_matrix, int nb_vertex,int* cycle,char* title);
#endif // K_OPT_H_INCLUDED
