/* ========================================
 *
 * @brief HC-SR04 Medium PSoC Project.
 *
 * This project demonstrates the usage of 
 * the HC-SR04 UltraSonic sensor with the 
 * PSoC 5LP.
 *
 * @author Davide Marzorati
 * @date 12/10/2018
 *
 * ========================================
*/
#include "isr.h"
#include "project.h"
#include "stdio.h"

#ifndef HIGH
    #define HIGH 1u
#endif

#ifndef LOW
    #define LOW 0U
#endif

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Init components 
    Timer_HCSR04_Start();
    UART_HC06_Start();
    
    // Call the Custom_ISR_Start function -- defined in isr.c
    Custom_ISR_Start();
    /* Send message over UART */
    UART_HC06_PutString("HC-SR04 Program Started\r\n");
    
    for(;;)
    {
        /* Generate 10uS pulse on Trigger PIN 
            _
        ___| |___________________________________
        
        The rising edge of the trigger pin will reset the counter.
        The rising and falling edge of the echo pin will trigger and
        force a capture of the timer, respectively. The capture event
        will trigger the ISR_HCSR04 defined in the isr.c source file.
        */
        ControlReg_TRIGGER_Write(HIGH);
        CyDelayUs(10);
        ControlReg_TRIGGER_Write(LOW);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
