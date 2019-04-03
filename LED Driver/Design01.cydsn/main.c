/* ===========================================================
 * @brief Basic example of LED control with 
 *        a push button.
 *
 * This project demonstrates the possibility to control a LED with 
 * a push button using only CPU. In the main for loop, we check the
 * status of the push button, and according to it we change the status
 * of the LED.
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

int main(void)
{   
    
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    // Set up a variable to store the status of the button
    uint8_t button_status = 0;
    
    // Light up the LED for 1 second, then turn it off
    Pin_LED_Write(ON);
    CyDelay(1000u);
    Pin_LED_Write(OFF);
        
    for(;;)
    {
        /*  Read the status of the push button. 
            Pin_Button_Read will return 1 if pin is HIGH, 0 otherwise. */
        button_status = Pin_Button_Read();
        
        /* If the button is high (not pressed since we're in pull down) 
           we turn off the LED */
        if (button_status)
        {
            Pin_LED_Write(OFF);
        }
        // If the button is low (pressed), then we turn on the LED
        else
        {
            Pin_LED_Write(ON);
        }
        
    }
}

/* [] END OF FILE */
