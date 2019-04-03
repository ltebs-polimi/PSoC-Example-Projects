/* ===========================================================
 * @file RGB_Led_Driver.h
 * @brief RGB Led Control Driver.
 *
 * @author: Davide Marzorati
 * @date: 19 March, 2019
 * ===========================================================
*/

#ifndef __RGB_LED_DRIVER_H
    #define __RGB_LED_DRIVER_H
    
    #include "cytypes.h"
    
    /**
     * @brief RGB Color struct.
     * 
     * This struct allows to store a RGB color (red, green, and blue)
     * in the same place.
    */
    typedef struct {
        uint8_t R; /** Red color */
        uint8_t G; /** Green color */
        uint8_t B; /** Blue color */
    } RGB_Color;
    
    /**
    * @brief Write new RGB Color.
    */
    void RGB_Led_WriteColor(RGB_Color color);
    
    
    #endif

/* [] END OF FILE */
