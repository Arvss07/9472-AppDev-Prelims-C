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
 * @param is_update If it's an update (non-zero), allows blank input; otherwise, requires non-empty input.
 */
void getStringInput(char *destination, const int size, char *prompt, int is_update)
{
    do
    {
        printf("%s", prompt);
        fgets(destination, size, stdin);                      // Get input from the user
    } while (is_update < 0 && strcmp(destination, "\n") == 0); // Repeat if input is empty and it's not an update

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

            char first_name[100];
            getStringInput(first_name, 100, "\nWhat is the citizen's first name?: ", -1);

            char middle_name[100];
            getStringInput(middle_name, 100, "\nWhat is the citizen's middle name?: ", -1);

            char last_name[100];
            getStringInput(last_name, 100, "\nWhat is the citizen's last name?: ", -1);

            char citizen_gender[100];
            getStringInput(citizen_gender, 100, "\nWhat is the citizen's gender? <Male, Female, Others>: ", -1);
            Gender gender = getGenderStr(citizen_gender);

            char birth_date[100];
            getStringInput(birth_date, 100, "\nWhat is the citizen's birth date?: ", -1);

            char citizen_marital_status[100];
            getStringInput(citizen_marital_status, 100,
                           "\nWhat is the citizen's marital status? <Single, Married, Divorced, Widowed>: ", -1);
            MaritalStatus marital_status = getMaritalStatusStr(citizen_marital_status);

            char nationality[100];
            getStringInput(nationality, 100, "\nWhat is the citizen's nationality?: ", -1);

            char religion[100];
            getStringInput(religion, 100, "\nWhat is the citizen's religion?: ", -1);

            char contact_number[100];
            getStringInput(contact_number, 100, "\nWhat is the citizen's contact number?: ", -1);

            char email_address[100];
            getStringInput(email_address, 100, "\nWhat is the citizen's email address?: ", -1);

            char house_number[100];
            getStringInput(house_number, 100, "\nWhat is the citizen's house number?: ", -1);

            char street[100];
            getStringInput(street, 100, "\nWhat is the citizen's street?: ", -1);

            char purok_zone[100];
            getStringInput(purok_zone, 100, "\nWhat is the citizen's purok zone?: ", -1);

            // Create and populate the citizen struct
            Address address;
            strcpy(address.house_number, house_number);
            strcpy(address.street, street);
            strcpy(address.purok_zone, purok_zone);

            Citizen new_citizen = {};
            new_citizen.citizen_id = list->tail->citizen.citizen_id + 1 + counter;
            strcpy(new_citizen.first_name, first_name);
            strcpy(new_citizen.middle_name, middle_name);
            strcpy(new_citizen.last_name, last_name);
            new_citizen.gender = gender;
            strcpy(new_citizen.birth_date, birth_date);
            new_citizen.marital_status = marital_status;
            strcpy(new_citizen.nationality, nationality);
            strcpy(new_citizen.religion, religion);
            strcpy(new_citizen.contact_number, contact_number);
            strcpy(new_citizen.email_address, email_address);
            new_citizen.address = address;

            ResponseCode status = addLast(list, new_citizen); // Add citizen to the list

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
            int search_option, search_id;

            printf("Search by:\n");
            printf("1. FirstName\n");
            printf("2. LastName\n");
            printf("3. MiddleName\n");
            printf("4. Citizen ID\n");
            printf("Enter your choice: ");
            scanf("%d", &search_option);
            getchar();

            char search_keyword[100];
            Citizen *found_citizen = NULL;

            switch (search_option)
            {
            case 1:
            {
                printf("Enter the name to search: ");
                fgets(search_keyword, sizeof(search_keyword), stdin);
                search_keyword[strcspn(search_keyword, "\n")] = '\0';

                found_citizen = searchCitizen(list, first_name, search_keyword);
                break;
            }
            case 2:
            {
                printf("Enter the name to search: ");
                fgets(search_keyword, sizeof(search_keyword), stdin);
                search_keyword[strcspn(search_keyword, "\n")] = '\0';

                found_citizen = searchCitizen(list, last_name, search_keyword);
                break;
            }
            case 3:
            {
                printf("Enter the name to search: ");
                fgets(search_keyword, sizeof(search_keyword), stdin);
                search_keyword[strcspn(search_keyword, "\n")] = '\0';
                found_citizen = searchCitizen(list, middle_name, search_keyword);
                break;
            }

            case 4:
            {
                printf("Enter the ID to search: ");
                scanf("%d", &search_id);
                getchar();
                found_citizen = searchCitizenById(list, search_id);
                break;
            }
            default:
                printf("Invalid choice. Please enter a number between 1 and 5.\n");
            }

            if (found_citizen)
            {
                printf("Citizen found.\n");
                printCitizen(*found_citizen); // Print details of the found citizen
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
            int citizen_id = atoi(uid);
            Citizen *existing_citizen = searchCitizenById(list, citizen_id);
            if (existing_citizen == NULL)
            {
                printf("Citizen with ID %d not found.\n", citizen_id);
                break;
            }

            // update citizen details
            printf("updating details for citizen ID %d:\n", citizen_id);

            getStringInput(citizen.first_name, sizeof(citizen.first_name), "Enter first name: ", 1);
            getStringInput(citizen.middle_name, sizeof(citizen.middle_name), "Enter middle name: ", 1);
            getStringInput(citizen.last_name, sizeof(citizen.last_name), "Enter last name: ", 1);
            char gender_update[100];
            getStringInput(gender_update, sizeof(gender_update), "Enter your gender (Male, Female, Others): ", 1);
            citizen.gender = getGenderStr(gender_update);
            getStringInput(citizen.birth_date, sizeof(citizen.birth_date), "Enter birth date (YYYY-MM-DD): ", 1);
            char marital_status_update[100];
            getStringInput(marital_status_update, sizeof(citizen.marital_status),
                           "Enter marital status (Single, Married, Divorced, Widowed): ", 1);
            citizen.marital_status = getMaritalStatusStr(marital_status_update);
            getStringInput(citizen.nationality, sizeof(citizen.nationality), "Enter nationality: ", 1);
            getStringInput(citizen.religion, sizeof(citizen.religion), "Enter religion: ", 1);
            getStringInput(citizen.contact_number, sizeof(citizen.contact_number), "Enter contact number: ", 1);
            getStringInput(citizen.email_address, sizeof(citizen.email_address), "Enter email address: ", 1);
            getStringInput(citizen.address.house_number, sizeof(citizen.address.house_number), "Enter house number: ",
                           1);
            getStringInput(citizen.address.street, sizeof(citizen.address.street), "Enter street: ", 1);
            getStringInput(citizen.address.purok_zone, sizeof(citizen.address.purok_zone), "Enter purok/zone: ", 1);

            citizen.citizen_id = citizen_id;

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
            int citizen_id;
            char confirm;

            // Prompt for the citizen ID to delete.
            printf("Enter the ID of the citizen you want to delete: ");
            scanf("%d", &citizen_id);

            // Clear the input buffer to avoid issues with further inputs.
            while (getchar() != '\n')
                ;

            // Confirm deletion from the user.
            printf("Are you sure you want to delete citizen %d? (y/n): ", citizen_id);
            scanf("%c", &confirm);

            // If user confirms, attempt to delete the citizen.
            if (confirm == 'y' || confirm == 'Y')
            {
                const ResponseCode delete_result = removeCitizen(list, citizen_id); // Attempt to remove the citizen.

                // Check if the deletion was successful.
                if (delete_result == success)
                {
                    saveListToFile(FILENAME, list); // Save changes to file.
                    printf("Citizen with the ID %d has been deleted successfully.\n", citizen_id);
                }
                else if (delete_result == failed)
                {
                    printf("Failed to delete citizen with ID %d.\n", citizen_id); // If deletion fails, notify the user.
                }
            }
            else
            {
                // If user cancels the deletion.
                printf("Deletion of Citizen %d has been cancelled.\n", citizen_id);
            }
            pressAnyKeyToContinue(); // Wait for user input before continuing.
            break;
        }

        case 5:
        {
            // Display the demographic's submenu.
            printf("Demographics\n");
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
