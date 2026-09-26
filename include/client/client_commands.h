#ifndef CLIENT_COMMANDS_H
#define CLIENT_COMMANDS_H


void CMD_send_broadcast(Client* client, const char* message);

void CMD_QuitServer(Client* client);

void CMD_SendDebug(Client* client, const char* message);

void CMD_SayHi(Client* client);



#endif