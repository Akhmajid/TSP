#ifndef LANGUAGE_H_INCLUDED
#define LANGUAGE_H_INCLUDED

#include "graph_lib.h"
#include "type.h"
#include "utility.h"

void file_access (lstrings* menu,FILE* current_language, char* cmp, int max_item);
void language_parser (item_language* language);
void language_choice (item_language* language);

#endif // LANGUAGE_H_INCLUDED
