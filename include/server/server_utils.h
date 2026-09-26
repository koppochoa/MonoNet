#ifndef SERVER_UTILS_H
#define SERVER_UTILS_H

#include <arpa/inet.h>
#include <unistd.h>
#include "client.h"
#include "network.h"
#include "utils.h"
#include <stdio.h>
#include <stdarg.h>
#include <sys/socket.h>

void CloseServer(int *fd, bool *stop_switch);

void log_server(enum DEBUG_TYPE type, char* format, ...);

void clean_client(int* fd, int* epfd, List* list);

void DisplayServerInfos(struct sockaddr_in* server_addr, int port);




#endif
