/**
*   Source file for the BME280 library.
*
*   \author Davide Marzorati
*   \date October 25, 2019
*/

#include "BME280.h"
#include "BME280_I2C_Interface.h"
#include "BME280_RegMap.h"
#include "CyLib.h" 

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

/**
*   \brief Device sleep mode bit settings.
*/
#define BME280_SLEEP_MODE 0x00

/**
*   \brief Device force mode bit settings.
*/
#define BME280_FORCED_MODE 0x01

/**
*   \brief Device normal mode bit settings.
*/
#define BME280_NORMAL_MODE 0x03

/**
*   \brief Number of registers for temperature and pressure calibration data.
*/
#define BME280_TEMP_PRESS_CALIB_DATA_LEN 26

/**
*   \brief Number of registers for humidity calibration data.
*/
#define BME280_HUMIDITY_CALIB_DATA_LEN 7

/**
*   \brief Number of registers with pressure, temperature, and humidity data.
*/
#define BME280_P_T_H_DATA_LEN 8

/**
*   \brief Macro to concatenate bytes together.
*/
#define BME280_CONCAT_BYTES(msb, lsb)   (((uint16_t) msb << 8) | ((uint16_t) lsb))

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
static BME280_ErrorCode BME280_SetMode(BME280* bme280, uint8_t mode);

/**
*   \brief Compensate raw temperature values.
*
*   This function is used to compensate the raw temperature values and convert them
*   in signed 32 bit integers.
*
*   \param[in] bme280 : pointer to device structure
*
*   \return Compensated temperature data.
*   \retval Compensated temperature data as 32 bit signed integer.
*
*/
static int32_t BME280_CompensateTemperature(BME280* bme280);

/**
*   \brief Compensate raw pressure values.
*
*   This function is used to compensate the raw pressure values and convert them
*   in unsigned 32 bit integers.
*
*   \param[in] bme280 : pointer to device structure
*
*   \return Compensated pressure data.
*   \retval Compensated pressure data as 32 bit unsigned integer.
*
*/
static int32_t BME280_CompensatePressure(BME280* bme280);
/**
*   \brief Compensate raw humidity values.
*
*   This function is used to compensate the raw humidity values and convert them
*   in unsigned 32 bit integers.
*
*   \param[in] bme280 : pointer to device structure
*
*   \return Compensated humidity data.
*   \retval Compensated humidity data as 32 bit unsigned integer.
*
*/
static uint32_t BME280_CompensateHumidity(BME280* bme280);


/**
*   \brief Read Who Am I register value.
*
*   This function reads the value of the Who Am I register.
*   If everything is set up correctly, you should read 0x60
*   \return Result of function execution 
*   \retval BME280_I2C_ERROR -> Error during I2C communication
*   \retval BME280_ERROR -> Generic error
*   \retval BME280_OK -> Success
*/
static BME280_ErrorCode BME280_ReadWhoAmI(uint8_t* value);

/**
*   \brief Read device calibration data.
*
*   This function reads the calibration data from the sensor, parses
*   them and stores them in the device structure.
*   \param[in] bme280 Pointer to device struct
*   \return Result of function execution 
*   \retval BME280_I2C_ERROR -> Error during I2C communication
*   \retval BME280_ERROR -> Generic error
*   \retval BME280_OK -> Success
*/
static BME280_ErrorCode BME280_ReadCalibrationData(BME280* bme280);

/**
*   \brief Parse temperature and pressure calibration data.
*
*   This function parses temperature and pressure calibration data and
*   stores them in the device structure.
*   \param[in] bme280 Pointer to device struct
*   \param[in] calib_data Array with unparsed calibration data
*/
static void BME280_ParseTempPressCalibData(BME280* bme280, uint8_t* calib_data);

/**
*   \brief Parse humidity calibration data.
*
*   This function parses humidity calibration data and
*   stores them in the device structure.
*   \param[in] bme280 Pointer to device struct
*   \param[in] calib_data Array with unparsed calibration data
*/
static void BME280_ParseHumidityCalibData(BME280* bme280, uint8_t* calib_data);

