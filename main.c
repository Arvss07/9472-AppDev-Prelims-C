#include <stdio.h>

#include "citizen/citizen.h"
#include "file/file.h"
#include "cmd/terminal_utils.h"

int main(void) {

   List list = {NULL, NULL};

    loadCitizensFromCSV("..\\data.csv", &list);
    // printList(&list);

    // printf("\n\nSorting citizen by last name\n");
    // List sortedLastName = sortCitizen(&list, LastName);
    // printTable(&sortedLastName);

    // printf("\n\nSorting citizen by first name\n");
    // List sortedFirstName = sortCitizen(&list, FirstName);
    //printTable(&sortedLastName);

    Citizen gio = {
        .citizenId = 1001,
        .firstName = "Giovanni",
        .middleName = " ",
        .lastName = "Leo",
        .gender = MALE,
        .birthDate = "2024-09-01",
        .maritalStatus = SINGLE,
        .nationality = "Filipino",
        .religion = "Catholic",
        .contactNumber = "1234567890",
        .emailAddress = "gio.vanni@example.com",
        .address = {
            .houseNumber = "101",
            .street = "Veni",
            .purokZone = "Vidi",
            .barangay = "Vici"
        }
    };

    Citizen addMe = {
        .citizenId = 1000,
        .firstName = "Arvs",
        .middleName = "Tayoan",
        .lastName = "Aggabao",
        .gender = MALE,
        .birthDate = "1234-56-78",
        .maritalStatus = SINGLE,
        .nationality = "Filipino",
        .religion = "Catholic",
        .contactNumber = "1234567890",
        .emailAddress = "arvy.a@example.com",
        .address = {
            .houseNumber = "111",
            .street = "Eagle Lair",
            .purokZone = "Eagle Crest Phase 1",
            .barangay = "Bakakeng Sur"
        }
    };

    ResponseCode result = addFirst(&list, addMe);

    if (result == Success) {
        printf("Citizen updated successfully.\n");
        printCitizen(&list, addMe.citizenId);
    } else {
        printf("Error updating citizen: %d\n", result);
    }

    createAndSaveCitizenCert(&list, &addMe);
    pressAnyKeyToContinue();

    return 0;
}
