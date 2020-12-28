/*
    This is a generic LinkedList library.
    It helps the interaction with the LinkedList.
    It introduces functions which are similar
    to other higher level programming languages' 
    LinkedList controlling functions.
    
    NOTICE:
    One LinkedList is capable of storing different types of data, 
    that's why user must keep in mind
    what type of data is stored in the LinkedList.
*/

#include<stdlib.h>

//One node of the linked LinkedList
typedef struct node
{
    void *data;
    struct node *prev;
    struct node *next;
} Node;

//Data about the whole LinkedList
typedef struct LinkedList
{
    Node *head;
    Node *tail;
    size_t sizeofElement;
    unsigned int size;
} LinkedList;

//creates empty LinkedList(for any data type)
LinkedList createLinkedList(size_t sizeofElement)
{
    Node *head = (Node *) malloc(sizeof(Node));
    Node *tail = (Node *) malloc(sizeof(Node));
    head->prev = NULL;
    tail->next = NULL;
    head->next = tail;
    tail->prev = head;
    return (LinkedList) {head,tail,sizeofElement,0};
}

//add new element(value) to the end of the LinkedList (generic type)
void add_value(LinkedList *LinkedList,void *data,size_t sizeofData)
{
    if(!LinkedList->head||!LinkedList->tail||LinkedList->tail->next||LinkedList->head->prev||sizeofData!=LinkedList->sizeofElement)
    {
        return;
    }
    Node *new = (Node *) malloc(sizeof(Node));
    new->next = LinkedList->tail;
    new->prev = LinkedList->tail->prev;
    LinkedList->tail->prev->next = new;
    LinkedList->tail->prev = new;
    new->data = malloc(sizeofData);
    //Copying byte to byte
    for(int i = 0; i < sizeofData;i++)
    {
        *(char *)(new->data + i) = *(char *)(data + i);
    }
    LinkedList->size += 1;
}
//add a previously allocated data to the end of the LinkedList(generic type)
void add_data(LinkedList *LinkedList,void *data)
{
    if(!LinkedList->head||!LinkedList->tail||LinkedList->tail->next||LinkedList->head->prev)
    {
        return;
    }
    Node *new = (Node *) malloc(sizeof(Node));
    new->next = LinkedList->tail;
    new->prev = LinkedList->tail->prev;
    LinkedList->tail->prev->next = new;
    LinkedList->tail->prev = new;
    new->data = data;
    LinkedList->size += 1;
}

//clears LinkedList
void empty_LinkedList(LinkedList *LinkedList)
{
    if(!LinkedList->size)
    {
        return;
    }
    Node *current = LinkedList->head->next;
    Node *next = current->next;
    Node *tail = LinkedList->tail;
    while (current!=tail)
    {
        free(current->data);
        free(current);
        current = next;
        next = current->next;
    }
    tail->prev = LinkedList->head;
    LinkedList->head->next = tail;
    LinkedList->size = 0;
}

//destroys the whole LinkedList
void free_LinkedList(LinkedList *LinkedList)
{
    //head and tail pointers are NULL pointers
    if(!LinkedList->head&&!!LinkedList->tail)
    {
        return;
    }
    //LinkedList is an empty LinkedList -> free up head and tail
    else if(!LinkedList->size)
    {
        free(LinkedList->tail);
        free(LinkedList->head);
        LinkedList->head=NULL;
        LinkedList->tail=NULL;
        return;
    }
    Node *current = LinkedList->head->next;
    Node *next = current->next;
    Node *tail = LinkedList->tail;
    while (current!=tail)
    {   
        free(current->data);
        free(current);
        current = next;
        next = current->next;
    }
    free(tail);
    free(LinkedList->head);
    LinkedList->size = 0;
    LinkedList->head=NULL;
    LinkedList->tail=NULL;
}

//gets element of LinkedList at index (generic type)
void *get(LinkedList LinkedList,int index)
{   
    //exits if non existing LinkedList or empty LinkedList or index out of bounds occurs
    if(!LinkedList.head||!LinkedList.tail||!LinkedList.size||LinkedList.size<=index)
    {
        return NULL;
    }
    //search from tail
    if(((LinkedList.size/2)-1)>index)
    {
        Node *current = LinkedList.tail->prev;
        for(int i = LinkedList.size-1; i >= 0; i--)
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
        Node *current = LinkedList.head->next;
        for(int i = 0; i < LinkedList.size; i++)
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

//gets element of LinkedList at index (generic type)
void LinkedList_remove(LinkedList *LinkedList, int index)
{
    //exits if non existing LinkedList or empty LinkedList or index out of bounds occurs
    if(!LinkedList->head||!LinkedList->tail||!LinkedList->size||LinkedList->size<=index)
    {
        return;
    }
    //search from tail
    if(((LinkedList->size/2)-1)>index)
    {
        Node *current = LinkedList->tail->prev;
        for(int i = LinkedList->size-1; i >= 0; i--)
        {
            if(i==index)
            {
                //freeing up node and connecting next and previous nodes
                free(current->data);
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                LinkedList->size -= 1;
                return;
            }
            current = current->prev;
        }
    }
    //search from head
    else
    {
        Node *current = LinkedList->head->next;
        for(int i = 0; i < LinkedList->size; i++)
        {
            if(i==index)
            {
                //freeing up node and connecting next and previous nodes
                free(current->data);
                current->prev->next = current->next;
                current->next->prev = current->prev;
                free(current);
                LinkedList->size -= 1;
                return;
            }
            current = current->next;
        }
    }
}

//returns int from LinkedList at index
int get_int(LinkedList LinkedList,int index)
{
    return *(int *)get(LinkedList,index);
}

//returns double from LinkedList at index
double get_double(LinkedList LinkedList,int index)
{
    return *(double *)get(LinkedList,index);
}

//returns character from LinkedList at index
char get_char(LinkedList LinkedList,int index)
{
    return *(char *)get(LinkedList,index);
}

//returns string from LinkedList at index
char *get_string(LinkedList LinkedList,int index)
{
    return *(char **)get(LinkedList,index);
}