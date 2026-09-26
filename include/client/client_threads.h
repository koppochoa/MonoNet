#ifndef CLIENT_TREADS_H
#define CLIENT_TREADS_H

struct ReceiveBroadcastArgs
{
    Client* client;
};

void T_StartReceiveBroadcast(pthread_t* thread, void* (*func)(void*), Client* client);
void* ReceiveBroadcast(void* args);



#endif