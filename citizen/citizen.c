#include "citizen.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../file/file.h"

void initCitizenList(CitizenList *list) {
    list->head = NULL;
    list->tail = NULL;
}


void copyCitizens(Node *newNode, int citizenId, const char *firstName, const char *middleName, const char *lastName,
                   Gender gender, const char *birthDate, MaritalStatus maritalStatus, const char *nationality,
                   const char *religion, const char *contactNumber, const char *emailAddress, Address address) {

    newNode->citizen.citizenId = citizenId;
    strncpy(newNode->citizen.firstName, firstName, sizeof(newNode->citizen.firstName) - 1);
    newNode->citizen.firstName[sizeof(newNode->citizen.firstName) - 1] = '\0';
    strncpy(newNode->citizen.middleName, middleName, sizeof(newNode->citizen.middleName) - 1);
    newNode->citizen.middleName[sizeof(newNode->citizen.middleName) - 1] = '\0';
    strncpy(newNode->citizen.lastName, lastName, sizeof(newNode->citizen.lastName) - 1);
    newNode->citizen.lastName[sizeof(newNode->citizen.lastName) - 1] = '\0';
    newNode->citizen.gender = gender;
    strncpy(newNode->citizen.birthDate, birthDate, sizeof(newNode->citizen.birthDate) - 1);
    newNode->citizen.birthDate[sizeof(newNode->citizen.birthDate) - 1] = '\0';
    newNode->citizen.maritalStatus = maritalStatus;
    strncpy(newNode->citizen.nationality, nationality, sizeof(newNode->citizen.nationality) - 1);
    newNode->citizen.nationality[sizeof(newNode->citizen.nationality) - 1] = '\0';
    strncpy(newNode->citizen.religion, religion, sizeof(newNode->citizen.religion) - 1);
    newNode->citizen.religion[sizeof(newNode->citizen.religion) - 1] = '\0';
    strncpy(newNode->citizen.contactNumber, contactNumber, sizeof(newNode->citizen.contactNumber) - 1);
    newNode->citizen.contactNumber[sizeof(newNode->citizen.contactNumber) - 1] = '\0';
    strncpy(newNode->citizen.emailAddress, emailAddress, sizeof(newNode->citizen.emailAddress) - 1);
    newNode->citizen.emailAddress[sizeof(newNode->citizen.emailAddress) - 1] = '\0';
    newNode->citizen.address = address;
}

ResponseCode addCitizenFirst(CitizenList *list, int citizenId, const char *firstName, const char *middleName, const char *lastName,
                                  Gender gender, const char *birthDate, MaritalStatus maritalStatus, const char *nationality,
                                  const char *religion, const char *contactNumber, const char *emailAddress, const Address address) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) return Failed;

    copyCitizens(newNode,  citizenId, firstName, middleName, lastName, gender, birthDate,  maritalStatus, nationality, religion, contactNumber,  emailAddress,  address);
    newNode->next = list->head;

    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }

    return Success;
}

ResponseCode addCitizenLast(CitizenList *list, int citizenId, const char *firstName, const char *middleName, const char *lastName,
                                 Gender gender, const char *birthDate, MaritalStatus maritalStatus, const char *nationality,
                                 const char *religion, const char *contactNumber, const char *emailAddress, Address address) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) return Failed;

    copyCitizens(newNode,  citizenId, firstName, middleName, lastName, gender, birthDate,  maritalStatus, nationality, religion, contactNumber,  emailAddress,  address);
    newNode->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode;
    }
    list->tail = newNode;

    return Success;
}

 ResponseCode removeCitizen(CitizenList *list, const int citizenId) {
    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL) {
        if (current->citizen.citizenId == citizenId) {
            if (previous == NULL) {
                list->head = current->next;
                if (list->head == NULL) {
                    list->tail = NULL;
                }
            } else {
                previous->next = current->next;
                if (previous->next == NULL) {
                    list->tail = previous;
                }
            }
            free(current);
            return Success;
        }
        previous = current;
        current = current->next;
    }
    return NotFound;
}

ResponseCode countCitizensInBarangay(const CitizenList *list, const Address address) {
    int count = 0;
    const Node *current = list->head;

    while (current != NULL) {
        if (current->citizen.address.barangay == address.barangay) {
            count++;
        }
        current = current->next;
    }
    return count;
}

ResponseCode countCitizens(const CitizenList *list) {
    int count = 0;
    const Node *current = list->head;

    while (current != NULL) {
        count++;
        current = current->next;
    }
    return count;
}

Citizen* filterCitizens(const CitizenList *list, Address address) {
    int count = countCitizensInBarangay(list, address);
    const Node *current = list->head;

    // First, count how many citizens match the filter
    while (current != NULL) {
        if (current->citizen.address.barangay == address.barangay) {
            count++;
        }
        current = current->next;
    }


    Citizen *result = malloc(sizeof(Citizen) * count);
    if (result == NULL) return NULL;

    current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->citizen.address.barangay == address.barangay) {
            result[index++] = current->citizen;
        }
        current = current->next;
    }

    return result;
}

void displayCitizensNode(const CitizenList *list) {
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");
    while (current != NULL) {
        printf("\n%d.Name: %s %s %s\n",i++, current->citizen.firstName, current->citizen.middleName, current->citizen.lastName);
        printf("Gender: %s\n", getGender(current->citizen.gender));
        printf("Birth Date: %s\n", current->citizen.birthDate);
        printf("Marital Status: %s\n", getMaritalStatus(current->citizen.maritalStatus));
        printf("Nationality: %s\n", current->citizen.nationality);
        printf("Religion: %s\n", current->citizen.religion);
        printf("Contact Number: %s\n", current->citizen.contactNumber);
        printf("Email Address: %s\n", current->citizen.emailAddress);
        printf("House Number:%s\n", current->citizen.address.houseNumber);
        printf("Street:%s\n", current->citizen.address.houseNumber);
        printf("Purok Zone:%s\n", current->citizen.address.houseNumber);
        printf("Barangay:%s\n", current->citizen.address.houseNumber);
        current = current->next;
        printf("\n");
    }
}

void displayCitizenName(const CitizenList *list) {
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");
    // header
    printf("%-5s %-20s %-20s %-20s\n", "No.", "First Name", "Middle Name", "Last Name");
    while (current != NULL) {
        printf("%-5d %-20s %-20s %-20s\n", i++, current->citizen.firstName, current->citizen.middleName, current->citizen.lastName);
        current = current->next;
    }
}

ResponseCode updateCitizen(CitizenList *list, Citizen *citizen) {
    if (list == NULL || citizen == NULL) return Failed;

    Node *current = list->head;
    int found = 0;

    while (current != NULL) {
        if (current->citizen.citizenId == citizen->citizenId) {
            found = 1;
            current->citizen = *citizen;
            break;
        }
        current = current->next;
    }

    if (found) {
        saveListToFile("..\\data.csv", list);
        return Success;
    } else {
        return NotFound;
    }
}


