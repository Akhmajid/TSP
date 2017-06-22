#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define LBUF 128
#define LMEN 10
#define LDAT 10
#define LALG 10
#define LERR 20

typedef struct coord
{
    double x;
    double y;
}coordinates;

typedef struct language_strings
{
    char line[LBUF];
}lstrings;

typedef struct language_item
{
    char name[12];
    lstrings menu[LMEN];
    lstrings dataset[LDAT];
    lstrings algos[LALG];
    lstrings errors[LERR];
}item_language;

typedef struct link_list
{
    int index;
    struct link_list* next;
}llist;
#endif // TYPE_H_INCLUDED
