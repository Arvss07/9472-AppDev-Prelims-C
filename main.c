#include <stdio.h>
#include <stdlib.h>

#include "LinkedList.h"

int main(void) {

    List list = {NULL, NULL};
    Citizen citizen1 = {"Alice", 1};
    Citizen citizen2 = {"Bob", 2};
    Citizen citizen3 = {"Charlie", 3};
    Citizen citizen4 = {"Charlie", 4};
    Citizen citizen5 = {"Charlie", 5};

    addFirst(&list, citizen1);
    addLast(&list, citizen2);
    addFirst(&list, citizen3);
    addLast(&list, citizen4);
    addFirst(&list, citizen5);

    printf("\nAll Citizen\n");
    printList(&list);

    printf("\nRemoving 2\n");
    removeCitizen(&list, 2);
    printList(&list);

    printf("\nFiltering name Charlie only\n");
    List filteredList = filterByName(&list, "Charlie");
    printList(&filteredList);

    freeList(&filteredList);
    freeList(&list);

    return 0;
}
