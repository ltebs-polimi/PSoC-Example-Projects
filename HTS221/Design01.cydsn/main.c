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
#include "I2C_Interface.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Debug_Start();
    UART_Debug_PutString("HTS221 Start\r\n");
    I2C_Peripheral_Start();
    
    uint8_t error = 0;
    char debug_string [30] = {'\0'};
    
    for (int address = 0; address < 128; address++)
    {
        if ( I2C_Peripheral_IsDeviceConnected(address) > 0)
        {
            sprintf(debug_string, "Device found @ address 0x%02X\r\n", address >> 1);
            UART_Debug_PutString(debug_string);
        }
    }
    
    uint8_t reg_value;
    error = I2C_Peripheral_ReadRegister(0xBE>>1,0x0F,&reg_value);
    sprintf(debug_string, "WHO AM I: 0x%02X\r\n", reg_value);
    UART_Debug_PutString(debug_string);
    
    error = I2C_Peripheral_ReadRegister(0xBE>>1,0x10,&reg_value);
    sprintf(debug_string, "AV_CONF: 0x%02X\r\n", reg_value);
    UART_Debug_PutString(debug_string);
    
    error = I2C_Peripheral_WriteRegister(0xBE>>1, 0x10, 0b010010); 
    
    error = I2C_Peripheral_ReadRegister(0xBE>>1,0x10,&reg_value);
    sprintf(debug_string, "AV_CONF: 0x%02X\r\n", reg_value);
    UART_Debug_PutString(debug_string);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
