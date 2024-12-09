#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "../citizen/citizen.h"
#include "menu.h"
#include "../file/file.h"

/**
 * @brief Welcomes the user to the application and displays the initial table and main menu.
 *
 * @param list The list of citizens to be displayed in the table.
 */
void welcome(List list)
{
    printf("Barangay Management Information System\n");
    printTable(&list);    // Display the list of citizens in a table format
    printMainMenu(&list); // Display the main menu
    printf("\n\n\n\n\n");
}

/**
 * @brief Gets user input as a string and stores it in the destination array.
 *
 * @param destination The array where the user input will be stored.
 * @param size The maximum size of the input string.
 * @param prompt The prompt message to be displayed to the user.
 * @param isUpdate If it's an update (non-zero), allows blank input; otherwise, requires non-empty input.
 */
void getStringInput(char *destination, const int size, char *prompt, int isUpdate)
{
    do
    {
        printf("%s", prompt);
        fgets(destination, size, stdin);                      // Get input from the user
    } while (isUpdate < 0 && strcmp(destination, "\n") == 0); // Repeat if input is empty and it's not an update

    destination[strcspn(destination, "\n")] = 0; // Remove the trailing newline character.
}

/**
 * @brief Displays the main menu and handles user choices for different actions.
 *
 * @param list Pointer to the list of citizens to be managed by the application.
 */
