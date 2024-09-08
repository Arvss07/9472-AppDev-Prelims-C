#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void printMainMenu() {
    printf("\nMENU:\n");
    printf("1. Add Citizen\n");
    printf("2. Search\n");
    printf("3. Update\n");
    printf("4. Delete\n");
    printf("5. File Management\n");
    printf("6. Create Brgy. Certificate\n");
    printf("7. Demographics\n");
    printf("8. Exit\n");
 }

void subMenu1() {
    int choice;
    do {
        printf("\nFile Management\n");
        printf("1. Save File\n");
        printf("2. Load File\n");
        printf("3. GO BACK\n");
        printf("Enter your choice: ");

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Invalid Choice\n");
                break;
        }
    } while (choice != 3);
}

void subMenu2() {
    int choice;
    do {
        printf("\nDemographics\n");
        printf("1. Average Age\n");
        printf("2. Total\n");
        printf("3. GO BACK\n");
        printf("Enter your choice: ");

        switch (choice) {
            case 1:
                break;
            case 2:
                break;
            case 3:
                break;
            default:
                printf("Invalid Choice\n");
            break;
        }
    } while (choice != 3);
}
