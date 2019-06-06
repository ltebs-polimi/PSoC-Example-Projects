/* ========================================
 * Main file for the PSoC 5LP slave device
 * @author Davide Marzorati
 * ========================================
*/
#include "project.h"
#include "stdio.h"

/* Buffer and packet size */
#define PACKET_SIZE          (1UL)

/* Buffer and packet size in the slave */
#define SL_BUFFER_SIZE    (PACKET_SIZE)

uint8_t i2cBuffer[SL_BUFFER_SIZE] = {0};

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Start();
    PWM_1_Start();
    
    // Set up EZI2C
    EZI2C_1_Start();
    EZI2C_1_SetBuffer1(SL_BUFFER_SIZE, SL_BUFFER_SIZE, i2cBuffer);
    
    UART_PutString("** I2C Slave **\r\n");
    for(;;)
    {
    }
}

void EZI2C_1_ISR_EntryCallback(void) 
{
    // Update PWM with received value
    PWM_1_WriteCompare(i2cBuffer[0]);
}

/* [] END OF FILE */
