/*
* This file contains utility functions for clearing the terminal and pausing execution
* to wait for user input in a cross-platform manner.
*/
#include "terminal_utils.h"
#include <stdio.h>  
#include <stdlib.h> 

/*
 * Clears the terminal screen.
 *
 * This function checks the operating system and uses the appropriate command
 * to clear the terminal screen. On Windows, it uses "cls". On Linux/macOS, it uses "clear".
 */
void clearTerminal() 
{
 #ifdef _WIN32
    system("cls");  
 #else
    system("clear");  
 #endif
}

/*
 * Pauses the program and waits for the user to press any key to continue.
 *
 * This function prints a message to the terminal asking the user to press any key.
 * After the user presses a key, it clears the terminal screen.
 */
void pressAnyKeyToContinue() 
{
    printf("Press ANY key to continue...");  
    getchar();  
    clearTerminal();  
}
