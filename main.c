#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"
#include "sorting/sort.h"


int main(void) {

    CitizenList list;
    initCitizenList(&list);

    loadCitizensFromCSV("..\\data.csv", &list);

    // clearTerminal();
    // printf("Unsorted list of citizens:\n");
    // displayCitizenName(&list);
    // pressAnyKeyToContinue();
    //
    // sortCitizens(&list, "firstName");
    //
    // printf("Sorted list of citizens:\n");
    // displayCitizenName(&list);
    // pressAnyKeyToContinue();

    printf("Default");
    displayCitizensNode(&list);

    Citizen gio = {
        .citizenId = 1001,
        .firstName = "Hatdog",
        .middleName = "Giovanni",
        .lastName = "Haha",
        .gender = OTHERS,
        .birthDate = "2024-09-01",
        .maritalStatus = WIDOWED,
        .nationality = "Chinese",
        .religion = "Jewish",
        .contactNumber = "1234567890",
        .emailAddress = "gio.vanni@example.com",
        .address = {
            .houseNumber = "101",
            .street = "Monglo",
            .purokZone = "Sablan",
            .barangay = "Bayabas"
        }
    };

    ResponseCode result = updateCitizen(&list, &gio);
    if (result == Success) {
        printf("Citizen updated successfully.\n");
        displayCitizensNode(&list);
    } else {
        printf("Error updating citizen: %d\n", result);
    }
    printf("Whutttt\n");


    return 0;
}
