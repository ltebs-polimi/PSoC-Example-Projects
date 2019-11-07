/**
*   \file EEPROM_ErrorCodes.h
*
*   \brief Error codes for the EEPROM Interface.
*/

#ifndef __EEPROM_ERROR_CODES_H
    #define __EEPROM_ERROR_CODES_H
    
    #include "cytypes.h"

    /**
    *   \brief Header length in bytes.
    */
    #ifndef EEPROM_HEADER_LENGTH
        #define EEPROM_HEADER_LENGTH 0x06
    #endif
    
    /**
    *   \brief Result of api execution -> Success
    */
    #ifndef EEPROM_OK
        #define EEPROM_OK 0
    #endif
    
    /**
    *   \brief Result of api execution -> Error write operation
    */
    #ifndef EEPROM_E_WRITE
        #define EEPROM_E_WRITE -1
    #endif
    
    /**
    *   \brief Result of api execution -> Address error
    */
    #ifndef EEPROM_E_ADDR
        #define EEPROM_E_ADDR -2
    #endif
    
    /**
    *   \brief Result of api execution -> Address error
    */
    #ifndef EEPROM_E_HEADER
        #define EEPROM_E_HEADER -3
    #endif

    /**
    *   \brief Error returned by api.
    */
    typedef int8_t EEPROM_ErrorCode;
#endif
/* [] END OF FILE */
