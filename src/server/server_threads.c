#include "chat.h"

/**
 * Entry point for the Registering Thread
 */
void T_StartRegisterClient(pthread_t* thread, void* (*func)(void*), int* server_fd, List* list, int* epfd, Queue* message_queue, bool* pause_switch)
{
    struct RegisterClientArgs* args = (struct RegisterClientArgs*)malloc(sizeof(struct RegisterClientArgs));
    if(!args)
    {
        perror("Error allocating args");
    }
    args->fd            = server_fd;
    args->list          = list;
    args->epfd          = epfd;
    args->pause_switch  = pause_switch;
    args->queue         = message_queue;

    if(pthread_create(thread, NULL, func, (void*)args) != 0)
    {
        perror("Error pthread_create");
        free(args);
        return;
    }
}

void* RegisterClient(void* args)
{
    struct RegisterClientArgs* _args = (struct RegisterClientArgs*)args;
    int* server_fd     = _args->fd;
    List* clients_list = _args->list;
    int* epfd          = _args->epfd;
    bool* pause_switch = _args->pause_switch;
    Queue* message_queue = _args->queue;

    free(_args);

    log_server(INFO, "Start Registering Clients");

    while (!app_killswitch)
    {
        while(*pause_switch){}

        struct sockaddr_in addr;
        socklen_t addr_size = sizeof(addr);

        int client_fd = accept(*server_fd, (struct sockaddr*)&addr, &addr_size);
        while(client_fd < 0)
        {
            if (errno == EAGAIN || errno == EWOULDBLOCK)
            {
                usleep(1000);
                client_fd = accept(*server_fd, (struct sockaddr*)&addr, &addr_size);
            }else
            {
                perror("accept");
                break;
            }

        }

        make_non_blocking(&client_fd);

        struct epoll_event client_ev;
        client_ev.events = EPOLLIN | EPOLLET;
        client_ev.data.fd = client_fd;
        if (epoll_ctl(*epfd, EPOLL_CTL_ADD, client_fd, &client_ev) == -1)
        {
            perror("epoll_ctl");
            close(client_fd);
            continue;
        }

        // On a un client valide

        Client* client = malloc(sizeof(Client));
        if (!client)
        {
            perror("malloc");
            close(client_fd);
            continue;
        }
        

        client->fd = client_fd;
        client->addr = addr;
        init_client_ctx(&client->ctx);

        // Générer un nom unique
        snprintf(client->username, sizeof(client->username), "default_%d", clients_list->size + 1);

        append(clients_list, client);

        //time_t now = time(NULL); 
        //struct tm time = *localtime(&now);
        //SRV_client_joined(client, message_queue, time);
        

        log_server(INFO, "New Client connected");
    }

    log_server(INFO, "Registering Clients Terminated");
    pthread_exit(NULL);

    return NULL;
}

/**
 * Entry Point for the Receiving Thread
 */
void T_StartReceivingFromClients(pthread_t* thread, void* (*func)(void*), int* server_fd, List* list, int* epfd, struct epoll_event* events, struct Queue* message_queue, bool* pause_switch)
{
    struct CatchingClientArgs* args = (struct CatchingClientArgs*)malloc(sizeof(struct CatchingClientArgs));
    if(!args)
    {
        perror("Error allocating args");
    }
    args->fd            = server_fd;
    args->list          = list;
    args->epfd          = epfd;
    args->events        = events;
    args->msg_queue     = message_queue;
    args->pause_switch  = pause_switch;

    if(pthread_create(thread, NULL, func, (void*)args) != 0)
    {
        perror("Error pthread_create");
        free(args);
        return;
    }
}

