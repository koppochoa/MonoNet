#ifndef CLIENT_INIT_H
#define CLIENT_INIT_H

void InitMyself(Client* myself, int* client_fd, struct sockaddr_in* com_server_addr, const unsigned char* key, const unsigned char* iv);


#ifdef _WIN32
    void InitClientSocket(WSADATA* wsa, SOCKET* client_fd, struct sockaddr_in* addr, int port, const char* ip);
#else
    void InitClientSocket(int* client_fd, struct sockaddr_in* addr, int port, const char* ip);
#endif



#endif
