#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"
#include "sorting/sort.h"


int main(void) {

    CitizenList list;
    initCitizenList(&list);

    loadCitizensFromCSV("..\\data.csv", &list);

    clearTerminal();
    printf("Unsorted list of citizens:\n");
    displayCitizenName(&list);
    pressAnyKeyToContinue();

    sortCitizens(&list, "firstName");

    printf("Sorted list of citizens:\n");
    displayCitizenName(&list);
    pressAnyKeyToContinue();


    return 0;
}
