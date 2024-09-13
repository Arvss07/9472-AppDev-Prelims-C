#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../citizen/citizen.h"

/**
 * @brief Converts a string to a Gender enum value.
 *
 * This function compares the input string to known gender options
 * and returns the corresponding enum value.
 *
 * @param str The string representing the gender (e.g., "Male", "Female").
 * @return The corresponding Gender enum value (MALE, FEMALE, OTHERS).
 */
Gender getGenderStr(const char *str) {
    if (strcmp(str, "Male") == 0) return MALE;
    if (strcmp(str, "Female") == 0) return FEMALE;
    if (strcmp(str, "Others") == 0) return OTHERS;
    return MALE;  // Default to MALE if input is unrecognized
}

/**
 * @brief Converts a string to a MaritalStatus enum value.
 *
 * This function compares the input string to known marital status options
 * and returns the corresponding enum value.
 *
 * @param str The string representing the marital status (e.g., "Single", "Married").
 * @return The corresponding MaritalStatus enum value (SINGLE, MARRIED, DIVORCED, WIDOWED).
 */
MaritalStatus getMaritalStatusStr(const char *str) {
    if (strcmp(str, "Single") == 0) return SINGLE;
    if (strcmp(str, "Married") == 0) return MARRIED;
    if (strcmp(str, "Divorced") == 0) return DIVORCED;
    if (strcmp(str, "Widowed") == 0) return WIDOWED;
    return SINGLE;  // Default to SINGLE if input is unrecognized
}

/**
 * @brief Converts a string to a ResponseCode enum value.
 *
 * This function compares the input string to known response codes
 * and returns the corresponding enum value.
 *
 * @param str The string representing the response code (e.g., "Success", "Failed").
 * @return The corresponding ResponseCode enum value (Success, Failed, NotFound).
 */
ResponseCode getResponseCode(const char *str) {
    if (strcmp(str, "Success") == 0) return Success;
    if (strcmp(str, "Failed") == 0) return Failed;
    if (strcmp(str, "Not Found") == 0) return NotFound;
    return Success;  // Default to Success if input is unrecognized
}
