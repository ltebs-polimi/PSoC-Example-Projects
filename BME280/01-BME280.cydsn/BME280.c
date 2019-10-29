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
#define BME280_SOFT_RESET_COMMAND 0xB6

#define BME280_SLEEP_MODE 0x00
#define BME280_FORCED_MODE 0x01
#define BME280_NORMAL_MODE 0x03


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
static BME280_ErrorCode BME280_SetMode(uint8_t mode);

/**
*   \brief Compensate raw temperature values.
*
*   This function is used to compensate the raw temperature values and convert them
*   in signed 32 bit integers.
*
*   \param[in] uncomp_data: Uncompensated temperature data
*   \param[in] calib_data: Calibration data 
*
*   \return Compensated temperature data.
*   \retval Compensated temperature data as 32 bit signed integer.
*
*/
static int32_t BME280_CompensateTemperature(const BME280_Uncomp_Data *uncomp_data,
                                            BME280_Calib_Data *calib_data);

/**
*   \brief Compensate raw pressure values.
*
*   This function is used to compensate the raw pressure values and convert them
*   in unsigned 32 bit integers.
*
*   \param[in] uncomp_data: Uncompensated pressure data
*   \param[in] calib_data: Calibration data 
*
*   \return Compensated pressure data.
*   \retval Compensated pressure data as 32 bit unsigned integer.
*
*/
static uint32_t BME280_CompensatePressure(const BME280_Uncomp_Data *uncomp_data,
                                          BME280_Calib_Data *calib_data);
/**
*   \brief Compensate raw humidity values.
*
*   This function is used to compensate the raw humidity values and convert them
*   in unsigned 32 bit integers.
*
*   \param[in] uncomp_data: Uncompensated humidity data
*   \param[in] calib_data: Calibration data 
*
*   \return Compensated humidity data.
*   \retval Compensated humidity data as 32 bit unsigned integer.
*
*/
static uint32_t BME280_CompensateHumidity(const BME280_Uncomp_Data *uncomp_data,
                                          BME280_Calib_Data *calib_data);

BME280_ErrorCode BME280_Start(void)
{
    uint8_t try_counts = 5;
    BME280_ErrorCode error;
    uint8_t who_am_i_value = 0x00;
    
    while(try_counts)
    {
        // Check device presence on I2C bus
        error = BME280_ReadWhoAmI(&who_am_i_value);
        if (error == BME280_OK && who_am_i_value == BME280_WHO_AM_I)
        {
            error = BME280_Reset();
            if ( error == BME280_OK)
            {
                // Read calibration data
            }
        }
        
        CyDelay(1);
        --try_counts;
    }
    
    if (!try_counts)
    {
        return BME280_DEVICE_NOT_FOUND;
    }
    
    return BME280_OK;
}
BME280_ErrorCode BME280_ReadWhoAmI(uint8_t* who_am_i)
{
    // Read WHO AM I register 
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_WHO_AM_I_REG_ADDR, who_am_i) == NO_ERROR)
    {
        return BME280_OK;
    }
    
    return BME280_I2C_ERROR;
}

BME280_ErrorCode BME280_Reset(void) 
{
    // Write reset value to sensor reset register
    if(BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_RESET_REG_ADDR, BME280_RESET_BYTE) == NO_ERROR)
    {
        return BME280_OK;
    }
    
    return BME280_I2C_ERROR;
}

BME280_ErrorCode BME280_SetHumidityOversampling(BME280_HumidityOversampling hos)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_HUM_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x07;
        temp_value |= hos;
        // Write new value to ctrl hum register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_HUM_REG_ADDR, temp_value) == NO_ERROR)
        {
            // Read value of control meas register
            if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
            {
                // Write value of control meas register
                if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
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
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, 
            BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0xE0; // Clear bits 7,6,5
        temp_value |= tos << 5;
        // Write new value to ctrl meas register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
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
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x1C;    // Clear bits 4,3,2
        temp_value |= pos << 2;  
        // Write new value to ctrl meas register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetMode(uint8_t mode)
{
    // Check that value is less than or equal to 3
    if (mode > 0x03)
    {
        return BME280_ERROR;
    }
    
    // Read current register value
    uint8_t temp_value = 0x00;
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x03; // Bit 1,0
        temp_value |= mode;
        // Write new value to ctrl meas register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetSleepMode(void)
{
    // Set sleep mode
    return BME280_SetMode(BME280_SLEEP_MODE);
}

BME280_ErrorCode BME280_SetForcedMode(void)
{
    // Set forced mode
   return BME280_SetMode(BME280_FORCED_MODE); 
}

BME280_ErrorCode BME280_SetNormalMode(void)
{
    // Set normal mode
   return BME280_SetMode(BME280_NORMAL_MODE);
}

BME280_ErrorCode BME280_SetStandbyTime(BME280_TStandby tStandby)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0xE0;    // Clear bits 7,6,5
        temp_value |= tStandby << 5;  
        // Write new value to config register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_SetIIRFilter(BME280_Filter filter)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x1C;    // Clear bits 4,3,2
        temp_value |= filter << 2;  
        // Write new value to ctrl hum register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_EnableSPI(void)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x01;    // Clear bit 1
        temp_value |= 0x01;
        // Write new value to ctrl hum register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

BME280_ErrorCode BME280_DisableSPI(void)
{
    // Read current register value
    uint8_t temp_value = 0x00;
    if (BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &temp_value) == NO_ERROR)
    {
        // Set new value of register
        temp_value &= ~0x01;    // Clear bit 1
        temp_value |= 0x00;
        // Write new value to ctrl hum register
        if (BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, temp_value) == NO_ERROR)
        {
            return BME280_OK;
        }
    }
    return BME280_ERROR;
}

/* [] END OF FILE */
