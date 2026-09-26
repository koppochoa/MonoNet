#ifndef SERVER_H
#define SERVER_H

#define MSG_COOLDOWN 0.4


void CreateServer(void* args);

void* ClientManager(void* index);

void* BroadcastClients();

void DisplayServerInfos();


#endif