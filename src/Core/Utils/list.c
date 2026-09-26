#include "list.h"

List* createList()
{
    List* list = (List*)malloc(sizeof(List));
    list->first = NULL;
    list->last = NULL;
    list->size = 0;
    return list;
}

void append(List* list, void* elem)
{
    List_Node* new_node = (List_Node*)malloc(sizeof(List_Node));
    if (new_node == NULL) {
        printf("Erreur d'allocation mémoire\n");
        return;
    }
    new_node->data = elem;
    new_node->next = NULL;

    if (list->first == NULL) {
        list->first = new_node;
        list->last = new_node;
    } else {
        list->last->next = new_node;
        list->last = new_node;
    }

    list->size++;
}

int listSize(List* list)
{
    int counter = 0;
    List_Node* cur = list->first;

    while (cur != NULL)  // Tant que cur n'est pas NULL (fin de la liste)
    {
        counter++;
        cur = cur->next;
    }

    return counter;
}

void* GetAt(List* list, int index)
{
    if(index < 0 || index >= listSize(list)) // attention ici, index >= au lieu de >
    {
        printf("Err : Out of range index\n");
        return NULL;
    }

    int counter = 0;
    List_Node* current = list->first;

    if(index == 0)
    {
        return current->data;
    }

    while (current != NULL && counter < index)
    {
        current = current->next;
        counter++;
    }

    if (current != NULL)
        return current->data;

    return NULL; // sécurité, même si en théorie on ne devrait jamais arriver ici
}


void RemoveAt(List* list, int index)
{
    if(index < 0 || index > listSize(list))
    {
        printf("Err : Out of range index \n");
        return;
    }

    List_Node* temp = list->first;
    List_Node* prev = NULL;

    // Si on veut supprimer le premier élément
    if (index == 0) {
        list->first = temp->next;  // Changer le premier élément
        free(temp);                // Libérer la mémoire du nœud
        list->size--;
        return;
    }

    // Recherche du nœud à supprimer
    int counter = 0;
    while (temp != NULL && counter < index) {
        prev = temp;
        temp = temp->next;
        counter++;
    }

    // Si l'élément est trouvé, on le supprime
    if (temp != NULL) {
        prev->next = temp->next;  // Lier le précédent au suivant
        if (temp == list->last) {
            list->last = prev;    // Si on a supprimé le dernier élément
        }
        free(temp);  // Libérer la mémoire du nœud supprimé
    }

    list->size--;
}

void clear_list(List* list)
{
    List_Node* current = list->first; // on part du début de la liste
    while (current != NULL) {
        List_Node* next = current->next; // on sauvegarde le suivant
        free(current->data);        // libère les données si nécessaire
        free(current);              // libère le noeud
        current = next;             // passe au suivant
    }
    list->first = NULL; // la liste est vide
}

void list_free(List* list)
{
    clear_list(list);
    free(list);
}

void printList(List* list) 
{
    List_Node* cur = list->first;
    while (cur != NULL) {
        printf("%d -> ", *(int*)cur->data);  // Accès aux données de type int
        cur = cur->next;
    }
    printf("NULL\n");
}

///void printClientList(List* list)
///{
   // List_Node* cur = list->first;
    //while (cur != NULL) 
    //{
      //  Client* client = (Client*)cur->data;
        //printf("%s -> ", client->username);  // Accès aux données de type int
        //cur = cur->next;
    //}
    //printf("NULL\n");
//}
