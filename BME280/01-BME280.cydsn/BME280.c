/**
*   Source file for the BME280 library.
*
*   \author Davide Marzorati
*   \date October 25, 2019
*/

#include "BME280.h"
#include "BME280_I2C_Interface.h"
#include "BME280_RegMap.h"

/******************************************/
/*               Macros                   */
/******************************************/

/**
*   \brief I2C Address of the BME280 sensor.
*/
#define BME280_I2C_ADDRESS 0x76

/**
*   \brief Byte to write on the reset register.
*/
#define BME280_RESET_BYTE 0xB6

/******************************************/
/*               Typedefs                 */
/******************************************/
/**
    *   \brief Sensor modes.
    *
    *   This enum contains all the possible values of sensor modes.
    */
typedef enum {
        BME280_SLEEP_MODE,      ///< Sleep mode
        BME280_FORCED_MODE,     ///< Forced mode
        BME280_NORMAL_MODE,     ///< Normal mode
    } BME280_Mode;

/******************************************/
/*          Function Prototypes           */
/******************************************/
/**
    *   \brief Set current mode of the device.
    *
    *   This function sets the current mode of the device (sleep, forced, normal)
    *   by setting the appropriate bits in the #BME280_CTRL_MEAS_REG_ADDR register. 
    *
    *   \param mode new value of #BME280_Mode
    */
    BME280_ErrorCode BME280_SetMode(BME280_Mode mode);


BME280_ErrorCode BME280_Start(void)
{
    // Check device presence on I2C bus
    if (I2C_Interface_IsDeviceConnected(BME280_I2C_ADDRESS) == 0)
    {
        return BME280_ERROR;
    }
    
    // Reset sensor and check if ok
    if (BME280_Reset() != BME280_OK)
    {
        return BME280_ERROR;
    }
    
    // Read WHO AM I register
    uint8_t who_am_i_value = 0x00;
    if (BME280_ReadWhoAmI(&who_am_i_value) == BME280_OK)
    {
        if ( who_am_i_value != BME280_WHO_AM_I)
        {
            return BME280_ERROR;
        }
    }
    else
    {
        return BME280_ERROR;
    }
    
    return BME280_OK;
}
BME280_ErrorCode BME280_ReadWhoAmI(uint8_t* who_am_i)
{
    // Read WHO AM I register 
    if (I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_WHO_AM_I_REG_ADDR, who_am_i) == NO_ERROR)
    {
        return BME280_OK;
    }
    
    return BME280_I2C_ERROR;
}

BME280_ErrorCode BME280_Reset(void) 
{
    // Write reset value to sensor reset register
    if(I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_RESET_REG_ADDR, BME280_RESET_BYTE) == NO_ERROR)
    {
        return BME280_OK;
    }
    
    return BME280_I2C_ERROR;
}

BME280_ErrorCode BME280_SetHumidityOversampling(BME280_HumidityOversampling hos)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_HUM_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x07;
        temp_value |= hos;
        // Write new value to ctrl hum register
        if (I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_HUM_REG_ADDR, temp_value) == NO_ERROR)
        {
            // Read value of control meas register
            if (I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
            {
                // Write value of control meas register
                if (I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
                {
                    return BME280_OK;
                }
            }
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetTemperatureOversampling(BME280_TemperatureOversampling tos)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0xE0; // Bit 7,6,5
        temp_value |= tos;
        // Write new value to ctrl hum register
        if (I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetPressureOversampling(BME280_PressureOversampling pos)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x1C; // Bit 4,3,2
        temp_value |= pos;
        // Write new value to ctrl hum register
        if (I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetMode(BME280_Mode mode)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x03; // Bit 1,0
        temp_value |= mode;
        // Write new value to ctrl hum register
        if (I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetSleepMode(void)
{
    BME280_SetMode(
}

BME280_ErrorCode BME280_SetForcedMode(void)
{
    
}

BME280_ErrorCode BME280_SetNormalMode(void)
{
    
}

/* [] END OF FILE */
