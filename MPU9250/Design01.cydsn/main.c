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
#include "MPU9250.h"
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    MPU9250_Start();
    UART_1_Start();
    CyDelay(1000);
    char message[30];
    
    UART_1_PutString("**************\r\n");
    UART_1_PutString("    MPU9250   \r\n");
    UART_1_PutString("**************\r\n");
    
    uint8_t connection = MPU9250_IsConnected();
    if (connection == 0) {
        UART_1_PutString("MPU9250 is not connected\r\n");   
    }
    else {
        UART_1_PutString("MPU9250 is connected\r\n"); 
        Connection_Led_Write(1);
    }

    uint8_t whoami = MPU9250_ReadWhoAmI();
    sprintf(message, "WHO AM I: %d\r\n", whoami);
    UART_1_PutString(message);
    
    //float deviation[6];
    //MPU9250_SelfTest(deviation);
    
    int16_t acc[3];
    int16_t gyro[3];
    
    MPU9250_SetAccFS(MPU9250_Acc_FS_2g);
    
    for(;;)
    {
        /* Place your application code here. */
        MPU9250_ReadAccGyro(acc, gyro);
        sprintf(message, "%5d %5d %5d\t", (int)(acc[0]*9.8*2/65535/2*100)
                                        , (int)(acc[1]*9.8*2/65535/2*100)
                                        , (int)(acc[2]*9.8*2/65535/2*100));
        UART_1_PutString(message);
        
        sprintf(message, "%5d %5d %5d\r\n", gyro[0], gyro[1], gyro[2]);
        UART_1_PutString(message);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
