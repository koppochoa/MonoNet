#include "mono_client.h"

// Affiche des information client
void log_client(enum DEBUG_TYPE type, char* format, ...)
{
    va_list args;
    va_start(args, format);

    switch(type)
    {   
        case INFO:
            ColorPrint(COLOR_BLUE, "[CLIENT INFO]: ");
            break;
        case WARNING:
            ColorPrint(COLOR_YELLOW, "[CLIENT WARNING]: ");
            break;
        case ALERT:
            ColorPrint(COLOR_RED, "[CLIENT ALERT]: ");
            break;
    }

    vprintf(format, args);
    va_end(args);
    printf("\n");
}

// Display basic client infos
void diplay_infos_client(Client* client, unsigned int port)
{
    log_client(INFO, "Welcome to No-Fly, you are actually initiating Client behaviour");

    char server_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client->addr, server_ip, INET_ADDRSTRLEN);
    
    log_client(WARNING, "Client Connection Infos");
    ColorPrint(COLOR_CYAN, "IP              ");printf("%s\n", server_ip);
    ColorPrint(COLOR_CYAN, "PORT            ");printf("%d\n", port);
    ColorPrint(COLOR_RED,  "KEY            ");print_hex("",client->key, 32);
    ColorPrint(COLOR_RED,  "IV             ");print_hex("",client->iv, 16);


    //printf("IP      :    %s\n", server_ip);
    //printf("PORT    :    %d\n", port);
    //print_hex("key : ",myself.key, 32);
    //print_hex("iv : ",myself.iv, 16);
}
