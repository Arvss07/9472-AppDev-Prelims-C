#ifndef CITIZEN_H
#define CITIZEN_H

#define FILENAME "../data.csv"
#define FILENAME2 "../"
typedef enum {
    FirstName,
    LastName,
    MiddleName,
    CitizenId,
}SortType;

typedef enum {
    Success,
    Failed,
    NotFound
}ResponseCode;

typedef enum {
    MALE = 0,
    FEMALE = 1,
    OTHERS = 3
} Gender;

typedef enum {
    SINGLE = 0,
    MARRIED = 1,
    DIVORCED = 2,
    WIDOWED = 3
} MaritalStatus;

typedef struct {
    char houseNumber[100];
    char street[100];
    char purokZone[100];
    char barangay[100];
} Address;

typedef struct {
    int citizenId;
    char firstName[100];
    char middleName[100];
    char lastName[100];
    Gender gender;
    char birthDate[100];
    MaritalStatus maritalStatus;
    char nationality[100];
    char religion[100];
    char contactNumber[100];
    char emailAddress[100];
    Address address;
} Citizen;

typedef struct Node {
    Citizen citizen;
    struct Node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

#define getGender(g) \
((g) == MALE ? "Male" : (g) == FEMALE ? "Female" : "Others")

#define getMaritalStatus(m) \
((m) == SINGLE ? "Single" : (m) == MARRIED ? "Married" : (m) == DIVORCED ? "Divorced" : "Widowed")

#define getFullName(firstName, middleName, lastName) ({ \
static char fullName[100]; \
sprintf(fullName, "%s %s %s", firstName, middleName, lastName); \
fullName; \
})



ResponseCode addFirst(List *list,  Citizen citizen);
ResponseCode addLast(List *list, Citizen citizen);
void printList(List * list);
void printTable(List *list);
void printCitizen(List *list, int citizenId);
ResponseCode removeCitizen(List *list, int citizenId);
List filterByName(List *list, const char *name);
List sortCitizen(List *list, SortType sort);
ResponseCode updateCitizen(List *list, const Citizen *citizen);
void freeList(List *list);
void createAndSaveCitizenCert(List *list, const char *firstName, const char *lastName);


#endif
