#include "client_init.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <poll.h>
#include <arpa/inet.h>
#include <sys/socket.h>


/**
 * Call this func to init ursefl
 */
void InitMyself(Client *myself, int *client_fd,
                struct sockaddr_in *com_server_addr, const unsigned char *key,
                const unsigned char *iv) {
  myself->fd = *client_fd;
  myself->addr = *com_server_addr;

  memcpy(myself->key, key, 32);
  memcpy(myself->iv, iv, 16);
}


int InitClientSocket(int *client_fd, struct sockaddr_in *addr,
                     int port, const char *ip)
{
    *client_fd = -1;

    // Create socket
    *client_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (*client_fd < 0) {
        perror("socket");
        return -1;
    }

    printf("[mononet][info]: Socket Successfully Created\n");

    // Configure server address
    memset(addr, 0, sizeof(*addr));

    addr->sin_family = AF_INET;
    addr->sin_port = htons(port);

    // Convert IP
    int ret = inet_pton(AF_INET, ip, &addr->sin_addr);

    if (ret == 0) {
        fprintf(stderr, "Invalid IPv4 address: %s\n", ip);
        close(*client_fd);
        *client_fd = -1;
        return -1;
    }

    if (ret < 0) {
        perror("inet_pton");
        close(*client_fd);
        *client_fd = -1;
        return -1;
    }

    printf("[mononet][info]: Addr Successfully Copied\n");

    // Save current socket flags
    int flags = fcntl(*client_fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl");
        close(*client_fd);
        *client_fd = -1;
        return -1;
    }

    // Set socket to non-blocking
    if (fcntl(*client_fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl");
        close(*client_fd);
        *client_fd = -1;
        return -1;
    }

    printf("[mononet][info]: Connecting to %s:%d...\n", ip, port);

    // Try to connect
    ret = connect(*client_fd,
                  (struct sockaddr *)addr,
                  sizeof(*addr));

    if (ret < 0 && errno != EINPROGRESS) {
        perror("connect");
        close(*client_fd);
        *client_fd = -1;
        return -1;
    }

    // Connection is in progress
    if (ret < 0) {
        struct pollfd pfd = {
            .fd = *client_fd,
            .events = POLLOUT
        };

        // Wait maximum 3 seconds
        ret = poll(&pfd, 1, 3000);

        if (ret == 0) {
            fprintf(stderr, "Connection timeout\n");
            close(*client_fd);
            *client_fd = -1;
            return -1;
        }

        if (ret < 0) {
            perror("poll");
            close(*client_fd);
            *client_fd = -1;
            return -1;
        }

        // Check if connect actually succeeded
        int socket_error = 0;
        socklen_t len = sizeof(socket_error);

        if (getsockopt(*client_fd,
                       SOL_SOCKET,
                       SO_ERROR,
                       &socket_error,
                       &len) < 0) {
            perror("getsockopt");
            close(*client_fd);
            *client_fd = -1;
            return -1;
        }

        if (socket_error != 0) {
            errno = socket_error;
            perror("connect");
            close(*client_fd);
            *client_fd = -1;
            return -1;
        }
    }

    // Put socket back in blocking mode
    if (fcntl(*client_fd, F_SETFL, flags) == -1) {
        perror("fcntl");
        close(*client_fd);
        *client_fd = -1;
        return -1;
    }

    printf("[mononet][info]: Successfully Connected to %s:%d\n",
           ip, port);

    return 0;
}


void HandleClientExit() {
  // TOdo
}
