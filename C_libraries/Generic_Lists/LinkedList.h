#ifndef HuList_S
#define HuList_S
#include<stdlib.h>

typedef struct node
{
    void *data;
    struct node *prev;
    struct node *next;
    
} Node;

typedef struct LinkedList
{
    Node *head;
    Node *tail;
    size_t size;
    unsigned int nitems;
} LinkedList;

LinkedList createLinkedList(size_t sizeofElement);
void add_value(LinkedList *LinkedList,void *data,size_t sizeofData);
void add_data(LinkedList *LinkedList,void *data);
void empty_LinkedList(LinkedList *LinkedList);
void free_LinkedList(LinkedList *LinkedList);
void *get(LinkedList LinkedList,int index);
void LinkedList_remove(LinkedList *LinkedList, int index);
int get_int(LinkedList LinkedList,int index);
double get_double(LinkedList LinkedList,int index);
char get_char(LinkedList LinkedList,int index);
char *get_string(LinkedList LinkedList,int index);

#endif