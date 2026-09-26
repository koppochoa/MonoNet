#ifndef MESSAGE_H
#define MESSAGE_H

#include <time.h>
#include "utils.h"
#include "packet.h"
#include "metadata.h"
typedef struct
{
    char        message[MESSAGE_SIZE];
    struct tm   time;
}Message;

Message create_message(char* message_text, struct tm time);
void    update_message(Message* message, char* message_text, struct tm time);
void    update_message_from_packet(Message* message, Packet* packet, Metadata* metadata);
void    log_message(Message* message);
void    reset_message(Message* message);

#endif
