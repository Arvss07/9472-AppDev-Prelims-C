#ifndef CITIZEN_H
#define CITIZEN_H

#define FILENAME "data.csv"

extern int counter;

// Define the search types
typedef enum {
    first_name,
    last_name,
    middle_name,
    citizen_id,
    birth_date
}Type;

// Define the response codes
typedef enum {
    success,
    failed,
    not_found
}ResponseCode;

// Define the gender
typedef enum {
    male = 0,
    female = 1,
    others = 3
} Gender;

// Define the marital status
typedef enum {
    single = 0,
    married = 1,
    divorced = 2,
    widowed = 3
} MaritalStatus;

// Define the address struct
typedef struct {
    char house_number[100];
    char street[100];
    char purok_zone[100];
} Address;

// Define the Citizen struct
typedef struct {
    int citizen_id;
    char first_name[100];
    char middle_name[100];
    char last_name[100];
    Gender gender;
    char birth_date[100];
    MaritalStatus marital_status;
    char nationality[100];
    char religion[100];
    char contact_number[100];
    char email_address[100];
    Address address;
} Citizen;

// Define the Node struct
typedef struct Node {
    Citizen citizen;
    struct Node *next;
} Node;

// Define the List struct
typedef struct {
    Node *head;
    Node *tail;
} List;

// Define the function prototypes
#define getGender(g) \
((g) == male ? "Male" : (g) == female ? "Female" : "Others")

#define getMaritalStatus(m) \
((m) == single ? "Single" : (m) == married ? "Married" : (m) == divorced ? "Divorced" : "Widowed")

#define getFullName(firstName, middleName, lastName) ({ \
static char fullName[100]; \
sprintf(fullName, "%s %s %s", firstName, middleName, lastName); \
fullName; \
})


ResponseCode addFirst(List *list,  Citizen citizen);
ResponseCode addLast(List *list, Citizen citizen);
void printList(List * list);
void printTable(List *list);
void printCitizen(Citizen citizen);
ResponseCode removeCitizen(List *list, int citizen_id);
List sortCitizen(List *list, Type sort);
ResponseCode updateCitizen(List *list, const Citizen *citizen);
void freeList(List *list);
Citizen *searchCitizen(List *list, Type search_type, const char *keyword);
Citizen *searchCitizenById(List *list,  int citizen_id);
int getCitizenAge(List *list, int citizen_id);

#endif
