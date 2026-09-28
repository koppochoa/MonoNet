#include "mono_client.h"

// Main Client Variables
Client myself = {0x0};
volatile bool client_killswitch = false;

unsigned char key[32] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                         0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F,
                         0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
                         0x18, 0x19, 0x1A, 0x1B, 0x1C, 0x1D, 0x1E, 0x1F};

unsigned char iv[16] = {0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
                        0x08, 0x09, 0x0A, 0x0B, 0x0C, 0x0D, 0x0E, 0x0F};

pthread_t ReceiveBroadcastTh;
int ReceiveBroadcastTh_id = 1;

int runClient(const char *ip, int port) {
  signal(SIGPIPE, SIG_IGN);
  signal(SIGINT, exit_network);

  if (InitClientSocket(&myself.fd, &myself.addr, port, ip) == -1) {
    return -1;
  }

  InitMyself(&myself, &myself.fd, &myself.addr, key, iv);

  diplay_infos_client(&myself, port);

  T_StartReceiveBroadcast(&ReceiveBroadcastTh, ReceiveBroadcast, &myself);

  char user_buffer[MESSAGE_SIZE] = {0x0};

  while (1) {
    print_prompt(ip);
    size_t len = WaitForInput(user_buffer, MESSAGE_SIZE);

    int res = handle_client_input(&myself, user_buffer, len);

    if (res == MONONET_EXIT_NETWORK) {
      break;
    }

    // CMD_send_broadcast(&myself, user_buffer);
    //  CMD_SendDebug(&myself, user_buffer);
    //  CMD_SayHi(&myself);

    memset(user_buffer, 0, MESSAGE_SIZE);
  }

  pthread_join(ReceiveBroadcastTh, NULL);

  return 0;
}
