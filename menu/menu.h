#ifndef MENU_H
#define MENU_H

#include "../citizen/citizen.h"
#include "../cmd/terminal_utils.h"

void welcome();
void getStringInput(char *destination, const int size, char *prompt);
void printMainMenu(List *list);
void subMenu1();
void subMenu2();
#endif