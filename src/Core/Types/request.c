
#include "request.h"

#include "packet.h"

ClientRequest create_client_request(RequestType rq_type, int sender_fd, 
    unsigned char packets[255][sizeof(Packet) + AES_BLOCK_SIZE], 
    uint8_t packet_count, uint8_t packet_type, struct tm time)
{
    ClientRequest client_request    = {0x0};
    client_request.rq_type          = rq_type;
    client_request.sender_fd        = sender_fd;
    client_request.packets_count    = packet_count;
    for(int i = 0; i < client_request.packets_count; i++)
    {
        memcpy(client_request.packets[i], packets[i], sizeof(Packet) + AES_BLOCK_SIZE);
    }
    client_request.packet_type      = packet_type;
    client_request.time             = time;
    return client_request;
}
