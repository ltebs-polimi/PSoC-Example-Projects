/* ===========================================================
 * @brief Source file for the RGB Led Control Driver.
 *
 * @author: Davide Marzorati
 * @date: 19 March, 2019
 * ===========================================================
*/

#include "PWM_1.h"
#include "PWM_2.h"
#include "RGB_Led_Driver.h"

/**
* @brief Write new red color.
*/
void RGB_Led_WriteRed(uint8_t red);

/**
* @brief Write new green color.
*/
void RGB_Led_WriteGreen(uint8_t green);

/**
* @brief Write new blue color.
*/
void RGB_Led_WriteBlue(uint8_t blue);

void RGB_Led_WriteColor(RGB_Color color) {
    // Write red, green, and blue values.
    RGB_Led_WriteRed(color.R);
    RGB_Led_WriteGreen(color.G);
    RGB_Led_WriteBlue(color.B);
}

void RGB_Led_WriteRed(uint8_t red) {
    // Write new value to PWM 1 compare 1.
    PWM_1_WriteCompare1(red);
}
void RGB_Led_WriteGreen(uint8_t green) {
    // Write new value to PWM 1 compare 2.
    PWM_1_WriteCompare2(green);
}

void RGB_Led_WriteBlue(uint8_t blue) {
    // Write new value to PMW 2 compare.
    PWM_2_WriteCompare(blue);
}



/* [] END OF FILE */
