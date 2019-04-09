/* 
* @brief EEPROM Program main file.
*
* This project shows the basic usage of the EEPROM
* component of the PSoC 5LP microcontroller.
*
* @author Davide Marzorati
* @date April 9, 2019
*/
#include "project.h"
#include "stdio.h"

/**
* @brief Base address of EEPROM memory location
*/
#define EEPROM_BASE_ADDRESS CYDEV_EE_BASE

/**
* @brief Base address of EEPROM remapped
*
* This is the base address to be used with the EEPROM component API.
*/
#define EEPROM_BASE_ADDRESS_REMAPPED 0x00

/**
* @brief New value to be written to EEPROM
*/
#define NEW_VALUE 0x98

// Some constant strings to be shown over UART
const char* WELCOME_STRING = {"\r\n** EEPROM PROGRAM **\r\n"};
const char* READ_STRING = {"Reading operation\r\n"};
const char* WRITE_STRING = {"Writing operation\r\n"};
const char* SUCCESS_STRING = {"Writing successfull\r\n"};
const char* BAD_PARAM_ERROR = {"Bad parameter error\r\n"};
const char* LOCKED_ERROR = {"SPC locked\r\n"};
const char* UNKNOWN_ERROR = {"Unknown error\r\n"};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    char msg[30] = {'\0'};
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    UART_PutString(WELCOME_STRING);
    
    // Reading operation using EEPROM Component 
    UART_PutString(READ_STRING);
    EEPROM_Start();
    EEPROM_UpdateTemperature();
    
    uint8_t read = EEPROM_ReadByte(EEPROM_BASE_ADDRESS_REMAPPED);
    sprintf(msg, "Byte value: 0x%02X\r\n", read);
    UART_PutString(msg);
    
    // Using memory address
    uint8_t read_pointer = (*((uint8*)EEPROM_BASE_ADDRESS));
    sprintf(msg, "Byte value: 0x%02X\r\n", read_pointer);
    UART_PutString(msg);
    
    // Write new value to it
    UART_PutString(WRITE_STRING);
    cystatus return_value = EEPROM_WriteByte(NEW_VALUE,EEPROM_BASE_ADDRESS_REMAPPED);
    switch(return_value) {
        case CYRET_SUCCESS:
            UART_PutString(SUCCESS_STRING);
            break;
        case CYRET_BAD_PARAM:
            UART_PutString(BAD_PARAM_ERROR);
            break;
        case CYRET_LOCKED:
            UART_PutString(LOCKED_ERROR);
            break;
        case CYRET_UNKNOWN:
            UART_PutString(UNKNOWN_ERROR);
            break;
    }
    
    // Using EEPROM Component
    UART_PutString(READ_STRING);
    read = EEPROM_ReadByte(EEPROM_BASE_ADDRESS_REMAPPED);
    sprintf(msg, "Byte value: 0x%02X\r\n", read);
    UART_PutString(msg);
    
    // Using memory address
    sprintf(msg, "Byte value: 0x%02X\r\n", read_pointer);
    UART_PutString(msg);
    
    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
