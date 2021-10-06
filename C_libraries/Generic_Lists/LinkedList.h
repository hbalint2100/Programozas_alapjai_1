#ifndef HuList_L
#define HuList_L
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
    size_t sizeofElement;
    unsigned int size;
} LinkedList;

//creates empty LinkedList(for any data type)
LinkedList createLinkedList(size_t sizeofElement);
//add new element(value) to the end of the LinkedList (generic type)
void add_value(LinkedList *LinkedList,void *data,size_t sizeofData);
//add a previously allocated data to the end of the LinkedList(generic type)
void add_data(LinkedList *LinkedList,void *data);
//clears LinkedList
void empty_LinkedList(LinkedList *LinkedList);
//destroys the whole LinkedList
void free_LinkedList(LinkedList *LinkedList);
//gets element of LinkedList at index (generic type)
void *get(LinkedList LinkedList,int index);
//removes element of LinkedList at index (generic type)
void LinkedList_remove(LinkedList *LinkedList, int index);
//returns int from LinkedList at index
int get_int(LinkedList LinkedList,int index);
//returns double from LinkedList at index
double get_double(LinkedList LinkedList,int index);
//returns character from LinkedList at index
char get_char(LinkedList LinkedList,int index);
//returns string from LinkedList at index
char *get_string(LinkedList LinkedList,int index);

#endif
