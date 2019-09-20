/*
*
*   This source file contains the function definitions
*   required in order to set up a working HTS221 
*   temperature and humidity sensor.
*   
*/

#include "HTS221.h"
#include "I2C_Interface.h"

/**
*   \brief Power up the sensor.
*
*   This function powers up the HTS221 sensor by setting the 
*   appropriate bit in the control registers.
*   \param hts221 a valid pointer to a ::HTS221_Struct
*   \return ::HTS221_Error depending on generated error
*/
static HTS221_Error HTS221_PowerUp(HTS221_Struct *hts221);

/**
*   \brief Power down the sensor.
*
*   This function powers down the HTS221 sensor by clearing the 
*   appropriate bit in the control registers.
*   \param hts221 a valid pointer to a ::HTS221_Struct
*   \return ::HTS221_Error depending on generated error
*/
static HTS221_Error HTS221_PowerDown(HTS221_Struct *hts221);



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
    if( ( genericError != NO_ERROR ) || (temp != HTS221_WHO_AM_I))
    {
        return HTS221_ERROR;
    }
    
    // Power up the device
    if (HTS221_PowerUp(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    // Set default resolution for temperature
    if (HTS221_SetTemperatureResolution(hts221, HTS221_AVGT_16) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Set default resolution for humidity
    if (HTS221_SetHumidityResolution(hts221, HTS221_AVGH_32) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Set output data rate
    if ( HTS221_SetOutputDataRate(hts221, HTS221_ODR_OneShot) == HTS221_ERROR) 
    {
        return HTS221_ERROR;
    }
    
    // Disable data ready signal -- default
    if ( HTS221_DisableDRDY(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    // Configure data ready signal to be active high -- default
    if (HTS221_ConfigureDRDYLevel(hts221, HTS221_DRDY_ACTIVE_HIGH) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    // Configure data ready pin to be in push pull -- default
    if( HTS221_ConfigureDRDYPin(hts221, HTS221_DRDY_PUSH_PULL) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    // Stop heater
    if (HTS221_HeaterStop(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Read calibration coefficients
    
    if (HTS221_ReadCalibrationCoefficients(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    return HTS221_OK;
}

HTS221_Error HTS221_Stop(HTS221_Struct* hts221)
{
    if(HTS221_PowerDown(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}

HTS221_Error HTS221_MeasureTemperature(HTS221_Struct* hts221, uint16_t timeout)
{
    // Start one-shot measurement
    if ( HTS221_StartOneShot() == HTS221_ERROR)
    {
         return HTS221_ERROR;
    }
    
    // Wait until measurement is ready or timeout has passed
    HTS221_Measurement_Ready meas_ready = HTS221_MEAS_NOT_READY;
    while ( meas_ready == HTS221_MEAS_NOT_READY)
    {
        HTS221_IsMeasurementReady(&meas_ready);
        timeout--;
        if (timeout == 0)
        {
            return HTS221_ERROR;
        }
    }
    
    // Read temperature
    if (HTS221_ReadTemperature(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Return
    return HTS221_OK;
}

HTS221_Error HTS221_MeasureHumidity(HTS221_Struct* hts221, uint16_t timeout)
{
    // Start one-shot measurement
    if ( HTS221_StartOneShot() == HTS221_ERROR)
    {
         return HTS221_ERROR;
    }
    
    // Wait until measurement is ready or timeout has passed
    HTS221_Measurement_Ready meas_ready = HTS221_MEAS_NOT_READY;
    while ( meas_ready == HTS221_MEAS_NOT_READY)
    {
        HTS221_IsMeasurementReady(&meas_ready);
        timeout--;
        if (timeout == 0)
        {
            return HTS221_ERROR;
        }
    }
    
    // Read temperature
    if (HTS221_ReadHumidity(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    // Return
    return HTS221_OK;
}

HTS221_Error HTS221_MeasureTemperatureHumidity(HTS221_Struct* hts221, uint16_t timeout)
{
    // Start one-shot measurement
    if ( HTS221_StartOneShot() == HTS221_ERROR)
    {
         return HTS221_ERROR;
    }
    
    // Wait until measurement is ready or timeout has passed
    HTS221_Measurement_Ready meas_ready = HTS221_MEAS_NOT_READY;
    while ( meas_ready == HTS221_MEAS_NOT_READY)
    {
        HTS221_IsMeasurementReady(&meas_ready);
        timeout--;
        if (timeout == 0)
        {
            return HTS221_ERROR;
        }
    }
    
    // Read temperature
    if (HTS221_ReadTemperatureHumidity(hts221) == HTS221_ERROR)
    {
        return HTS221_ERROR;
    }
    
    // Return
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

HTS221_Error HTS221_ReadTemperatureHumidity(HTS221_Struct* hts221)
{

    // Read raw humidity values
    uint8_t temp_array[4];
    ErrorCode error = I2C_Peripheral_ReadRegisterMulti(HTS221_I2C_ADDRESS,
                                        HTS221_HUMIDITY_OUT_L_REG,
                                        4,
                                        temp_array);   
    
    // Convert humidity 
    int32_t tmp32 = 0;
    int16_t rawHum = (((uint16_t) temp_array [1]) << 8) | ((uint16_t) temp_array[0]);
    tmp32 = ((int32_t) rawHum - hts221->coeff.H0_T0_OUT) * ((int32_t)(hts221->coeff.H1_rH - hts221->coeff.H0_rH) * 10);
    hts221->humidity = tmp32 / (hts221->coeff.H1_T0_OUT - hts221->coeff.H0_T0_OUT) + hts221->coeff.H0_rH * 10;
    
    if (hts221->humidity > 1000)
        hts221->humidity = 1000;
    
    // Convert temperature 
    int16_t rawTemp = (((uint16_t) temp_array [3]) << 8) | ((uint16_t) temp_array[2]);
    tmp32 = ((int32_t) rawTemp - hts221->coeff.T0_OUT) * ((int32_t)(hts221->coeff.T1_degC - hts221->coeff.T0_degC) * 10);
    hts221->temperature = tmp32 / (hts221->coeff.T1_OUT - hts221->coeff.T0_OUT) + hts221->coeff.T0_degC * 10;
        
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

HTS221_Error HTS221_StartOneShot(void) 
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

HTS221_Error HTS221_IsMeasurementReady(HTS221_Measurement_Ready* meas_ready)
{
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                                    HTS221_STATUS_REG,
                                                    &temp);
    if ( ( temp & 0x03 )  == 0x03 )
    {
        *meas_ready = HTS221_MEAS_READY;
    }
    else
    {
        *meas_ready = HTS221_MEAS_NOT_READY;
    }
    
    if ( error != NO_ERROR)
        return HTS221_ERROR;
    
    return HTS221_OK;
}

HTS221_Error HTS221_ReadWhoAmI(HTS221_Struct* hts221, uint8_t* reg_val)
{
    // Read who am i register
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                        HTS221_WHO_AM_I_REG,
                                        reg_val);
    // Check if WHO AM I value was as expeected
    if ( (error != NO_ERROR) || (*reg_val != HTS221_WHO_AM_I))
    {
        return HTS221_ERROR;
    }
    hts221->who_am_i_check = 1;
    
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

/************************************************/
/*         SETTINGS RELATED FUNCTIONS           */
/************************************************/

 HTS221_Error HTS221_SetOutputDataRate(HTS221_Struct* hts221, HTS221_ODR odr)
{
    // Bits[1:0] of CTRL_REG_1 allows to set the desired output data rate
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with desired value of ODR
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    (temp & ~0x03) | odr);
    hts221->odr = odr;
    
    // Check for errors
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}

HTS221_Error HTS221_BlockDataUpdate(HTS221_Struct* hts221) 
{
    // Bit 2 of CTRL_REG_1 allows to block or enable the data update
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 2 set
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    temp | (1<<2));
    
    hts221->du = HTS221_UPDATE_BLOCKED;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}

HTS221_Error HTS221_EnableDataupdate(HTS221_Struct* hts221)
{
    // Bit 2 of CTRL_REG_1 allows to block or enable the data update
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 2 cleared
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    temp & ~(1<<2));
    
    hts221->du = HTS221_UPDATE_CONTINUOUS;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}



HTS221_Error HTS221_RebootMemoryContent(void)
{
    // Bit 7 of CTRL_REG_2 allows to reboot memory content
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 7 set
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    (temp | (1<<7)));
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}


/************************************************/
/*            HEATER RELATED SETTINGS           */
/************************************************/
HTS221_Error HTS221_HeaterStart(HTS221_Struct* hts221)
{
    // Bit 1 of CTRL_REG_2 allows to start or stop the internal heater
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 2 set
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    temp | (1<<1));
    
    hts221->heater = HTS221_HEATER_ON;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;   
}

HTS221_Error HTS221_HeaterStop(HTS221_Struct* hts221)
{
    // Bit 1 of CTRL_REG_2 allows to start or stop the internal heater
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 2 cleared
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_2,
                                    (temp & (~(1<<1))));
    
    hts221->heater = HTS221_HEATER_OFF;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;   
}

/************************************************/
/*         DATA READY SIGNAL SETTINGS           */
/************************************************/

HTS221_Error HTS221_ConfigureDRDYLevel(HTS221_Struct* hts221, HTS221_DRDY_Level drdy_level)
{
    // Bit 7 of CTRL_REG_3 allows to set the drdy signal as active low or high
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_3,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 7 changed
    if ( drdy_level == HTS221_DRDY_ACTIVE_LOW)
    {
        error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                        HTS221_CTRL_REG_3,
                                     (temp | (1<<7)));
    }
    else if ( drdy_level == HTS221_DRDY_ACTIVE_HIGH)
    {
        error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                        HTS221_CTRL_REG_3,
                                     (temp & (~(1<<7))));
    }
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    
    hts221->drdy_level = drdy_level;
    
    return HTS221_OK;
    
}

HTS221_Error HTS221_ConfigureDRDYPin(HTS221_Struct* hts221, HTS221_DRDY_Configuration drdy_config)
{
    // Bit 6 of CTRL_REG_3 allows to set the drdy pin as push pull or open drain
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_3,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 6 changed
    if ( drdy_config == HTS221_DRDY_OPEN_DRAIN)
    {
        error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                        HTS221_CTRL_REG_3,
                                     (temp | (1<<6)));
    }
    else if ( drdy_config == HTS221_DRDY_PUSH_PULL)
    {
        error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                        HTS221_CTRL_REG_3,
                                     (temp & (~(1<<6))));
    }
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    
    hts221->drdy_config = drdy_config;
    
    return HTS221_OK;
}

HTS221_Error HTS221_EnableDRDY(HTS221_Struct* hts221)
{
    // Bit 2 of CTRL_REG_3 allows to enable or disable the drdy signal
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_3,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 2 set
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_3,
                                    (temp | (1<<2)));
    
    hts221->drdy_enable = HTS221_DRDY_ENABLED;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}

HTS221_Error HTS221_DisableDRDY(HTS221_Struct* hts221)
{
    // Bit 2 of CTRL_REG_3 allows to enable or disable the drdy signal
    // Read current value of register
    uint8_t temp;
    ErrorCode error = I2C_Peripheral_ReadRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_3,
                                    &temp);
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    // Write new register value with bit 2 cleared
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_3,
                                    (temp & (~(1<<2))));
    
    hts221->drdy_enable = HTS221_DRDY_DISABLED;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
}

/************************************************/
/*           POWER UP/DOWN FUNCTIONS            */
/************************************************/
static HTS221_Error HTS221_PowerUp(HTS221_Struct *hts221) 
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
                                    temp | (1<<7));
    hts221->power = HTS221_POWER_ON;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
    
}

static HTS221_Error HTS221_PowerDown(HTS221_Struct *hts221) 
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
    // Write new register value with bit 7 cleared
    error = I2C_Peripheral_WriteRegister(HTS221_I2C_ADDRESS,
                                    HTS221_CTRL_REG_1,
                                    temp &~ (1<<7));
    hts221->power = HTS221_POWER_OFF;
    
    if ( error != NO_ERROR)
    {
        return HTS221_ERROR;
    }
    return HTS221_OK;
    
}

/* [] END OF FILE */
