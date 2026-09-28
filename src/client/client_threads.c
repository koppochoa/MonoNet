#include "mono_client.h"

/**
 * Entry point for the Registering Thread
 */
void T_StartReceiveBroadcast(pthread_t* thread, void* (*func)(void*), Client* client)
{
    struct ReceiveBroadcastArgs* args = (struct ReceiveBroadcastArgs*)malloc(sizeof(struct ReceiveBroadcastArgs));
    if(!args)
    {
        perror("Error allocating args");
        return;
    }
    
    args->client = client;

    if(pthread_create(thread, NULL, func, (void*)args) != 0)
    {
        perror("Error pthread_create");
        free(args);
        return;
    }
}

void* ReceiveBroadcast(void* args)
{
    struct ReceiveBroadcastArgs* _args = (struct ReceiveBroadcastArgs*)args;

    Client* client = _args->client;
    strcpy(client->username, "ee");

    free(args); 

    Header header       = {0x0};
    Metadata metadata   = {0x0};
    Packet new_packet   = {0x0};
    
    Message message     = {0x0};

    //* Reception
    unsigned char reception[255][sizeof(Packet) + AES_BLOCK_SIZE];
    for(int i = 0; i < 255; i++)
    {
        memset(&reception[i], 0, sizeof(Packet) + AES_BLOCK_SIZE);
    }


    while(!client_killswitch)
    {
        //InterceptDataFromServer(client, &header, &message);
        receive_protocol_data(&client->fd, &header, &metadata);
        receive_packets(&client->fd, reception, header.packet_count);
        
        if(header.packet_type == CMD_BROADCAST_MESSAGE)
        {
            for(int i = 0; i < header.packet_count; i++)
            {
                unsigned char new_packet_s[sizeof(Packet)];
                size_t newLen = sizeof(Packet) + (AES_BLOCK_SIZE - (sizeof(Packet) % AES_BLOCK_SIZE));
                aes_decrypt(reception[0], newLen, client->key, client->iv, new_packet_s);
                int result = deserialize_packet(&new_packet, new_packet_s, sizeof(Packet));
                
                message = create_message(new_packet.data, metadata.time);
                log_message(&message);
            }

            //log_client(INFO, "[%d:%d:%d]Reiceived Broadcast from server: %s",message.time.tm_hour, message.time.tm_min, message.time.tm_sec, message.message);
        }
        else
        {
            // handle recept...
            // Gerer les types de messages
            // if(header.packet_type == CMD_BROADCAST_MESSAGE)
            // {   
            //     printf("We received a broadcast message ! len : %u\n", header.packet_size);
            //     //printf("%s\n",message->message);
            // }
        }
        

        
        for(int i = 0; i < header.packet_count; i++)
        {
            memset(&reception[i], 0, sizeof(Packet) + AES_BLOCK_SIZE);
        }
        reset_header(&header);
        reset_metadata(&metadata);
    }

    pthread_exit(NULL);
    return NULL;
}
