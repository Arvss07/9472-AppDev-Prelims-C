#include <stdio.h>

#include "citizen/citizen.h"

int main(void) {

   List list  ={};

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

    addFirst(&list, gio);
    printList(&list);



    return 0;
}
