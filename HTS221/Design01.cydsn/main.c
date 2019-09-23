/*
*   Main file to test the functionality of the HTS221
*   temperature and relative humidity sensor.
*   
*   \author: Davide Marzorati
*   \date: September 23, 2019
*/
#include "project.h"
#include "stdio.h"
#include "HTS221.h"
#include "Logging.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    Logging_Start();
    
    HTS221_Struct hts221;
    char str[300] = {'\0'};
    
    HTS221_Error error = HTS221_Start(&hts221);
    
    if ( error != HTS221_OK)
    {
        sprintf(str, "HTS221 not configured. Error: %d\r\n", error);
        UART_Debug_PutString(str);
    }
    
    else
    {
        // Configure DRDY pin
        HTS221_ConfigureDRDYLevel(&hts221, HTS221_DRDY_ACTIVE_HIGH);
        HTS221_ConfigureDRDYPin(&hts221, HTS221_DRDY_PUSH_PULL);
        HTS221_EnableDRDY(&hts221);
        // Set output data rate
        HTS221_SetOutputDataRate(&hts221, HTS221_ODR_1Hz);
    }
        
    
    Logging_PrintHTS221Configuration(&hts221);
   
    for(;;)
    {
        if (error == HTS221_OK && DRDY_Pin_Read() == 1)
        {
                HTS221_ReadTemperatureHumidity(&hts221);
                sprintf(str, "Temp %d\tHum %d\r\n",
                    hts221.temperature,
                    hts221.humidity);
                UART_Debug_PutString(str);
            
        }
    }
}

/* [] END OF FILE */
