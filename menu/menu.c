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

        char searchKeyword[100];
        int searchOption;

        printf("Search by:\n");
        printf("1. FirstName\n");
        printf("2. LastName\n");
        printf("3. MiddleName\n");
        printf("4. Citizen ID\n");
        printf("Enter your choice: ");
        scanf("%d", &searchOption);
        getchar();

        switch (searchOption) {
            case 1:
                printf("Enter the name to search: ");
                fgets(searchKeyword, sizeof(searchKeyword), stdin);
                searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                Citizen *givenName = searchCitizen(list, FirstName, searchKeyword);
                if (givenName) {
                    printf("Citizen found:\n");
                    printCitizen(*givenName);
                } else {
                    printf("There is no citizen named '%s'.\n", searchKeyword);
                }
                break;

            case 2:
                printf("Enter the name to search: ");
                fgets(searchKeyword, sizeof(searchKeyword), stdin);
                searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                Citizen *surname = searchCitizen(list, LastName, searchKeyword);
                if (surname) {
                    printf("Citizen found:\n");
                    printCitizen(*surname);
                } else {
                    printf("There is no citizen named '%s'.\n", searchKeyword);
                }
                break;

            case 3:
                printf("Enter the name to search: ");
            fgets(searchKeyword, sizeof(searchKeyword), stdin);
            searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

            Citizen *middle = searchCitizen(list, MiddleName, searchKeyword);
            if (middle) {
                printf("Citizen found:\n");
                printCitizen(*middle);
            } else {
                printf("There is no citizen named '%s'.\n", searchKeyword);
            }
            break;

            case 4:
                int searchId;
                printf("Enter the ID to search: ");
                scanf("%d", &searchId);
                getchar();

                Citizen *resultId = searchCitizenById(list, searchId);
                if (resultId) {
                    printf("Citizen found:\n");
                    printCitizen(*resultId);
                } else {
                    printf("There is no citizen found with the ID '%d'.\n", searchId);
                }
                break;

            default:
                printf("Invalid choice.");
        }
        break;
    case 3:
        Citizen citizen;
        int citizenId;
        printf("Enter the ID of the citizen to update: ");
        scanf("%d", &citizenId);

        Citizen *existingCitizen = searchCitizenById(list, citizenId);
        if (existingCitizen == NULL) {
            printf("Citizen with ID %d not found.\n", citizenId);
            break;
        }

        printf("updating details for citizen ID %d: ", citizenId);

        printf("Enter first name: ");
        scanf("%s", citizen.firstName);
        printf("Enter Middle Name: ");
        scanf("%s", citizen.middleName);
        printf("Enter last name: ");
        scanf("%s", citizen.lastName);
        printf("Enter gender (0 for Male, 1 for Female, 3 for Others): ");
        int gender;
        scanf("%d", &gender);
        citizen.gender = (Gender)gender;
        printf("Enter birth date (YYYY-MM-DD): ");
        scanf("%s", citizen.birthDate);
        printf("Enter marital status (0 for single, 1 for Married, 2 for Divorced, 3 for Widowed): ");
        int maritalStatus;
        scanf("%d", &maritalStatus);
        citizen.maritalStatus = (MaritalStatus)maritalStatus;
        printf("Enter nationality: ");
        scanf("%s", &citizen.nationality);
        printf("Enter religion: ");
        scanf("%s", &citizen.religion);
        printf("Enter contact number: ");
        scanf("%d", &citizen.contactNumber);
        printf("Enter email address: ");
        scanf("%s", citizen.emailAddress);
        printf("Enter house number: ");
        scanf("%s", citizen.address.houseNumber);
        printf("Enter street: ");
        scanf("%s", citizen.address.street);
        printf("Enter purok/zone: ");
        scanf("%s", citizen.address.purokZone);

        citizen.citizenId = citizenId;

        ResponseCode result = updateCitizen(list, &citizen);
        if (result == Success) {
            printf("Citizen updated successfully.\n");
        } else if (result == NotFound) {
            printf("Citizen not found.\n");
        } else {
            printf("Failed to update details of the citizen.\n");
        }
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
