#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"

int main(void) {

   List list = {NULL, NULL};

    loadCitizensFromCSV("..\\data.csv", &list);

   Citizen *c = searchCitizenById(&list, 1009);
   Citizen *b = searchCitizen(&list, FirstName, "Gio");
    Citizen *d = searchCitizen(&list, LastName, "Le");
    Citizen *e = searchCitizen(&list, MiddleName, "M");
    Citizen *f = searchCitizen(&list, Barangay, "B");



    if(c != NULL) {
        printCitizen(*c);

    }

    if(b != NULL) {
        printCitizen(*b);
    }



    pressAnyKeyToContinue();

    return 0;
}
