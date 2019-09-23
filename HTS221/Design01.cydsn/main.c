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
#include "project.h"
#include "stdio.h"
#include "HTS221.h"

#include "I2C_Interface.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Debug_Start();
    UART_Debug_PutString("\n\n\n\nHTS221 Start\r\n");
    
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
    
    HTS221_Measurement_Ready meas_ready = HTS221_MEAS_READY;
        
    
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