/**
*   \brief Validate device structure for null conditions.
*
*   \param[in] bme280 : pointer to device structure
*   
*   \return Result of null pointer check
*   \retval BME280_OK -> Structure initialized
*   \retval BME280_NULL_PTR ->
*/
static BME280_ErrorCode BME280_NullPtrCheck(const BME280* bme280);

/******************************************/
/*          Function Definitions          */
/******************************************/

BME280_ErrorCode BME280_Start(BME280* bme280)
{
    uint8_t try_counts = 5;
    BME280_ErrorCode error;
    uint8_t who_am_i_value = 0x00;
    
    // Start I2C Interface
    BME280_I2C_Interface_Start();
    while(try_counts)
    {
        // Check device presence on I2C bus
        error = BME280_ReadWhoAmI(&who_am_i_value);
        if (error == BME280_OK && who_am_i_value == BME280_WHO_AM_I)
        {
            bme280->chip_id = BME280_WHO_AM_I;
            error = BME280_Reset();
            if ( error == BME280_OK)
            {
                // Read calibration data
                error = BME280_ReadCalibrationData(bme280);
            }
            break;
        }
        
        CyDelay(1);
        --try_counts;
    }
    
    if (!try_counts)
    {
        return BME280_E_DEV_NOT_FOUND;
    }
    
    return BME280_OK;
}
BME280_ErrorCode BME280_ReadWhoAmI(uint8_t* who_am_i)
{
    // Read WHO AM I register 
    return BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, 
                                        BME280_WHO_AM_I_REG_ADDR, who_am_i);
}

BME280_ErrorCode BME280_Reset(void) 
{
    BME280_ErrorCode error;
    uint8_t try_counts = 5;
    uint8_t status_reg = 0;
    
    // Write reset value to sensor reset register
    error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, 
                        BME280_RESET_REG_ADDR, BME280_SOFT_RESET_COMMAND);
    if ( error == BME280_OK)
    {
        // If NVM not copied yet, wait for NVM to copy --> Status register
        do 
        {
            CyDelay(2);
            error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, 
                BME280_STATUS_REG_ADDR, &status_reg);
        } while ((error == BME280_OK) && (try_counts--) && (status_reg & BME280_STATUS_IM_UPDATE));
        if ( status_reg & BME280_STATUS_IM_UPDATE)
        {
            error = BME280_E_NVM_COPY_FAILED;
        }
    }
    return error;
}

BME280_ErrorCode BME280_ReadStatusRegister(uint8_t* value)
{
    BME280_ErrorCode error;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS,
        BME280_STATUS_REG_ADDR, value);
    return error;
    
}

BME280_ErrorCode BME280_SetHumidityOversampling(BME280* bme280, BME280_Oversampling hos)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS,
        BME280_CTRL_HUM_REG_ADDR, &reg_data);
    if (error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0x07;
        reg_data |= hos;
        // Write new value to ctrl hum register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_HUM_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            // Read value of control meas register
            error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, &reg_data);
            if ( error == BME280_OK)
            {
                // Write value of control meas register
                error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, reg_data);
                if (error == BME280_OK)
                {
                    bme280->settings.osr_h = hos;
                }
            }
        }
    }
    return error;
}

BME280_ErrorCode BME280_SetTemperatureOversampling(BME280* bme280, BME280_Oversampling tos)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, 
            BME280_CTRL_MEAS_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0xE0; // Clear bits 7,6,5
        reg_data |= tos << 5;
        // Write new value to ctrl meas register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS,
                            BME280_CTRL_MEAS_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            bme280->settings.osr_t = tos;
        }

    }
    return error;
}

