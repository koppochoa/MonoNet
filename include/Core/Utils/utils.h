#ifndef UTILS_H
#define UTILS_H

#include "list.h"
#include "menu.h"
#include "queue.h"
#include <stddef.h>
#include <unistd.h>

enum DEBUG_TYPE { INFO, WARNING, ALERT };

#define COLOR_BLACK "30"
#define COLOR_RED "31"
#define COLOR_GREEN "32"
#define COLOR_YELLOW "33"
#define COLOR_BLUE "34"
#define COLOR_MAGENTA "35"
#define COLOR_CYAN "36"
#define COLOR_WHITE "37"

void ColorPrint(const char *color, char *format);
size_t WaitForInput(char *buffer, size_t buff_len);
void print_bytes(const char *label, const unsigned char *data, int len);

#endif
