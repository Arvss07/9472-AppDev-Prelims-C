#ifndef MENU_H
#define MENU_H

#include "../citizen/citizen.h"
#include "../cmd/terminal_utils.h"
#include "../utils/util.h"

void welcome(List list);
void getStringInput(char *destination, const int size, char *prompt, int isUpdate);
void printMainMenu(List *list);
void subMenu1();
void subMenu2();
#endif