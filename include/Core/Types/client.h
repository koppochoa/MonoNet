#ifndef CLIENT_H
#define CLIENT_H

#include "client_ctx.h"
#include "list.h"
#include <netinet/in.h>
#include <signal.h>

#define CANNOT_CONNECT_ERR 0

typedef struct {
  int fd;
  struct sockaddr_in addr;
  ClientContext ctx;

  char username[30];

  unsigned char key[32];
  unsigned char iv[16];

} Client;

Client *client_from_fd(int fd, List *client_list);
int runClient(const char *ip, int port);

#endif
