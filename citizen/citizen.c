#include "citizen.h"
#include "../file/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Counter for the number of citizens in the list
int counter = 0;


// compare two Citizen objects based on the specified sort type.
// Returns the result of the comparison.
int cmpCtz(const Citizen a, const Citizen b, Type sort) {
    // Compare based on the sorting type provided
    if (sort == FirstName) {
        return strcmp(a.firstName, b.firstName);
    }

    if (sort == MiddleName) {
        return strcmp(a.middleName, b.middleName);
    }

    if (sort == LastName) {
        return strcmp(a.lastName, b.lastName);
    }

    if (sort == CitizenId) {
        return a.citizenId - b.citizenId;
    }
    if (sort == BirthDate) {
        return strcmp(a.birthDate, b.birthDate);
    }
    return 0;
}


// check if a Citizen's attribute contains a keyword.
int com(const Citizen a, const char *keyword, Type type) {
    // Search in the citizen's specified attribute based on the type
    if (type == FirstName) {
        return strstr(a.firstName, keyword) != NULL;
    }

    if (type == MiddleName) {
        return strstr(a.middleName, keyword) != NULL;
    }

    if (type == LastName) {
        return strstr(a.lastName, keyword) != NULL;
    }


    return 0;
}

// create a deep copy of a list of citizens.
List *copyList(List *list) {
    List *copy = malloc(sizeof(List));
    if (copy == NULL) {
        fprintf(stderr, "Failed to allocate memory for copied list\n");
        return NULL;
    }

    copy->head = NULL;
    copy->tail = NULL;

    // Traverse the original list and add each citizen to the copied list
    Node *current = list->head;
    while (current != NULL) {
        addLast(copy, current->citizen);
        current = current->next;
    }


    return copy;
}

// add a citizen to the front of the list.
ResponseCode addFirst(List *list, Citizen citizen) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return Failed;
    }
    newNode->citizen = citizen;
    newNode->next = list->head;

    if (list->head == NULL) {
        list->tail = newNode;
    }
    counter++;
    list->head = newNode;
    return Success;
}

