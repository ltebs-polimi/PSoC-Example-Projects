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

#include "BME280.h"
#include "BME280_I2C_Interface.h"
#include "BME280_RegMap.h"

#define BME280_I2C_ADDRESS 0x76

uint8_t BME280_ReadWhoAmI(void)
{
    uint8_t who_am_i = 0x00;
    I2C_Peripheral_ReadRegister(BME280_I2C_ADDRESS, BME280_WHO_AM_I_REG_ADDR, &who_am_i);
    return who_am_i;
}

void BME280_Reset(void) 
{
    I2C_Peripheral_WriteRegister(BME280_I2C_ADDRESS, BME280_RESET_REG_ADDR, 0xB6);
}

/* [] END OF FILE */
