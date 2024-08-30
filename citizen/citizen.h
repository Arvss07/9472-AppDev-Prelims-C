#ifndef CITIZEN_H
#define CITIZEN_H

enum Brgy { BRY1, BRY2, BRY3, BRY4 };
enum ResponseCode {Success, Failed, NotFound};

typedef struct {
    char name[50];
    enum Brgy barangay;
    int age;
    int citizenId;
    char completeAddr[100];
} Citizen;

typedef struct Node {
    Citizen citizen;
    struct Node *next;
} Node;


typedef struct {
    Node *head;
    Node *tail;
} CitizenList;


void initCitizenList(CitizenList *list);

// first
enum ResponseCode addCitizenFirst(CitizenList *list, const char *name, enum Brgy barangay, int age, int citizenId, const char *completeAddr);

// last
enum ResponseCode addCitizenLast(CitizenList *list, const char *name, enum Brgy barangay, int age, int citizenId, const char *completeAddr);

// remove a citizen from the linked list by citizenId
enum ResponseCode removeCitizen(CitizenList *list, int citizenId);

// count the number of citizens in a specific barangay
enum ResponseCode countCitizens(CitizenList *list, enum Brgy barangay);

// filter citizens by barangay and return an array
Citizen* filterCitizens(CitizenList *list, enum Brgy barangay, int *count);

// display citizens
void displayCitizensNode(CitizenList *list);

// display citizens
void displayCitizensArray(Citizen *citizens, int count);

#endif
