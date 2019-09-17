/*
*
*   This source file contains the function definitions
*   required in order to set up a working HTS221 
*   temperature and humidity sensor.
*   
*/

#include "HTS221.h"
#include "I2C_Interface.h"



ErrorCode HTS221_ReadWhoAmI(HTS221_Struct* hts221, uint8_t* reg_val)
{
    (hts221);
    return I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                        HTS221_WHO_AM_I_REG,
                                        reg_val);
}

/* [] END OF FILE */
