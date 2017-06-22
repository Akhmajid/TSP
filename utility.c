#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "k_opt.h"
#include "nearest_neighbour.h"
#include "language.h"
#include "type.h"


void clear_buffer()
{
    int c = 0;
    while (c != '\n' && c != EOF)
    {
        c = getchar();
    }
}

void clear(){
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}
