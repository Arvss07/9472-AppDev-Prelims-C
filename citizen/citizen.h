#ifndef CITIZEN_H
#define CITIZEN_H


typedef enum {
    Success,
    Failed,
    NotFound
}ResponseCode;

typedef enum {
    MALE,
    FEAMLE ,
    OTHERS
} Gender;

typedef enum {
    SINGLE,
    MARRIED ,
    DIVORCED ,
    WIDOWED
} MaritalStatus;

typedef struct {
    char *houseNumber;
    char *street;
    char *purokZone;
    char *barangay;
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
} CitizenList;

#define getGender(g) \
((g) == MALE ? "Male" : (g) == FEAMLE ? "Female" : "Others")

#define getMaritalStatus(m) \
((m) == SINGLE ? "Single" : (m) == MARRIED ? "Married" : (m) == DIVORCED ? "Divorced" : "Widowed")



void initCitizenList(CitizenList *list);

// first
ResponseCode addCitizenFirst(CitizenList *list, int citizenId, const char *firstName, const char *middleName, const char *lastName,
                                  Gender gender, const char *birthDate, MaritalStatus maritalStatus, const char *nationality,
                                  const char *religion, const char *contactNumber, const char *emailAddress, Address address);

// last
ResponseCode addCitizenLast(CitizenList *list, int citizenId, const char *firstName, const char *middleName, const char *lastName,
                                  Gender gender, const char *birthDate, MaritalStatus maritalStatus, const char *nationality,
                                  const char *religion, const char *contactNumber, const char *emailAddress, Address address);

// remove a citizen from the linked list by citizenId
ResponseCode removeCitizen(CitizenList *list, int citizenId);

// count the number of citizens in a specific address
ResponseCode countCitizensByAddress(CitizenList *list, Address address);

// count the number of citizens
ResponseCode countCitizens(const CitizenList *list);

// filter citizens by address and return an array
Citizen* filterCitizens(const CitizenList *list, Address address);

// display citizens
void displayCitizensNode(const CitizenList *list);


#endif