void printMainMenu(List *list)
{
    int choice;

    do
    {
        // Display the menu options.
        printf("\nMENU:\n");
        printf("1. Add Citizen\n");
        printf("2. Search\n");
        printf("3. Update\n");
        printf("4. Delete\n");
        printf("5. Demographics\n");
        printf("6. Display Citizens\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);
        getchar(); // Consume the leftover newling character from scanf.
        switch (choice)
        {
            case 1:
            {
                // Add new citizen
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

                char citizenMaritalStatus[100];
                getStringInput(citizenMaritalStatus, 100,
                               "\nWhat is the citizen's marital status? <Single, Married, Divorced, Widowed>: ", -1);
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

                // Create and populate the citizen struct
                Address address;
                strcpy(address.house_number, houseNumber);
                strcpy(address.street, street);
                strcpy(address.purok_zone, purokZone);

                Citizen newCitizen = {};
                newCitizen.citizen_id = list->tail->citizen.citizen_id + 1 + counter;
                strcpy(newCitizen.first_name, firstName);
                strcpy(newCitizen.middle_name, middleName);
                strcpy(newCitizen.last_name, lastName);
                newCitizen.gender = gender;
                strcpy(newCitizen.birth_date, birthDate);
                newCitizen.marital_status = maritalStatus;
                strcpy(newCitizen.nationality, nationality);
                strcpy(newCitizen.religion, religion);
                strcpy(newCitizen.contact_number, contactNumber);
                strcpy(newCitizen.email_address, emailAddress);
                newCitizen.address = address;

                ResponseCode status = addLast(list, newCitizen); // Add citizen to the list

                if (status == success)
                {
                    printf("\n Citizen successfully added.");
                    saveListToFile(FILENAME, list);
                    pressAnyKeyToContinue();
                }
                else
                {
                    printf("\n Citizen not added. Please try again.");
                }
                pressAnyKeyToContinue();
                break;
            }
            case 2:
            {
                // search for a citizen based on different criteria
                int searchOption, searchId;

                printf("Search by:\n");
                printf("1. FirstName\n");
                printf("2. LastName\n");
                printf("3. MiddleName\n");
                printf("4. Citizen ID\n");
                printf("Enter your choice: ");
                scanf("%d", &searchOption);
                getchar();

                char searchKeyword[100];
                Citizen *foundCitizen = NULL;

                switch (searchOption)
                {
                    case 1:
                    {
                        printf("Enter the name to search: ");
                        fgets(searchKeyword, sizeof(searchKeyword), stdin);
                        searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                        foundCitizen = searchCitizen(list, first_name, searchKeyword);
                        break;
                    }
                    case 2:
                    {
                        printf("Enter the name to search: ");
                        fgets(searchKeyword, sizeof(searchKeyword), stdin);
                        searchKeyword[strcspn(searchKeyword, "\n")] = '\0';

                        foundCitizen = searchCitizen(list, last_name, searchKeyword);
                        break;
                    }
                    case 3:
                    {
                        printf("Enter the name to search: ");
                        fgets(searchKeyword, sizeof(searchKeyword), stdin);
                        searchKeyword[strcspn(searchKeyword, "\n")] = '\0';
                        foundCitizen = searchCitizen(list, middle_name, searchKeyword);
                        break;
                    }

                    case 4:
                    {
                        printf("Enter the ID to search: ");
                        scanf("%d", &searchId);
                        getchar();
                        foundCitizen = searchCitizenById(list, searchId);
                        break;
                    }
                    default:
                        printf("Invalid choice. Please enter a number between 1 and 5.\n");
                }

                if (foundCitizen)
                {
                    printf("Citizen found.\n");
                    printCitizen(*foundCitizen); // Print details of the found citizen
                }
                else
                {
                    printf("Citizen not found.\n");
                }
                pressAnyKeyToContinue();
                break;
            }
            case 3:
            {
                // Update the citizen details base on their ID.
                Citizen citizen;
                char uid[100];
                getStringInput(uid, sizeof(uid), "Enter the ID of the citizen to update: ", 1);
                int citizenId = atoi(uid);
                Citizen *existingCitizen = searchCitizenById(list, citizenId);
                if (existingCitizen == NULL)
                {
                    printf("Citizen with ID %d not found.\n", citizenId);
                    break;
                }

                // update citizen details
                printf("updating details for citizen ID %d:\n", citizenId);

                getStringInput(citizen.first_name, sizeof(citizen.first_name), "Enter first name: ", 1);
                getStringInput(citizen.middle_name, sizeof(citizen.middle_name), "Enter middle name: ", 1);
                getStringInput(citizen.last_name, sizeof(citizen.last_name), "Enter last name: ", 1);
                char genderUpdate[100];
                getStringInput(genderUpdate, sizeof(genderUpdate), "Enter your gender (Male, Female, Others): ", 1);
                citizen.gender = getGenderStr(genderUpdate);
                getStringInput(citizen.birth_date, sizeof(citizen.birth_date), "Enter birth date (YYYY-MM-DD): ", 1);
                char maritalStatusUpdate[100];
                getStringInput(maritalStatusUpdate, sizeof(citizen.marital_status),
                               "Enter marital status (Single, Married, Divorced, Widowed): ", 1);
                citizen.marital_status = getMaritalStatusStr(maritalStatusUpdate);
                getStringInput(citizen.nationality, sizeof(citizen.nationality), "Enter nationality: ", 1);
                getStringInput(citizen.religion, sizeof(citizen.religion), "Enter religion: ", 1);
                getStringInput(citizen.contact_number, sizeof(citizen.contact_number), "Enter contact number: ", 1);
                getStringInput(citizen.email_address, sizeof(citizen.email_address), "Enter email address: ", 1);
                getStringInput(citizen.address.house_number, sizeof(citizen.address.house_number), "Enter house number: ",
                               1);
                getStringInput(citizen.address.street, sizeof(citizen.address.street), "Enter street: ", 1);
                getStringInput(citizen.address.purok_zone, sizeof(citizen.address.purok_zone), "Enter purok/zone: ", 1);

                citizen.citizen_id = citizenId;

                // Save the updated details back to the citizen list
                ResponseCode result = updateCitizen(list, &citizen);
                if (result == success)
                {
                    saveListToFile(FILENAME, list);
                    printf("Citizen updated successfully.\n");
                    printCitizen(citizen);
                    pressAnyKeyToContinue();
                }
                else if (result == not_found)
                {
                    printf("Citizen not found.\n");
                }
                else
                {
                    printf("Failed to update details of the citizen.\n");
                }
                pressAnyKeyToContinue();
                break;
            }
            case 4:
            {
                // Delete a citizen based on their ID.
                int citizenID;
                char confirm;

                // Prompt for the citizen ID to delete.
                printf("Enter the ID of the citizen you want to delete: ");
                scanf("%d", &citizenID);

                // Clear the input buffer to avoid issues with further inputs.
                while (getchar() != '\n')
                    ;

                // Confirm deletion from the user.
                printf("Are you sure you want to delete citizen %d? (y/n): ", citizenID);
                scanf("%c", &confirm);

                // If user confirms, attempt to delete the citizen.
                if (confirm == 'y' || confirm == 'Y')
                {
                    const ResponseCode deleteResult = removeCitizen(list, citizenID); // Attempt to remove the citizen.

                    // Check if the deletion was successful.
                    if (deleteResult == success)
                    {
                        saveListToFile(FILENAME, list); // Save changes to file.
                        printf("Citizen with the ID %d has been deleted successfully.\n", citizenID);
                    }
                    else if (deleteResult == failed)
                    {
                        printf("Failed to delete citizen with ID %d.\n", citizenID); // If deletion fails, notify the user.
                    }
                }
                else
                {
                    // If user cancels the deletion.
                    printf("Deletion of Citizen %d has been cancelled.\n", citizenID);
                }
                pressAnyKeyToContinue(); // Wait for user input before continuing.
                break;
            }

            case 5:
            {
                // Display the demographic's submenu.
                subMenu1(list);
                break;
            }
            case 6:
            {
                // Display the list of citizens in a table format.
                printTable(list);
                break;
            }
            case 7:
            {
                // Exit the application.
                printf("Thank you for using the application");
                break;
            }
            default:
                printf("Invalid choice. Please enter a number between 1 and 8\n"); // Handle invalid menu choices.
        }
    } while (choice != 7);
}

/*
 * @param list A pointer to the list of citizens.
 */
void subMenu1(List *list)
{
    int choice;         // Variable to store the user's menu choice
    char continue_choice; // Variable to determine if the user wants to continue
    do
    {
        // Display the submenu options
        printf("\nDemographics\n");
        printf("1. View Demographics\n");
        printf("2. Get Citizen Age\n");
        printf("3. Go Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar(); // Consume the newline character left by scanf
        // Handle the user's menu choice
        switch (choice)
        {
            case 1:
            {
                // View demographics of the citizens
                viewDemographics(list);
                pressAnyKeyToContinue(); // Wait for user to press a key before continuing
                break;
            }
            case 2:
            {
                // Loop to handle checking multiple citizens' ages
                do
                {
                    int citizen_id;
                    // Prompt for the citizen's ID
                    printf("Enter Citizen ID: ");
                    scanf("%d", &citizen_id);
                    getchar(); // Consume newline character
                    // Get the age of the citizen
                    int age = getCitizenAge(list, citizen_id);
                    Citizen *citizen = searchCitizenById(list, citizen_id);
                    // Check if the citizen exists and display the result
                    if (citizen != NULL && age != -1)
                    {
                        printf("Citizen %s %s %s is %d years old.\n", citizen->first_name, citizen->middle_name, citizen->last_name, age);
                    }
                    else
                    {
                        printf("Citizen ID %d not found.\n", citizen_id);
                    }
                    // Ask if the user wants to check another citizen's age
                    printf("Do you want to know the age of another citizen (y/n)? ");
                    scanf("%c", &continue_choice);
                    getchar(); // Consume newline character
                } while (tolower(continue_choice) == 'y'); // Continue if user inputs 'y'
                break;
            }
            case 3:
            {
                // Option to go back to the main menu
                printf("Going back to the main menu...\n");
                break;
            }
            default:
                // Invalid input
                printf("Invalid Choice\n");
        }
    } while (choice != 3); // Continue the submenu until the user selects option 3
}

