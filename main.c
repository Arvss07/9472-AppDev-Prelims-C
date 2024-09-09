#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"
#include "menu/menu.h"

int main(void) {

   List list = {NULL, NULL};
    loadCitizensFromCSV("..\\data.csv", &list);

    // print the oldest citizen
    Citizen oldest = getOldestCitizen(&list);
    printCitizen(oldest);
    printf("Age: %d\n", getCitizenAge(&list, oldest.citizenId));

    //printTable(&list);
    //printMainMenu(&list);

    pressAnyKeyToContinue();

    return 0;
}
