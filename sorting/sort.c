#include <string.h>
#include "sort.h"

// helper func to compare two Citizen structs based on a specified field
int cmpCtz(const
     Citizen *a, const Citizen *b, const char *field) {
    if (strcmp(field, "firstName") == 0) {
        return strcmp(a->firstName, b->firstName);
    } else if (strcmp(field, "middleName") == 0) {
        return strcmp(a->middleName, b->middleName);
    } else if (strcmp(field, "lastName") == 0) {
        return strcmp(a->lastName, b->lastName);
    }

    return 0;
}

// Insertion sort algorithm to sort the linked list of citizens
void sortCitizens(CitizenList *list, const char *field) {
    if (list->head == NULL) return;

    Node *sorted = NULL;
    Node *curr = list->head;

    while (curr != NULL) {
        Node *next = curr->next;
        Node **head = &sorted;

        for (; *head != NULL; head = &(*head)->next) {
            // check if the current node should be inserted before the current head
            if (cmpCtz(&curr->citizen, &(*head)->citizen, field) < 0) {
                break;
            }
        }

        // Insert the current node in the sorted list
        curr->next = *head;
        *head = curr;
        curr = next;
    }

    // Update the head of the list
    list->head = sorted;

    // Update the tail
    Node *tail = sorted;
    while (tail != NULL && tail->next != NULL) {
        tail = tail->next;
    }
}
