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

#include "BME280.h"
#include "BME280_I2C_Interface.h"
#include "project.h"
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    I2C_Master_Start();
    UART_Debug_Start();
    
    UART_Debug_PutString("************************\r\n");
    UART_Debug_PutString("          BME280        \r\n");
    UART_Debug_PutString("************************\r\n");
    
    char message[50];
    
    for (int i = 0; i < 128; i++)
    {
        if ( I2C_Peripheral_IsDeviceConnected(i))
        {
            sprintf(message, "Device 0x%02X connected\r\n", i);
            UART_Debug_PutString(message);
        }
        I2C_Master_MasterSendStop();
        
    }
    
    uint8_t who_am_i_val = BME280_ReadWhoAmI();
    sprintf(message, "Who Am I Value: 0x%02X\r\n", who_am_i_val);
    UART_Debug_PutString(message);
    
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
