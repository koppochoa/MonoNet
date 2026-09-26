#ifndef REQUEST_H
#define REQUEST_H

#include "packet.h"
#include <openssl/aes.h>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
typedef enum { ServerType, ClientType } RequestType;

typedef struct {
  RequestType rq_type;

  int sender_fd;

  unsigned char packets[255][sizeof(Packet) + AES_BLOCK_SIZE];
  uint8_t packets_count;
  uint8_t packet_type;
  struct tm time;
} ClientRequest;

ClientRequest create_client_request(
    RequestType rq_type, int sender_fd,
    unsigned char packets[255][sizeof(Packet) + AES_BLOCK_SIZE],
    uint8_t packet_count, uint8_t packet_type, struct tm time);

#endif
