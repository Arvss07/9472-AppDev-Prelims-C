#include "citizen.h"
#include "../file/file.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Counter for the number of citizens in the list
int counter = 0;

/*
 * Gets the age based on a birthdate
 */
int getAge(const char *birth_date)
{
    int birth_year, birth_month, birthday;

    // Parse the birthdate string
    if (sscanf(birth_date, "%4d-%2d-%2d", &birth_year, &birth_month, &birthday) != 3)
    {
        return -1; // Return -1 for invalid date format
    }

    // Get the current date
    time_t t = time(NULL);
    struct tm current_date = *localtime(&t);

    int current_year = current_date.tm_year + 1900;
    int current_month = current_date.tm_mon + 1;
    int current_day = current_date.tm_mday;

    // Calculate age
    int age = current_year - birth_year;

    // Adjust for incomplete year
    if (current_month < birth_month || (current_month == birth_month && current_day < birthday))
    {
        age--;
    }

    return age;
}

/*
 * Compare two Citizen objects based on the specified sort type.
 * Returns the result of the comparison.
 */
int compareCitizen(const Citizen citizen_a, const Citizen citizen_b, Type sort)
{
    // Compare based on the sorting type provided
    if (sort == first_name)
    {
        return strcmp(citizen_a.first_name, citizen_b.first_name);
    }

    if (sort == middle_name)
    {
        return strcmp(citizen_a.middle_name, citizen_b.middle_name);
    }

    if (sort == last_name)
    {
        return strcmp(citizen_a.last_name, citizen_b.last_name);
    }

    if (sort == citizen_id)
    {
        return citizen_a.citizen_id - citizen_b.citizen_id;
    }

    if (sort == birth_date)
    {
        int citizen_a_age = getAge(citizen_a.birth_date);
        int citizen_b_age = getAge(citizen_b.birth_date);

        return citizen_a_age - citizen_b_age;
    }
    return 0;
}

// check if a Citizen's attribute contains a keyword.
int com(const Citizen citizen_a, const char *keyword, Type type) 
{
    // Search in the citizen's specified attribute based on the type
    if (type == first_name) 
    {
        return strstr(citizen_a.first_name, keyword) != NULL;
    }

    if (type == middle_name) 
    {
        return strstr(citizen_a.middle_name, keyword) != NULL;
    }

    if (type == last_name) 
    {
        return strstr(citizen_a.last_name, keyword) != NULL;
    }


    return 0;
}

// create a deep copy of a list of citizens.
List *copyList(List *list) 
{
    List *copy = malloc(sizeof(List));
    if (copy == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory for copied list\n");
        return NULL;
    }

    copy->head = NULL;
    copy->tail = NULL;

    Node *current = list->head;
    while (current != NULL) 
    {
        addLast(copy, current->citizen);
        current = current->next;
    }
    return copy;
}

// add a citizen to the front of the list.
ResponseCode addFirst(List *list, Citizen citizen) 
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL) 
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return failed;
    }
    new_node->citizen = citizen;
    new_node->next = list->head;

    if (list->head == NULL)
    {
        list->tail = new_node;
    }
    counter++;
    list->head = new_node;
    return success;
}

// add a citizen to the end of the list.
ResponseCode addLast(List *list, Citizen citizen)
{
    Node *new_node = malloc(sizeof(Node));
    if (new_node == NULL)
    {
        fprintf(stderr, "Failed to allocate memory\n");
        return failed;
    }
    new_node->citizen = citizen;
    new_node->next = NULL;

    if (list->tail == NULL)
    {
        list->head = new_node;
        list->tail = new_node;
    }
    else
    {
        list->tail->next = new_node;
        list->tail = new_node;
    }
    counter++;
    return success;
}

// print all citizens in the list with detailed information.
void printList(List *list)
{
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");

    while (current != NULL)
    {
        printf("\n%d.citizen_id: %d\n", i++, current->citizen.citizen_id);
        printf("Name: %s %s %s\n", current->citizen.first_name, current->citizen.middle_name, current->citizen.last_name);
        printf("Gender: %s\n", getGender(current->citizen.gender));
        printf("Birth Date: %s\n", current->citizen.birth_date);
        printf("Marital Status: %s\n", getMaritalStatus(current->citizen.marital_status));
        printf("Nationality: %s\n", current->citizen.nationality);
        printf("Religion: %s\n", current->citizen.religion);
        printf("Contact Number: %s\n", current->citizen.contact_number);
        printf("Email Address: %s\n", current->citizen.email_address);
        printf("House Number: %s\n", current->citizen.address.house_number);
        printf("Street: %s\n", current->citizen.address.street);
        printf("Purok Zone: %s\n", current->citizen.address.purok_zone);
        current = current->next;
        printf("\n");
    }
}

