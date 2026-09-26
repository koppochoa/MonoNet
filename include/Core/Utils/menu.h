#ifndef MENU_H
#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

typedef struct Menu_Template
{
    char** actions_titles;
    void (**functions)(void*);
    int current_size;
    int max_size;

}Menu_Template;

Menu_Template* CreateMenuTemplate(int max);
void AddMenuAction(Menu_Template* menu, char* title, void *func);
void DisplayMenu(Menu_Template* menu);
void Quit();

void menu_free(Menu_Template* menu);



#endif
