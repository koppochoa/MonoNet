#include "network.h"

// Send Data
int send_data(int *fd, const unsigned char *data, unsigned int len) {
  unsigned int total_sent = 0;
  // log_server(INFO, "Sending %u", len);
  while (total_sent < len) {
    int sent = send(*fd, data + total_sent, len - total_sent, 0);
    if (sent < 0) {
      perror("Error while sending data");
      return -1;
    }
    total_sent += sent;
  }

  return total_sent;
}

int async_receive_data(int *fd, unsigned char *output, size_t *len) {
  size_t total_received = 0;
  while (total_received < *len) {
    int received = recv(*fd, output + total_received, *len - total_received, 0);
    if (received < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK)
        break; // On a lu tout ce qui était dispo
      // perror("recv");
      return 0;
    } else if (received == 0) {
      // Connexion fermée proprement par le client
      return -1;
    }
    total_received += received;
  }

  return total_received;
}

// int async_receive_data_partial(int* fd, unsigned char* output, size_t
// total_size, size_t already_received) {
//     size_t total_received = already_received;
//     while (total_received < total_size) {
//         int received = recv(*fd, output + total_received, total_size -
//         total_received, 0); if (received < 0) {
//             if (errno == EAGAIN || errno == EWOULDBLOCK)
//                 break;
//             perror("recv");
//             return -1;
//         }
//         if (received == 0)
//             return -1;
//         total_received += received;
//     }
//     return total_received - already_received; // retourne ce qu'on a reçu en
//     plus
// }

int async_receive_data_partial(int *fd, unsigned char *output,
                               size_t total_size, size_t already_received,
                               int *errcode) {
  size_t total_received = already_received;

  // log_server(ALERT,"RECEIVING FOR:   %ld", total_received);

  while (total_received < total_size) {
    ssize_t received =
        recv(*fd, output + total_received, total_size - total_received, 0);
    // log_server(ALERT,"READ:   %ld", received);

    if (received < 0) {
      if (errno == EAGAIN || errno == EWOULDBLOCK) {
        if (errcode)
          *errcode = errno;
        return 0; // Rien à lire maintenant, pas une erreur grave
      }
      fprintf(stderr, "recv() failed: %s\n", strerror(errno));
      if (errcode)
        *errcode = errno;
      return -1;
    }

    if (received == 0) {
      fprintf(stderr, "Connection closed by peer\n");
      if (errcode)
        *errcode = 0;
      return -1;
    }

    total_received += received;
  }
  // log_server(ALERT,"OUT WITH : %ld", total_received - already_received);

  if (errcode)
    *errcode = 0; // aucune erreur
  return total_received - already_received;
}

// int async_receive_data_partial(int* fd, void* buffer, size_t target_len,
// size_t already_received) {
//     size_t total_received = already_received;

//     while (total_received < target_len) {
//         int received = recv(*fd, ((uint8_t*)buffer) + total_received,
//         target_len - total_received, 0);

//         if (received < 0) {
//             if (errno == EAGAIN || errno == EWOULDBLOCK) {
//                 return 0; // Rien de dispo pour le moment, pas une erreur
//             }
//             perror("recv");
//             return -1;
//         } else if (received == 0) {
//             // Connexion fermée par le client
//             fprintf(stderr, "Client closed connection\n");
//             return -1;
//         }

//         total_received += received;
//     }

//     return total_received - already_received; // On retourne le nombre de
//     nouveaux octets lus
// }

// Receive Data
// unsigned char* async_receive_data(int* fd, int len)
// {
//     //log_server(INFO, "Trying to receive %d bytes of data", len);

//     unsigned char* data = NULL;
//     int retries = 5;

//     while (retries-- > 0)
//     {
//         data = malloc(len);
//         if (data) break;

//         fprintf(stderr, "malloc failed, retrying in 1s...\n");
//         sleep(1); // pause de 1 seconde (Linux/Unix)
//     }

//     if (!data)
//     {
//         fprintf(stderr, "malloc failed after multiple attempts\n");
//         exit(EXIT_FAILURE); // ou une autre gestion d’erreur
//     }

//     int total_received = 0;
//     while(total_received < len)
//     {
//         int received = recv(*fd, data + total_received, len - total_received,
//         0); if(received < 0)
//         {
//             if (errno == EAGAIN || errno == EWOULDBLOCK)
//                 break; // On a lu tout ce qui était dispo
//             perror("recv");
//             free(data);
//             return NULL;
//         }
//         else if (received == 0)
//         {
//             // Connexion fermée proprement par le client
//             free(data);
//             return NULL;
//         }
//         total_received += received;
//     }

//     return data;
// }

unsigned char *ReceiveData(int *fd, int len) {
  unsigned char *data = (unsigned char *)malloc(len);
  if (!data) {
    perror("Error while allocating memory for receiving");
  }

  int total_received = 0;
  while (total_received < len) {
    int received = recv(*fd, data + total_received, len - total_received, 0);
    if (received <= 0) {
      perror("Error while recepting data");
      return NULL;
    }
    total_received += received;
  }

  return data;
}
