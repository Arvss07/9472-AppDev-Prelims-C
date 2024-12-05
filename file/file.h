#ifndef FILE_H
#define FILE_H

#define MAX_LINE_LENGTH 1024

#include "../citizen/citizen.h"
#include "../utils/util.h"

/**
 * @brief Loads citizens from a CSV file and populates the given list.
 *
 * @param filename The name of the CSV file.
 * @param list The list where the citizens will be stored.
 */
void loadCitizensFromCSV(const char *filename, List *list);

/**
 * @brief Saves the list of citizens to a CSV file.
 *
 * @param filename The target CSV file where the list will be saved.
 * @param list The list of citizens to save.
 */
void saveListToFile(const char *filename, List *list);

#endif // FILE_H
