#ifndef CLIENT_TRANSFERT_H
#define CLIENT_TRANSFERT_H

#include "client.h"
#include "data_exchange.h"
#include "struct_transfer.h"

int client_send(Client* client, Packet* packet, unsigned int packet_count, int type, uint8_t metadata_type);

#endif
