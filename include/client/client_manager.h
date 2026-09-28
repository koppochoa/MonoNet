#ifndef CLIENT_MANAGER_H
#define CLIENT_MANAGER_H

#include <stddef.h>
#include "client.h"

#define MONONET_EXIT_NETWORK -1

int handle_client_input(Client* client, const char *buff, size_t len);

int handle_local_command(Client* client, const char* buff, size_t len);
int handle_network_command(Client* client, const char* buff, size_t len);

void exit_network();


#endif