BME280_ErrorCode BME280_SetPressureOversampling(BME280* bme280, BME280_Oversampling pos)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, 
        BME280_CTRL_MEAS_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0x1C;    // Clear bits 4,3,2
        reg_data |= pos << 2;  
        // Write new value to ctrl meas register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, 
            BME280_CTRL_MEAS_REG_ADDR, reg_data);
        if (error == BME280_OK)
        {
            bme280->settings.osr_p = pos;
        }
    }
    return error;
}

BME280_ErrorCode BME280_SetMode(BME280* bme280, uint8_t mode)
{
    BME280_ErrorCode error;
    uint8_t reg_data = 0x00;

    // Read current register value
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, 
        BME280_CTRL_MEAS_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0x03; // Bit 1,0
        reg_data |= mode;
        // Write new value to ctrl meas register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CTRL_MEAS_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            bme280->settings.mode = mode;
        }
    }
    return error;
}

BME280_ErrorCode BME280_SetSleepMode(BME280* bme280)
{
    // Set sleep mode
    return BME280_SetMode(bme280, BME280_SLEEP_MODE);
}

BME280_ErrorCode BME280_SetForcedMode(BME280* bme280)
{
    // Set forced mode
   return BME280_SetMode(bme280, BME280_FORCED_MODE); 
}

BME280_ErrorCode BME280_SetNormalMode(BME280* bme280)
{
    // Set normal mode
   return BME280_SetMode(bme280, BME280_NORMAL_MODE);
}

BME280_ErrorCode BME280_SetStandbyTime(BME280* bme280, BME280_TStandby tStandby)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0xE0;    // Clear bits 7,6,5
        reg_data |= tStandby << 5;  
        // Write new value to config register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            bme280->settings.stanby_time = tStandby;
        }
    }
    return error;
}

BME280_ErrorCode BME280_SetIIRFilter(BME280* bme280, BME280_Filter filter)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0x1C;    // Clear bits 4,3,2
        reg_data |= filter << 2;  
        // Write new value to ctrl hum register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            bme280->settings.filter = filter;
        }
    }
    return error;
}

BME280_ErrorCode BME280_EnableSPI(BME280* bme280)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0x01;    // Clear bit 1
        reg_data |= 0x01;
        // Write new value to ctrl hum register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            bme280->settings.spi_enable = 1;
        }
    }
    return error;
}

BME280_ErrorCode BME280_DisableSPI(BME280* bme280)
{
    BME280_ErrorCode error;
    // Read current register value
    uint8_t reg_data = 0x00;
    error = BME280_I2C_Interface_ReadRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, &reg_data);
    if ( error == BME280_OK)
    {
        // Set new value of register
        reg_data &= ~0x01;    // Clear bit 1
        reg_data |= 0x00;
        // Write new value to ctrl hum register
        error = BME280_I2C_Interface_WriteRegister(BME280_I2C_ADDRESS, BME280_CONFIG_REG_ADDR, reg_data);
        if ( error == BME280_OK)
        {
            bme280->settings.spi_enable = 0;
        }
    }
    return error;
}

static BME280_ErrorCode BME280_ReadCalibrationData(BME280* bme280)
{
    // Error code returned by the function
    BME280_ErrorCode error;
    // Array where we will store calibration data
    uint8_t calib_data[BME280_TEMP_PRESS_CALIB_DATA_LEN] = {0};
    
    // Read calibration data
    error = BME280_I2C_Interface_ReadRegisterMulti(BME280_I2C_ADDRESS,
                BME280_CALIB_TEMP_PRESS_REG_ADDR, 
                BME280_TEMP_PRESS_CALIB_DATA_LEN, 
                calib_data);
    if (error == BME280_OK)
    {
        // Parse calibration data
        BME280_ParseTempPressCalibData(bme280, calib_data);
        // Read humidity calibration data
        error = BME280_I2C_Interface_ReadRegisterMulti(BME280_I2C_ADDRESS,
                BME280_CALIB_HUM_REG_ADDR, 
                BME280_TEMP_PRESS_CALIB_DATA_LEN, 
                calib_data);
        if (error == BME280_OK)
        {
            BME280_ParseHumidityCalibData(bme280, calib_data);
        }
    }
    return error;
    
}

