#include "mono_client.h"

#define CLIENT_PORT     8081
#define SERVER_IP       "192.168.1.154"

// Main Client Variables
Client                  myself;
struct sockaddr_in      com_server_addr;

    int                     client_fd;

//* MAIN CLIENT KILLSWITCH
volatile bool client_killswitch = false;

unsigned char key[32] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
    0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
};

unsigned char iv[16] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
    0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
};


pthread_t ReceiveBroadcastTh;
int ReceiveBroadcastTh_id = 1;


void runClient(void* args)
{
    signal(SIGPIPE, SIG_IGN);
    signal(SIGINT, HandleClientClosing);

    client_InitSignals(&myself, args);

    InitClientSocket(&client_fd, &com_server_addr, CLIENT_PORT, SERVER_IP);

    InitMyself(&myself, &client_fd, &com_server_addr, key, iv);

    diplay_infos_client(&myself, CLIENT_PORT);

      
    T_StartReceiveBroadcast(&ReceiveBroadcastTh, ReceiveBroadcast, &myself);

    char user_buffer[MESSAGE_SIZE] = {0x0};

    while(1)
    {
        WaitForInput(user_buffer, MESSAGE_SIZE);
        CMD_send_broadcast(&myself, user_buffer);
        //CMD_SendDebug(&myself, user_buffer);
        //CMD_SayHi(&myself);

        memset(user_buffer, 0, MESSAGE_SIZE);
    }

    pthread_join(ReceiveBroadcastTh, NULL);
}

