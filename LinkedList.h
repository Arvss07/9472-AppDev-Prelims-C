#ifndef LINKEDLIST_H
#define LINKEDLIST_H
#include <stddef.h>

typedef struct {
    char name[100];
    int id;
} Citizen;

typedef struct Node {
    Citizen citizen;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

void addFirst(List *list,  Citizen citizen);
void addLast(List *list, Citizen citizen);
void printList(List * list);
void removeCitizen(List *list, int citizenId);
List filterByName(List *list, const char *name);
List sortCitizen(List * list);
void freeList(List *list);

#endif //LINKEDLIST_H
