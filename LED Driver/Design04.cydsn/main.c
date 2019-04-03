/* ===========================================================
 * @brief Basic example of LED controlled with an ISR triggered
 *        by a timer.
 *
 * This project demonstrates the possibility to control a LED with 
 * an ISR triggered by a timer. In the main for loop, we check the
 * status of a push button, and according to it we change the 
 * period of the timer. In the isr_1.c we toggle the status of a flag,
 * that is then checked in the infinite for loop.
 *
 * @author: Davide Marzorati
 * @date: 19 March, 2019
 * ===========================================================
*/
#include "project.h"
/**
* @brief Simple define for status ON
*/
#define ON  1u

/**
* @brief Simple define for status OFF
*/
#define OFF 0u

// Flag used to determine if the LED should be ON or OFF
uint8 LED_Flag = 0;

int main(void)
{   
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    // Period of the timer
    uint8_t timer_period = 0;
    
    // Button status
    uint8_t button_status = 0;
    
    // Start the timer component
    Timer_1_Start();
    
    // Start the ISR component
    isr_1_Start();
 
    // Set up the timer_period by reading the period of the timer
    timer_period = Timer_1_ReadPeriod();
    
    for(;;)
    {
        // Read the status of the button
        button_status = Pin_Button_Read();
      
        // If the button was pressed, we change the period of the timer
        // to 250 (that means 2.5 seconds)
        if (!button_status) 
        {
            Timer_1_WritePeriod(250u);
        }
        // Otherwise we reset the original value of 100 (1 second)
        else
        {
           Timer_1_WritePeriod(timer_period);
        }
            
        // According to the value of flag we turn ON/OFF the LED 
        // The value of flag is set in the ISR routine 
        if (LED_Flag)
        {
            Pin_LED_Write(ON);
        }
        else 
        {
           Pin_LED_Write(OFF);
        }
    }
}

/* [] END OF FILE */
