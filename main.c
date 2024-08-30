#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"


int main(void) {

    CitizenList list;
    initCitizenList(&list);

    loadCitizensFromCSV("..\\data.csv", &list);

    clearTerminal();
    displayCitizensNode(&list);
    pressAnyKeyToContinue();


    return 0;
}
