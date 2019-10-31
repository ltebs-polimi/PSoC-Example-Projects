/*
*   \file main.c
*   \brief Main source file for the BME280 Example Project.
*
*   This file represents the main source file used for the 01-BME280
*   PSoC Creator project. It shows how to interact with the BME280
*   APIs and sends data over UART.
*
*   \author Davide Marzorati
*   \date October 25, 2019
*/

#include "BME280.h"
#include "BME280_I2C_Interface.h"
#include "BME280_RegMap.h"
#include "project.h"
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Debug_Start();
    
    UART_Debug_PutString("************************\r\n");
    UART_Debug_PutString("          BME280        \r\n");
    UART_Debug_PutString("************************\r\n");
    
    char message[50];
    BME280 bme280;
    uint8_t data_array[12] = {0};
    uint8_t status_reg = 0;
    
    data_array[0] = 0x0A;
    data_array[1] = 0x0D;
    data_array[10] = 0xA0;
    data_array[11] = 0xC0;
    
    for (int i = 0; i < 128; i++)
    {
        if (BME280_I2C_Interface_IsDeviceConnected(i) == BME280_OK)
        {
            sprintf(message, "Device 0x%02X connected\r\n", i);
            UART_Debug_PutString(message);
        }
        
    }
    
    if (BME280_Start(&bme280) == BME280_OK)
    {
        UART_Debug_PutString("Sensor was initialized properly\r\n");
        if (BME280_SetNormalMode(&bme280) == BME280_OK)
        {
            BME280_SetHumidityOversampling(&bme280, BME280_OVERSAMPLING_16X);
            BME280_SetTemperatureOversampling(&bme280, BME280_OVERSAMPLING_1X);
            BME280_SetPressureOversampling(&bme280, BME280_OVERSAMPLING_1X);
            BME280_SetStandbyTime(&bme280, BME280_TSTANBDY_500_MS);
            
        }
    }
    
    for(;;)
    {
        /* Place your application code here. */
        if (BME280_ReadData(&bme280, BME280_TEMP_COMP | BME280_PRESS_COMP) == BME280_OK)
        {
            sprintf(message, "T: %ld P: %ld H: %ld \r\n", bme280.data.temperature,
                bme280.data.pressure, bme280.data.humidity);
            UART_Debug_PutString(message);
            
        }
        else
        {
            UART_Debug_PutString("Error\r\n");
            BME280_Reset();
            if (BME280_SetNormalMode(&bme280) == BME280_OK)
            {
                BME280_SetHumidityOversampling(&bme280, BME280_OVERSAMPLING_16X);
                BME280_SetTemperatureOversampling(&bme280, BME280_OVERSAMPLING_1X);
                BME280_SetPressureOversampling(&bme280, BME280_OVERSAMPLING_1X);
                BME280_SetStandbyTime(&bme280, BME280_TSTANBDY_500_MS);
                
            }
        }
        
        CyDelay(1000);

    }
}

/* [] END OF FILE */
