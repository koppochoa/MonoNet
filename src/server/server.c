#include "server.h"

// Main Server Variables
int                 server_fd;              // Server file descriptor
struct sockaddr_in  server_addr;            // Server address  
#define MAX_CLIENTS 3

// Secondary Server Variables
struct Queue*       messages_queue;               // Store all sended messages 

// Server Applications
pthread_t           RegisterClientTh,           BroadcastMessageTh,             ReceivingFromClientsTh;
bool                pause_th_rc = false,        pause_th_bm = false,            pause_th_rfc = false;
bool                thread_switch = true;       // Applications Killswitch

// Server Management Variables
List                *clients;
int                 clients_capacity = MAX_CLIENTS;
int                 clients_current_len = 0;
pthread_mutex_t     client_current_len_lock = PTHREAD_MUTEX_INITIALIZER;

// Epoll
int                 epfd;
struct epoll_event  ev;
#define MAX_EVENTS  10
struct epoll_event  events[MAX_EVENTS];

int                 last_client = 0;                    // Last client index
socklen_t           addr_size;                          // Address size

//* MAIN KILLSWITCH
volatile bool app_killswitch = false;

//* Main Server Method
void runServer(int port)
{
    signal(SIGINT, handle_server_closing);

    // Initialise la Queue de communication
    messages_queue = create_queue();

    // Initialisation du tableau de clients
    clients = createList();

    //server_InitSignals(&server_fd, args, clients, &epfd,&pause_th_rc, &pause_th_bm, &pause_th_rfc);

    log_server(INFO, "Creating Server\n");

    InitServerSocket(&server_fd, &server_addr, port, MAX_CLIENTS);

    InitEpoll(&epfd, server_fd);

    // Affiche des infos serveur
    DisplayServerInfos(&server_addr, port);

    T_StartRegisterClient       (&RegisterClientTh,         RegisterClient, &server_fd, clients, &epfd, messages_queue, &pause_th_rc);
    T_StartReceivingFromClients (&ReceivingFromClientsTh,   ReceivingFromClients, &server_fd, clients, &epfd, events, messages_queue, &pause_th_rfc);
    T_StartBroadcastMessage     (&BroadcastMessageTh,       BroadcastMessage, clients, messages_queue, &pause_th_bm);

    pthread_join(RegisterClientTh, NULL);
    pthread_join(ReceivingFromClientsTh, NULL);
    pthread_join(BroadcastMessageTh, NULL);

}
