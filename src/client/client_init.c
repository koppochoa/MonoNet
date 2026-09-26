#include "client_init.h"

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

void InitClientSocket(int *client_fd, struct sockaddr_in *addr, int port,
                      const char *ip) {
  // Create Socket
  *client_fd = socket(AF_INET, SOCK_STREAM, 0);
  if (*client_fd < 0) {
    perror("Error while creating socket");
    exit(1);
  }
  
  memset(addr, 0, sizeof(*addr));

  // Configure Server Addr
  addr->sin_family = AF_INET;
  addr->sin_port = htons(port);

  printf("pton-ing...\n");

  if (inet_pton(AF_INET, ip, &addr->sin_addr) <= 0) {
    perror("inet_pton");
    exit(1);
}

printf("connecting...\n");
  // Connect
  if (connect(*client_fd, (struct sockaddr *)addr, sizeof(*addr)) < 0) {
    perror("Error while connecting");
    exit(1);
  }

  printf("Successfully Connected to : %s\n", ip);

}

void HandleClientExit() {
  // TOdo
}
