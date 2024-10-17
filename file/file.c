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
void loadCitizensFromCSV(const char *filename, List *list) {
    FILE *file = fopen(filename, "r"); // Open the CSV file in read mode

    if (file == NULL) { // Check if the file could not be opened
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH]; // Buffer to store each line of the file


    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        perror("Error reading file header");
        fclose(file);
        return;
    }

    // Read each line and process it
    while (fgets(line, sizeof(line), file)) {
        // Trim the newline character from the end of the line
        const size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        // Tokenize the line using comma as a delimiter
        const char *token = strtok(line, ",");

        if (token != NULL) {

            Address address;
            Citizen citizen;

            // Parse each field from the CSV and assign values to the citizen struct
            citizen.citizenId = atoi(token);
            token = strtok(NULL, ",");

            strncpy(citizen.firstName, token ? token : "", sizeof(citizen.firstName) - 1);
            citizen.firstName[sizeof(citizen.firstName) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.middleName, token ? token : "", sizeof(citizen.middleName) - 1);
            citizen.middleName[sizeof(citizen.middleName) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.lastName, token ? token : "", sizeof(citizen.lastName) - 1);
            citizen.lastName[sizeof(citizen.lastName) - 1] = '\0';

            token = strtok(NULL, ",");
            citizen.gender = token ? getGenderStr(token) : MALE;

            token = strtok(NULL, ",");
            strncpy(citizen.birthDate, token ? token : "", sizeof(citizen.birthDate) - 1);
            citizen.birthDate[sizeof(citizen.birthDate) - 1] = '\0';

            token = strtok(NULL, ",");
            citizen.maritalStatus = token ? getMaritalStatusStr(token) : SINGLE;

            token = strtok(NULL, ",");
            strncpy(citizen.nationality, token ? token : "", sizeof(citizen.nationality) - 1);
            citizen.nationality[sizeof(citizen.nationality) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.religion, token ? token : "", sizeof(citizen.religion) - 1);
            citizen.religion[sizeof(citizen.religion) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.contactNumber, token ? token : "", sizeof(citizen.contactNumber) - 1);
            citizen.contactNumber[sizeof(citizen.contactNumber) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(citizen.emailAddress, token ? token : "", sizeof(citizen.emailAddress) - 1);
            citizen.emailAddress[sizeof(citizen.emailAddress) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(address.houseNumber, token ? token : "", sizeof(address.houseNumber) - 1);
            address.houseNumber[sizeof(address.houseNumber) - 1] = '\0';

            token = strtok(NULL, ",");
            strncpy(address.street, token ? token : "", sizeof(address.street) - 1);
            address.street[sizeof(address.street) - 1] = '\0';

            token = strtok(NULL, "\n");
            strncpy(address.purokZone, token ? token : "", sizeof(address.purokZone) - 1);
            address.purokZone[sizeof(address.purokZone) - 1] = '\0';

            citizen.address = address;
            const ResponseCode result = addLast(list, citizen); // Add the citizen to the list

            if (result != Success) {
                fprintf(stderr, "Error adding citizen: %d\n", result);
            }
        }
    }
    fclose(file);// Close the file
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
void saveListToFile(const char *filename, List *list) {
    FILE *tempFile = fopen(TEMP_FILEPATH, "w"); // Open temp file for writing
    if (tempFile == NULL) {
        fprintf(stderr, "Error: Could not open file temp.csv for writing.\n");
        return;
    }

    // Write header
    fprintf(tempFile,
            "CitizenID,FirstName,MiddleName,LastName,Gender,BirthDate,MaritalStatus,Nationality,Religion,ContactNumber,EmailAddress,HouseNumber,Street,PurokZone\n");

    // Iterate through the list and write each citizen's data
    Node *current = list->head;
    while (current != NULL) {
        Citizen *citizen = &current->citizen;
        fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
                citizen->citizenId,
                citizen->firstName,
                citizen->middleName,
                citizen->lastName,
                getGender(citizen->gender),
                citizen->birthDate,
                getMaritalStatus(citizen->maritalStatus),
                citizen->nationality,
                citizen->religion,
                citizen->contactNumber,
                citizen->emailAddress,
                citizen->address.houseNumber,
                citizen->address.street,
                citizen->address.purokZone
             );
        current = current->next;
    }

    fclose(tempFile); // Close the temporary file

    // remove original file
    if (remove(filename) != 0) {
        fprintf(stderr, "Error: Could not remove file %s\n", filename);
        remove("TEMP_FILEPATH");
        return;
    }

    // rename temp file to original file
    if (rename("./output/temp.csv", filename) != 0) {
        fprintf(stderr, "Error: Could not rename file temp.csv to %s\n", filename);
        remove("TEMP_FILEPATH");
        return;
    }
}