// print all citizens in tabular format.
void printTable(List *list)
{
    Node *current = list->head;
    int i = 1;
    printf("List of Citizens\n\n");
    printf("%-3s %-5s %-40s %-10s %-10s %-10s %-10s %-15s %-15s %-30s %-7s %-25s %-10s \n",
           "No.", "CtzId", "Name", "Gender", "BDate", "MStat", "Nat", "Rel", "CNum", "Email", "House#", "St", "P/Z");
    // Traverse the list and print each citizen's data in tabular format
    while (current != NULL)
    {
        printf("%-3d %-5d %-40s %-10s %-10s %-10s %-10s %-15s %-15s %-30s %-7s %-25s %-10s \n",
               i++,
               current->citizen.citizen_id,
               getFullName(current->citizen.first_name, current->citizen.middle_name, current->citizen.last_name),
               getGender(current->citizen.gender),
               current->citizen.birth_date,
               getMaritalStatus(current->citizen.marital_status),
               current->citizen.nationality,
               current->citizen.religion, current->citizen.contact_number,
               current->citizen.email_address,
               current->citizen.address.house_number,
               current->citizen.address.street,
               current->citizen.address.purok_zone);
        current = current->next;
    }
}

// print detailed information of a single citizen.
void printCitizen(Citizen citizen)
{
    printf("citizen_id: %d\n", citizen.citizen_id);
    printf("Full Name: %s %s %s\n", citizen.first_name, citizen.middle_name, citizen.last_name);
    printf("Gender: %s\n", getGender(citizen.gender));
    printf("Birth Date: %s\n", citizen.birth_date);
    printf("Marital Status: %s\n", getMaritalStatus(citizen.marital_status));
    printf("Nationality: %s\n", citizen.nationality);
    printf("Religion: %s\n", citizen.religion);
    printf("Contact Number: %s\n", citizen.contact_number);
    printf("Email Address: %s\n", citizen.email_address);
    printf("House Number: %s\n", citizen.address.house_number);
    printf("Street: %s\n", citizen.address.street);
    printf("Purok Zone: %s\n", citizen.address.purok_zone);
}

// remove a citizen from the list based on citizen_id.
ResponseCode removeCitizen(List *list, int citizen_id)
{
    Node *current = list->head;
    Node *previous = NULL;

    while (current != NULL && current->citizen.citizen_id != citizen_id)
    {
        previous = current;
        current = current->next;
    }

    if (current == NULL)
    {
        printf("Citizen with ID %d not found.\n", citizen_id);
        return failed;
    }

    if (previous == NULL)
    {
        list->head = current->next;
        if (list->head == NULL)
        {
            list->tail = NULL;
        }
    }
    else
    {
        previous->next = current->next;
        if (current->next == NULL)
        {
            list->tail = previous;
        }
    }
    counter--;
    free(current);
    return success;
}

// update a citizen's information in the list.
ResponseCode updateCitizen(List *list, const Citizen *citizen)
{
    if (list == NULL || citizen == NULL)
    {
    return failed;
    }

    Node *current = list->head;
    int found = 0;

    while (current != NULL)
    {
        if (current->citizen.citizen_id == citizen->citizen_id)
        {
            found = 1;
            current->citizen = *citizen;
            break;
        }
        current = current->next;
    }

    if (found)
    {
        return success;
    }
    else
    {
        return not_found;
    }
}

// sort a list of citizens based on a specified attribute.
List sortCitizen(List *list, Type sort)
{
    List sorted_list = {NULL, NULL};

    if (list->head == NULL)
    {
        return sorted_list;
    }

    List *copy = copyList(list);
    if (copy == NULL)
    {
        return sorted_list;
    }

    const Node *current = copy->head;

    while (current != NULL)
    {
        const Node *min = current;
        const Node *search = current->next;


        while (search != NULL)
        {
            if (compareCitizen(min->citizen, search->citizen, sort) > 0)
            {
                min = search;
            }
            search = search->next;
        }

        addLast(&sorted_list, min->citizen);
        removeCitizen(copy, min->citizen.citizen_id);
        current = copy->head;
    }

    freeList(copy);
    return sorted_list;
}

// free the memory allocated for a list of citizens.
void freeList(List *list)
{
    Node *current = list->head;

    while (current != NULL)
    {
        Node *next = current->next;
        free(current);
        current = next;
    }

    list->head = NULL;
    list->tail = NULL;
}

