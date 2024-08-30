#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "citizen.h"

void initCitizenList(CitizenList *list) {
    list->head = NULL;
    list->tail = NULL;
}


enum ResponseCode addCitizenFirst(CitizenList *list, const char *name, enum Brgy barangay, int age, int citizenId, const char *completeAddr) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return Failed;

    strncpy(newNode->citizen.name, name, sizeof(newNode->citizen.name) - 1);
    newNode->citizen.barangay = barangay;
    newNode->citizen.age = age;
    newNode->citizen.citizenId = citizenId;
    strncpy(newNode->citizen.completeAddr, completeAddr, sizeof(newNode->citizen.completeAddr) - 1);
    newNode->next = list->head;

    list->head = newNode;
    if (list->tail == NULL) {
        list->tail = newNode;
    }

    return Success;
}

enum ResponseCode addCitizenLast(CitizenList *list, const char *name, enum Brgy barangay, int age, int citizenId, const char *completeAddr) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return Failed;

    strncpy(newNode->citizen.name, name, sizeof(newNode->citizen.name) - 1);
    newNode->citizen.barangay = barangay;
    newNode->citizen.age = age;
    newNode->citizen.citizenId = citizenId;
    strncpy(newNode->citizen.completeAddr, completeAddr, sizeof(newNode->citizen.completeAddr) - 1);
    newNode->next = NULL;

    if (list->tail != NULL) {
        list->tail->next = newNode;
    } else {
        list->head = newNode; // List was empty
    }
    list->tail = newNode;

    return Success;
}

enum ResponseCode removeCitizen(CitizenList *list, int citizenId) {
    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL) {
        if (current->citizen.citizenId == citizenId) {
            if (previous == NULL) {
                list->head = current->next;
                if (list->head == NULL) {
                    list->tail = NULL; // List is now empty
                }
            } else {
                previous->next = current->next;
                if (previous->next == NULL) {
                    list->tail = previous; // Removed last node
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

enum ResponseCode countCitizens(CitizenList *list, enum Brgy barangay) {
    int count = 0;
    Node *current = list->head;

    while (current != NULL) {
        if (current->citizen.barangay == barangay) {
            count++;
        }
        current = current->next;
    }
    return count;
}

Citizen* filterCitizens(CitizenList *list, enum Brgy barangay, int *count) {
    *count = 0;
    Node *current = list->head;

    // First, count how many citizens match the filter
    while (current != NULL) {
        if (current->citizen.barangay == barangay) {
            (*count)++;
        }
        current = current->next;
    }


    Citizen *result = malloc(sizeof(Citizen) * *count);
    if (result == NULL) return NULL;

    current = list->head;
    int index = 0;
    while (current != NULL) {
        if (current->citizen.barangay == barangay) {
            result[index++] = current->citizen;
        }
        current = current->next;
    }

    return result;
}

void displayCitizensNode(CitizenList *list) {
    Node *current = list->head;

    while (current != NULL) {
        printf("Name: %s, Barangay: %d, Age: %d, ID: %d, Address: %s\n",
               current->citizen.name,
               current->citizen.barangay,
               current->citizen.age,
               current->citizen.citizenId,
               current->citizen.completeAddr);
        current = current->next;
    }
}

void displayCitizensArray(Citizen *citizens, int count) {
    for (int i = 0; i < count; i++) {
        printf("Name: %s, Barangay: %d, Age: %d, ID: %d, Address: %s\n",
               citizens[i].name,
               citizens[i].barangay,
               citizens[i].age,
               citizens[i].citizenId,
               citizens[i].completeAddr);
    }
}
