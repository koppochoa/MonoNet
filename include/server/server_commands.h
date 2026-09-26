#ifndef SERVER_COMMANDS_H
#define SERVER_COMMANDS_H

void SRV_add_message_to_queue(struct Queue* packets_queue, unsigned char* packet);

void SRV_CMD_send_packet_to_client(Client* client, unsigned char packet[255][sizeof(Packet) + AES_BLOCK_SIZE], uint8_t* packets_count, uint8_t* type, struct tm* time);

void SRV_client_joined(Client* client, Queue* message_queue, struct tm when);

void SRV_disconnect_client(int* fd, int* epfd, List* list);

void SRV_sayhi();


#endif