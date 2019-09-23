/**
*   \file Logging_Interface.h
*
*   \brief Interface to the logging system.
*   
*   This interface allows to set up a logging system 
*   in such a that, in case the hardware changes, only
*   this file should be modified. 
*   
*
*   \author: Davide Marzorati
*   \date: September 23, 2019
*/

#ifndef __LOGGING_INTERFACE_H
    #define __LOGGING_INTERFACE_H

    #include "cytypes.h"
    
    /*
    *   \brief Error codes for the logging interface.
    *
    *   Define some error codes to be used throughout the
    *   interface when returning a value from functions.
    */
    typedef enum 
    {
        LOGGING_OK,     ///< Everything good.
        LOGGING_ERROR   ///< Some error occurred.
    } LoggingError;
    
    /**
    *   \brief Start the interface.
    *
    *   This function takes care of starting the peripheral
    *   used for logging and debug purposes.
    */
    LoggingError Logging_Interface_Start(void);
    
    /**
    *   \brief Stop the interface.
    *
    *   This function takes care of stopping the peripheral
    *   used for logging and debug purposes.
    */
    LoggingError Logging_Interface_Stop(void);
    
    /**
    *   \brief Print out a string.
    *
    *   This function allows to print out a string.
    *   \param string pointer to the null terminated string 
    *       residing in ROM or RAM to be transmitted
    */
    LoggingError Logging_Interface_PutString(const char8 string[]);
    
    /**
    *   \brief Print out a string.
    *
    *   This function allows to print out a string.
    *   \param string[] address of the memory array residing in RAM or ROM.
    *   \param byteCount number of bytes to be transmitted.
    */
    LoggingError Logging_Interface_PutArray(const uint8 string[], uint8 byteCount);
    
    /**
    *   \brief Print out a number in int format.
    *
    *   This function allows to print out a number in int format.
    *   \param value the number to be printed
    */
    LoggingError Logging_Interface_PutInt(int value);
    
    
#endif


/* [] END OF FILE */
