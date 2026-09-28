#ifndef CLIENT_INIT_H
#define CLIENT_INIT_H

#include "client.h"
#include <arpa/inet.h>
#include <sys/socket.h>

void InitMyself(Client *myself, int *client_fd,
                struct sockaddr_in *com_server_addr, const unsigned char *key,
                const unsigned char *iv);

int InitClientSocket(int *client_fd, struct sockaddr_in *addr, int port,
                     const char *ip);

#endif
