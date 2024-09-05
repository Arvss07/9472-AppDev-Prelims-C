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


void loadCitizensFromCSV(const char *filename, List *list) {
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
        // Trim the newline character from the end of the line
        const size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }

        const char *token = strtok(line, ",");

        if (token != NULL) {

            Citizen citizen;

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
            citizen.gender = token ? stringToGender(token) : MALE;

            token = strtok(NULL, ",");
            strncpy(citizen.birthDate, token ? token : "", sizeof(citizen.birthDate) - 1);
            citizen.birthDate[sizeof(citizen.birthDate) - 1] = '\0';

            token = strtok(NULL, ",");
            citizen.maritalStatus = token ? stringToMaritalStatus(token) : SINGLE;

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

            token = strtok(NULL, "\n");
            strncpy(citizen.barangay, token ? token : "", sizeof(citizen.barangay) - 1);
            citizen.barangay[sizeof(citizen.barangay) - 1] = '\0';

            const ResponseCode result = addLast(list, citizen);

            if (result != Success) {
                fprintf(stderr, "Error adding citizen: %d\n", result);
            }
        }
    }

    fclose(file);
}

void saveListToFile(const char *filename, List *list) {
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
        fprintf(tempFile, "%d,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s,%s\n",
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
                citizen->barangay
             );
        current = current->next;
    }

    fclose(tempFile);
    remove(filename);
    rename("temp.csv", filename);
}

// Create a certificate for a citizen
char* createCitizenCert(const Citizen *citizen) {
    char *cert = malloc(1024); // Allocate memory for certificate
    if (cert == NULL) {
        perror("Error: Could not allocate memory for certificate.\n");
        return NULL;
    }
    sprintf(cert, "This is to certify that %s %s, a bona fide resident of %s \n"
                  "and one of the citizen of our barangay with good moral character and law-abiding citizen in the community.\n"
                  "That he/she never violated any laws and ordinances of the barangay nor has been"
                  " involved in any subversive activity.\n"
                  "This certification is issued upon the request of the above-named person for whatever legal purpose it may serve.\n",
            citizen->firstName, citizen->lastName, citizen->barangay);
    return cert;
}

// Save the citizen certificate to a file
void saveCitizenCertToFile(const char *filename, const char *cert) {
    FILE *file = fopen("temp.txt", "w");
    if (file == NULL) {
        perror("Error: Could not open file temp.txt for writing.\n");
        return;
    }
    fprintf(file, "%s", cert); // Write certificate to file
    fclose(file); // Close file
    remove(filename); // Remove the old file
    rename("temp.txt", filename); // Rename the temp file to the desired filename
}
