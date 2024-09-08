#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../citizen/citizen.h"

Gender getGenderStr(const char *str) {
    if (strcmp(str, "Male") == 0) return MALE;
    if (strcmp(str, "Female") == 0) return FEMALE;
    if (strcmp(str, "Others") == 0) return OTHERS;
    return MALE;
}

MaritalStatus getMaritalStatusStr(const char *str) {
    if (strcmp(str, "Single") == 0) return SINGLE;
    if (strcmp(str, "Married") == 0) return MARRIED;
    if (strcmp(str, "Divorced") == 0) return DIVORCED;
    if (strcmp(str, "Widowed") == 0) return WIDOWED;
    return SINGLE;
}

ResponseCode getResponseCode(const char *str){
    if (strcmp(str, "Success") == 0) return Success;
    if (strcmp(str, "Failed") == 0) return Failed;
    if (strcmp(str, "Not Found") == 0) return NotFound;
    return Success;
}
