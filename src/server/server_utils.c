#include "chat.h"

// Ferme le serveur | WIN/UNIX
void CloseServer(int *fd, bool *stop_switch)
{
    *stop_switch = false;
    close(*fd);
}

// Affiche des information server
void log_server(enum DEBUG_TYPE type, char* format, ...)
{
    va_list args;
    va_start(args, format);

    switch(type)
    {   
        case INFO:
            ColorPrint(COLOR_BLUE, "[SERVER INFO]: ");
            break;
        case WARNING:
            ColorPrint(COLOR_YELLOW, "[SERVER WARNING]: ");
            break;
        case ALERT:
            ColorPrint(COLOR_RED, "[SERVER ALERT]: ");
            break;
    }

    vprintf(format, args);
    va_end(args);
    printf("\n");
}

void DisplayServerInfos(struct sockaddr_in* server_addr, int port)
{
    char server_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &server_addr->sin_addr, server_ip, INET_ADDRSTRLEN);

    log_client(WARNING, "Server Connection Infos");
    ColorPrint(COLOR_CYAN, "IP              ");printf("%s\n", server_ip);
    ColorPrint(COLOR_CYAN, "PORT            ");printf("%d\n", port);
}

int index_from_fd(int fd, List* client_list)
{
    List_Node* current = client_list->first;

    int counter = 0;

    while (current != NULL)
    {
        Client* current_client = (Client*) current->data;

        if (current_client->fd == fd)
        {
            return counter;
        }

        counter++;
        current = current->next;
    }

    return -1; // fd non trouvé
}



void clean_client(int* fd, int* epfd, List* list)
{
    close(*fd);
    
    epoll_ctl(*epfd, EPOLL_CTL_DEL, *fd, NULL);

    pthread_mutex_lock(&list->lock); // 🔐
    RemoveAt(list, index_from_fd(*fd, list));
    pthread_mutex_unlock(&list->lock); // 🔓

}