// search for a citizen in the list by a specific attribute and keyword.
Citizen *searchCitizen(List *list, Type search_type, const char *keyword)
{
    Node *current = list->head;
    while (current != NULL)
    {
        if (com(current->citizen, keyword, search_type))
        {
            return &current->citizen;
        }
        current = current->next;
    }
    return NULL;
}

// search for a citizen in the list by citizen_id.
Citizen *searchCitizenById(List *list, int citizen_id)
{
    Node *current = list->head;

    // Traverse the list to find the citizen with the specified citizen_id
    while (current != NULL) {
        if (current->citizen.citizen_id == citizen_id) {
            return &current->citizen;
        }
        current = current->next;
    }
    return NULL;
}


// Get the age of the citizen
int getCitizenAge(List *list, int citizen_id)
{
    Node *current = list->head;

    time_t now = time(NULL);
    struct tm *current_time = localtime(&now);
    int current_year = current_time->tm_year + 1900;
    int current_month = current_time->tm_mon + 1;
    int current_day = current_time->tm_mday;

    while (current != NULL)
    {
        if (current->citizen.citizen_id == citizen_id)
        {
            return getAge(current->citizen.birth_date);
        }
        current = current->next;
    }
    return -1;
}

/**
 * @brief Get the male population from the citizen list.
 *
 * This function iterates through the list of citizens and counts how many are male.
 *
 * @param list A pointer to the list of citizens.
 * @return The number of male citizens in the list.
 */
int getMalePopulation(List *list)
{
    Node *current = list->head;
    int male_population = 0;

    while (current != NULL)
    {
        if (current->citizen.gender == male)
        {
            male_population++;
        }
        current = current->next;
    }
    return male_population;
}

/**
 * @brief Get the female population from the citizen list.
 *
 * This function iterates through the list of citizens and counts how many are female.
 *
 * @param list A pointer to the list of citizens.
 * @return The number of female citizens in the list.
 */
int getFemalePopulation(List *list)
{
    Node *current = list->head;
    int female_population = 0;

    while (current != NULL)
    {
        if (current->citizen.gender == female)
        {
            female_population++;
        }
        current = current->next; 
    }
    return female_population;
}

/**
 * @brief Get the oldest citizen from the list.
 *
 * This function sorts the citizens by birth_date and returns the oldest citizen.
 *
 * @param list A pointer to the list of citizens.
 * @return The oldest citizen in the list.
 */
Citizen getOldestCitizen(List *list)
{
    List sorted_bdate = sortCitizen(list, birth_date);
    Citizen oldest_citizen = sorted_bdate.tail->citizen;
    return oldest_citizen;
}

/**
 * @brief Get the youngest citizen from the list.
 *
 * This function sorts the citizens by birth date and returns the youngest citizen.
 *
 * @param list A pointer to the list of citizens.
 * @return The youngest citizen in the list.
 */

Citizen getYoungestCitizen(List *list)
{
    List sorted_bdate = sortCitizen(list, birth_date);
    Citizen youngest_citizen = sorted_bdate.head->citizen;
    return youngest_citizen;
}

/**
 * @brief View demographic information of the citizen list.
 *
 * This function prints the total population, male population, female population, the oldest citizen, and the youngest citizen.
 *
 * @param list A pointer to the list of citizens.
 */
void viewDemographics(List *list)
{
    // Check if the list is empty
    if (list == NULL || list->head == NULL)
    {
        printf("No demographic information available. The list is empty.\n");
        return;
    }

    // Get demographic details
    int total_population = getMalePopulation(list) + getFemalePopulation(list);
    int total_male_population = getMalePopulation(list);
    int total_female_population = getFemalePopulation(list);

    // Get oldest and youngest citizens
    Citizen oldest_citizen = getOldestCitizen(list);
    Citizen youngest_citizen = getYoungestCitizen(list);

    // Display the demographic information
    printf("Demographic Information\n");
    printf("Total Population: %d\n", total_population);
    counter = 0;
    printf("Total Male Population: %d\n", total_male_population);
    printf("Total Female Population: %d\n", total_female_population);

    // Print details of the oldest citizen
    char oldest_name[200];
    snprintf(oldest_name, sizeof(oldest_name), "%s %s", oldest_citizen.first_name, oldest_citizen.last_name);
    printf("The Oldest Citizen: %s\n", oldest_name);
    printf("Age: %d\n", getCitizenAge(list, oldest_citizen.citizen_id));

    // Print details of the youngest citizen
    char youngest_name[200];
    snprintf(youngest_name, sizeof(youngest_name), "%s %s", youngest_citizen.first_name, youngest_citizen.last_name);
    printf("The Youngest Citizen: %s\n", youngest_name);
    printf("Age: %d\n", getCitizenAge(list, youngest_citizen.citizen_id));
}