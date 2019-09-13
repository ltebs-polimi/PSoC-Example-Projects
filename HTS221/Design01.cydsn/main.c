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
    sprintf(debug_string, "WHO AM I: 0x%02X (True: 0x%02X)\r\n", reg_value, 0xBC);
    UART_Debug_PutString(debug_string);
    
    error = I2C_Peripheral_ReadRegister(0xBE>>1,0x10,&reg_value);
    sprintf(debug_string, "AV_CONF: 0x%02X\r\n", reg_value);
    UART_Debug_PutString(debug_string);
    
    uint8_t value_written = 0b010010;
    error = I2C_Peripheral_WriteRegister(0xBE>>1, 0x10, value_written ); 
    
    error = I2C_Peripheral_ReadRegister(0xBE>>1,0x10,&reg_value);
    sprintf(debug_string, "AV_CONF: 0x%02X (True: 0x%02X)\r\n", reg_value, value_written);
    UART_Debug_PutString(debug_string);
    
    // power up the device
    UART_Debug_PutString("Powering up the device\r\n");
    uint8_t read_value;
    error = I2C_Peripheral_ReadRegister(0xBE>>1, 0x20, &read_value); 
    // Set power up bit to 1
    read_value |= 0x80;
    error = I2C_Peripheral_WriteRegister(0xBE>>1, 0x20, read_value); 
    
    // Read data
    uint8_t data[4] = {1,1,1,1};
    error = I2C_Peripheral_ReadRegisterMulti(0xBE>>1, 0x28, 4, data);
    sprintf(debug_string, "{0x%02X, 0x%02X, 0x%02X, 0x%02X}\r\n", 
        data[0],data[1],data[2],data[3]);
    UART_Debug_PutString(debug_string);
    
    // Start one shot measurement
    error = I2C_Peripheral_ReadRegister(0xBE>>1, 0x21, &read_value); 
    // Set power up bit to 1
    read_value |= 0x01;
    error = I2C_Peripheral_WriteRegister(0xBE>>1, 0x21, read_value); 
    
    // Wait until new data is available
    uint8_t data_available = 0;
    while (data_available == 0)
    {
        I2C_Peripheral_ReadRegister(0xBE>>1, 0x27, &read_value);
        if ( (read_value & 0x03) == 0x03)
        {
            data_available = 1;
        }
    }

    // Read data again
    error = I2C_Peripheral_ReadRegisterMulti(0xBE>>1, 0x30, 4, data);
    sprintf(debug_string, "{0x%02X, 0x%02X, 0x%02X, 0x%02X}\r\n", 
        data[0],data[1],data[2],data[3]);
    UART_Debug_PutString(debug_string);
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
