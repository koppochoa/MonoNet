#ifndef FOOTER_H
#define FOOTER_H

#include <stdint.h>

typedef struct
{
    uint8_t             packet_count;
}Footer;

Footer create_footer(uint8_t packet_count); 

// void reset_header(Footer* header);

// int serialize_header(const Header* header, unsigned char* buffer, size_t buffer_len);
// int deserialize_header(Header* header, const unsigned char* buffer, size_t buffer_len);

// void show_header(Header* header);

#endif
