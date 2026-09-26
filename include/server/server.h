#ifndef SERVER_H
#define SERVER_H

#define MSG_COOLDOWN 0.4

#include <stddef.h>
#include <stdbool.h>
#include <pthread.h>
#include "utils.h"
#include "network.h"
#include <sys/epoll.h>
#include <signal.h>
#include "server_manager.h"

#include "server_threads.h"

void runServer(void* args);

void* ClientManager(void* index);

void* BroadcastClients();

void DisplayServerInfos();


#endif
