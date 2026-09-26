#ifndef COMMANDS_H
#define COMMANDS_H

#define CMD_DEBUG_SERVER        0
#define CMD_SAYHI               1
#define CMD_CLIENT_LEAVE        2
#define CMD_BROADCAST_MESSAGE   3

#define CMD_SERVER_BROADCAST    7


void call_cmd(const char* command_call);


#endif