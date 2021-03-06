/*
    This is a generic ArrayList library.
    It helps the interaction with the ArrayList.
    It introduces functions which are similar
    to other higher level programming languages' 
    ArrayList controlling functions.
    
    NOTICE:
    One ArrayList is capable of storing different types of data, 
    that's why user must keep in mind
    what type of data is stored in the ArrayList.
*/

#include<stdlib.h>

//Data about the whole ArrayList
typedef struct ArrayList
{
    void **array;
    unsigned int size;
    size_t allocation;
    size_t sizeofElement;
} ArrayList;

//creates empty ArrayList(for any data type)
ArrayList createArrayList(size_t sizeofElement)
{
    ArrayList arraylist;
    arraylist.array = calloc(1000,sizeof(void *));
    arraylist.sizeofElement = sizeofElement;
    arraylist.size = 0;
    arraylist.allocation = 1000;
    return arraylist;
}

//add new element(value) to the end of the ArrayList (generic type)
void add_value(ArrayList *ArrayList,void *data,size_t sizeofData)
{
    if(!ArrayList||!ArrayList->array||sizeofData!=ArrayList->sizeofElement)
    {
        return;
    }
    if(ArrayList->size>=ArrayList->allocation)
    {
        ArrayList->array = realloc(ArrayList->array,(ArrayList->allocation+1000)*sizeof(void *));
        ArrayList->allocation += 1000;
    }
    void *new = malloc(sizeofData);
    //Copying byte to byte
    for(int i = 0; i < sizeofData;i++)
    {
        *(char *)(new + i) = *(char *)(data + i);
    }
    ArrayList->array[ArrayList->size] = new;
    ArrayList->size += 1;
}
//add a previously allocated data to the end of the ArrayList(generic type)
void add_data(ArrayList *ArrayList,void *data)
{
    if(!ArrayList||!ArrayList->array)
    {
        return;
    }
    if(ArrayList->size>=ArrayList->allocation)
    {
        ArrayList->array = realloc(ArrayList->array,(ArrayList->allocation+1000)*sizeof(void *));
        ArrayList->allocation += 1000;
    }
    ArrayList->array[ArrayList->size] = data;
    ArrayList->size += 1;
}

//clears ArrayList
void empty_ArrayList(ArrayList *ArrayList)
{
    if(!ArrayList||!ArrayList->size||!ArrayList->array)
    {
        return;
    }
    for(int i = 0; i < ArrayList->size; i++)
    {
        free(ArrayList->array[i]);
        ArrayList->array[i] = NULL;
    }
    ArrayList->size = 0;
}

//destroys the whole ArrayList
void free_ArrayList(ArrayList *ArrayList)
{
    if(!ArrayList||!ArrayList->array)
    {
        return;
    }
    //ArrayList is an empty ArrayList -> free up array of pointers
    else if(!ArrayList->size)
    {
        free(ArrayList->array);
        ArrayList->array = NULL;
        ArrayList->sizeofElement = 0;
        ArrayList->allocation = 0;
        return;
    }
    for(int i = 0; i < ArrayList->size; i++)
    {
        free(ArrayList->array[i]);
        ArrayList->array[i] = NULL;
    }
    free(ArrayList->array);
    ArrayList->array = NULL;
    ArrayList->size = 0;
    ArrayList->allocation = 0;
    ArrayList->sizeofElement = 0;
}

//gets element of ArrayList at index (generic type)
void *get(ArrayList ArrayList,int index)
{   
    //exits if non existing ArrayList or empty ArrayList or index out of bounds occurs
    if(!ArrayList.array||!ArrayList.size||ArrayList.size<=index)
    {
        return NULL;
    }
    return ArrayList.array[index];
}

//gets element of ArrayList at index (generic type)
void ArrayList_remove(ArrayList *ArrayList, int index)
{
    //exits if non existing ArrayList or empty ArrayList or index out of bounds occurs
    if(!ArrayList||!ArrayList->array||!ArrayList->size||ArrayList->size<=index)
    {
        return;
    }
    free(ArrayList->array[index]);
    for(int i = index; i < ArrayList->size-1; i++)
    {
        ArrayList->array[i] = ArrayList->array[i+1];
    }
    ArrayList->size -= 1;
}

//returns int from ArrayList at index
int get_int(ArrayList ArrayList,int index)
{
    return *(int *)get(ArrayList,index);
}

//returns double from ArrayList at index
double get_double(ArrayList ArrayList,int index)
{
    return *(double *)get(ArrayList,index);
}

//returns character from ArrayList at index
char get_char(ArrayList ArrayList,int index)
{
    return *(char *)get(ArrayList,index);
}

//returns string from ArrayList at index
char *get_string(ArrayList ArrayList,int index)
{
    return *(char **)get(ArrayList,index);
}