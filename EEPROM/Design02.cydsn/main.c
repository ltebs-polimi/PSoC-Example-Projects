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

/**
* @brief Length of the string that we need to read
*/
#define STRING_LENGTH 12

/**
*  @brief Offset from base address
*/
#define EEPROM_OFFSET 0x54

/**
* @brief Base address of EEPROM memory location
*/
#define EEPROM_BASE_ADDRESS CYDEV_EE_BASE + EEPROM_OFFSET

/**
* @brief Base address of EEPROM remapped
*
* This is the base address to be used with the EEPROM component API.
*/
#define EEPROM_BASE_ADDRESS_REMAPPED 0x00 + EEPROM_OFFSET


// Some constant strings to be shown over UART
const char* WELCOME_STRING = {"\r\n** EEPROM PROGRAM **\r\n"};
const char* READ_STRING = {"Reading operation\r\n"};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    UART_PutString(WELCOME_STRING);
    
    // Reading operation using EEPROM Component 
    UART_PutString(READ_STRING);
    EEPROM_Start();
    
    for (int i = 0 ; i < STRING_LENGTH; i++) {
        // Read the byte
        uint8_t read = EEPROM_ReadByte(EEPROM_BASE_ADDRESS_REMAPPED + i);
        // If it is the last char, add CR and LF 
        if ( i == STRING_LENGTH - 1)
            UART_PutCRLF(read);
        // Otherwise send the char without CR and LF
        else
            UART_PutChar(read);
    }

    for(;;)
    {
        /* Place your application code here. */
    }
}

/* [] END OF FILE */