void* ReceivingFromClients(void* args)
{
    struct CatchingClientArgs* _args = (struct CatchingClientArgs*)args;
    int* server_fd              = _args->fd;// a enlever si pas besoin
    List* clients_list          = _args->list;
    struct epoll_event* events  = _args->events;
    int* epfd                   = _args->epfd;
    struct Queue* message_queue = _args->msg_queue;
    //bool* pause_switch          = _args->pause_switch;

    free(_args);

    log_server(INFO, "Start Receiving message");

    Header      header          = {0x0};
    Metadata    metadata        = {0x0};
    Message     message         = {0x0};

    //* Clé AES 256 bits (32 octets)
    unsigned char key2[32] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
        0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 
        0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F
    };
    
    unsigned char iv2[16] = {
        0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 
        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F
    };
    


    while(!app_killswitch)
    {
        //while(*pause_switch){}

        int n = epoll_wait(*epfd, events, 10, 1000); // TODO : Set la variable max events
        if(n == -1)
        {
            perror("epoll_wait");
            break;
        }
        else if(n == 0)
        {
            continue;
        }

        for(int i = 0; i < n; i++)
        {
            int fd = events[i].data.fd;

            if(fd == *server_fd)
            {
                continue;
            }

            if(events[i].events & EPOLLHUP) // client deconecte
            {
                clean_client(&fd, epfd, clients_list);
            }

            if(events[i].events & EPOLLIN)
            {
                //ClientContext *ctx = ctx_from_fd(fd, clients_list);
                Client* current_client = client_from_fd(fd, clients_list);
                ClientContext* ctx = &current_client->ctx;
                if (current_client == NULL) continue;


                //! fonction de rearmement

                int result = receive_protocol_data_new(fd, ctx);
                //log_server(INFO, "receive_protocol_data_new(%d) = %d", fd, result);

                if (result == 1) 
                {
                    handle_header(&fd, &ctx->header, epfd, clients_list);
                    debug_protocol(&ctx->header, &ctx->metadata);

                    //* Ne pas rearmer si le client a quitte le serveur
                    if(ctx->header.packet_type == CMD_CLIENT_LEAVE)
                    {
                        break;
                    }
                    // Ne pas réarmer, on attendra une nouvelle requête
                    struct epoll_event ev;
                    ev.events = EPOLLIN | EPOLLONESHOT;
                    ev.data.fd = fd;
                    if (epoll_ctl(*epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
                        perror("epoll_ctl: EPOLL_CTL_MOD");
                    } else {
                        //log_server(INFO, "Réarmement du fd %d avec EPOLLONESHOT", fd);
                    }
                }
                else if (result == 0) {
                    // Protocole incomplet : réarmer pour continuer plus tard
                    struct epoll_event ev;
                    ev.events = EPOLLIN | EPOLLONESHOT;
                    ev.data.fd = fd;
                    if (epoll_ctl(*epfd, EPOLL_CTL_MOD, fd, &ev) == -1) {
                        perror("epoll_ctl: EPOLL_CTL_MOD");
                    } else {
                        //log_server(INFO, "Réarmement du fd %d avec EPOLLONESHOT", fd);
                    }
                }
                else {
                    // Erreur ou déconnexion
                    //log_server(WARNING, "Client déconnecté (fd %d)", fd);
                    clean_client(&fd, epfd, clients_list);
                    close(fd);
                    epoll_ctl(*epfd, EPOLL_CTL_DEL, fd, NULL);
                }


                if(ctx->can_read && ctx->header.packet_type == CMD_DEBUG_SERVER)
                {
                    Packet new_packet = {0x0};
                    unsigned char new_packet_s[sizeof(Packet)];
                    size_t newLen = sizeof(Packet) + (AES_BLOCK_SIZE - (sizeof(Packet) % AES_BLOCK_SIZE));
                    aes_decrypt(ctx->packets[0], newLen, key2, iv2, new_packet_s);
                    int result = deserialize_packet(&new_packet, new_packet_s, sizeof(Packet));

                    //log_server(WARNING, "[%d:%d:%d] USER :  %s", metadata.time.tm_hour, metadata.time.tm_min, metadata.time.tm_sec, new_packet.data);
                    
                    message = create_message(new_packet.data, ctx->metadata.time);
                    log_message(&message);

                }
                if(ctx->can_read && ctx->header.packet_type == CMD_BROADCAST_MESSAGE)
                {
                    ClientRequest request   = create_client_request(ClientType, 
                                                                    current_client->fd, 
                                                                    ctx->packets, 
                                                                    ctx->header.packet_count, 
                                                                    ctx->header.packet_type, 
                                                                    ctx->metadata.time);
                    enqueue(message_queue, &request, sizeof(ClientRequest));

                }

                if(result == 1)
                {
                    //* Reset metadata et header
                    reset_metadata(&ctx->metadata);
                    reset_header(&ctx->header);
                }

                
            }
        }
    }

    log_server(INFO, "Receiving message Terminated");

    // Clean-up ici
    close(*epfd); // Fermer l'epoll descriptor
    pthread_exit(NULL);

    return NULL;
}

/**
 * Entry point for the Broadcast of all messages
 */
void T_StartBroadcastMessage(pthread_t* thread, void* (*func)(void*), List* clients_list, struct Queue* message_queue, bool* pause_switch)
{
    struct BroadcastClientArgs* args = (struct BroadcastClientArgs*)malloc(sizeof(struct BroadcastClientArgs));
    if(!args)
    {
        perror("Error allocating args");
    }
    args->list          = clients_list;
    args->queue         = message_queue;
    args->pause_switch  = pause_switch;

    if(pthread_create(thread, NULL, func, (void*)args) != 0)
    {
        perror("Error pthread_create");
        free(args);
        return;
    }
}

void* BroadcastMessage(void* args)  
{
    struct BroadcastClientArgs* _args = (struct BroadcastClientArgs*)args;
    List* clients_list          = _args->list;
    struct Queue* message_queue = _args->queue;
    bool* pause_switch          = _args->pause_switch;


    free(_args);

    log_server(INFO, "Start Broadcasting messages");

    ClientRequest* request = NULL;


    while(!app_killswitch)
    {
        request = dequeue(message_queue); 
     
        if(request != NULL)
        {
            for(unsigned int i = 0; i < clients_list->size; i++)
            {
                Client* current_client = GetAt(clients_list, i);

                if(current_client->fd != request->sender_fd)
                {
                    SRV_CMD_send_packet_to_client(current_client, request->packets, &request->packets_count, &request->packet_type, &request->time);
                }
            }
        }

        free(request);
        
        sleep(MSG_COOLDOWN);

        //while(*pause_switch){}
        // int* sender_fd                   = (int*)dequeue(message_queue); 
        // unsigned char* current_packet   = dequeue(message_queue);
        // if(current_packet != NULL)
        // {
        //     for(unsigned int i = 0; i < clients_list->size; i++)
        //     {
        //         Client* current_client = GetAt(clients_list, i);
        //         if(current_client->fd != *sender_fd)
        //         {
        //             SRV_CMD_send_packet_to_client(current_client, current_packet, *sender_fd == -1 ? CMD_SERVER_BROADCAST : CMD_BROADCAST_MESSAGE);
        //         }
        //     }
        // }
        
    }


    log_server(INFO, "Start Broadcasting messages Terminated");
    pthread_exit(NULL);

    return NULL;
}