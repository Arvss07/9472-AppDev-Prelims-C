// terminal_utils.c
#include "terminal_utils.h"
#include <stdio.h>
#include <stdlib.h>

void clearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pressAnyKeyToContinue() {
    printf("Press ANY key to continue...");
    getchar();
    clearTerminal();
}