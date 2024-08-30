#ifndef LIST_H
#define LIST_H

// include the citizen.h file and the responseCode.h file
#include "./citizen/citizen.h"
#include "./citizen/response_code.h"

// Linked-list implementation
typedef struct Node {
    Citizen data;
    struct Node *next;
} Node;


// Func Prototypes for operations
Node *createNode(Citizen c, ResponseCode *res);
ResponseCode addCitizen(Node **head, Citizen c);
ResponseCode display(Node *head);

#endif //LIST_H
