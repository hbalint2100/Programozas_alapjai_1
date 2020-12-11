/*
    This is a generic linked list library.
    It helps the interaction with the list.
    It introduces functions which are similar
    to other higher level programming languages' 
    list controlling functions.
    
    NOTICE:
    One list is capable of storing different types of data, 
    that's why user must keep in mind
    what type of data is stored in the list.
*/

#include<stdlib.h>

//One node of the linked list
typedef struct node
{
    void *data;
    struct node *prev;
    struct node *next;
} Node;

//Data about the whole list
typedef struct list
{
    Node *head;
    Node *tail;
    unsigned int size;
} List;

//creates empty list(for any data type)
List createList()
{
    Node *head = (Node *) malloc(sizeof(Node));
    Node *tail = (Node *) malloc(sizeof(Node));
    head->prev = NULL;
    tail->next = NULL;
    head->next = tail;
    tail->prev = head;
    return (List) {head,tail,0};
}

//add new element(value) to the end of the list (generic type)
void add_value(List *list,void *data,int SizeofData)
{
    if(!list->head||!list->tail||list->tail->next||list->head->prev)
    {
        return;
    }
    Node *new = (Node *) malloc(sizeof(Node));
    new->next = list->tail;
    new->prev = list->tail->prev;
    list->tail->prev->next = new;
    list->tail->prev = new;
    new->data = malloc(SizeofData);
    //Copying byte to byte
    for(int i = 0; i < SizeofData;i++)
    {
        *(char *)(new->data + i) = *(char *)(data + i);
    }
    list->size += 1;
}
//add a previously allocated data to the end of the list(generic type)
void add_data(List *list,void *data)
{
    if(!list->head||!list->tail||list->tail->next||list->head->prev)
    {
        return;
    }
    Node *new = (Node *) malloc(sizeof(Node));
    new->next = list->tail;
    new->prev = list->tail->prev;
    list->tail->prev->next = new;
    list->tail->prev = new;
    new->data = data;
    list->size += 1;
}

//clears list
void empty_list(List *list)
{
    if(!list->size)
    {
        return;
    }
    Node *current = list->head->next;
    Node *next = current->next;
    Node *tail = list->tail;
    while (current!=tail)
    {
        free(current->data);
        free(current);
        current = next;
        next = current->next;
    }
    tail->prev = list->head;
    list->head->next = tail;
    list->size = 0;
}

//destroys the whole list
void free_list(List *list)
{
    //head and tail pointers are NULL pointers
    if(!list->head&&!!list->tail)
    {
        return;
    }
    //List is an empty list -> free up head and tail
    else if(!list->size)
    {
        free(list->tail);
        free(list->head);
        list->head=NULL;
        list->tail=NULL;
        return;
    }
    Node *current = list->head->next;
    Node *next = current->next;
    Node *tail = list->tail;
    while (current!=tail)
    {   
        free(current->data);
        free(current);
        current = next;
        next = current->next;
    }
    free(tail);
    free(list->head);
    list->size = 0;
    list->head=NULL;
    list->tail=NULL;
}

//gets element of list at index (generic type)
void *get(List list,int index)
{   
    //exits if non existing list or empty list or index out of bounds occurs
    if(!list.head||!list.tail||!list.size||list.size<=index)
    {
        return NULL;
    }
    //search from tail
    if(((list.size/2)-1)>index)
    {
        Node *current = list.tail->prev;
        for(int i = list.size-1; i >= 0; i--)
        {
            if(i==index)
            {
                return current->data;
            }
            current = current->prev;
        }
    }
    //search from head
    else
    {
        Node *current = list.head->next;
        for(int i = 0; i < list.size; i++)
        {
            if(i==index)
            {
                return current->data;
            }
            current = current->next;
        }
    }
    //Impossible but needed
    return NULL;
}

//gets element of list at index (generic type)
void list_remove(List *list, int index)
{
    //exits if non existing list or empty list or index out of bounds occurs
    if(!list->head||!list->tail||!list->size||list->size<=index)
    {
        return;
    }
    //search from tail
    if(((list->size/2)-1)>index)
    {
        Node *current = list->tail->prev;
        for(int i = list->size-1; i >= 0; i--)
        {
            if(i==index)
            {
                //freeing up node and connecting next and previous nodes
                free(current->data);
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                list->size -= 1;
                return;
            }
            current = current->prev;
        }
    }
    //search from head
    else
    {
        Node *current = list->head->next;
        for(int i = 0; i < list->size; i++)
        {
            if(i==index)
            {
                //freeing up node and connecting next and previous nodes
                free(current->data);
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                list->size -= 1;
                return;
            }
            current = current->next;
        }
    }
}

//returns int from list at index
int get_int(List list,int index)
{
    return *(int *)get(list,index);
}

//returns double from list at index
double get_double(List list,int index)
{
    return *(double *)get(list,index);
}

//returns character from list at index
char get_char(List list,int index)
{
    return *(char *)get(list,index);
}

//returns string from list at index
char *get_string(List list,int index)
{
    return *(char **)get(list,index);
}