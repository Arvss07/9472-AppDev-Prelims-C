#ifndef FILE_H
#define FILE_H
#define MAX_LINE_LENGTH 1024

#include "..//citizen/citizen.h"

void loadCitizensFromCSV(const char *filename, List *list);
void saveListToFile(const char *filename, List *list);
char* createCitizenCert(const Citizen *citizen);
void saveCitizenCertToFile(const char *filename, const char *cert);
#endif //FILE_H
