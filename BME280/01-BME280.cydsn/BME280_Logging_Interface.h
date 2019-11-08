/**
*   \file BME280_Logging_Interface.h
*
*   \brief Interface for the logging system.
*
*   This header file contains function declarations to be used
*   with the logging interface to implement system logging.
*
*   \author Davide Marzorati
*   \date November 8, 2019
*/

#ifndef __BME280_LOGGING_INTERFACE_H
    #define __BME280_LOGGING_INTERFACE_H
    
    #include "cytypes.h"
    
    /**
    *   \brief Start the logging interface
    *   
    *   This function starts the peripheral used for the logging
    *   interface.
    */
    void Logging_Interface_Start(void);
    
    /**
    *   \brief Stop the logging interface
    *   
    *   This function stops the peripheral used for the logging
    *   interface.
    */
    void Logging_Interface_Stop(void);
    
    /**
    *   \brief Send a char using the logging interface.
    *   
    *   This function logs the char passed as a parameter.
    *   \param[in] txDataByte : the data to be logged
    */
    void Logging_Interface_PutChar(uint8_t txDataByte);
    
    /**
    *   \brief Send a string of data using the logging interface.
    *   
    *   This function logs the string passed as a parameter.
    *   \param[in] string : the string to be logged
    */
    void Logging_Interface_PutString(const char string[]);
    
    /**
    *   \brief Send the value of an using the the logging interface.
    *   
    *   This function logs the int passed as a parameter.
    *   \param[in] value : the int to be logged
    */
    void Logging_Interface_PutInt(int value);
    
    /**
    *   \brief Send the value of a long int using the logging interface.
    *   
    *   This function logs the long int passed as a parameter.
    *   \param[in] value : the long int to be logged
    */
    void Logging_Interface_PutLongInt(long int value);
    
    /**
    *   \brief Send an array of bytes using the logging interface.
    *   
    *   This function logs the array passed in as a parameter.
    *   \param[in] string : the array to be logged
    *   \param[in] byteCount : the long int to be logged
    */
    void Logging_Interface_PutArray(const char string[], uint8_t byteCount);
    
#endif


/* [] END OF FILE */