BME280_ErrorCode BME280_ReadData(BME280* bme280, uint8_t sensor_comp)
{
    BME280_ErrorCode error;
    uint8_t reg_data[BME280_P_T_H_DATA_LEN] = {0};
    
    error = BME280_NullPtrCheck(bme280);
    if ( error == BME280_OK)
    {
        error = BME280_I2C_Interface_ReadRegisterMulti(BME280_I2C_ADDRESS,
                        BME280_PRESS_MSB_REG_ADDR,
                        BME280_P_T_H_DATA_LEN,
                        reg_data);
        if ( error == BME280_OK)
        {
            // Parse sensor data
            BME280_ParseSensorData(bme280, reg_data);
            
            // Compensate sensor data
            error = BME280_CompensateData(bme280, sensor_comp);
        }
    }
    else
    {
        error = BME280_E_NULL_PTR;
    }
    return error;
}

static void BME280_ParseTempPressCalibData(BME280* bme280, uint8_t* reg_data)
{
    // Get pointer to struct to calibration data
    BME280_Calib_Data *calib_data = &bme280->calib_data;
    // Parse temperature and pressure calibration data
    calib_data->dig_T1 = BME280_CONCAT_BYTES(reg_data[1],reg_data[0]);
    calib_data->dig_T2 = (int16_t)BME280_CONCAT_BYTES(reg_data[3],reg_data[2]);
    calib_data->dig_T3 = (int16_t)BME280_CONCAT_BYTES(reg_data[5],reg_data[4]);
    calib_data->dig_P1 = BME280_CONCAT_BYTES(reg_data[7],reg_data[6]);
    calib_data->dig_P2 = (int16_t)BME280_CONCAT_BYTES(reg_data[9], reg_data[8]);
    calib_data->dig_P3 = (int16_t)BME280_CONCAT_BYTES(reg_data[11], reg_data[10]);
    calib_data->dig_P4 = (int16_t)BME280_CONCAT_BYTES(reg_data[13], reg_data[12]);
    calib_data->dig_P5 = (int16_t)BME280_CONCAT_BYTES(reg_data[15], reg_data[14]);
    calib_data->dig_P6 = (int16_t)BME280_CONCAT_BYTES(reg_data[17], reg_data[16]);
    calib_data->dig_P7 = (int16_t)BME280_CONCAT_BYTES(reg_data[19], reg_data[18]);
    calib_data->dig_P8 = (int16_t)BME280_CONCAT_BYTES(reg_data[21], reg_data[20]);
    calib_data->dig_P9 = (int16_t)BME280_CONCAT_BYTES(reg_data[23], reg_data[22]);
    calib_data->dig_H1 = reg_data[25];
}

static void BME280_ParseHumidityCalibData(BME280* bme280, uint8_t* reg_data)
{
    // Get pointer to struct with calibration data
    BME280_Calib_Data* calib_data = &bme280->calib_data;
    // Parse temperature and pressure calibration data
    int16_t dig_H4_lsb;
    int16_t dig_H4_msb;
    int16_t dig_H5_lsb;
    int16_t dig_H5_msb;
    
    calib_data->dig_H2 = (int16_t)BME280_CONCAT_BYTES(reg_data[1], reg_data[0]);
    calib_data->dig_H3 = reg_data[2];
    dig_H4_msb = (int16_t)(int8_t)reg_data[3] * 16;
    dig_H4_lsb = (int16_t)(reg_data[4] & 0x0F);
    calib_data->dig_H4 = dig_H4_msb | dig_H4_lsb;
    dig_H5_msb = (int16_t)(int8_t)reg_data[5] * 16;
    dig_H5_lsb = (int16_t)(reg_data[4] >> 4);
    calib_data->dig_H5 = dig_H5_msb | dig_H5_lsb;
    calib_data->dig_H6 = (int8_t)reg_data[6];
}

