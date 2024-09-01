#ifndef FILE_H
#define FILE_H
#define MAX_LINE_LENGTH 1024

#include "..//citizen/citizen.h"

void loadCitizensFromCSV(const char *filename, CitizenList *list);
void saveListToFile(const char *filename, CitizenList *list);

#endif //FILE_H
