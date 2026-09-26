#include "mono_client.h"

/**
 * Call this func to send broadcast message to everybody 
 */
void CMD_send_broadcast(Client* client, const char* message)
{
    call_cmd("sending broadcast");

    Packet packet = {0x0};
    memset(&packet, 0, sizeof(Packet));
    strcpy(packet.data, message);   //! gerer les messages trop volumineux
    packet.type = 45;

    Packet packet_to_send[1] = {0x0};
    packet_to_send[0] = packet;

    client_send(client, packet_to_send, 1, CMD_BROADCAST_MESSAGE, 0);

    //log_client(WARNING, "TOTAL BYTES SENT : %d", total_bytes_sent);
}

/**
 * Call this func to quit the server properly
 */
void CMD_QuitServer(Client* client)
{
    call_cmd("QUITSERVER");

    client_send(client, NULL, 0, CMD_CLIENT_LEAVE, 0);
    //SendCommandToServer(client,&packet, CMD_CLIENT_LEAVE);
}

/**
 * Call this func to send debug message to server 
 */
void CMD_SendDebug(Client* client, const char* message)
{
    call_cmd("debug server msg");

    Packet packet = {0x0};
    memset(&packet, 0, sizeof(Packet));
    strcpy(packet.data, message);   //! gerer les messages trop volumineux
    packet.type = 45;

    Packet packet_to_send[1] = {0x0};
    packet_to_send[0] = packet;

    client_send(client, packet_to_send, 1, CMD_DEBUG_SERVER, 0);

    //log_client(WARNING, "TOTAL BYTES SENT : %d", total_bytes_sent);
}

/**
 * Call this func whenever u want to greet the server
 */
void CMD_SayHi(Client* client)
{
    int total_bytes_sent = client_send(client, NULL, 0, CMD_SAYHI, 0);

    log_client(WARNING, "TOTAL BYTES SENT : %d", total_bytes_sent);
}
