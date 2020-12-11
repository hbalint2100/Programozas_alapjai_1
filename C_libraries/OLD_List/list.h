#ifndef HuList_H
#define HuList_H

typedef struct int_node
{
    int data;
    struct int_node *next;
} Node_i;

void int_add(Node_i **header,int in);
void free_list(Node_i *header);
int size(Node_i *header);
int int_get(Node_i *header,int index);
Node_i *get_node(Node_i *header,int index);
void int_set(Node_i *header,int index,int numb);
void list_remove(Node_i **header,int index);

#endif