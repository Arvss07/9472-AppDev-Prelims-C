#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

int main(void) {

    List list = {NULL, NULL};
    Citizen citizen1 = {"Alice", 1};
    Citizen citizen2 = {"Bob", 2};
    Citizen citizen3 = {"Charlie", 3};


    addFirst(&list, citizen1);
    addLast(&list, citizen2);
    addFirst(&list, citizen3);


    printf("\nAll Citizen\n");
    printList(&list);

    printf("\nRemoving 4\n");
    removeCitizen(&list, 4);
    printList(&list);

    printf("\nFiltering name Charlie only\n");
    List filteredList = filterByName(&list, "Charlie");
    printList(&filteredList);

    printf("\nSorted by name\n");
    List sortedList = sortCitizen(&list);
    printList(&sortedList);


    printf("\nAll Citizen\n");
    printList(&list);

    freeList(&sortedList);
    freeList(&filteredList);
    freeList(&list);

    return 0;
}
