/* ===========================================================
 * @brief Basic example of LED PWM control with 
 *        a push button.
 *
 * This project demonstrates the possibility to control a LED with 
 * a push button using a PWM. In the main for loop, we check the
 * status of a push button, and according to it we change the 
 * period of the PWM.
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
    
    // We need to start the PWM component
    PWM_1_Start();
    // We store the reference value of the PWM
    uint8_t ref_pwm_compare = PWM_1_ReadCompare();
    
    for(;;)
    {      
        /* Place your application code here. */
       
        // Read the button status
        button_status = Pin_Button_Read();
               
        // Modify duty cycle accordingly
        if (!button_status)
        {
            PWM_1_WriteCompare(ref_pwm_compare/2);
        }
        else
        {
            PWM_1_WriteCompare(ref_pwm_compare);
        }
        
    }
}

/* [] END OF FILE */
