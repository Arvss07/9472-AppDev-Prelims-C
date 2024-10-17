#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"


int main(void) {
    // gcc command: gcc -o a main.c citizen/citizen.c citizen/citizen.h file/file.c file/file.h cmd/terminal_utils.c cmd/terminal_utils.h menu/menu.c menu/menu.h utils/util.c utils/util.h
    List list = {NULL, NULL};
    loadCitizensFromCSV(FILENAME, &list);

    int play = 1;
    while(play == 1) {

        printf("\nEnter 1 to show demographics : ");
        scanf(" %d", &play);

        if(play == 1) {
            viewDemographics(&list);
        }

        printf("\n\n");

    }

    return 0;
}


