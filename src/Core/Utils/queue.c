
#include "queue.h"

Queue* create_queue()
{
    Queue *q = (Queue*)malloc(sizeof(Queue));
    q->first = q->last = NULL;
    pthread_mutex_init(&q->lock, NULL);
    return q;
}



void enqueue(Queue* q, void* elem, size_t elem_size)
{
    if(!elem)
    {
        perror("elem is null");
        return;
    }

    pthread_mutex_lock(&q->lock);

    Node *node = malloc(sizeof(Node));
    if(!node)
    {
        perror("node malloc");
    }

    node->value = malloc(elem_size);
    if (!node->value) {
        perror("malloc value");
        free(node);
        pthread_mutex_unlock(&q->lock);
        return;
    }

    memcpy(node->value, elem, elem_size);
    node->next = NULL;

    if (q->last == NULL) {
        q->first = q->last = node;
    } else {
        q->last->next = node;
        q->last = node;
    }

    pthread_mutex_unlock(&q->lock);
}



void* dequeue(Queue* q)
{
    pthread_mutex_lock(&q->lock);

    if (q->first == NULL)
    {
        pthread_mutex_unlock(&q->lock);
        return NULL;
    }

    Node* tmp = q->first;
    void* data = tmp->value;
    q->first = q->first->next;

    if (q->first == NULL)
        q->last = NULL;

    free(tmp);

    pthread_mutex_unlock(&q->lock);
    return data;
}


void destroy_queue(Queue* q, void (*free_func)(void*))
{
    while (!is_empty(q)) {
        void* data = dequeue(q);
        if (free_func)
            free_func(data); // Libère les contenus si besoin
    }
    pthread_mutex_destroy(&q->lock);
    free(q);
}


bool is_empty(Queue* q)
{
    pthread_mutex_lock(&q->lock);
    bool empty = (q->first == NULL);
    pthread_mutex_unlock(&q->lock);
    return empty;
}

// void display_queue(Queue* q)
// {
//     // if (q->first == NULL) {
//     //     printf("La queue est vide\n");
//     //     return;
//     // }

//     // Node* temp = q->first;
//     // while (temp != NULL) 
//     // {
//     //     printf("%s\n", temp->value->message);
//     //     temp = temp->next;
//     // }
//     // printf("\n");
// }

void clear_screen() {
    printf("\033[H\033[J"); // Code ANSI : Réinitialise l'affichage du terminal
}

// void dynamic_display_queue(Queue* q) {
//     // clear_screen(); // Efface l'écran avant d'afficher la queue

//     // if (q->first == NULL) {
//     //     printf("La queue est vide\n");
//     // } else {
//     //     Node* temp = q->first;
//     //     printf("Messages dans la queue :\n");
//     //     while (temp != NULL) {
//     //         printf("- %s\n", temp->value->message);
//     //         temp = temp->next;
//     //     }
//     // }

//     // fflush(stdout); // Force l'affichage immédiat
//     // sleep(1); // Pause de 1 seconde avant mise à jour
// }
