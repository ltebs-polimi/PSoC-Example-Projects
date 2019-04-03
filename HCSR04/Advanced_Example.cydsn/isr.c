/**
 * @brief Source file for ISR functions.
 * 
 * This source file contains some function declaration
 * to be used with the ISR component.
 * 
 * @author Davide Marzorati
 * @date March 28, 2019
 */

#include "isr.h"
#include "stdio.h"
#include "UART_HC06.h"
#include "Timer_HCSR04.h"
#include "ISR_HCSR04.h"

/**
* @brief Conversion factor from time to cm.
*/
#ifndef CONV_FACTOR
    #define CONV_FACTOR 58.25
#endif

/**
* @brief Conversion factor from cm to mm.
*/
#ifndef TO_MM
    #define TO_MM 10.00
#endif

// Message to send over UART
char message[30];
// Timer period value
int timer_period;


void Custom_ISR_Start(void) {
    // Store the value of the timer
    timer_period = Timer_HCSR04_ReadPeriod();
    // Start the ISR component
    ISR_HCSR04_StartEx(ISR_ULTRASONIC); 
}

CY_ISR(ISR_ULTRASONIC){
    // Compute distance and send it over uart
    sprintf(message, "Distance: %d mm\r\n",
        (int)((timer_period - Timer_HCSR04_ReadCapture())/CONV_FACTOR*TO_MM));
    UART_HC06_PutString(message);
}
/* [] END OF FILE */
