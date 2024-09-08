#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../citizen/citizen.h"
#include "../file/file.h"

void welcome() {
    printf("Welcome to <name> Application\n");
    List list = {NULL, NULL};
    loadCitizensFromCSV("..\\data.csv", &list);

    printTable(&list);
}


void printMainMenu(List *list) {
    int choice;
    printf("\nMENU:\n");
    printf("1. Add Citizen\n");
    printf("2. Search\n");
    printf("3. Update\n");
    printf("4. Delete\n");
    printf("5. File Management\n");
    printf("6. Create Brgy. Certificate\n");
    printf("7. Demographics\n");
    printf("8. Exit\n");
    printf("Enter your choice: ");

    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("\n You are now adding a citizen");

            char firstName[100];
            printf("\nWhat is the citizen's first name?: ");
            scanf("%s", &firstName);

            char middleName[100];
            printf("\nWhat is the citizen's middle name?: ");
            scanf("%s", &middleName);

            char lastName[100];
            printf("\nWhat is the citizen's last name?: ");
            scanf("%s", &lastName);

            char citizenGender[100];
            printf("\nWhat is the citizen's gender? <MALE, FEMALE, OTHERS>: ");
            scanf("%s", &citizenGender);
            Gender gender;
            strcpy(gender, citizenGender);

            char birthDate[];
            printf("\nWhat is the citizen's birth date?: ");
            scanf("%s", &birthDate);

            char citizenMaritalStatus [100];
            printf("\nWhat is the citizen's marital status? <SINGLE, MARRIED, DIVORCED, WIDOWED>: ");
            scanf("%s", &citizenMaritalStatus);
            MaritalStatus maritalStatus;
            strcpy(maritalStatus, citizenMaritalStatus);

            char nationality[];
            printf("\nWhat is the citizen's nationality?: ");
            scanf("%s", &nationality);

            char religion[];
            printf("\nWhat is the citizen's religion?: ");
            scanf("%s", &religion);

            char contactNumber[];
            printf("\nWhat is the citizen's contact number?: ");
            scanf("%s", &contactNumber);

            char emailAddress[];
            printf("\nWhat is the citizen's email address?: ");
            scanf("%s", &emailAddress);

            char houseNumber[];
            printf("\nWhat is the citizen's house number?: ");
            scanf("%s", &houseNumber);

            char street[];
            printf("\nWhat is the citizen's street?: ");
            scanf("%s", &street);

            char purokZone[];
            printf("\nWhat is the citizen's purok zone?: ");
            scanf("%s", &purokZone);

            Address address;
            strcpy(address.houseNumber, houseNumber);
            strcpy(address.street, street);
            strcpy(address.purokZone, purokZone);

            Citizen newCitizen;
            strcpy(newCitizen.firstName, firstName);
            strcpy(newCitizen.middleName, middleName);
            strcpy(newCitizen.lastName, lastName);
            strcpy(newCitizen.gender, citizenGender);
            strcpy(newCitizen.birthDate, birthDate);
            strcpy(newCitizen.maritalStatus, citizenMaritalStatus);
            strcpy(newCitizen.nationality, nationality);
            strcpy(newCitizen.religion, religion);
            strcpy(newCitizen.contactNumber, contactNumber);
            strcpy(newCitizen.emailAddress, emailAddress);
            strcpy(newCitizen.address, address);

            addLast(list, newCitizen);
            char status[10];
            strcpy(status, addLast(list, newCitizen));

            if (status == "Success") {
                printf("\n Citizen successfully added.");
            } else {
                printf("\n Citizen not added. Please try again.");
            }
            break;
        case 2:
            break;
        case 3:
            break;
        case 4:
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            break;
        default: ;
    }
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
