#include "mono_client.h"

Client *ref_client;

int handle_client_input(Client* client, const char *buff, size_t len) {
  if (!buff)
    return 0;

  if(len == 0)return 0;

  if(buff[0] == '/')
  {
	  // non network 
	return handle_local_command(client, buff, len);
  }else
  {
	// network
	return handle_network_command(client, buff, len);
  }

  return 0;

}

int handle_local_command(Client* client, const char* buff, size_t len)
{
	printf("Command Received: [%s]\n", buff);

	if(strcmp(buff, "/exit") == 0)
	{
		exit_network(client);
		return MONONET_EXIT_NETWORK;
	}

	return 0;
}

int handle_network_command(Client* client, const char* buff, size_t len)
{
    CMD_send_broadcast(client, buff);
	return 0;
}

/**
 * Gere la fin du programme
 * */
void exit_network() {
  // Gerer chaque os dans des fonctions

  ColorPrint(COLOR_RED,("\n[mononet]Exiting !\n"));
client_killswitch = true;
  CMD_QuitServer(&myself);
  close(myself.fd);
}
