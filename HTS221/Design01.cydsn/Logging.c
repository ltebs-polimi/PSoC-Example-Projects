/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "Logging.h"
#include "stdio.h"

LoggingError Logging_Start(void)
{
    // Start the interface
    LoggingError error = Logging_Interface_Start();
    if ( error == LOGGING_ERROR)
    {
        return LOGGING_ERROR;
    }
    
    // Print welcome string
    error = Logging_Interface_PutString(WELCOME_STRING);
    if ( error == LOGGING_ERROR)
    {
        return LOGGING_ERROR;
    }
    
    // Print debug string
    #ifdef DEBUG_ENABLED
        error = Logging_Interface_PutString(DEBUG_ENABLED_STRING);
        if ( error == LOGGING_ERROR)
        {
            return LOGGING_ERROR;
        }
    #endif
    
    return error;
}

LoggingError Logging_PrintHTS221Configuration(HTS221_Struct* hts221)
{
    char str[50] = {'\0'};
    Logging_Interface_PutString("HTS221 Configuration\n");
    Logging_Interface_PutString("\t-HTS221_AVGH:");
    sprintf(str,"%d\n", hts221->avgHum);
    return LOGGING_OK;
}

/* [] END OF FILE */
