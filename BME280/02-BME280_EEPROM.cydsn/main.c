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

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Debug_Start();
    
    UART_Debug_PutString("************************\r\n");
    UART_Debug_PutString("     BME280 EEEPROM     \r\n");
    UART_Debug_PutString("************************\r\n");
    
    char message[50];
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

    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