// add a citizen to the end of the list.
ResponseCode addLast(List *list, Citizen citizen) {
    Node *newNode = malloc(sizeof(Node));
    if (newNode == NULL) {
        fprintf(stderr, "Failed to allocate memory\n");
        return Failed;
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
    counter++;
    return Success;
}

// print all citizens in the list with detailed information.
void printList(List *list) {
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");

    // Traverse the list and print each citizen's information
    while (current != NULL) {
        printf("\n%d.CitizenId: %d\n", i++, current->citizen.citizenId);
        printf("Name: %s %s %s\n", current->citizen.firstName, current->citizen.middleName, current->citizen.lastName);
        printf("Gender: %s\n", getGender(current->citizen.gender));
        printf("Birth Date: %s\n", current->citizen.birthDate);
        printf("Marital Status: %s\n", getMaritalStatus(current->citizen.maritalStatus));
        printf("Nationality: %s\n", current->citizen.nationality);
        printf("Religion: %s\n", current->citizen.religion);
        printf("Contact Number: %s\n", current->citizen.contactNumber);
        printf("Email Address: %s\n", current->citizen.emailAddress);
        printf("House Number: %s\n", current->citizen.address.houseNumber);
        printf("Street: %s\n", current->citizen.address.street);
        printf("Purok Zone: %s\n", current->citizen.address.purokZone);
        current = current->next;
        printf("\n");
    }
}

// print all citizens in tabular format.
void printTable(List *list) {
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");
    // Print table headers
    printf("%-3s %-5s %-40s %-10s %-10s %-10s %-10s %-15s %-15s %-30s %-7s %-25s %-10s \n",
           "No.", "CtzId", "Name", "Gender", "BDate", "MStat", "Nat", "Rel", "CNum", "Email", "House#", "St", "P/Z");
    // Traverse the list and print each citizen's data in tabular format
    while (current != NULL) {
        printf("%-3d %-5d %-40s %-10s %-10s %-10s %-10s %-15s %-15s %-30s %-7s %-25s %-10s \n",
               i++,
               current->citizen.citizenId,
               getFullName(current->citizen.firstName, current->citizen.middleName, current->citizen.lastName),
               getGender(current->citizen.gender),
               current->citizen.birthDate,
               getMaritalStatus(current->citizen.maritalStatus),
               current->citizen.nationality,
               current->citizen.religion, current->citizen.contactNumber,
               current->citizen.emailAddress,
               current->citizen.address.houseNumber,
               current->citizen.address.street,
               current->citizen.address.purokZone);
        current = current->next;
    }
}

// print detailed information of a single citizen.
void printCitizen(Citizen citizen) {
    printf("CitizenId: %d\n", citizen.citizenId);
    printf("Full Name: %s %s %s\n", citizen.firstName, citizen.middleName, citizen.lastName);
    printf("Gender: %s\n", getGender(citizen.gender));
    printf("Birth Date: %s\n", citizen.birthDate);
    printf("Marital Status: %s\n", getMaritalStatus(citizen.maritalStatus));
    printf("Nationality: %s\n", citizen.nationality);
    printf("Religion: %s\n", citizen.religion);
    printf("Contact Number: %s\n", citizen.contactNumber);
    printf("Email Address: %s\n", citizen.emailAddress);
    printf("House Number: %s\n", citizen.address.houseNumber);
    printf("Street: %s\n", citizen.address.street);
    printf("Purok Zone: %s\n", citizen.address.purokZone);
}

// remove a citizen from the list based on citizenId.
ResponseCode removeCitizen(List *list, int citizenId) {
    Node *current = list->head;
    Node *previous = NULL;

    // Traverse the list to find the citizen with the specified citizenId
    while (current != NULL && current->citizen.citizenId != citizenId) {
        previous = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Citizen with ID %d not found.\n", citizenId);
        return Failed;
    }

    // Adjust the list pointers to remove the node
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
    counter--;
    free(current);
    return Success;
}

// update a citizen's information in the list.
ResponseCode updateCitizen(List *list, const Citizen *citizen) {
    if (list == NULL || citizen == NULL) return Failed;

    Node *current = list->head;
    int found = 0;

    // Traverse the list to find and update the citizen
    while (current != NULL) {
        if (current->citizen.citizenId == citizen->citizenId) {
            found = 1;
            current->citizen = *citizen;
            break;
        }
        current = current->next;
    }

    if (found) {
        return Success;
    } else {
        return NotFound;
    }
}

// sort a list of citizens based on a specified attribute.
List sortCitizen(List *list, Type sort) {
    List sortedList = {NULL, NULL};

    if (list->head == NULL) {
        return sortedList;
    }

    List *copy = copyList(list); // Create a copy of the list
    if (copy == NULL) {
        return sortedList;
    }

    const Node *current = copy->head;

    // Perform selection sort on the copied list
    while (current != NULL) {
        const Node *min = current;
        const Node *search = current->next;


        while (search != NULL) {
            if (cmpCtz(min->citizen, search->citizen, sort) > 0) {
                min = search;
            }
            search = search->next;
        }


        // Add the smallest element to the sorted list
        addLast(&sortedList, min->citizen);
        removeCitizen(copy, min->citizen.citizenId);
        current = copy->head;
    }

    freeList(copy); // Free the memory used by the copied list
    return sortedList;
}

// free the memory allocated for a list of citizens.
void freeList(List *list) {
    Node *current = list->head;

    // Traverse the list and free each node
    while (current != NULL) {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

// search for a citizen in the list by a specific attribute and keyword.
Citizen *searchCitizen(List *list, Type searchType, const char *keyword) {
    Node *current = list->head;

    // Traverse the list to search for a citizen that matches the keyword
    while (current != NULL) {
        if (com(current->citizen, keyword, searchType)) {
            return &current->citizen;
        }
        current = current->next;
    }

    // If no match is found, return NULL
    return NULL;
}

// search for a citizen in the list by citizenId.
Citizen *searchCitizenById(List *list, int citizenId) {
    Node *current = list->head;

    // Traverse the list to find the citizen with the specified citizenId
    while (current != NULL) {
        if (current->citizen.citizenId == citizenId) {
            return &current->citizen;
        }
        current = current->next;
    }

    // If no match is found, return NULL
    return NULL;
}

// Create a certificate for a citizen and save it to a file
void createAndSaveCitizenCert(List *list, const Citizen *citizen) {
    Node *current = list->head; // Start at the head of the list
    while (current != NULL) {
        // Iterate through the list
        if (strcmp(current->citizen.firstName, citizen->firstName) == 0 && strcmp(
                current->citizen.lastName, citizen->lastName) == 0) {
            char *cert = createCitizenCert(&current->citizen); // Create a certificate for the citizen
            if (cert != NULL) {
                char filename[256]; // Allocate enough memory for the filename
                snprintf(filename, sizeof(filename), "%s%s_%s_Certificate.txt", CERT_FILEPATH, citizen->firstName,
                         citizen->lastName); // Create the filename
                saveCitizenCertToFile(filename, cert); // Save the certificate to a file
                free(cert); // Free the allocated memory for the certificate string
            }
            return; // Exit the function after finding the citizen
        }
        current = current->next; // Move to the next node
    }
    printf("Citizen %s %s not found in the list.\n", citizen->firstName, citizen->lastName);
    // Print an error message if the citizen is not found
}

//Get the age of the citizen
int getCitizenAge(List *list, int citizenId) {
    Node *current = list->head;

    // Get the current date
    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    int currentYear = current_time->tm_year + 1900;
    int currentMonth = current_time->tm_mon + 1;
    int currentDay = current_time->tm_mday;

    while (current != NULL) {
        if (current->citizen.citizenId == citizenId) {
            char *token;
            char delimiter[] = "-";
            char birthYear[5];
            char birthMonth[3];
            char birthDay[3];

            token = strtok(current->citizen.birthDate, delimiter);
            strcpy(birthYear, token);

            token = strtok(NULL, delimiter);
            strcpy(birthMonth, token);

            token = strtok(NULL, delimiter);
            strcpy(birthDay, token);

            int birth_year = atoi(birthYear);
            int birth_month = atoi(birthMonth);
            int birth_day = atoi(birthDay);

            int age = currentYear - birth_year;

            if (currentMonth < birth_month || (currentMonth == birth_month && currentDay < birth_day)) {
                age--;
            }
            return age;
        }
        current = current->next;
    }
    return -1;
}

int getMalePopulation(List *list) {
    Node *current = list->head;

    int malePopulation = 0;

    while (current != NULL) {
        if (current->citizen.gender == MALE) {
            malePopulation++;
        }
        current = current->next;
    }
    return malePopulation;
}

int getFemalePopulation(List *list) {
    Node *current = list->head;

    int femalePopulation = 0;

    while (current != NULL) {
        if (current->citizen.gender == FEMALE) {
            femalePopulation++;
        }
        current = current->next;
    }
    return femalePopulation;
}

Citizen getOldestCitizen(List *list) {
    // sort by age
    List sortedBdate = sortCitizen(list, BirthDate);
    Citizen oldestCitizen = sortedBdate.head->citizen;
    return oldestCitizen;
}

Citizen getYoungestCitizen(List *list) {
    // sort by age
    List sortedBdate = sortCitizen(list, BirthDate);
    Citizen oldestCitizen = sortedBdate.tail->citizen;
    return oldestCitizen;
}


void viewDemographics(List *list) {
    if (list == NULL || list->head == NULL) {
        printf("No demographic information available. The list is empty.\n");
        return;
    }

    int totalPopulation = counter;
    int totalMalePopulation = getMalePopulation(list);
    int totalFemalePopulation = getFemalePopulation(list);

    Citizen oldestCitizen = getOldestCitizen(list);
    Citizen youngestCitizen = getYoungestCitizen(list);

    printf("Demographic Information\n");
    printf("Total Population: %d\n", totalPopulation);
    printf("Total Male Population: %d\n", totalMalePopulation);
    printf("Total Female Population: %d\n", totalFemalePopulation);

    char oldestName[200];
    snprintf(oldestName, sizeof(oldestName), "%s %s", oldestCitizen.firstName, oldestCitizen.lastName);
    printf("The Oldest Citizen: %s\n", oldestName);
    printf("Age: %d\n", getCitizenAge(list, oldestCitizen.citizenId));

    char youngestName[200];
    snprintf(youngestName, sizeof(youngestName), "%s %s", youngestCitizen.firstName, youngestCitizen.lastName);
    printf("The Youngest Citizen: %s\n", youngestName);
    printf("Age: %d\n", getCitizenAge(list, youngestCitizen.citizenId));
}
