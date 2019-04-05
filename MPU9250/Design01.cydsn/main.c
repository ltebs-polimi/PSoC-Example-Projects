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
    char message[30];
    UART_1_Start();

    UART_1_PutString("**************\r\n");
    UART_1_PutString("    MPU9250   \r\n");
    UART_1_PutString("**************\r\n");
    
    
    I2C_MPU9250_Master_Start();
    
    CyDelay(1000);
    
    for (int address = 0; address < 128; address++) {
        if (I2C_MPU9250_Master_MasterSendStart(address, 0) == I2C_MPU9250_Master_MSTR_NO_ERROR) {
            sprintf(message, "Found device at: 0x%02x\r\n", address);
            UART_1_PutString(message);
        }
        I2C_MPU9250_Master_MasterSendStop();
    }
    
    MPU9250_Start();
    
    uint8_t connection = MPU9250_IsConnected();
    if (connection == 0) {
        UART_1_PutString("MPU9250 is not connected\r\n");   
        Connection_Led_Write(0);
    }
    else {
        UART_1_PutString("MPU9250 is connected\r\n"); 
        Connection_Led_Write(1);
    }

    uint8_t whoami = MPU9250_ReadWhoAmI();
    sprintf(message, "WHO AM I: 0x%02x\r\n", whoami);
    UART_1_PutString(message);
    
    float deviation[6];
    MPU9250_SelfTest(deviation);
    sprintf(message, "Deviation: %5d %5d %5d %5d %5d %5d\r\n", (int)(deviation[0]*100)
                                        , ((int)deviation[1]*100)
                                        , ((int)deviation[2]*100)
                                        , ((int)deviation[3]*100)
                                        , ((int)deviation[4]*100)
                                        , ((int)deviation[5]*100));
    UART_1_PutString(message);
    
    int16_t acc[3];
    int16_t gyro[3];
    
    MPU9250_ReadAccelerometerOffset(acc);
    sprintf(message, "Offset: %5d %5d %5d\r\n", acc[0]
                                        , acc[1]
                                        , acc[2]);
    UART_1_PutString(message);
    
    MPU9250_SetAccFS(MPU9250_Acc_FS_2g);
    
    for(;;)
    {
        /* Place your application code here. */
        MPU9250_ReadAccGyro(acc, gyro);
        sprintf(message, "%5d %5d %5d\t", acc[0]
                                        , acc[1]
                                        , acc[2]);
        UART_1_PutString(message);
        
        sprintf(message, "%5d %5d %5d\r\n", gyro[0], gyro[1], gyro[2]);
        UART_1_PutString(message);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
