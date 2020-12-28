#ifndef HuList_A
#define HuList_A
#include<stdlib.h>

typedef struct ArrayList
{
    void **array;
    unsigned int size;
    size_t allocation;
    size_t sizeofElement;
} ArrayList;

ArrayList createArrayList(size_t sizeofElement);
void add_value(ArrayList *ArrayList,void *data,size_t sizeofData);
void add_data(ArrayList *ArrayList,void *data);
void empty_ArrayList(ArrayList *ArrayList);
void free_ArrayList(ArrayList *ArrayList);
void *get(ArrayList ArrayList,int index);
void ArrayList_remove(ArrayList *ArrayList, int index);
int get_int(ArrayList ArrayList,int index);
double get_double(ArrayList ArrayList,int index);
char get_char(ArrayList ArrayList,int index);
char *get_string(ArrayList ArrayList,int index);

#endif