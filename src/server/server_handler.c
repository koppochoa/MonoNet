#include "server_handler.h"

void mononet_hello() { printf("Hi From MonoNet, Have Fun !\n"); }

void display_banner() {
  printf("       __        __        ___ ___\n");
  printf(" |\\/| /  \\ |\\ | /  \\ |\\ | |__   |  \n");
  printf(" |  | \\__/ | \\| \\__/ | \\| |___  |  \n");

  printf("\n");
}

void program_handler() {

  display_banner();
  display_helper();

  while (1) {
    char buffer[100] = {0x0};
    WaitForInput(buffer, sizeof(buffer));

    char *argv[32];
    int argc = 0;

    char *token = strtok(buffer, " ");

    while (token != NULL && argc < 32) {
      argv[argc++] = token;
      token = strtok(NULL, " ");
    }

    if (strcmp(argv[0], "exit") == 0)
      break;

    if (strcmp(argv[0], "hi") == 0) {
      mononet_hello();
    }

    if (strcmp(argv[0], "host") == 0) {
      if (argc != 2) {
        printf(
            "[mononet][err]: Incorrect Number of args : connect <IP> <PORT>\n");
        continue;
      }
      runServer(atoi(argv[1]));
    }
  }
}

void display_helper() {

  ColorPrint(COLOR_YELLOW, "exit\n");
  ColorPrint(COLOR_YELLOW, "host <PORT>\n");

  printf("\n");
}

