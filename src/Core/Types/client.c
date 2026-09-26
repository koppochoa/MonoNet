#include "client.h"

Client* client_from_fd(int fd, List* client_list)
{
    List_Node* current = client_list->first;

    while (current != NULL)
    {
        Client* current_client = (Client*) current->data;

        if (current_client->fd == fd)
        {
            return current_client;
        }

        current = current->next;
    }

    return NULL; // fd non trouvé
}
