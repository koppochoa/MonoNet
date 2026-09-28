#pragma once

#include <openssl/aes.h>
#include "utils.h"
#include "network.h"

#include <stddef.h>
#include <stdint.h>



typedef struct {
  uint8_t packet_type;
  uint8_t packet_count;
  size_t packet_size;
} Header;

Header create_header(uint8_t packet_type, uint8_t packet_count,
                     size_t packet_size);

void reset_header(Header *header);

int serialize_header(const Header *header, unsigned char *buffer,
                     size_t buffer_len);
int deserialize_header(Header *header, const unsigned char *buffer,
                       size_t buffer_len);

void show_header(Header *header);

int send_header(int *fd, unsigned int packet_count, unsigned int packet_type);
int receive_header(Header *header, int *fd);

