#include "citizen/citizen.h"
#include "file/file.h"


int main(void) {

    CitizenList list;
    initCitizenList(&list);

    loadCitizensFromCSV("..\\data.csv", &list);

    displayCitizensNode(&list);

    return 0;
}
