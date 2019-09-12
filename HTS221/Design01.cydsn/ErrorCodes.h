/**
*   \file ErrorCodes.h
*   \brief Error codes definition.
*   
*   This file contains several definition of error codes to be used throughout
*   the project to be consisted with the written firmware.
*
*   \author Davide Marzorati
*   \date September 12, 2019
*/

/**
*   \brief Error codes.
* 
*   This definition defines several error codes that will
*   be used throughout the project.
*/
typedef enum {
    NO_ERROR,           // No error generated
    UNKNOWN_ERROR,      // Unknown error
    BAD_PARAMETER,      // Bad parameter error
    BAD_INDEX,          // Null pointer
    UNINIT_VARIABLE,    // Uninitialized variable
    UNINIT_SYSTEM      // Uninitialized system
} ErrorCode;

/* [] END OF FILE */
