#pragma once

#define MESSAGE_SIZE 100

#include <stdbool.h>

extern volatile bool client_killswitch;

#include "struct_transfer.h"
#include "client_transfer.h"
#include <stdarg.h>
#include "util.h"
#include "client.h"
#include "packet.h"
#include "client_utils.h"
#include "commands.h"
#include "security.h"
#include "message.h"
#include "data_exchange.h"
#include "client_init.h"
#include "client_manager.h"
#include "client_threads.h"
#include "client_utils.h"
#include "struct_transfer.h"
#include "client_utils.h"
#include "client_commands.h"
#include "menu.h"
#include <arpa/inet.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
