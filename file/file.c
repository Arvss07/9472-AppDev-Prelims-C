#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Gender stringToGender(const char *str) {
    if (strcmp(str, "Male") == 0) return MALE;
    if (strcmp(str, "Female") == 0) return FEMALE;
    if (strcmp(str, "Others") == 0) return OTHERS;
    return MALE;
}

MaritalStatus stringToMaritalStatus(const char *str) {
    if (strcmp(str, "Single") == 0) return SINGLE;
    if (strcmp(str, "Married") == 0) return MARRIED;
    if (strcmp(str, "Divorced") == 0) return DIVORCED;
    if (strcmp(str, "Widowed") == 0) return WIDOWED;
    return SINGLE;
}


void loadCitizensFromCSV(const char *filename, CitizenList *list) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    char line[MAX_LINE_LENGTH];

    // Skip the header line
    if (fgets(line, sizeof(line), file) == NULL) {
        perror("Error reading file header");
        fclose(file);
        return;
    }

    while (fgets(line, sizeof(line), file)) {
        const char *token = strtok(line, ",");

        if (token != NULL) {
            Address address;
            const int citizenId = atoi(token);
            const char *firstName = strtok(NULL, ",");
            const char *middleName = strtok(NULL, ",");
            const char *lastName = strtok(NULL, ",");
            const Gender gender =  strtok(NULL, ",") ? stringToGender(token) : MALE;
            const char *birthDate = strtok(NULL, ",");
            const MaritalStatus maritalStatus = strtok(NULL, ",") ? stringToMaritalStatus(token) : SINGLE;
            const char *nationality = strtok(NULL, ",");
            const char *religion = strtok(NULL, ",");
            const char *contactNumber = strtok(NULL, ",");
            const char *emailAddress = strtok(NULL, ",");


            strncpy(address.houseNumber, strtok(NULL, ","), sizeof(address.houseNumber) - 1);
            address.houseNumber[sizeof(address.houseNumber) - 1] = '\0';
            strncpy(address.street, strtok(NULL, ","), sizeof(address.street) - 1);
            address.street[sizeof(address.street) - 1] = '\0';
            strncpy(address.purokZone, strtok(NULL, ","), sizeof(address.purokZone) - 1);
            address.purokZone[sizeof(address.purokZone) - 1] = '\0';
            strncpy(address.barangay, strtok(NULL, "\n"), sizeof(address.barangay) - 1);
            address.barangay[sizeof(address.barangay) - 1] = '\0';


            const ResponseCode result = addCitizenLast(list, citizenId, firstName, middleName, lastName, gender, birthDate, maritalStatus, nationality, religion, contactNumber, emailAddress, address);
            if (result != Success) {
                fprintf(stderr, "Error adding citizen: %d\n", result);
            }
        }
    }

    fclose(file);
}

void saveListToFile(const char *filename, CitizenList *list) {
    FILE *tempFile = fopen("temp.csv", "w"); // Open temp file for writing
    if (tempFile == NULL) {
        fprintf(stderr, "Error: Could not open file temp.csv for writing.\n");
        return;
    }

    // Write header
    fprintf(tempFile,
            "CitizenID,FirstName,MiddleName,LastName,Gender,BirthDate,MaritalStatus,Nationality,Religion,ContactNumber,EmailAddress,HouseNumber,Street,PurokZone,Barangay\n");

    // Iterate through the list and write each citizen's data
    Node *current = list->head;
    while (current != NULL) {
        Citizen *citizen = &current->citizen;
        fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
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
                citizen->address.purokZone,
                citizen->address.barangay);
        current = current->next;
    }

    fclose(tempFile);
    remove(filename);
    rename("temp.csv", filename);
}
