#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Node *createNode(Citizen c, ResponseCode *res) {
    // memory allocation for the node
    Node *node = (Node *)malloc(sizeof(Node));

    // check if memory allocation was successful
    if(node == NULL) {
        // set the response code to MEMORY_ALLOCATION_FAILED
        *res = MEMORY_ALLOCATION_FAILED;
        return NULL;
    }

    // set the data of the node to the citizen data
    node->data = c;
    // adjust the next pointer to NULL
    node->next = NULL;
    // set the response code to SUCCESS
    *res = SUCCESS;
    return node;
} // end of createNode

ResponseCode addCitizen(Node **head, Citizen c) {
    ResponseCode status;
    Node *newNode = createNode(c, &status);
    if (status != SUCCESS) {
        return status;
    }

    // get the new node to point to the head
    newNode->next = *head;
    // assign the head to the new node
    *head = newNode;
    return SUCCESS;
} // end of addCitizen


ResponseCode display(Node *head) {
    if(head == NULL) return NOT_FOUND;

    Node *current = head;
    while(current != NULL) {
        Citizen c = current->data;
        printf("Full Name: %s %s %s\n", c.firstName, c.middleName, c.lastName);
        printf("Gender: %s\n", getGender(c.gender));
        printf("Birthdate: %s\n", c.birthDate);
        printf("Marital Status: %s\n", getMaritalStatus(c.maritalStatus));
        printf("Nationality: %s\n", c.nationality);
        printf("Religion: %s\n", c.religion);
        printf("Contact Number: %s\n", c.contactNumber);
        printf("Email Address: %s\n", c.emailAddress);

        // print the address
        printf("Address \n");
        printf("House Number: %s\n", c.address.houseNumber);
        printf("Street: %s\n", c.address.street);
        printf("Purok/Zone: %s\n", c.address.purokZone);
        printf("Barangay: %s\n", c.address.barangay);
        printf("\n");
        current = current->next;
    }
    return SUCCESS;
}
