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
    UART_Debug_PutString("HTS221 Start\r\n");
    I2C_Peripheral_Start();
    
    HTS221_Struct hts221;
    uint8_t who_am_i = 0;
    char str[10] = {'\0'};
    
    HTS221_ReadWhoAmI(&hts221, &who_am_i);
    sprintf(str, "0x%02X [0x%02X]\r\n", who_am_i, HTS221_WHO_AM_I);
    UART_Debug_PutString(str);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
