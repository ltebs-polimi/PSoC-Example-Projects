/*
*
*   This source file contains the function definitions
*   required in order to set up a working HTS221 
*   temperature and humidity sensor.
*   
*/

#include "HTS221.h"
#include "I2C_Interface.h"

HTS221_Error HTS221_PowerUp(HTS221_Struct *hts221);

HTS221_Error HTS221_Start(HTS221_Struct* hts221) 
{
    ErrorCode genericError;
    // Start I2C peripheral
    I2C_Peripheral_Start();
    
    // Set up hts221 struct
    hts221->measReady = HTS221_MEAS_NOT_READY;
    hts221->heater = HTS221_HEATER_OFF;
    hts221->power  = HTS221_POWER_OFF;
    
    // Read WHO AM I to check if everything is ok
    uint8_t temp;
    genericError = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                                HTS221_WHO_AM_I_REG,
                                                &temp);
    if( ( genericError != NO_ERROR ) || temp != HTS221_WHO_AM_I)
    {
        return HTS221_ERROR;
    }
    
    // Power up the device
    if (HTS221_PowerUp(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    // Set default resolution for temperature
    if (HTS221_SetTemperatureResolution(hts221, HTS221_AVGT_8) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Set default resolution for humidity
    if (HTS221_SetHumidityResolution(hts221, HTS221_AVGH_8) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Set output data rate
    
    // Set data ready signal
    
    // Stop heater
    
    // Read calibration coefficients
    
    if (HTS221_ReadCalibrationCoefficients(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    return HTS221_OK;
}

HTS221_Error HTS221_ReadTemperature(HTS221_Struct* hts221)
{

    // Read raw temperature values
    uint8_t temp_array[2];
    ErrorCode error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_TEMP_OUT_L_REG,
                                        2,
                                        temp_array);   
    
    // Convert temperature 
    int32_t tmp32 = 0;
    int16_t rawTemp = (((uint16_t) temp_array [1]) << 8) | ((uint16_t) temp_array[0]);
    tmp32 = ((int32_t) rawTemp - hts221->coeff.T0_OUT) * ((int32_t)(hts221->coeff.T1_degC - hts221->coeff.T0_degC) * 10);
    hts221->temperature = tmp32 / (hts221->coeff.T1_OUT - hts221->coeff.T0_OUT) + hts221->coeff.T0_degC * 10;

        
    if ( error != NO_ERROR)
        return HTS221_ERROR;
    
    return HTS221_OK;
}

HTS221_Error HTS221_ReadHumidity(HTS221_Struct* hts221)
{

    // Read raw humidity values
    uint8_t temp_array[2];
    ErrorCode error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_HUMIDITY_OUT_L_REG,
                                        2,
                                        temp_array);   
    
    // Convert humidity 
    int32_t tmp32 = 0;
    int16_t rawHum = (((uint16_t) temp_array [1]) << 8) | ((uint16_t) temp_array[0]);
    tmp32 = ((int32_t) rawHum - hts221->coeff.H0_T0_OUT) * ((int32_t)(hts221->coeff.H1_rH - hts221->coeff.H0_rH) * 10);
    hts221->humidity = tmp32 / (hts221->coeff.H1_T0_OUT - hts221->coeff.H0_T0_OUT) + hts221->coeff.H0_rH * 10;
    
    if (hts221->humidity > 1000)
        hts221->humidity = 1000;
        
    if ( error != NO_ERROR)
        return HTS221_ERROR;
    
    return HTS221_OK;
}

HTS221_Error HTS221_SetTemperatureResolution(HTS221_Struct* hts221, 
                                            HTS221_AVGTemperature avgTemp)
{
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_AV_CONF_REG,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_AV_CONF_REG,
                                    temp | (avgTemp << 3));
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    hts221->avgTemp = avgTemp;
    return HTS221_OK;
}

HTS221_Error HTS221_SetHumidityResolution(HTS221_Struct* hts221, 
                                            HTS221_AVGHumidity avgHum)
{
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_AV_CONF_REG,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_AV_CONF_REG,
                                    temp | (avgHum & 0x07 ) );
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    hts221->avgHum = avgHum;
    return HTS221_OK;
}

HTS221_Error HTS221_OneShot(void) 
{
    // Set bit 0 in CTRL_REG2
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 0 set
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    temp | 0x01);
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}

