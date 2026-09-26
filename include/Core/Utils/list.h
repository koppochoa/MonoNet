#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
typedef struct List_Node
{
    void*               data;
    struct List_Node*   next;

}List_Node;


typedef struct 
{
    List_Node*  first;
    List_Node*  last;
    unsigned int size;

    pthread_mutex_t lock;
}List;


List*   createList();
int     listSize(List* list);
void    append(List* list, void* elem);
void*   GetAt(List* list, int index);
void    RemoveAt(List* list, int index);
void    clear_list(List* list);
void    list_free(List* list);
void    printList(List* list);
void    printClientList(List* list);



#endif
