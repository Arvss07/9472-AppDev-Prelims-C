#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"

int main(void) {

   List list  ={};

    loadCitizensFromCSV("..\\data.csv", &list);
    printList(&list);

    printf("\n\nSorting citizen by first name\n");
    List sorted = sortCitizen(&list);
    printList(&sorted);



    return 0;
}
