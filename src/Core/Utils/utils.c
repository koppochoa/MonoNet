#include "utils.h"

void ColorPrint(const char *color, char *format) {
  printf("\033[%sm", color);
  printf("%s", format);
  printf("\033[0m");
}

size_t WaitForInput(char *buffer, size_t buff_len) {
  // ColorPrint(COLOR_BLUE, "mononet$ ");

  fflush(stdout);

  if (buff_len == 0)
    return 0;

  ssize_t bytes = read(STDIN_FILENO, buffer, buff_len - 1);

  if (bytes < 0) {
    buffer[0] = '\0';
    return 0;
  }

  size_t endofbuff = strcspn(buffer, "\n");
  buffer[endofbuff] = '\0';

  return endofbuff;
}

void print_bytes(const char *label, const unsigned char *data, int len) {
  printf("%s (%d bytes): ", label, len);
  for (int i = 0; i < len; ++i)
    printf("%02X ", data[i]);
  printf("\n");
}
