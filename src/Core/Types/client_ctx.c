#include "client_ctx.h"

#include "client.h"

void init_client_ctx(ClientContext* ctx)
{
    ctx->bytes_received = 0;
    ctx->step           = RECV_HEADER;
    ctx->packet_index   = 0;
    
    memset(&ctx->header, 0, sizeof(Header));
    memset(&ctx->metadata, 0, sizeof(Metadata));

    for(int i = 0; i < 255; i++)
    {
        memset(ctx->packets[i], 0, sizeof(Packet) + AES_BLOCK_SIZE);
    }
}

ClientContext* ctx_from_fd(int fd, List* client_list)
{
    List_Node* current = client_list->first;

    while (current != NULL)
    {
        Client* current_client = (Client*) current->data;

        if (current_client->fd == fd)
        {
            return &current_client->ctx;
        }

        current = current->next;
    }

    return NULL; // fd non trouvé
}

void reset_client_ctx(ClientContext* ctx)
{
    ctx->step = RECV_HEADER;
    ctx->bytes_received = 0;
    memset(&ctx->header, 0, sizeof(Header));
    memset(&ctx->metadata, 0, sizeof(Metadata));
}