void BME280_ParseSensorData(BME280* bme280, uint8_t* reg_data)
{
    // Pointer to uncompensated data
    BME280_Uncomp_Data* uncomp_data = &bme280->uncomp_data;
    // Variables to store data
    uint32_t data_xlsb;
    uint32_t data_lsb;
    uint32_t data_msb;
    
    // Pressure
    data_msb = (uint32_t) reg_data[0] << 12;
    data_lsb = (uint32_t) reg_data[1] << 4;
    data_xlsb = (uint32_t) reg_data[2] >> 4;
    uncomp_data->pressure = data_msb | data_lsb | data_xlsb;
    
    // Temperature
    data_msb = (uint32_t) reg_data[3] << 12;
    data_lsb = (uint32_t) reg_data[4] << 4;
    data_xlsb = (uint32_t) reg_data[5] >> 4;
    uncomp_data->temperature = data_msb | data_lsb | data_xlsb;
    
    // Humidity
    data_msb = (uint32_t) reg_data[6] << 8;
    data_lsb = (uint32_t) reg_data[7];
    uncomp_data->humidity = data_msb | data_lsb;
}

BME280_ErrorCode BME280_CompensateData(BME280* bme280, uint8_t sensor_comp)
{
    BME280_ErrorCode error = BME280_OK;
    // Set up data with initialization to 0
    BME280_Data* data = &bme280->data;
    data->temperature = 0;
    data->pressure = 0;
    data->humidity = 0;
    
    // If we need to compensate temperature, pressure, or humidity
    if ( sensor_comp & ( BME280_TEMP_COMP | BME280_PRESS_COMP | BME280_HUM_COMP ))
    {
        // Compensate temperature data
        data->temperature = BME280_CompensateTemperature(bme280);
    }
    if (sensor_comp & BME280_PRESS_COMP)
    {
        
        // Compensate pressure data
        data->pressure = BME280_CompensatePressure(bme280);
    }
    if (sensor_comp & BME280_HUM_COMP)
    {
        // Compensate humidity data
        data->humidity = BME280_CompensateHumidity(bme280);
    }
    
    return error;
}

static int32_t BME280_CompensateTemperature(BME280* bme280)
{
    // Set up variables
    int32_t var1;
    int32_t var2;
    int32_t temperature;
    int32_t temperature_min = -4000;
    int32_t temperature_max = 8500;
    
    // Get pointer to uncompensated data structure
    BME280_Uncomp_Data* uncomp_data = &bme280->uncomp_data;
    // Get pointer to calibration data 
    BME280_Calib_Data* calib_data = &bme280->calib_data;
    
    var1 = (int32_t)((uncomp_data->temperature/8) - ((int32_t)calib_data->dig_T1 * 2));
    var1 = (var1*((int32_t)calib_data->dig_T2))/2048;
    var2 = (int32_t)((uncomp_data->temperature / 16) - ((int32_t)calib_data->dig_T1));
    var2 = (((var2*var2)/4096) * ((int32_t)calib_data->dig_T3))/16384;
    calib_data->t_fine = var1 + var2;
    temperature = (calib_data->t_fine * 5 + 128 ) / 256;
    if (temperature < temperature_min)
        temperature = temperature_min;
    if (temperature > temperature_max)
        temperature = temperature_max;
    return temperature;
}

