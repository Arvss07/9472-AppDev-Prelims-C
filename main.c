#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"
#include "menu/menu.h"

int main(void) {

   List list = {NULL, NULL};
    loadCitizensFromCSV(FILENAME, &list);

    // print the oldest citizen
    welcome(list);

    //printTable(&list);
    //printMainMenu(&list);
    return 0;
}
