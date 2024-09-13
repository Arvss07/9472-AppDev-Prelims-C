#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "menu/menu.h"

int main(void) {
    // gcc command: gcc -o a main.c citizen/citizen.c citizen/citizen.h file/file.c file/file.h cmd/terminal_utils.c cmd/terminal_utils.h menu/menu.c menu/menu.h utils/util.c utils/util.h
   List list = {NULL, NULL};
   loadCitizensFromCSV(FILENAME, &list);
   welcome(list);

    //printTable(&list);
    //printMainMenu(&list);
    return 0;
}
