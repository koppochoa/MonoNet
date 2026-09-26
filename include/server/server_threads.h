#ifndef SERVER_THREADS_H
#define SERVER_THREADS_H

struct RegisterClientArgs
{
    int*    fd;
    List*   list;
    int*    epfd;
    bool*   pause_switch;
    Queue*  queue;
};

struct CatchingClientArgs
{
    int*                    fd;
    List*                   list;
    int*                    epfd;
    struct epoll_event*     events;
    struct Queue*           msg_queue;
    bool*                   pause_switch;
};

struct BroadcastClientArgs
{   
    List*           list;
    struct Queue*   queue;
    bool*           pause_switch;
};

void T_StartRegisterClient(pthread_t* thread, void* (*func)(void*), int* server_fd, List* list, int* epfd, Queue* message_queue, bool* pause_switch);
void T_StartReceivingFromClients(pthread_t* thread, void* (*func)(void*), int* server_fd, List* list, int* epfd, struct epoll_event* events, struct Queue* message_queue, bool* pause_switch);
void T_StartBroadcastMessage(pthread_t* thread, void* (*func)(void*), List* clients_list, struct Queue* message_queue, bool* pause_switch);

void* RegisterClient(void* args);
void* ReceivingFromClients(void* args);
void* BroadcastMessage(void* args);

#endif