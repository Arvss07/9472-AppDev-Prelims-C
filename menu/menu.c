#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include "../citizen/citizen.h"
#include "menu.h"

#include "../file/file.h"
#include "../utils/util.h"
void welcome(List list) {
    printf("Welcome to <name> Application\n");
    printTable(&list);
}

void getStringInput(char *destination, const int size, char *prompt, int isUpdate)
{
    do {
        printf("%s", prompt);
        fgets(destination, size, stdin);
    }while(isUpdate < 0 && strcmp(destination, "\n") == 0);

    destination[strcspn(destination, "\n")] = 0;
}


void printMainMenu(List *list) {
    int choice;
    do {
        printf("\nMENU:\n");
        printf("1. Add Citizen\n");
        printf("2. Search\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Create Brgy. Certificate\n");
        printf("6. Demographics\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("\n You are now adding a citizen");

                char firstName[100];
                getStringInput(firstName, 100, "\nWhat is the citizen's first name?: ", -1);

                char middleName[100];
                getStringInput(middleName, 100, "\nWhat is the citizen's middle name?: ", -1);

                char lastName[100];
                getStringInput(lastName, 100, "\nWhat is the citizen's last name?: ", -1);

                char citizenGender[100];
                getStringInput(citizenGender, 100, "\nWhat is the citizen's gender? <Male, Female, Others>: ", -1);
                Gender gender = getGenderStr(citizenGender);

                char birthDate[100];
                getStringInput(birthDate, 100, "\nWhat is the citizen's birth date?: ", -1);

                char citizenMaritalStatus [100];
                getStringInput(citizenMaritalStatus, 100, "\nWhat is the citizen's marital status? <Single, Married, Divorced, Widowed>: ", -1);
                MaritalStatus maritalStatus = getMaritalStatusStr(citizenMaritalStatus);

                char nationality[100];
                getStringInput(nationality, 100, "\nWhat is the citizen's nationality?: ", -1);

                char religion[100];
                getStringInput(religion, 100, "\nWhat is the citizen's religion?: ", -1);

                char contactNumber[100];
                getStringInput(contactNumber, 100, "\nWhat is the citizen's contact number?: ", -1);

                char emailAddress[100];
                getStringInput(emailAddress, 100, "\nWhat is the citizen's email address?: ", -1);

                char houseNumber[100];
                getStringInput(houseNumber, 100, "\nWhat is the citizen's house number?: ", -1);

                char street[100];
                getStringInput(street, 100, "\nWhat is the citizen's street?: ", -1);

                char purokZone[100];
                getStringInput(purokZone, 100, "\nWhat is the citizen's purok zone?: ", -1);

                Address address;
                strcpy(address.houseNumber, houseNumber);
                strcpy(address.street, street);
                strcpy(address.purokZone, purokZone);

                Citizen newCitizen;
                strcpy(newCitizen.firstName, firstName);
                strcpy(newCitizen.middleName, middleName);
                strcpy(newCitizen.lastName, lastName);
                newCitizen.gender = gender;
                strcpy(newCitizen.birthDate, birthDate);
                newCitizen.maritalStatus = maritalStatus;
                strcpy(newCitizen.nationality, nationality);
                strcpy(newCitizen.religion, religion);
                strcpy(newCitizen.contactNumber, contactNumber);
                strcpy(newCitizen.emailAddress, emailAddress);
                newCitizen.address = address;

                ResponseCode status = addLast(list, newCitizen);

                if (status == Success) {
                    printf("\n Citizen successfully added.");
                } else {
                    printf("\n Citizen not added. Please try again.");
                }
                break;
            case 2:
                int searchOption;
                do {
                    printf("Search by:\n");
                    printf("1. FirstName\n");
                    printf("2. LastName\n");
                    printf("3. MiddleName\n");
                    printf("4. Citizen ID\n");
                    printf("5. Exit\n");
                    printf("Enter your choice: ");
                    scanf("%d", &searchOption);
                    getchar();

                    if (searchOption == 5) {
                        break;
                    }

                    char searchKeyword[100];
                    Citizen *foundCitizen = NULL;

                    switch (searchOption) {
                        case 1:
                            printf("Enter the name to search: ");
                        fgets(searchKeyword, sizeof(searchKeyword), stdin);
                        searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                        foundCitizen = searchCitizen(list, FirstName, searchKeyword);
                        break;

                        case 2:
                            printf("Enter the name to search: ");
                        fgets(searchKeyword, sizeof(searchKeyword), stdin);
                        searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                        foundCitizen = searchCitizen(list, LastName, searchKeyword);
                        break;

                        case 3:
                            printf("Enter the name to search: ");
                        fgets(searchKeyword, sizeof(searchKeyword), stdin);
                        searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                        foundCitizen = searchCitizen(list, MiddleName, searchKeyword);
                        break;

                        case 4:
                            int searchId;
                        printf("Enter the ID to search: ");
                        scanf("%d", &searchId);
                        getchar();

                        foundCitizen = searchCitizenById(list, searchId);
                        break;

                        default:
                            printf("Invalid choice. Please enter a number between 1 and 5.\n");
                        continue;
                    }

                    if (foundCitizen) {
                        printf("Citizen found.\n");
                        printCitizen(*foundCitizen);
                    } else {
                        printf("Citizen not found.\n");
                    }
                } while (searchOption != 5);  // Continue looping until the user chooses to exit
                break;
            case 3:
                Citizen citizen;
                int citizenId;

                getStringInput(citizenId, sizeof(citizenId), "Enter the ID of the citizen to update: ", 1);


                Citizen *existingCitizen = searchCitizenById(list, citizenId);
                if (existingCitizen == NULL) {
                    printf("Citizen with ID %d not found.\n", citizenId);
                    break;
                }

                printf("updating details for citizen ID %d:\n", citizenId);

                getStringInput(citizen.firstName, sizeof(citizen.firstName), "Enter first name: ", 1);
                getStringInput(citizen.middleName, sizeof(citizen.middleName), "Enter middle name: ", 1);
                getStringInput(citizen.lastName, sizeof(citizen.lastName), "Enter last name: ", 1);
                char genderUpdate[100];
                getStringInput(genderUpdate, sizeof(genderUpdate), "Enter your gender (Male, Female, Others): ", 1);
                citizen.gender = getGenderStr(genderUpdate);
                getStringInput(citizen.birthDate, sizeof(citizen.birthDate), "Enter birth date (YYYY-MM-DD): ", 1);
                char maritalStatusUpdate[100];
                getStringInput(maritalStatusUpdate, sizeof(citizen.maritalStatus), "Enter marital status (Single, Married, Divorced, Widowed): ", 1);
                citizen.maritalStatus = getMaritalStatusStr(maritalStatusUpdate);
                getStringInput(citizen.nationality, sizeof(citizen.nationality), "Enter nationality: ", 1);
                getStringInput(citizen.religion, sizeof(citizen.religion), "Enter religion: ", 1);
                getStringInput(citizen.contactNumber, sizeof(citizen.contactNumber), "Enter contact number: ", 1);
                getStringInput(citizen.emailAddress, sizeof(citizen.emailAddress), "Enter email address: ", 1);
                getStringInput(citizen.address.houseNumber, sizeof(citizen.address.houseNumber), "Enter house number: ", 1);
                getStringInput(citizen.address.street, sizeof(citizen.address.street), "Enter street: ", 1);
                getStringInput(citizen.address.purokZone, sizeof(citizen.address.purokZone), "Enter purok/zone: ", 1);

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
                int citizenID;
                char confirm;
                printf("Enter the ID of the citizen you want to delete: ");
                scanf("%d", &citizenID);

                while (getchar() != '\n');

                printf("Are you sure you want to delete citizen %d? (y/n): ", citizenID);
                scanf("%c", &confirm);

                if (confirm == 'y' || confirm == 'Y') {
                    const ResponseCode deleteResult = removeCitizen(list, citizenID);
                    if (deleteResult == Success) {
                        printf("Citizen with  the ID %d has deleted successfully.", citizenID);
                    } else if (deleteResult == Failed) {
                        printf("Failed to delete citizen %d", citizenID);
                    }
                } else {
                    printf("Deletion of Citizen %d has been cancelled.\n", citizenID);
                }
                break;
            case 5:
                printf("Creating barangay certificate for a citizen.");
            int citizenIdToPrint;
            Citizen *citizenToPrint = NULL;
            do {
                printf("Enter the ID of the citizen to print the Brgy. Certificate: ");
                scanf("%d", &citizenIdToPrint);
                citizenToPrint = searchCitizenById(list, citizenIdToPrint);
                if (citizenToPrint == NULL) {
                    printf("Citizen with ID %d not found.\n", citizenIdToPrint);
                }
            }while (citizenToPrint == NULL);
            createAndSaveCitizenCert(list, citizenToPrint);
            break;
                break;
            case 6:
                subMenu1();
                break;
            case 7:
                printf("Thank you for using the application");
                break;
            default:
                printf("Invalid choice. Please enter a number between 1 and 8\n");
        }
    } while (choice != 8);
}

void subMenu1() {
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
