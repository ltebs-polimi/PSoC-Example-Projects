/*
*   Source file for the logging interface.
*/

#warning // Change the UART_Debug with the correct name of your UART component.
#define UART_Debug_Name(fn) UART_Debug_ ## fn
#define UART_Debug_Name_Header_File "UART_Debug.h"

#include "Logging_Interface.h"
#include UART_Debug_Name_Header_File

#include "stdio.h"

LoggingError Logging_Interface_Start(void)
{
    UART_Debug_Name(Start)();
    
    return LOGGING_OK;
}

LoggingError Logging_Interface_Stop(void)
{
    UART_Debug_Name(Stop)();
    
    return LOGGING_OK;
}
    

LoggingError Logging_Interface_PutString(const char8 string[])
{
    UART_Debug_Name(PutString)(string);
    
    return LOGGING_OK;
}
    
    
LoggingError Logging_Interface_PutArray(const uint8 string[], 
                                            uint8 byteCount)
{
    UART_Debug_Name(PutArray)(string, byteCount);
    return LOGGING_OK;
}

/* [] END OF FILE */
