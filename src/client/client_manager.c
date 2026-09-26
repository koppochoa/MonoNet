#include "mono_client.h"

Client* ref_client;
Menu_Template* refc_menu;

void client_InitSignals(Client* client, void* menu)
{
    refc_menu = (Menu_Template*)menu;
    ref_client = client;
}

/**
 * Gere la fin du programme
 * */ 
void HandleClientClosing() 
{
    // Gerer chaque os dans des fonctions

    printf("\nBrrrr !\n");
    
    //* Stop All Threads
    client_killswitch = true;
    //CMD_QuitServer(&myself);

    #ifdef _WIN32
        closesocket(client_fd);
        WSACleanup();
    #else
        CMD_QuitServer(ref_client);
        close(ref_client->fd);
        menu_free(refc_menu);
        exit(0);
    #endif

}
