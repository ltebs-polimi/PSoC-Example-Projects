/*
*   This is the source code for the logging
*   driver. 
*
*   \author Davide Marzorati
*   \date September 23, 2019
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
    // Print out average humidity samples
    Logging_Interface_PutString("\t- HTS221_AVGH:");
    sprintf(str,"%d\n", hts221->avgHum);
    Logging_Interface_PutString(str);
    // Print out average temperature samples
    Logging_Interface_PutString("\t- HTS221_AVGT:");
    sprintf(str,"%d\n", hts221->avgTemp);
    Logging_Interface_PutString(str);
    // Heater status
    Logging_Interface_PutString("\t- HTS221_Heater:");
    if (hts221->heater == HTS221_HEATER_OFF)
    {
        Logging_Interface_PutString("OFF\n");
    }
    else
    {
        Logging_Interface_PutString("ON\n");
    }
    // Power status
    Logging_Interface_PutString("\t- HTS221_Power:");
    if (hts221->power == HTS221_POWER_OFF)
    {
        Logging_Interface_PutString("OFF\n");
    }
    else
    {
        Logging_Interface_PutString("ON\n");
    }
    // Output data rate
    Logging_Interface_PutString("\t- HTS221_ODR:");
    switch(hts221->odr)
    {
        case HTS221_ODR_OneShot:
            Logging_Interface_PutString("One Shot\n");
        break;
        case HTS221_ODR_1Hz:
            Logging_Interface_PutString("1 Hz\n");
        break;
        case HTS221_ODR_7Hz:
            Logging_Interface_PutString("7 Hz\n");
        break;
        case HTS221_ODR_12_5Hz:
            Logging_Interface_PutString("12.5 Hz\n");
        break;
        default:
            Logging_Interface_PutString("Unknown\n");
        break;
    }
    
    return LOGGING_OK;
}

/* [] END OF FILE */
