#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../citizen/citizen.h"
#include "menu.h"
#include "../utils/util.h"
void welcome(List list) {
    printf("Welcome to <name> Application\n");
    printTable(&list);
}

void getStringInput(char *destination, const int size, char *prompt)
{
    printf("%s", prompt);
    fgets(destination, size, stdin);
    destination[strcspn(destination, "\n")] = 0;
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
        getStringInput(firstName, 100, "\nWhat is the citizen's first name?: ");

        char middleName[100];
        getStringInput(middleName, 100, "\nWhat is the citizen's middle name?: ");

        char lastName[100];
        getStringInput(lastName, 100, "\nWhat is the citizen's last name?: ");

        char citizenGender[100];
        getStringInput(citizenGender, 100, "\nWhat is the citizen's gender? <Male, Female, Others>: ");
        Gender gender = stringToGender(citizenGender);

        char birthDate[100];
        getStringInput(birthDate, 100, "\nWhat is the citizen's birth date?: ");

        char citizenMaritalStatus [100];
        getStringInput(citizenMaritalStatus, 100, "\nWhat is the citizen's marital status? <Single, Married, Divorced, Widowed>: ");
        MaritalStatus maritalStatus = stringToMaritalStatus(citizenMaritalStatus);

        char nationality[100];
        getStringInput(nationality, 100, "\nWhat is the citizen's nationality?: ");

        char religion[100];
        getStringInput(religion, 100, "\nWhat is the citizen's religion?: ");

        char contactNumber[100];
        getStringInput(contactNumber, 100, "\nWhat is the citizen's contact number?: ");

        char emailAddress[100];
        getStringInput(emailAddress, 100, "\nWhat is the citizen's email address?: ");

        char houseNumber[100];
        getStringInput(houseNumber, 100, "\nWhat is the citizen's house number?: ");

        char street[100];
        getStringInput(street, 100, "\nWhat is the citizen's street?: ");

        char purokZone[100];
        getStringInput(purokZone, 100, "\nWhat is the citizen's purok zone?: ");

        Address address;
        strcpy(address.houseNumber, houseNumber);
        strcpy(address.street, street);
        strcpy(address.purokZone, purokZone);

        Citizen newCitizen;
        strcpy(newCitizen.firstName, firstName);
        strcpy(newCitizen.middleName, middleName);
        strcpy(newCitizen.lastName, lastName);
        strcpy(newCitizen.gender, gender);
        strcpy(newCitizen.birthDate, birthDate);
        strcpy(newCitizen.maritalStatus, maritalStatus);
        strcpy(newCitizen.nationality, nationality);
        strcpy(newCitizen.religion, religion);
        strcpy(newCitizen.contactNumber, contactNumber);
        strcpy(newCitizen.emailAddress, emailAddress);
        strcpy(newCitizen.address, address);

        addLast(list, newCitizen);
        ResponseCode status = addLast(list, newCitizen);

        // if (status == "Success") {
        //     printf("\n Citizen successfully added.");
        // } else {
        //     printf("\n Citizen not added. Please try again.");
        // }
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
