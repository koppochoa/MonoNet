#include "message.h"

Message create_message(char* message_text, struct tm time)
{
    Message message =  {0x0};
    strcpy(message.message,message_text);
    message.time = time;
    return message;
}

void update_message(Message* message, char* message_text, struct tm time)
{
    reset_message(message);
    strcpy(message->message, message_text);
    message->time = time;
}

void update_message_from_packet(Message* message, Packet* packet, Metadata* metadata)
{
    update_message(message, packet->data, metadata->time);
}

void log_message(Message* message)
{
    char info_message[11] = {0x0};
    int hour = message->time.tm_hour;
    int min  = message->time.tm_min;
    int sec  = message->time.tm_sec;

    snprintf(info_message,sizeof(info_message), "[%d:%d:%d] : ", hour, min, sec);

    char text_message[MESSAGE_SIZE] = {0x0};
    sprintf(text_message, "%s", message->message);

    ColorPrint(COLOR_YELLOW, info_message);
    ColorPrint(COLOR_CYAN, text_message);

    printf("\n");
}

void reset_message(Message* message)
{
    memset(message, 0, sizeof(Message));
}
