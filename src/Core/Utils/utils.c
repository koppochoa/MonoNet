#include "utils.h"

void ColorPrint(const char* color, char* format)
{
    printf("\033[%sm", color);
    printf("%s", format);
    printf("\033[0m");
}


void WaitForInput(char* buffer, size_t buff_len)
{
    ColorPrint(COLOR_BLUE, "[Myself]>>");

    fgets(buffer, buff_len, stdin);
    printf("\n");

    size_t len = strcspn(buffer, "\n");
    if (buffer[len] == '\n') 
    {
        buffer[len] = '\0'; // Supprime le \n
    } 
    else 
    {
        // Trop long : flush le reste
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
    }
}

void print_bytes(const char* label, const unsigned char* data, int len) 
{
    printf("%s (%d bytes): ", label, len);
    for (int i = 0; i < len; ++i)
        printf("%02X ", data[i]);
    printf("\n");
}

