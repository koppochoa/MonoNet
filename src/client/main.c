#include "client.h"


void DisplayMainMenu()
{
    Menu_Template* menu = CreateMenuTemplate(4);
    //AddMenuAction(menu, "Host Server", CreateServer);
    AddMenuAction(menu, "Connect Client", runClient);
    AddMenuAction(menu, "Exit", Quit);

    DisplayMenu(menu);

    menu_free(menu);
}

int main(void)
{

	DisplayMainMenu();

	return 0;
}
