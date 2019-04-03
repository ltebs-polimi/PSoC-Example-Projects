/* ===========================================================
 * @brief RGB Led Control.
 *
 * This project demonstrates the possibility to control an RGB 
 * LED with two PWMs.
 *
 * @author: Davide Marzorati
 * @date: 19 March, 2019
 * ===========================================================
*/
#include "project.h"
#include "RGB_Led_Driver.h"
/**
* @brief Simple define for status ON
*/
#define ON  1u

/**
* @brief Simple define for status OFF
*/
#define OFF 0u

/**
* @brief Number of colors to show
*/
#define COLORS 9

int main(void)
{
    
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // Start the PWM Components
    PWM_1_Start();
    PWM_2_Start();
    
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    // Let's define some colors -- We could have defined these as constants
    RGB_Color red     = {255,  0,  0};
    RGB_Color lime    = {  0,255,  0};
    RGB_Color blue    = {  0,  0,255};
    RGB_Color yellow  = {255,255,  0};
    RGB_Color cyan    = {  0,255,255};
    RGB_Color magenta = {255,  0,255};
    RGB_Color white   = {255,255,255};
    RGB_Color olive   = {128,128,128};
    RGB_Color teal    = {  0,128,128};
    
    // Set up an array of colors
    RGB_Color colors[] = {red,
                                lime,
                                blue,
                                yellow, 
                                cyan,
                                magenta,
                                white,
                                olive,
                                teal};
    
    for(;;)
    {
        // Let's show some colors
        for (int i = 0 ; i < COLORS; i++) {
            RGB_Led_WriteColor(colors[i]);   
            CyDelay(1000u);
        }
        
    }
}

/* [] END OF FILE */
