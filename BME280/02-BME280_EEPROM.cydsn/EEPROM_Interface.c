/**
*   \brief Source file for the EEPROM interface.
*
*   \author Davide Marzorati
*   \date November 5, 2019
*/

#include "EEPROM_Interface.h"
#include "EEPROM.h"

EEPROM_ErrorCode EEPROM_Interface_Start()
{
    EEPROM_Start();
    CyDelay(1);
    return EEPROM_OK;
}

EEPROM_ErrorCode EEPROM_Interface_Stop()
{
    EEPROM_Stop();
    return EEPROM_OK;
}


EEPROM_ErrorCode EEPROM_Interface_WriteBytes(const uint8_t* data, uint16_t len,
    uint16_t start_address)
{
    EEPROM_ErrorCode error;
    cystatus api_error = CYRET_SUCCESS;
    
    // Check that addresses are valid
    if ( ((start_address + len) < CY_EEPROM_SIZE))
    {
        // Update temperature
        EEPROM_UpdateTemperature();
        
        uint16_t counter = 0;
        
        // Write all the required bytes
        while ( counter < len )
        {
            api_error = EEPROM_WriteByte(data[counter], start_address + counter);
            counter++;
            if ((api_error != CYRET_SUCCESS) )
            {
                break;
            }
        }
        
        if (api_error == CYRET_SUCCESS)
        {
            error = EEPROM_OK;
        }
        else
        {
            error = EEPROM_E_WRITE;
        }
    }
    else
    {
        error = EEPROM_E_ADDR;
    }
    return error;
}

EEPROM_ErrorCode EEPROM_Interface_WriteRow(const uint8_t* data,
        uint16_t row_number)
{
    EEPROM_ErrorCode error;
    cystatus api_error;
    // Write row worth of data
    api_error = EEPROM_Write(data, row_number);
    if (api_error == CYRET_SUCCESS)
    {
        error = EEPROM_OK;
    }
    else
    {
        error = EEPROM_E_WRITE;
    }
    return error;
}

EEPROM_ErrorCode EEPROM_Interface_ReadBytes(uint8_t* data, 
    uint16_t len, uint16_t start_address)
{
     EEPROM_ErrorCode error;
    // Check that addresses are valid
    if ( ((start_address + len) < CY_EEPROM_SIZE))
    {
        // Read the data
        uint16_t counter = 0;
        while ( counter < len)
        {
            data[counter] = EEPROM_ReadByte(start_address + counter);
            counter++;
        }
        error = EEPROM_OK;
    }
    else
    {
        error = EEPROM_E_ADDR;
    }
    return error;
}


/* [] END OF FILE */
