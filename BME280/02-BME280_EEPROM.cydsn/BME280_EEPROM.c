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
#include "BME280_EEPROM.h"
#include "EEPROM_Interface.h"

#define HEADER_LENGTH 4
#define HEADER_START_ADDRESS 0

#define COUNTER_LENGTH 2
#define COUNTER_START_ADDRESS ( HEADER_START_ADDRESS + HEADER_LENGTH )

#define DATA_LENGTH 8
#define DATA_START_ADDRESS ( COUNTER_START_ADDRESS + COUNTER_LENGTH )

static EEPROM_ErrorCode BME280_EEPROM_CheckHeader(void);
static EEPROM_ErrorCode BME280_EEPROM_WriteHeader(void);
static EEPROM_ErrorCode BME280_EEPROM_WriteCounter(uint16_t counter);
static EEPROM_ErrorCode BME280_EEPROM_ReadCounter(uint16_t* counter);

const uint8_t HEADER[HEADER_LENGTH] = {0xA0,0xC0,0xA1,0xC1};

EEPROM_ErrorCode BME280_EEPROM_Start(void)
{
    EEPROM_ErrorCode error;
    error = EEPROM_Interface_Start();  
    if ( error == EEPROM_OK)
    {
        error = BME280_EEPROM_CheckHeader();
        if ( error == EEPROM_E_HEADER)
        {
            // Write header
            error = BME280_EEPROM_WriteHeader();
            if ( error == EEPROM_OK)
            {
                // Reset everything
                error = BME280_EEPROM_WriteCounter(0);
            }
        }
    }
    
    return error;
    
}
    
EEPROM_ErrorCode BME280_EEPROM_Stop(void)
{
    EEPROM_ErrorCode error;
    error = EEPROM_Interface_Stop();
    return error;
}

EEPROM_ErrorCode BME280_EEPROM_WriteData(BME280* bme280)
{
    EEPROM_ErrorCode error;
    uint16_t counter;
    error = BME280_EEPROM_ReadCounter(&counter);
    if ( error == EEPROM_OK)
    {
        uint8_t data_array[DATA_LENGTH];
        data_array[0] = ((uint8_t)(bme280->data.temperature >> 24));
        data_array[1] = ((uint8_t)(bme280->data.temperature >> 16));
        data_array[2] = ((uint8_t)(bme280->data.temperature >> 8));
        data_array[3] = ((uint8_t)(bme280->data.temperature & 0xFF));
        data_array[4] = ((uint8_t)(bme280->data.humidity >> 24));
        data_array[5] = ((uint8_t)(bme280->data.humidity >> 16));
        data_array[6] = ((uint8_t)(bme280->data.humidity >> 8));
        data_array[7] = ((uint8_t)(bme280->data.humidity & 0xFF));
        error = EEPROM_Interface_WriteBytes(data_array, DATA_LENGTH,
            DATA_START_ADDRESS + counter * DATA_LENGTH);
        if ( error == EEPROM_OK)
        {
            error = BME280_EEPROM_WriteCounter(counter+1);
        }
    }
    
    return error;
}

static EEPROM_ErrorCode BME280_EEPROM_CheckHeader(void)
{
    EEPROM_ErrorCode error;
    uint8_t header[HEADER_LENGTH];
    
    error = EEPROM_Interface_ReadBytes(header,HEADER_LENGTH,HEADER_START_ADDRESS);
    
    for (uint8_t i = 0; i < HEADER_LENGTH; i++)
    {
        if ( header[i] != HEADER[i])
        {
            error = EEPROM_E_HEADER;
            break;
        }
    }
    if ( error != EEPROM_E_HEADER)
    {
        error = EEPROM_OK;
    }
    return error;
}
static EEPROM_ErrorCode BME280_EEPROM_WriteHeader(void)
{
    EEPROM_ErrorCode error;
    
    error = EEPROM_Interface_WriteBytes(HEADER, HEADER_LENGTH, HEADER_START_ADDRESS);
    
    return error;
}
static EEPROM_ErrorCode BME280_EEPROM_WriteCounter(uint16_t counter)
{
    EEPROM_ErrorCode error;
    uint8_t counter_array [] = { (uint8_t)counter >> 8, (uint8_t)counter & 0xFF};
    error = EEPROM_Interface_WriteBytes(counter_array, COUNTER_LENGTH, COUNTER_START_ADDRESS);
    
    return error;
}
static EEPROM_ErrorCode BME280_EEPROM_ReadCounter(uint16_t* counter)
{
    EEPROM_ErrorCode error;
    uint8_t counter_array [2];
    error = EEPROM_Interface_ReadBytes(counter_array, COUNTER_LENGTH, COUNTER_START_ADDRESS);
    *counter  = (counter_array[0] << 8) | (counter_array[1] & 0xFF);
    return error;
}

/* [] END OF FILE */
