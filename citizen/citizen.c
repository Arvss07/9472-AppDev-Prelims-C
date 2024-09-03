#include "citizen.h"
#include "../file/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

ResponseCode addFirst(List *list, Citizen citizen) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return Failed;
    }
    newNode->citizen = citizen;
    newNode->next = list->head;

    if (list->head == NULL) {
        list->tail = newNode;
    }
    list->head = newNode;
    saveListToFile(FILENAME, list);
    return Success;
}

ResponseCode addLast(List *list, Citizen citizen) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return Failed;
    }
    newNode->citizen = citizen;
    newNode->next = NULL;

    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    saveListToFile(FILENAME, list);
    return Success;
}

void printList(List *list) {
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");
    while (current != NULL) {
        printf("\n%d.CitizenId: %d\n",i++, current->citizen.citizenId);
        printf("Name: %s %s %s\n", current->citizen.firstName, current->citizen.middleName, current->citizen.lastName);
        printf("Gender: %s\n", getGender(current->citizen.gender));
        printf("Birth Date: %s\n", current->citizen.birthDate);
        printf("Marital Status: %s\n", getMaritalStatus(current->citizen.maritalStatus));
        printf("Nationality: %s\n", current->citizen.nationality);
        printf("Religion: %s\n", current->citizen.religion);
        printf("Contact Number: %s\n", current->citizen.contactNumber);
        printf("Email Address: %s\n", current->citizen.emailAddress);
        printf("House Number:%s\n", current->citizen.address.houseNumber);
        printf("Street:%s\n", current->citizen.address.street);
        printf("Purok Zone:%s\n", current->citizen.address.purokZone);
        printf("Barangay:%s\n", current->citizen.address.barangay);
        current = current->next;
        printf("\n");
    }
}

void printTable(List *list) {
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");
    printf("%-5s %-10s %-25s %-15s %-15s %-15s %-15s %-20s %-15s %-30s %-15s %-15s %-20s %-25s\n",
           "No.", "CtzId", "Name", "Gender", "BDate", "MStat", "Nat", "Rel", "CNum", "Email", "House#", "St.#", "P/Z", "Brgy");
    while (current != NULL) {
        printf("%-5d %-10d %-25s %-15s %-15s %-15s %-15s %-20s %-15s %-30s %-15s %-15s %-20s %-25s\n",
               i++,
               current->citizen.citizenId,
               getFullName(current->citizen.firstName, current->citizen.middleName, current->citizen.lastName),
               getGender(current->citizen.gender),
               current->citizen.birthDate,
               getMaritalStatus(current->citizen.maritalStatus),
               current->citizen.nationality,
               current->citizen.religion, current->citizen.contactNumber,
               current->citizen.emailAddress,
               current->citizen.address.houseNumber,
               current->citizen.address.street,
               current->citizen.address.purokZone,
                current->citizen.address.barangay);
        current = current->next;
    }
}

void printCitizen(List *list, int citizenId) {
    Node *current = list->head;
    while (current != NULL) {
        if (current->citizen.citizenId == citizenId) {
            printf("CitizenId: %d\n", current->citizen.citizenId);
            printf("Full Name: %s %s %s\n", current->citizen.firstName, current->citizen.middleName, current->citizen.lastName);
            printf("Gender: %s\n", getGender(current->citizen.gender));
            printf("Birth Date: %s\n", current->citizen.birthDate);
            printf("Marital Status: %s\n", getMaritalStatus(current->citizen.maritalStatus));
            printf("Nationality: %s\n", current->citizen.nationality);
            printf("Religion: %s\n", current->citizen.religion);
            printf("Contact Number: %s\n", current->citizen.contactNumber);
            printf("Email Address: %s\n", current->citizen.emailAddress);
            printf("House Number: %s\n", current->citizen.address.houseNumber);
            printf("Street: %s\n", current->citizen.address.street);
            printf("Purok Zone: %s\n", current->citizen.address.purokZone);
            printf("Barangay: %s\n", current->citizen.address.barangay);
            break;
        }
        current = current->next;
    }
}
ResponseCode removeCitizen(List *list, int citizenId) {
    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL && current->citizen.citizenId != citizenId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Citizen with ID %d not found.\n", citizenId);
        return Failed;
    }

    if (previous == NULL) {
        list->head = current->next;
        if (list->head == NULL) {
            list->tail = NULL;
        }
    } else {
        previous->next = current->next;
        if (current->next == NULL) {
            list->tail = previous;
        }
    }

    free(current);
    return Success;
}

