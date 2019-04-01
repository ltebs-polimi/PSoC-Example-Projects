/*
 *
 * @brief HC-SR04 Advanced PSoC Project.
 *
 * This project demonstrates the usage of 
 * the HC-SR04 UltraSonic sensor with the 
 * PSoC 5LP.
 *
 * @author Davide Marzorati
 * @date 12/10/2018
 *
*/
#include "isr.h"
#include "project.h"
#include "stdio.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Init components */
    Timer_HCSR04_Start();
    PWM_Trigger_Start();
    Timer_TRIGGER_Start();
    UART_HC06_Start();
    Custom_ISR_Start();
    
    /* Send message over UART */
    UART_HC06_PutString("HC-SR04 Program Started\r\n");
    
    for(;;)
    {

    }
}

/* [] END OF FILE */