static int32_t BME280_CompensatePressure(BME280* bme280)
{
    // Set up variables
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    uint32_t var5;
    uint32_t pressure;
    uint32_t pressure_min = 30000;
    uint32_t pressure_max = 110000;
    
    // Get pointer to uncompensated data structure
    BME280_Uncomp_Data* uncomp_data = &bme280->uncomp_data;
    // Get pointer to calibration data 
    BME280_Calib_Data* calib_data = &bme280->calib_data;
    
    var1 = (((int32_t)calib_data->t_fine) / 2) - (int32_t)64000;
    var2 = (((var1 / 4) * (var1 / 4)) / 2048) * ((int32_t)calib_data->dig_P6);
    var2 = var2 + ((var1 * ((int32_t)calib_data->dig_P5)) * 2);
    var2 = (var2 / 4) + (((int32_t)calib_data->dig_P4) * 65536);
    var3 = (calib_data->dig_P3 * (((var1 / 4) * (var1 / 4)) / 8192)) / 8;
    var4 = (((int32_t)calib_data->dig_P2) * var1) / 2;
    var1 = (var3 + var4) / 262144;
    var1 = (((32768 + var1)) * ((int32_t)calib_data->dig_P1)) / 32768;

    /* avoid exception caused by division by zero */
    if (var1)
    {
        var5 = (uint32_t)((uint32_t)1048576) - uncomp_data->pressure;
        pressure = ((uint32_t)(var5 - (uint32_t)(var2 / 4096))) * 3125;
        if (pressure < 0x80000000)
        {
            pressure = (pressure << 1) / ((uint32_t)var1);
        }
        else
        {
            pressure = (pressure / (uint32_t)var1) * 2;
        }
        var1 = (((int32_t)calib_data->dig_P9) * ((int32_t)(((pressure / 8) * (pressure / 8)) / 8192))) / 4096;
        var2 = (((int32_t)(pressure / 4)) * ((int32_t)calib_data->dig_P8)) / 8192;
        pressure = (uint32_t)((int32_t)pressure + ((var1 + var2 + calib_data->dig_P7) / 16));
        if (pressure < pressure_min)
        {
            pressure = pressure_min;
        }
        else if (pressure > pressure_max)
        {
            pressure = pressure_max;
        }
    }
    else
    {
        pressure = pressure_min;
    }

    return pressure;
}

static uint32_t BME280_CompensateHumidity(BME280* bme280)
{
    // Set up variables
    int32_t var1;
    int32_t var2;
    int32_t var3;
    int32_t var4;
    int32_t var5;
    uint32_t humidity;
    uint32_t humidity_max = 102400;
    
    // Get pointer to uncompensated data structure
    BME280_Uncomp_Data* uncomp_data = &bme280->uncomp_data;
    // Get pointer to calibration data 
    BME280_Calib_Data* calib_data = &bme280->calib_data;
    
    var1 = calib_data->t_fine - ((int32_t)76800);
    var2 = (int32_t)(uncomp_data->humidity * 16384);
    var3 = (int32_t)(((int32_t)calib_data->dig_H4) * 1048576);
    var4 = ((int32_t)calib_data->dig_H5) * var1;
    var5 = (((var2 - var3) - var4) + (int32_t)16384) / 32768;
    var2 = (var1 * ((int32_t)calib_data->dig_H6)) / 1024;
    var3 = (var1 * ((int32_t)calib_data->dig_H3)) / 2048;
    var4 = ((var2 * (var3 + (int32_t)32768)) / 1024) + (int32_t)2097152;
    var2 = ((var4 * ((int32_t)calib_data->dig_H2)) + 8192) / 16384;
    var3 = var5 * var2;
    var4 = ((var3 / 32768) * (var3 / 32768)) / 128;
    var5 = var3 - ((var4 * ((int32_t)calib_data->dig_H1)) / 16);
    var5 = (var5 < 0 ? 0 : var5);
    var5 = (var5 > 419430400 ? 419430400 : var5);
    humidity = (uint32_t)(var5 / 4096);
    if (humidity > humidity_max)
    {
        humidity = humidity_max;
    }

    return humidity;
}

static BME280_ErrorCode BME280_NullPtrCheck(const BME280* bme280)
{
    BME280_ErrorCode error;
    if (bme280 == NULL)
    {
        error = BME280_E_NULL_PTR;
    }
    else
    {
        error = BME280_OK;
    }
    return error;
}
/* [] END OF FILE */
