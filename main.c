#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"

int main(void) {

   List list  ={};

    loadCitizensFromCSV("..\\data.csv", &list);
    printList(&list);

    printf("\n\nSorting citizen by last name\n");
    List sortedLastName = sortCitizen(&list, LastName);
    printList(&sortedLastName);

    printf("\n\nSorting citizen by first name\n");
    List sortedFirstName = sortCitizen(&list, FirstName);
    printList(&sortedFirstName);

    return 0;
}
