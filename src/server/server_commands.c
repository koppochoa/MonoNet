#include "server_commands.h"

/**
 * Call this func to add a message to the ciphered queue
 */
void SRV_add_message_to_queue(struct Queue* packets_queue, unsigned char* packet)
{
    call_cmd("QUEUEMSGADD");

    log_server(INFO, "New message arrived");
    
    enqueue(packets_queue, packet, sizeof(Packet) + AES_BLOCK_SIZE);
}

/**
 * Call this func to send CIPHERED_MESSAGE to a client (From server)
 */
void SRV_CMD_send_packet_to_client(Client* client, unsigned char packet[255][sizeof(Packet) + AES_BLOCK_SIZE], uint8_t* packets_count, uint8_t* type, struct tm* time)
{
    send_protocol_data(&client->fd, *packets_count, *type, 0, time);

    //* UPGRADE
    for(int i = 0; i < *packets_count; i++)
    {
        send_data(&client->fd, packet[i], sizeof(Packet) + AES_BLOCK_SIZE);
    }    
}

void SRV_client_joined(Client* client, Queue* message_queue, struct tm when)
{
    log_server(INFO, "GREE");
    char greeting[100];
    int false_fd    = -1;
    snprintf(greeting, 100, "[%d:%d:%d](%s) Just Joined", when.tm_hour, when.tm_min, when.tm_sec, client->username);
    enqueue(message_queue, &false_fd, sizeof(int));
    enqueue(message_queue, &greeting, 100);
}

/**
 * Call this func to disconnect a client 
 */
void SRV_disconnect_client(int* fd, int* epfd, List* list)
{
    log_server(INFO, "Client disconnect from server");
    clean_client(fd, epfd, list);
}

/**
 * Call this func quand c le caca 
 */
void SRV_sayhi()
{
    log_server(ALERT, "someone said hi");
}
