#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "menu/menu.h"

int main(void) {

   List list = {NULL, NULL};
   loadCitizensFromCSV(FILENAME, &list);
   welcome(list);

    //printTable(&list);
    //printMainMenu(&list);
    return 0;
}
