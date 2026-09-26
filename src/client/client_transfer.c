#include "client_transfer.h"

int client_send(Client* client, Packet* packet, unsigned int packet_count, int type, uint8_t metadata_type)
{
    //* Envoi du protocol
    int bytes_sent_header = send_protocol_data(&client->fd, packet_count, type, metadata_type, NULL); //* Envoi du protocol

    //* Envoi du/des packets
    int sended_count = send_packets(&client->fd, packet, packet_count, client->key, client->iv);

    return bytes_sent_header + sended_count;
}
