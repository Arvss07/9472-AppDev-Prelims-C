#include "file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


Gender stringToGender(const char *str) {
    if (strcmp(str, "Male") == 0) return MALE;
    if (strcmp(str, "Female") == 0) return FEAMLE;
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
            address.houseNumber = strtok(NULL, ",");
            address.street = strtok(NULL, ",");
            address.purokZone = strtok(NULL, ",");
            address.barangay = strtok(NULL, "\n");


            const ResponseCode result = addCitizenLast(list, citizenId, firstName, middleName, lastName, gender, birthDate, maritalStatus, nationality, religion, contactNumber, emailAddress, address);
            if (result != Success) {
                fprintf(stderr, "Error adding citizen: %d\n", result);
            }
        }
    }

    fclose(file);
}
