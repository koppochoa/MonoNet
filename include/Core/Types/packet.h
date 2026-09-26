#ifndef PACKET_H
#define PACKET_H



#define PACKET_TYPE_MESSAGE
#define MESSAGE_SIZE 100

#include "utils.h"
#include "security.h"
#include <string.h>
#include <stdint.h>
#include <stddef.h>
typedef struct 
{
    unsigned char       data[MESSAGE_SIZE];
    uint8_t             type;
}Packet;



int serialize_packet(const Packet* msg, unsigned char* buffer, size_t buffer_len);
int deserialize_packet(Packet* msg, const unsigned char* serialized_msg, size_t serialized_msg_len);

size_t prepare_packet(Packet* packet, unsigned char* packet_s_c, const unsigned char* key, const unsigned char* iv);

void show_packet(Packet* packet);


#endif
