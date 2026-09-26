#ifndef CLIENT_CTX_H
#define CLIENT_CTX_H

#include "list.h"
#include "header.h"
#include "metadata.h"
#include "packet.h"
#include <stddef.h>
#include <stdbool.h>
#include <openssl/aes.h>

typedef enum { RECV_HEADER, RECV_METADATA, RECV_PACKET } RecvStep;

typedef struct {
    RecvStep        step;
    size_t          bytes_received;
    Header          header;
    Metadata        metadata;

    unsigned char   header_container[sizeof(Header)];
    unsigned char   metadata_container[sizeof(Metadata)];

    unsigned char   packets[255][sizeof(Packet) + AES_BLOCK_SIZE];
    unsigned int    packet_index;

    bool            can_read;
}ClientContext;

void            init_client_ctx(ClientContext* ctx);
ClientContext*  ctx_from_fd(int fd, List* client_list);
void            reset_client_ctx(ClientContext* ctx);

#endif
