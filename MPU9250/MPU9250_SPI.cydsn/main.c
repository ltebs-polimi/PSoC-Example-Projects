/* ========================================
 *
 * @brief Main file for MPU9250 project.
 * 
 * This is the main file to be used with the
 * MPU9250 project. It sets up all the 
 * components required for the project.
 * 
 * @author Davide Marzorati
 * @date 29 March, 2019
 * ========================================
*/

// Include required header files
#include "project.h"
//#include "MPU9250.h"
#include "stdio.h"

#define READ_FLAG 0x80
CY_ISR_PROTO(MPU9250_DR_ISR);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start UART component
    UART_1_Start();
    
    UART_1_PutString("***************\r\n");
    UART_1_PutString("     MPU9250   \r\n");
    UART_1_PutString(" SPI INTERFACE \r\n");
    UART_1_PutString("***************\r\n");
    
    // Start SPI component
    SPIM_1_Start();
    
    CyDelay(1000);
    
    char message[30];       // Message to send over UART
    uint8_t connection = 0; // Variable to store connection status
    
    // Read MPU9250 Who Am I Register
    MPU9250_CS_Write(0);
    SPIM_1_WriteTxData(READ_FLAG | 0x75);
    while( 0!= (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
    SPIM_1_WriteTxData(0xFF);
    while( 0!= (SPIM_1_ReadTxStatus() & SPIM_1_STS_SPI_DONE));
    uint8_t who_am_i = SPIM_1_ReadRxData();
    sprintf(message, "WHO AM I: %d\r\n", who_am_i);
    UART_1_PutString(message);
    MPU9250_CS_Write(1);
    
    /*
    // Wait until MPU9250 is connected
    do {
        connection = MPU9250_IsConnected();
    } while (connection == 0);
    
    // Show connection status feedback
    Connection_Led_Write(1);
    
    // Star the MPU9250
    MPU9250_Start();
    MPU9250_SetAccFS(MPU9250_Acc_FS_2g);

    // Read WHO AM I register and compare with the expected value
    uint8_t whoami = MPU9250_ReadWhoAmI();
    sprintf(message, "WHO AM I: 0x%02x - Expected: 0x%02x\r\n", whoami, MPU9250_WHO_AM_I);
    UART_1_PutString(message);
    
    MPU9250_ISR_StartEx(MPU9250_DR_ISR);*/
    
    for(;;)
    {
    }
}

CY_ISR(MPU9250_DR_ISR) {
    // prepare packet
    static uint8_t data[14];
    // header
    data[0] = 0xA0;
    // footer
    data[13] = 0xC0;
    // read data
    MPU9250_ReadAccGyroRaw(&data[1]);
    // send packet over uart
    UART_1_PutArray(data,14);
    MPU9250_ReadInterruptStatus();
}

/* [] END OF FILE */
