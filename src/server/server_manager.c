#include "server_manager.h"

int* ref_server_socket;
bool* ref_pause_th_rc, ref_pause_th_bm, ref_pause_th_rfc;
Menu_Template* ref_menu;
List* ref_client_list;
int* ref_epfd;

void server_InitSignals(int* server, void* menu, List* list, int* epfd,bool* th1, bool* th2, bool* th3)
{
    ref_menu            = (Menu_Template*)menu;
    ref_server_socket   = server;
    ref_client_list     = list;
    ref_epfd            = epfd;
    ref_pause_th_rc     = th1;
    ref_pause_th_bm     = th2;
    ref_pause_th_rfc    = th3;
}

/**
 * Initialize the socket of the created server
 */
void InitServerSocket(int* socket_fd, struct sockaddr_in* server_addr, int port, int max_clients)
{
    // Create Server Socket
    *socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    // Configure Server Addr
    (*server_addr).sin_family       = AF_INET;
    (*server_addr).sin_addr.s_addr  = INADDR_ANY;
    (*server_addr).sin_port         = htons(port);
    
    // Bind Socket to addr
    bind(*socket_fd, (struct sockaddr*)server_addr, sizeof(*server_addr));

    // Listen to connections
    listen(*socket_fd, max_clients);

    make_non_blocking(socket_fd);
}

// Initialise Epoll
void InitEpoll(int* epfd_out, int server_fd)
{
    int epfd = epoll_create1(0);
    if (epfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    struct epoll_event ev;
    ev.events = EPOLLIN | EPOLLONESHOT;
    ev.data.fd = server_fd;

    if (epoll_ctl(epfd, EPOLL_CTL_ADD, server_fd, &ev) == -1)
    {
        perror("epoll_ctl");
        close(server_fd);
        close(epfd);
        exit(EXIT_FAILURE);
    }

    *epfd_out = epfd; // rendre l'epfd au reste du code
}

void handle_header(int* fd, Header* header, int* epfd, List* client_list)
{
    switch (header->packet_type)
    {
    case CMD_CLIENT_LEAVE:
        SRV_disconnect_client(fd, epfd, client_list);
        break;
    case CMD_SAYHI:
        SRV_sayhi();
    default:
        break;
    }
}

int handle_client_command(int* fd, Header* header, struct Queue* queue)
{
    //? Opti : hashset

    if(!fd)     return -1;
    if(!header) return -1;
    if(!queue)  return -1;
    
    switch (header->packet_type)
    {
    case CMD_BROADCAST_MESSAGE:
       //SRV_add_message_to_queue(queue, message);
       return 0;
    default:
        break;
    }

    return 0;
}


/**
 * signal call func
 */
void handle_server_closing()
{
    log_server(INFO, "Server Bye Bye...");

    //* Stop All Threads
    app_killswitch = true;

    close(*ref_server_socket);
    close(*ref_epfd);
    menu_free(ref_menu);
    list_free(ref_client_list);

    exit(0);
}
