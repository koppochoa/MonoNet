#ifndef SERVER_MANAGER_H
#define SERVER_MANAGER_H

void server_InitSignals(int* server, void* menu, List* list, int* epfd, bool* th1, bool* th2, bool* th3);

void InitServerSocket(int* socket_fd, struct sockaddr_in* server_addr, int port, int max_clients);

void InitEpoll(int* epfd_out, int server_fd);

void handle_header(int* fd, Header* header, int* epfd, List* client_list);

//int handle_command(int* fd, int* epfd, List* client_list, Header* header, Ciphered_Message* message, struct Queue* queue);

void handle_server_closing();




#endif