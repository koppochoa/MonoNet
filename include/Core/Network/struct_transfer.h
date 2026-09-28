#ifndef STRUCT_TRANSFER_H
#define STRUCT_TRANSFER_H

#include <openssl/aes.h>

#include "header.h"
#include "metadata.h"
#include "packet.h"

// int send_header(int* fd, unsigned int packet_count, unsigned int
// packet_type); int receive_header(Header* header, int* fd);

int send_packet(int *fd, Packet *packet, const unsigned char *key,
                const unsigned char *iv);
int send_packets(int *fd, Packet *packet, unsigned int packet_count,
                 const unsigned char *key, const unsigned char *iv);
int receive_packets(
    int *fd, unsigned char reception[255][sizeof(Packet) + AES_BLOCK_SIZE],
    unsigned int packet_count);

int send_metadata(int *fd, uint8_t type, struct tm *time);
int receive_metadata(Metadata *metadata, int *fd);

#endif
