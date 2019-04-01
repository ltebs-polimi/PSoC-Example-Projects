/* ========================================
 *
 * @brief HC-SR04 Base PSoC Project.
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
#include "project.h"
#include "stdio.h"

#ifndef HIGH
    #define HIGH 1u
#endif

#ifndef LOW
    #define LOW 0u
#endif

/*
 * @brief Conversion factor (time to distance)
 *
 * This conversion factor is correct if temperature 
 * is 20° C.
 */
#ifndef CONV_FACTOR
    #define CONV_FACTOR 58.25
#endif

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    // Set up variables 
    int timer_count_begin = 0;  // Timer count value @ begin 
    int timer_count_end = 0;    // Timer count value @ end
    int duration = 0;           // Duration of echo 
    char message[50];           // Message to send over UART
    
    // Start components
    Timer_HCSR04_Start();
    UART_HC06_Start();
    
    // Send initial message over UART
    UART_HC06_PutString("HC-SR04 Program Started\r\n");
    
    for(;;)
    {
        /* Generate 10uS pulse on Trigger PIN 
            _
        ___| |___________________________________
        */
        Pin_TRIGGER_Write(HIGH);
        CyDelayUs(10);
        Pin_TRIGGER_Write(LOW);        
        /* Wait until Echo PIN is low */
        while(Pin_ECHO_Read() == LOW);
        /* Read Timer value when Echo PIN becomes HIGH */
        timer_count_begin = Timer_HCSR04_ReadCounter();
        /* Wait until Echo PIN remains high 
                         ______
        ________________|      |_________________
        */
        while(Pin_ECHO_Read());
        /* Read Timer value when Echo PIN becomes LOW */
        timer_count_end = Timer_HCSR04_ReadCounter();
        /* Compute the duration */
        if (timer_count_end > timer_count_begin)
            duration = (Timer_HCSR04_ReadPeriod() + timer_count_begin) - timer_count_end;
        else
            duration = timer_count_begin - timer_count_end;
        /* Prepare the string and send it over the UART */
        sprintf(message, "Duration: %d uS - Distance: %d mm\r\n",
            duration, 
            (int)(duration/CONV_FACTOR*10));
        UART_HC06_PutString(message);
        
        CyDelay(1000);
    }
}

/* [] END OF FILE */
