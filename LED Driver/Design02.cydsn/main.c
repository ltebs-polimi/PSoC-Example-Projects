/* ===========================================================
 * @brief Basic example of blinking LED control with 
 *        a push button.
 *
 * This project demonstrates the possibility to control a LED with 
 * a push button using only CPU. In the main for loop, we check the
 * status of the push button, and according to it we change the status
 * of the LED. If the button is pressed, we blink the LED with 
 * a period of 200 ms (DC 50%), otherwise we turn it off.
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
    
    for(;;)
    {
        /* Place your application code here. */
        button_status = Pin_Button_Read();
        
        // If the button is pressed, we blink the LED
        if (!button_status)
        {
            /* We can use the Pin_LED APIs or write directly
               to the port registers */
            //Pin_LED_Write(ON);  -- API
            Pin_LED_DR |= Pin_LED_MASK; // Port Data Register
            CyDelay(100u);
            
            //Pin_LED_Write(OFF);  -- API
            Pin_LED_DR &= ~Pin_LED_MASK; // Port Data Register
            CyDelay(100u);
        }
        // Otherwise, we switch it off
        else
        {
            //Pin_LED_Write(OFF);
            Pin_LED_DR &= ~Pin_LED_MASK;
            CyDelay(1u);
        }
        
    }
}

/* [] END OF FILE */
