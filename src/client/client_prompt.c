#include "client_prompt.h"
#include "utils.h"
#include <stdio.h>

void print_prompt(char* ip)
{
	const char* baseprompt = "mononet";
	const char* promptsymbol = "$";

	char buff[100] = {0x0};

	if(ip)
	{

	snprintf(buff, sizeof(buff), "%s(%s)%s ", baseprompt, ip, promptsymbol);
	}
	else
	{
		snprintf(buff, sizeof(buff), "%s%s ", baseprompt, promptsymbol);
	}

	ColorPrint(COLOR_BLUE, buff);

}
