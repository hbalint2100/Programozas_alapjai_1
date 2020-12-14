#ifndef HuList_S
#define HuList_S
typedef struct node
{
    void *data;
    struct node *prev;
    struct node *next;
    
} Node;

typedef struct list
{
    Node *head;
    Node *tail;
    unsigned int size;
} List;

List createList();
void add_value(List *list,void *data,int SizeofData);
void add_data(List *list,void *data);
void empty_list(List *list);
void free_list(List *list);
void *get(List list,int index);
void list_remove(List *list, int index);
int get_int(List list,int index);
double get_double(List list,int index);
char get_char(List list,int index);
char *get_string(List list,int index);

#endif