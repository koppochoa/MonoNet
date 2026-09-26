#ifndef CLIENT_UTILS_H
#define CLIENT_UTILS_H

#include "network.h"
#include "utils.h"
#include "client.h"

void log_client(enum DEBUG_TYPE type, char* format, ...);

void diplay_infos_client(Client* client, unsigned int port);

#endif