HTS221_Error HTS221_IsMeasurementReady(HTS221_Struct* hts221)
{
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                                    HTS221_STATUS_REG,
                                                    &temp);
    if ( ( temp & 0x01 )  == 0x01 )
    {
        hts221->measReady = HTS221_MEAS_READY;
    }
    else
    {
        hts221->measReady = HTS221_MEAS_NOT_READY;
    }
    if ( error != NO_ERROR)
        return HTS221_ERROR;
    
    return HTS221_OK;
}

HTS221_Error HTS221_ReadWhoAmI(HTS221_Struct* hts221, uint8_t* reg_val)
{
    (hts221);
    // Read who am i register
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                        HTS221_WHO_AM_I_REG,
                                        reg_val);
    if ( error != NO_ERROR)
        return HTS221_ERROR;
    
    return HTS221_OK;
}

HTS221_Error HTS221_ReadCalibrationCoefficients(HTS221_Struct* hts221) {
    uint8_t temp_val;
    uint8_t temp_array[2];
    // Read all the calibration registers and store them in the struct
    ErrorCode error;
    // H0_rH_x2
    error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                        HTS221_H0_rH_x2_REG,
                                        &temp_val);
    hts221->coeff.H0_rH = temp_val >> 1;
    
    // H1_rH_x2
    error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                        HTS221_H1_rH_x2_REG,
                                        &temp_val);
    hts221->coeff.H1_rH = temp_val >> 1;
    
    // T1/T0 msb
    error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                        HTS221_T1_T0_MSB_REG,
                                        &temp_val);
    
    // T0_degC_x8 and T1_degC_x8
    error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_T0_degC_x8_REG,
                                        2,
                                        temp_array);
    
    
    hts221->coeff.T0_degC = (((uint16_t) temp_val & 0x03) << 8) | ((uint16_t)temp_array[0]);
    hts221->coeff.T1_degC = (((uint16_t) temp_val & 0x0C) << 6) | ((uint16_t)temp_array[1]);
    hts221->coeff.T0_degC = hts221->coeff.T0_degC >> 3;
    hts221->coeff.T1_degC = hts221->coeff.T1_degC >> 3;
    
    
    // H0_T0_OUT
    error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_H0_T0_OUT_L_REG,
                                        2,
                                        temp_array);
    // Signed 16 bit with 2's complement format
    hts221->coeff.H0_T0_OUT = (((uint16_t)temp_array[1]) << 8) | ((uint16_t) temp_array[0]);
    
    // H1_T0_OUT
    error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_H1_T0_OUT_L_REG,
                                        2,
                                        temp_array);
    // Signed 16 bit with 2's complement format
    hts221->coeff.H1_T0_OUT = (((uint16_t)temp_array[1]) << 8) | ((uint16_t)temp_array[0]);
    
    // T0_OUT
    error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_T0_OUT_L_REG,
                                        2,
                                        temp_array);
    // Signed 16 bit with 2's complement format
    hts221->coeff.T0_OUT = (((uint16_t) temp_array[1]) << 8) | ((uint16_t)temp_array[0]);
    
    // T1_OUT
    error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_T1_OUT_L_REG,
                                        2,
                                        temp_array);
    // Signed 16 bit with 2's complement format
    hts221->coeff.T1_OUT = (((uint16_t) temp_array[1]) << 8) | ((uint16_t) temp_array[0]);
    
    if ( error != NO_ERROR)
        return HTS221_ERROR;
    
    return HTS221_OK;
}

HTS221_Error HTS221_PowerUp(HTS221_Struct *hts221) 
{
    // Set bit 7 of CTRL_REG_1 to power up the device
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 7 set
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    temp | 0x80);
    hts221->power = HTS221_POWER_ON;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
    
}

/* [] END OF FILE */
