#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph_lib.h"
#include "k_opt.h"
#include "nearest_neighbour.h"
#include "type.h"
#include "utility.h"

void file_access (lstrings* item,FILE* current_language, char* cmp, int max_item)
{
    int cur_item=0;
    char cur_string[LBUF];
    while(cur_item<max_item && fgets(cur_string, LBUF, current_language)!=NULL && strcmp(cur_string,cmp))
    {
        strcpy(item[cur_item].line,cur_string);
        cur_item++;
    }
}
void language_parser (item_language* language)
{
    char cur_file[30];
    FILE* current_language = NULL;
    sprintf(cur_file,"%s.csv",language->name);
    current_language = fopen(cur_file,"r");
    if (current_language!=NULL)
    {
        file_access(language->menu,current_language,"ERRORS\n",LMEN);
        file_access(language->errors,current_language,"ALGOS\n",LERR);
        file_access(language->algos,current_language,"GRAPHS\n",LALG);
        file_access(language->dataset,current_language,"EOF\n",LDAT);
    }
    else
    {
        printf("A critic error occured, maybe %s is not in the program directory\nUne erreur critique est survenue, il se peut que %s ne soit pas dans le dossier du programme\n",cur_file,cur_file);
    }
    fclose(current_language);


}
void language_choice (item_language* language)
{
    int choice;
    printf("1. English\n");
    printf("2. Francais\n");
    scanf("%d",&choice);
    clear();
    clear_buffer();
    switch(choice)
    {
    case 1:
        strcpy(language->name , "english");
        break;
    case 2:
        strcpy(language->name, "francais");
        break;
    default:
        printf("Please try with a correct value\n Veuillez essayer avec une valeur correcte\n");
        break;
    }
    language_parser(language);
}


