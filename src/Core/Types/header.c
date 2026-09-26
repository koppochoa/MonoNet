#include "header.h"

Header create_header(uint8_t packet_type, uint8_t packet_count, size_t packet_size)
{  
    Header header = {.packet_type = packet_type, .packet_count = packet_count, .packet_size = packet_size};
    return header;
}

void reset_header(Header* header)
{
    header->packet_count = 0;
    header->packet_size  = 0;
    header->packet_type  = 0;
}

void show_header(Header* header)
{
    ColorPrint(COLOR_BLUE, "[HEADER DEBUG]  ");

    printf("    TYPE    : %d", header->packet_type);
    printf("    Count   : %d", header->packet_count);
    printf("    SIZE    : %ld", header->packet_size);
    printf("\n");
}

int serialize_header(const Header* header, unsigned char* buffer, size_t buffer_len) 
{
    if(!header)                         return -1;
    if(!buffer)                         return -1;
    if(buffer_len != sizeof(Header))    return -1;

    buffer[0] = (unsigned char)(header->packet_type & 0xFF);
    buffer[1] = (unsigned char)(header->packet_count & 0xFF);

    for (size_t j = 0; j < sizeof(size_t); j++)
    {
        buffer[2 + j] = (header->packet_size >> (8 * j)) & 0xFF;
    }

    return 0;
}

int deserialize_header(Header* header, const unsigned char* buffer, size_t buffer_len) 
{
    if(!header)                                     return -1;
    if(!buffer)                                     return -1;
    if(buffer_len != sizeof(Header))    return -1;

    header->packet_type     = buffer[0];
    header->packet_count    = buffer[1];

    for (size_t j = 0; j < sizeof(size_t); j++)
    {
        header->packet_size |= ((size_t)buffer[2 + j]) << (8 * j);
    }

    return 0;
}

