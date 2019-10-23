
/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef __BME280_H_
    #define __BME280_H_

    #include "cytypes.h"
    #include "ErrorCodes.h"
    
    /**
    *   \brief Read Who Am I register value.
    *
    *   This function reads the value of the Who Am I register.
    *   If everything is set up correctly, you should read 0x60
    *   from it.
    */
    uint8_t BME280_ReadWhoAmI(void);
    
    /**
    *   \brief Reset the sensor.
    *
    *   This function reset the sensor by writing a 0xB6 value to the 
    *   reset register. The reset is performed using the complete
    *   power-on reset procedure. 
    */
    void BME280_Reset(void);
    
#endif


/* [] END OF FILE */
