#ifndef QUEUE_H
#define QUEUE_H

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <string.h>

/**
 * @brief Structure representant un element d'une File
 */
typedef struct Node
{
    /**Un pointeur vers une structure contenant un message*/
    void*        value;
    /**Un pointeur vers le prochain element de la File*/
    struct Node*    next;

}Node;

/**
 * @brief Structure representant une File 
 * 
 */
typedef struct Queue 
{
    /**Le premier element de la Queue*/ 
    Node* first;
    /**Le dernier element de la Queue*/
    Node* last;
    /**Le mutex d'acces a la Queue*/
    pthread_mutex_t lock;
}Queue;

/**
 * @brief Cree une File de Messages
 */
Queue* create_queue();
/**
 * @brief Ajoute un Message a la File
 */
void enqueue(Queue* q, void* elem, size_t elem_size);
/**
 * @brief Recupere le premier Message de la File
 */
void* dequeue(Queue* q);
/**
 * @brief Retourne True si la File est vide
 */
bool is_empty(Queue* q);


void display_queue(Queue* q);
void dynamic_display_queue(Queue* q);
void destroy_queue(Queue* q, void (*free_func)(void*));

#endif
