#ifndef HEADER_H
#define HEADER_H

#include <stddef.h>
#include <stdint.h>
#include "utils.h"
typedef struct
{
    uint8_t             packet_type;
    uint8_t             packet_count;
    size_t              packet_size;
}Header;


Header create_header(uint8_t packet_type, uint8_t packet_count, size_t packet_size); 

void reset_header(Header* header);

int serialize_header(const Header* header, unsigned char* buffer, size_t buffer_len);
int deserialize_header(Header* header, const unsigned char* buffer, size_t buffer_len);

void show_header(Header* header);

#endif
