#include "menu.h"

Menu_Template* CreateMenuTemplate(int max)
{
    Menu_Template* menu = (Menu_Template*)malloc(sizeof(Menu_Template));
    menu->max_size = max;
    menu->current_size = 0;
    menu->actions_titles = (char**)malloc(max * sizeof(char*));
    menu->functions = malloc(max * sizeof(void (*)(void*)));
    return menu;
}

void AddMenuAction(Menu_Template* menu, char* title, void *func)
{
    if (menu->current_size >= menu->max_size) 
    {
        menu->max_size++;
        
        char** tmp_titles = (char**)realloc(menu->actions_titles, menu->max_size * sizeof(char*));
        if (!tmp_titles) {
            printf("Erreur : impossible de réallouer de la mémoire pour les titres\n");
            return;  // Retourne immédiatement en cas d'erreur
        }

        void (**func_tmp)(void*)  = realloc(menu->functions, menu->max_size * sizeof(void (*)(void*)));
        if (!func_tmp) {
            // Si la réallocation pour les fonctions échoue, annuler la précédente
            printf("Erreur : impossible de réallouer de la mémoire pour les fonctions\n");
            // On libère tmp_titles pour éviter une fuite de mémoire
            free(tmp_titles);
            return;  // Retourne immédiatement en cas d'erreur
        }

        menu->actions_titles = tmp_titles;
        menu->functions = func_tmp;

        return;
    }

    menu->actions_titles[menu->current_size] = title;
    menu->functions[menu->current_size] = func;
    menu->current_size++;
}

void DisplayMenu(Menu_Template* menu)
{
    printf("_____   __            _______________           \n");
    printf("___  | / /_____       ___  ____/__  /____  __       \n");
    printf("__   |/ /_  __ \\________  /_   __  /__  / / /       \n");
    printf("_  /|  / / /_/ //_____/  __/   _  / _  /_/ /        \n");
    printf("/_/ |_/  \\____/       /_/      /_/  _\\__, /         \n");
    printf("                                    /____/          \n");

    // printf("____ ____ ____ ____ _ ___  ____ ____    \n"); 
    // printf("|    |  | |__/ |__/ | |  \\ |  | |__/   \n");
    // printf("|___ |__| |  \\ |  \\ | |__/ |__| |  \\ \n");

    printf(
        "\n"
    );

    for(int i = 0; i < menu->current_size; i++)
    {
        printf("%d   - [%s]\n", i, menu->actions_titles[i]);
    }

    char user_input[2];

    WaitForInput(user_input, sizeof(user_input));

    menu->functions[atoi(user_input)]((void*)menu);
}

void Quit()
{
    return; 
}



void menu_free(Menu_Template* menu)
{
    free(menu->functions);
    free(menu->actions_titles);
    free(menu);
}

