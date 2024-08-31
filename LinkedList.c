#include "LinkedList.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void addFirst(List *list, Citizen citizen) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return;
    }
    newNode->citizen = citizen;
    newNode->next = list->head;

    if (list->head == NULL) {
        list->tail = newNode;
    }
    list->head = newNode;
}

void addLast(List *list, Citizen citizen) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return;
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
}

void printList(List *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("Citizen Name: %s, ID: %d\n", current->citizen.name, current->citizen.id);
        current = current->next;
    }
}

void removeCitizen(List *list, int citizenId) {
    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL && current->citizen.id != citizenId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Citizen with ID %d not found.\n", citizenId);
        return;
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
}

List filterByName(List *list, const char *name) {
    List filteredList = {NULL, NULL};
    const Node *current = list->head;

    while (current != NULL) {
        if (strcmp(current->citizen.name, name) == 0) {
            addLast(&filteredList, current->citizen);
        }
        current = current->next;
    }

    return filteredList;
}

void freeList(List *list) {
    Node *current = list->head;
    Node *next;

    while (current != NULL) {
        next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}