ResponseCode updateCitizen(List *list, const Citizen *citizen) {
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
        saveListToFile(FILENAME, list);
        return Success;
    } else {
        return NotFound;
    }
}

List filterByName(List *list, const char *name) {
    List filteredList = {NULL, NULL};
    const Node *current = list->head;

    while (current != NULL) {
        if (strcmp(current->citizen.firstName, name) == 0) {
            addLast(&filteredList, current->citizen);
        }
        current = current->next;
    }

    return filteredList;
}

List *copyList(List *list) {
    List *copy = malloc(sizeof(List));
    if (copy == NULL) {
        fprintf(stderr, "Failed to allocate memory for copied list\n");
        return NULL;
    }

    copy->head = NULL;
    copy->tail = NULL;

    Node *current = list->head;
    while (current != NULL) {
        addLast(copy, current->citizen);
        current = current->next;
    }


    return copy;
}


int cmpCtz(const Citizen a, const Citizen b,SortType sort) {
    if (sort == FirstName) {
        return strcmp(a.firstName, b.firstName);
    }

    if (sort == MiddleName) {
        return strcmp(a.middleName, b.middleName);
    }

    if (sort == LastName) {
        return strcmp(a.lastName, b.lastName);
    }

    if (sort == CitizenId) {
       return a.citizenId - b.citizenId;
    }

    return 0;
}


List sortCitizen(List *list, SortType sort) {
    List sortedList = {NULL, NULL};

    if (list->head == NULL) {
        return sortedList;
    }

    List *copy = copyList(list);
    if (copy == NULL) {
        return sortedList;
    }

    const Node *current = copy->head;

    while (current != NULL) {
        const Node *min = current;
        const Node *search = current->next;


        while (search != NULL) {
            if (cmpCtz(min->citizen, search->citizen, sort) > 0) {
                min = search;
            }
            search = search->next;
        }


        addLast(&sortedList, min->citizen);
        removeCitizen(copy, min->citizen.citizenId);
        current = copy->head;
    }

    freeList(copy);
    return sortedList;
}



void freeList(List *list) {
    Node *current = list->head;

    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}
// Create a certificate for a citizen and save it to a file
void createAndSaveCitizenCert(List *list, const Citizen *citizen) {
    Node *current = list->head; // Start at the head of the list
    while (current != NULL) { // Iterate through the list
        if (strcmp(current->citizen.firstName, citizen->firstName) == 0 && strcmp(current->citizen.lastName, citizen->lastName) == 0) {
            char *cert = createCitizenCert(&current->citizen); // Create a certificate for the citizen
            if (cert != NULL) {
                char filename[256]; // Allocate enough memory for the filename
                snprintf(filename, sizeof(filename), "%s%s_%s_Certificate.txt", FILEPATH, citizen->firstName, citizen->lastName); // Create the filename
                saveCitizenCertToFile(filename, cert); // Save the certificate to a file
                free(cert); // Free the allocated memory for the certificate string
                printf("Certificate created and saved for %s %s.\n", citizen->firstName, citizen->lastName); // Print a success message
            }
            return; // Exit the function after finding the citizen
        }
        current = current->next; // Move to the next node
    }
    printf("Citizen %s %s not found in the list.\n", citizen->firstName, citizen->lastName); // Print an error message if the citizen is not found
}

