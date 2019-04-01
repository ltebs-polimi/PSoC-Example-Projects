/**
 * @file isr.h
 * @brief Header file for ISR functions.
 * 
 * This header file contains some function definitions
 * to be used with the ISR component.
 * 
 * @author Davide Marzorati
 * @date March 28, 2019
 */

#ifndef ISR_H
    #define ISR_H

    #include "cytypes.h"
    
    /**
    * @brief Start the ISR component.
    *
    * This function starts the ISR component and stores
    * the period of the timer to be used when converting
    * time to distance.
    *
    * @return Nothing
    */
    void Custom_ISR_Start(void);
    
    /**
    * @brief ISR routine.
    *
    * This ISR is used to compute the distance starting
    * from a measurement of time.
    */
    CY_ISR_PROTO(ISR_ULTRASONIC);

#endif

/* [] END OF FILE */
