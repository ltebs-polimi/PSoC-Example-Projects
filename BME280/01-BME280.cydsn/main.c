/*
*   \file main.c
*   \brief Main source file for the BME280 Example Project.
*
*   This file represents the main source file used for the 01-BME280
*   PSoC Creator project. It shows how to interact with the BME280
*   APIs and sends data over UART.
*   You can use the provided Bridge Control Panel files (01-BME280.iic and
*   01-BME280.ini) to configure the Bridge Control Panel and see the 
*   data streaming in real-time.
*
*   \author Davide Marzorati
*   \date October 25, 2019
*/

#include "BME280.h"
#include "project.h"
#include "stdio.h"

#define HEADER_SIZE 2
#define TAIL_SIZE 2
#define PACKET_SIZE (HEADER_SIZE + TAIL_SIZE + 4*3) 

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_Debug_Start();
    I2C_Master_Start();
    
    UART_Debug_PutString("************************\r\n");
    UART_Debug_PutString("          BME280        \r\n");
    UART_Debug_PutString("************************\r\n");
    
    char message[50];
    BME280 bme280;
    BME280_ErrorCode error;
    uint8_t data_array[PACKET_SIZE] = {0};
    uint8_t status_reg = 0;
    
    data_array[0] = 0x0A;
    data_array[1] = 0x0D;
    data_array[PACKET_SIZE-2] = 0xA0;
    data_array[PACKET_SIZE-1] = 0xC0;

    error = BME280_Start(&bme280);
    if (error == BME280_OK)
    {
        UART_Debug_PutString("Sensor was initialized properly\r\n");

        BME280_SetHumidityOversampling(&bme280, BME280_OVERSAMPLING_1X);
        BME280_SetTemperatureOversampling(&bme280, BME280_OVERSAMPLING_1X);
        BME280_SetPressureOversampling(&bme280, BME280_OVERSAMPLING_1X);
        BME280_SetStandbyTime(&bme280, BME280_TSTANBDY_500_MS);
        BME280_SetNormalMode(&bme280);

    }
    else
    {
        UART_Debug_PutString("Could not initialize sensor\r\n");
    }

    for(;;)
    {
        /* Place your application code here. */
        do
        {
            error = BME280_ReadStatusRegister(&status_reg);
            if (error == BME280_OK && ( (status_reg & 16) == 0))
            {
                break;
            }
            else
            {
                CyDelay(1);
            }
        } while ( (error!=BME280_OK) || (status_reg & 16));

        error = BME280_ReadData(&bme280, BME280_ALL_COMP);
        if (error == BME280_OK)
        {
            // Pressure
            data_array[2] = ((uint8_t) (bme280.data.pressure >> 24) & 0xFF);
            data_array[3] = ((uint8_t) (bme280.data.pressure >> 16) & 0xFF);
            data_array[4] = ((uint8_t) (bme280.data.pressure >> 8) & 0xFF);
            data_array[5] = ((uint8_t) (bme280.data.pressure) & 0xFF);
            // Temperature
            data_array[6] = ((uint8_t) (bme280.data.temperature >> 24) & 0xFF);
            data_array[7] = ((uint8_t) (bme280.data.temperature >> 16) & 0xFF);
            data_array[8] = ((uint8_t) (bme280.data.temperature >> 8) & 0xFF);
            data_array[9] = ((uint8_t) (bme280.data.temperature) & 0xFF);
            // Humidity
            data_array[10] = ((uint8_t) (bme280.data.humidity >> 24) & 0xFF);
            data_array[11] = ((uint8_t) (bme280.data.humidity >> 16) & 0xFF);
            data_array[12] = ((uint8_t) (bme280.data.humidity >> 8) & 0xFF);
            data_array[13] = ((uint8_t) (bme280.data.humidity) & 0xFF);
            UART_Debug_PutArray(data_array, PACKET_SIZE);
        }
        else
        {
            UART_Debug_PutString("Error: ");
            switch(error)
            {
                case(BME280_E_DEV_NOT_FOUND):
                    UART_Debug_PutString("BME280_E_DEV_NOT_FOUND\r\n");
                break;
                case(BME280_E_NULL_PTR):
                    UART_Debug_PutString("BME280_E_NULL_PTR\r\n");
                break;
                case(BME280_E_INVALID_LEN):
                    UART_Debug_PutString("BME280_E_INVALID_LEN\r\n");
                break;
                case(BME280_E_COMM_FAIL):
                    UART_Debug_PutString("BME280_E_COMM_FAIL\r\n");
                break;
                case(BME280_E_SLEEP_MODE_FAIL):
                    UART_Debug_PutString("BME280_E_SLEEP_MODE_FAIL\r\n");
                break;
                case(BME280_E_NVM_COPY_FAILED):
                    UART_Debug_PutString("BME280_E_NVM_COPY_FAILED\r\n");
                break;
            }
            BME280_Reset(&bme280);    
        }

    }
}

/* [] END OF FILE */
