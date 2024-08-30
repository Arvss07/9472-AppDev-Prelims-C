#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citizen/citizen.h"

#define MAX_LINE_LENGTH 256

enum Brgy stringToBrgy(const char *str) {
    if (strcmp(str, "BRY1") == 0) return BRY1;
    if (strcmp(str, "BRY2") == 0) return BRY2;
    if (strcmp(str, "BRY3") == 0) return BRY3;
    if (strcmp(str, "BRY4") == 0) return BRY4;
    return BRY1;
}

int main(void) {

    CitizenList list;
    initCitizenList(&list);

    //from here lipat sa ibang header file
    FILE *file = fopen("..\\data.csv", "r");

    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    char line[MAX_LINE_LENGTH];

    // Skip header line
    if (fgets(line, sizeof(line), file) == NULL) {
        perror("Error reading file header");
        fclose(file);
        return EXIT_FAILURE;
    }

    while (fgets(line, sizeof(line), file) != NULL) {
        const char *name = strtok(line, ",");
        const char *barangayStr = strtok(NULL, ",");
        const char *ageStr = strtok(NULL, ",");
        const char *citizenIdStr = strtok(NULL, ",");
        const char *completeAddr = strtok(NULL, "\n");

        if (name && barangayStr && ageStr && citizenIdStr && completeAddr) {
            const enum Brgy barangay = stringToBrgy(barangayStr);
            const int age = atoi(ageStr);
            const int citizenId = atoi(citizenIdStr);

            enum ResponseCode result = addCitizenLast(&list, name, barangay, age, citizenId, completeAddr);
            if (result != Success) {
                fprintf(stderr, "Error adding citizen: %d\n", result);
            }
        } else {
            fprintf(stderr, "Malformed line: %s", line);
        }
    }

    fclose(file);
    //hanggang here


    displayCitizensNode(&list);
    return EXIT_SUCCESS;
}
