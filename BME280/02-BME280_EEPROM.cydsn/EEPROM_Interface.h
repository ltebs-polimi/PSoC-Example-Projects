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

#ifndef __EEPROM_INTERFACE_H
    #define __EEPROM_INTERFACE_H

    #include "EEPROM_ErrorCodes.h"
    /**
    *   \brief Address in the EEPROM memory of the header.
    */
    #ifndef EEPROM_HEADER_START_ADDR
        #define EEPROM_HEADER_START_ADDR 0x00
    #endif
    
    #ifndef EEPROM_BLOCK_WRITE
        #define EEPROM_BLOCK_WRITE 0x00
    #endif
    
    #ifndef EEPROM_NO_BLOCK_WRITE
        #define EEPROM_NO_BLOCK_WRITE 0x01
    #endif
    
    
    /**
    *   \brief Start the EEPROM.
    *
    *   This function starts the EEPROM. It is necessary
    *   to start the interface before performing any kind of
    *   reading/writing operation.
    */
    EEPROM_ErrorCode EEPROM_Interface_Start();

    /**
    *   \brief Stop the EEPROM.
    *
    *   This function stops and powers down the EEPROM.
    */
    EEPROM_ErrorCode EEPROM_Interface_Stop();
    
    /**
    *   \brief Write bytes to the EEPROM.
    *
    *   This function allows to write the bytes passed in as parameter
    *   to a specific location of the EEPROM.
    *
    *   \param[in] data : the data to be written to the EEPROM
    *   \param[in] len  : length of data to be written to the EEPROM
    *   \param[in] start_address : start address in EEPROM where writing must be perfomred
    *   
    *   \return Result of function execution
    *   \retval #EEPROM_OK -> Success
    *   \retval #EEPROM_E_WRITE -> Error
    */
    EEPROM_ErrorCode EEPROM_Interface_WriteBytes(const uint8_t* data, uint16_t len,
        uint16_t start_address);
    
    /**
    *   \brief Write bytes to the EEPROM.
    *
    *   This function allows to write the bytes passed in as parameter
    *   to a specific row of the EEPROM.
    *
    *   \param[in] data : the data to be written to the EEPROM
    *   \param[in] row_address : row address where data will be written
    *   
    *   \return Result of function execution
    *   \retval #EEPROM_OK -> Success
    *   \retval #EEPROM_E_WRITE -> Error
    */
    EEPROM_ErrorCode EEPROM_Interface_WriteRow(const uint8_t* data,
        uint16_t row_address);
    
    /**
    *   \brief Read bytes from EEPROM.
    *
    *   This function allows to read bytes from the EEPROM memory.
    *   \param[out] data :  pointer to an array where data will be stored
    *   \param[in] len  :  length of data to read
    *   \param[in] start_address : start address in EEPROM where reading will occur.
    *   
    *   \return Result of function execution
    *   \retval #EEPROM_OK -> Success
    */
    EEPROM_ErrorCode EEPROM_Interface_ReadBytes(uint8_t* data, 
        uint16_t len, uint16_t start_address);
    
#endif

/* [] END OF FILE */
