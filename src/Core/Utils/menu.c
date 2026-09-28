#include "menu.h"

#include "client.h"


Menu_Template *CreateMenuTemplate(int max) {
  Menu_Template *menu = (Menu_Template *)malloc(sizeof(Menu_Template));
  menu->max_size = max;
  menu->current_size = 0;
  menu->actions_titles = (char **)malloc(max * sizeof(char *));
  menu->functions = malloc(max * sizeof(void (*)(void *)));
  return menu;
}

void AddMenuAction(Menu_Template *menu, char *title, void *func) {
  if (menu->current_size >= menu->max_size) {
    menu->max_size++;

    char **tmp_titles =
        (char **)realloc(menu->actions_titles, menu->max_size * sizeof(char *));
    if (!tmp_titles) {
      printf(
          "Erreur : impossible de réallouer de la mémoire pour les titres\n");
      return; // Retourne immédiatement en cas d'erreur
    }

    void (**func_tmp)(void *) =
        realloc(menu->functions, menu->max_size * sizeof(void (*)(void *)));
    if (!func_tmp) {
      // Si la réallocation pour les fonctions échoue, annuler la précédente
      printf("Erreur : impossible de réallouer de la mémoire pour les "
             "fonctions\n");
      // On libère tmp_titles pour éviter une fuite de mémoire
      free(tmp_titles);
      return; // Retourne immédiatement en cas d'erreur
    }

    menu->actions_titles = tmp_titles;
    menu->functions = func_tmp;

    return;
  }

  menu->actions_titles[menu->current_size] = title;
  menu->functions[menu->current_size] = func;
  menu->current_size++;
}

void menu_free(Menu_Template *menu) {
  free(menu->functions);
  free(menu->actions_titles);
  free(menu);
}
