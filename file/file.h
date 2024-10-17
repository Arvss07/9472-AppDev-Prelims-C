#ifndef FILE_H
#define FILE_H
#define MAX_LINE_LENGTH 1024

#include "..//citizen/citizen.h"
#include "../utils/util.h"


void loadCitizensFromCSV(const char *filename, List *list);
void saveListToFile(const char *filename, List *list);
#endif //FILE_H
