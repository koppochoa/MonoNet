


#include "server.h"
#include "menu.h"
#include <stdio.h>

void DisplayMainMenu()
{
    Menu_Template* menu = CreateMenuTemplate(4);
    AddMenuAction(menu, "Host Server", runServer);
    AddMenuAction(menu, "Exit", Quit);

    DisplayMenu(menu);

    menu_free(menu);
}

int main(void)
{
	DisplayMainMenu();

	return 0;
}
