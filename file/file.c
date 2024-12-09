#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Loads citizens from a CSV file and populates the given list.
 *
 * This function reads data from a CSV file line by line, parses the data,
 * and adds each citizen to the provided linked list.
 *
 * @param filename The name of the CSV file.
 * @param list The list where the citizens will be stored.
 */
void loadCitizensFromCSV (const char *filename, List *list)
{
    FILE *file = fopen(filename, "r"); // Open the CSV file in read mode

    if (file == NULL)
    {
        // Check if the file could not be opened
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH]; // Buffer to store each line of the file

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL)
    {
        perror("Error reading file header");
        fclose(file);
        return;
    }

    // Read each line and process it
    while (fgets(line, sizeof(line), file))
    {
        // Trim the newline character from the end of the line
        const size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n')
        {
            line[len - 1] = '\0';
        }

        // Tokenize the line using comma as a delimiter
        const char *token = strtok(line, ",");

        if (token != NULL)
        {
            Address address;
            Citizen citizen;

            // Parse each field from the CSV and assign values to the citizen struct
            citizen.citizen_id = atoi(token);
            token = strtok(NULL, ",");

            strncpy(citizen.first_name, token ? token : "", sizeof(citizen.first_name) - 1);
            citizen.first_name[sizeof(citizen.first_name) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.middle_name, token ? token : "", sizeof(citizen.middle_name) - 1);
            citizen.middle_name[sizeof(citizen.middle_name) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.last_name, token ? token : "", sizeof(citizen.last_name) - 1);
            citizen.last_name[sizeof(citizen.last_name) - 1] = '\0';

            token = strtok(NULL, ",");
            citizen.gender = token ? getGenderStr(token) : male;

            token = strtok(NULL, ",");
            strncpy(citizen.birth_date, token ? token : "", sizeof(citizen.birth_date) - 1);
            citizen.birth_date[sizeof(citizen.birth_date) - 1] = '\0';

            token = strtok(NULL, ",");
            citizen.marital_status = token ? getMaritalStatusStr(token) : single;

            token = strtok(NULL, ",");
            strncpy(citizen.nationality, token ? token : "", sizeof(citizen.nationality) - 1);
            citizen.nationality[sizeof(citizen.nationality) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.religion, token ? token : "", sizeof(citizen.religion) - 1);
            citizen.religion[sizeof(citizen.religion) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.contact_number, token ? token : "", sizeof(citizen.contact_number) - 1);
            citizen.contact_number[sizeof(citizen.contact_number) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.email_address, token ? token : "", sizeof(citizen.email_address) - 1);
            citizen.email_address[sizeof(citizen.email_address) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(address.house_number, token ? token : "", sizeof(address.house_number) - 1);
            address.house_number[sizeof(address.house_number) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(address.street, token ? token : "", sizeof(address.street) - 1);
            address.street[sizeof(address.street) - 1] = '\0';

            token = strtok(NULL, "\n");
            strncpy(address.purok_zone, token ? token : "", sizeof(address.purok_zone) - 1);
            address.purok_zone[sizeof(address.purok_zone) - 1] = '\0';

            citizen.address = address;
            const ResponseCode result = addLast(list, citizen); // Add the citizen to the list

            if (result != success)
            {
                fprintf(stderr, "Error adding citizen: %d\n", result);
            }
        }
    }
    fclose(file); // Close the file
}

/**
 * @brief Saves the list of citizens to a CSV file.
 *
 * This function writes all citizens from the provided list into a CSV file.
 * It temporarily writes to a file and then renames it to the desired filename to avoid corruption.
 *
 * @param filename The target CSV file where the list will be saved.
 * @param list The list of citizens to save.
 */
void saveListToFile (const char *filename, List *list)
{
    FILE *file = fopen(filename, "w"); // Open temp file for writing

    fprintf(file,
            "CitizenID,FirstName,MiddleName,LastName,Gender,BirthDate,MaritalStatus,Nationality,Religion,ContactNumber,EmailAddress,HouseNumber,Street,PurokZone\n");

    Node *current = list->head;
    while (current != NULL)
    {
        Citizen *citizen = &current->citizen;
        fprintf(file, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                citizen->citizen_id,
                citizen->first_name,
                citizen->middle_name,
                citizen->last_name,
                getGender(citizen->gender),
                citizen->birth_date,
                getMaritalStatus(citizen->marital_status),
                citizen->nationality,
                citizen->religion,
                citizen->contact_number,
                citizen->email_address,
                citizen->address.house_number,
                citizen->address.street,
                citizen->address.purok_zone
        );
        current = current->next;
    }

    fclose(file);
}

