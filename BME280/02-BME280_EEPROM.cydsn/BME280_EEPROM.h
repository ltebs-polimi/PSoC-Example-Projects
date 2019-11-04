/**
*   \file BME280_EEPROM.h
*   
*   \brief Header file with macros and function declarations
*          to be used for EEPROM reading and writing operations.
*
*   This header file contains macros and function declarations
*   that allows to interface with the embedded EEPROM memory of
*   PSoC 5LP devices.
*
*   \author Davide Marzorati
*   \date November 4, 2019
*/

#ifndef __BME280_EEPROM_H
    #define __BME280_EEPROM_H

    #include "cytypes.h"
    
    /**
    *   \brief Address in the EEPROM memory of the header.
    */
    #ifndef BME280_EEPROM_HEAD_START_ADDR
        #define BME280_EEPROM_HEAD_START_ADDR 0x00
    #endif
    
    /**
    *   \brief Header length in bytes.
    */
    #ifndef BME280_EEPROM_HEAD_LENGTH
        #define BME280_EEPROM_HEAD_LENGHT 0x06
    #endif
    
    #define BME280_EEPROM_OK 0
    
    #define BME280_EEPROM_E_HEAD_CHK_FAIL -1
    
    typedef int8_t BME280_EEPROM_ErrorCode;
    
    BME280_EEPROM_ErrorCode BME280_EEPROM_Start();

    
#endif

/* [] END OF FILE */
