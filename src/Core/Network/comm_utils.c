#include "network.h"

void make_non_blocking(int* fd)
{
    int flags = fcntl(*fd, F_GETFL, 0);
    if (flags == -1) {
        perror("fcntl(F_GETFL)");
        return;
    }

    if (fcntl(*fd, F_SETFL, flags | O_NONBLOCK) == -1) {
        perror("fcntl(F_SETFL)");
    }
}
