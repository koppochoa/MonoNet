#include "packet.h"

int serialize_packet(const Packet* msg, unsigned char* buffer, size_t buffer_len) 
{
    if(!msg)                            return -1;
    if(!buffer)                         return -1;
    if(buffer_len != sizeof(Packet))   return -1;

    memset(buffer, 0, sizeof(Packet));

    size_t offset = 0;

    //* Sérialisation de "type"
    buffer[offset] = msg->type;
    offset += sizeof(msg->type);

    //* Sérialisation de "data"
    memcpy(buffer + offset, msg->data, MESSAGE_SIZE);

    return 0; 
}

int deserialize_packet(Packet* msg, const unsigned char* serialized_msg, size_t serialized_msg_len) 
{
    if(!msg)                                    return -1;
    if(!serialized_msg)                         return -1;
    if(serialized_msg_len != sizeof(Packet))   return -1;

    unsigned int offset = 0;

    //* Désérialiser "type"
    msg->type = serialized_msg[offset];
    offset += sizeof(msg->type);

    //* Désérialiser 'message'
    memcpy(msg->data, serialized_msg + offset, MESSAGE_SIZE);

    return 0;
}

size_t prepare_packet(Packet* packet, unsigned char* packet_s_c, const unsigned char* key, const unsigned char* iv)
{
    if(!packet)             return -1;
    if(!packet_s_c)         return -1;
    if(!key)                return -1;
    if(!iv)                 return -1;

    
    //* Packet Serialize
    unsigned char packet_s[sizeof(Packet)];
    serialize_packet(packet, packet_s, sizeof(Packet)); //* Serialization du Message 

    size_t ciphered_len = aes_encrypt(packet_s, sizeof(Packet), key, iv, packet_s_c); //* Encodage du Message

    return ciphered_len;
}

void show_packet(Packet* packet)
{
    ColorPrint(COLOR_BLUE, "PACKET\n");
    printf("DATA : [%s]\n", packet->data);
    printf("TYPE : [%d]\n", packet->type);
}
