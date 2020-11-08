#include<stdlib.h>


typedef struct int_node
{
    int data;
    struct int_node *next;
} Node_i;

void int_add(Node_i **header,int in)
{
    if(!*header)
    {
        *header = (Node_i *) malloc(sizeof(Node_i));
        (*header)->data = in;
        (*header)->next = NULL;
        return;
    }
    Node_i *current = *header;
    while (current->next!=NULL)
    {
        current = current->next;
    }
    Node_i *new = (Node_i *)malloc(sizeof(Node_i));
    new->next = NULL;
    new->data = in;
    current->next = new;
}

void free_list(Node_i *header)
{
    Node_i *next = header->next;
    while (header!=NULL)
    {
        free(header);
        header = next;
        if(header!=NULL)
        {
            next = header->next;
        }
    }
    
}

int size(Node_i *header)
{
    int i;
    for(i = 0;header!=NULL;i++)
    {
        header = header->next;
    }
    return i;
}

int int_get(Node_i *header,int index)
{
    if(index>=size(header))
    {
        exit(-1);
    }
    int i;
    for(i = 0;i!=index;i++)
    {
        header = header->next;
    }
    return header->data;
}

Node_i *get_node(Node_i *header,int index)
{
    if(index>=size(header))
    {
        return NULL;
    }
    else if(index<0)
    {
        return header;
    }
    
    int i;
    for(i = 0;i!=index;i++)
    {
        header = header->next;
    }
    return header;
}

void int_set(Node_i *header,int index,int numb)
{
    if(index>=size(header))
    {
        exit(-1);
    }
    int i;
    for(i = 0;i!=index;i++)
    {
        header = header->next;
    }
    header->data = numb;
}

void list_remove(Node_i **header,int index)
{
    if(index>=size(*header))
    {
        exit(-1);
    }
    else if(index == 0)
    {
        free(*header);
        *header = get_node(*header,1);
        return;
    }
    Node_i *prev = get_node(*header,index-1);
    Node_i *current = get_node(*header,index);
    Node_i *next = get_node(*header,index+1);
    free(current);
    prev->next = next;
}