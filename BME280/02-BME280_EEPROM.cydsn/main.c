/*
*   \file main.c
*   \brief Main source file for the BME280 Example Project.
*
*   This file represents the main source file used for the 02-BME280 EEPROM
*   PSoC Creator project. It shows how to interact with the BME280
*   APIs, how to store these data in EEPROM memory and retrieve them
*   from UART.
*
*   \author Davide Marzorati
*   \date November 4, 2019
*/

#include "BME280.h"
#include "project.h"
#include "stdio.h"
#include "EEPROM_Interface.h"
#include "BME280_EEPROM.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Debug_Start();
    
    UART_Debug_PutString("************************\r\n");
    UART_Debug_PutString("     BME280 EEEPROM     \r\n");
    UART_Debug_PutString("************************\r\n");

    BME280 bme280;
    BME280_ErrorCode error;

    error = BME280_Start(&bme280);
    if (error == BME280_OK)
    {
        UART_Debug_PutString("Sensor was initialized properly\r\n");

        BME280_SetHumidityOversampling(&bme280, BME280_OVERSAMPLING_1X);
        BME280_SetTemperatureOversampling(&bme280, BME280_OVERSAMPLING_1X);
        BME280_SetPressureOversampling(&bme280, BME280_OVERSAMPLING_1X);
        BME280_SetStandbyTime(&bme280, BME280_TSTANBDY_62_5_MS);
        BME280_SetSleepMode(&bme280);
        
    }
    else
    {
        UART_Debug_PutString("Could not initialize sensor\r\n");
    }
    
    BME280_SetNormalMode(&bme280);
    BME280_EEPROM_Start();
    
    for (int i = 0; i < 10; i++)
    {
        BME280_ReadData(&bme280, BME280_ALL_COMP);
        BME280_EEPROM_Start();
        BME280_EEPROM_WriteData(&bme280);
        BME280_EEPROM_Stop();
        CyDelay(20000);
    }
    
    char message[50] = {'\0'};
    
    for (int i = 0; i < 10; i++)
    {
        BME280_EEPROM_Start();
        uint8_t data[8];
        EEPROM_Interface_ReadBytes(data,8,6+i*8);
        int32_t temperature = (data[0] << 24) | (data[1] << 16) | (data[2] << 8) | data[3];
        uint32_t humidity = (data[4] << 24) | (data[5] << 16) | (data[6] << 8) | data[7];
        sprintf(message, "%d - T: %ld - H: %ld\r\n", i, (long)temperature, (long)humidity);
        UART_Debug_PutString(message);
    }

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
