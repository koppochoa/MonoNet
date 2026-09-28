#include "client_handler.h"
#include "client_prompt.h"
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

    print_prompt(NULL);
    WaitForInput(buffer, sizeof(buffer));

    char *argv[32];
    int argc = 0;

    char *token = strtok(buffer, " ");

    while (token != NULL && argc < 32) {
      argv[argc++] = token;
      token = strtok(NULL, " ");
    }

    if (strcmp(argv[0], "exit") == 0){
      	exit(0);
	break;
    }

    if (strcmp(argv[0], "hi") == 0) {
      mononet_hello();
    }

    if (strcmp(argv[0], "connect") == 0) {
      if (argc != 3) {
        printf(
            "[mononet][err]: Incorrect Number of args : connect <IP> <PORT>\n");
        continue;
      }
      runClient((const char *)argv[1], atoi(argv[2]));
    }
  }
}

void display_helper() {

  ColorPrint(COLOR_YELLOW, "exit\n");
  ColorPrint(COLOR_YELLOW, "connect <IP> <PORT>\n");

  printf("\n");
}
