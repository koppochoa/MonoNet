#pragma once

#ifdef _WIN32
    #include <WinSock2.h>
    #include <WS2tcpip.h>
    #include <stdint.h>
    // Win compile : -lsw2_32 
#else
    #include <sys/types.h>
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <arpa/inet.h>
    #include <unistd.h>
    #include <netdb.h>
    #include <sys/epoll.h>
    #include <fcntl.h>
#endif

#include <openssl/aes.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <openssl/err.h>

#include <stdbool.h>

#define MESSAGE_SIZE 100

extern volatile bool            app_killswitch;
extern volatile bool            client_killswitch;

#include <signal.h>

#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdarg.h>

#include "types.h"
#include "utils.h"
#include "list.h"

#include "menu.h"

#include "metadata.h"
#include "header.h"
#include "packet.h"
#include "footer.h"
#include "client_ctx.h"
#include "message.h"
#include "client.h"
#include "request.h"


#include "queue.h"

#include "security.h"
#include "serializer.h"

#include "client_utils.h"

#include "comm_utils.h"
#include "data_transfer.h"
#include "struct_transfer.h"
#include "data_exchange.h"

#include "client_transfer.h"
#include "server_transfer.h"

#include "commands.h"
#include "server_commands.h"
#include "client_commands.h"

#include "client_manager.h"
#include "client_threads.h"
#include "client_init.h"

#include "server_utils.h"
#include "server_manager.h"
#include "server_threads.h"

#include "server_main.h"
#include "client_main.h"

#include "tests.h"


#define IP_ADDR "127.0.0.1"




