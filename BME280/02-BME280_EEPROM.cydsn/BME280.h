/**
*   \file BME280.h
*   \brief Header for the interface to the BME280 sensor.
*
*   This header file contains all the functions declarations to
*   interface with a BME280 sensor.
*
*   \author Davide Marzorati
*   \date October 25, 2019
*/

#ifndef __BME280_H_
    #define __BME280_H_

    #include "cytypes.h"
    #include "BME280_ErrorCodes.h"
    
    /******************************************/
    /*              Macros                    */
    /******************************************/
    
    
    /**
    *   \brief WHO AM I value for the BME280 Sensor.
    *   
    *   This is the value that should be returned when reading
    *   the #BME280_WHO_AM_I_REG_ADDR. It can be used to check
    *   that the device is working and that the I2C communication
    *   is working properly.
    */
    #ifndef BME280_WHO_AM_I
        #define BME280_WHO_AM_I 0x60
    #endif
    
    /**
    *   \brief Macro for pressure compensation selection
    *
    *   This macro can be used with the provided API to 
    *   select the compensation of the pressure data
    */
    #ifndef BME280_PRESS_COMP
        #define BME280_PRESS_COMP 1
    #endif
    
    /**
    *   \brief Macro for temprature compensation selection
    *
    *   This macro can be used with the provided API to 
    *   select the compensation of the temperature data.
    */
    #ifndef BME280_TEMP_COMP
        #define BME280_TEMP_COMP 1 << 1
    #endif
    
    /**
    *   \brief Macro for humidity compensation selection
    *
    *   This macro can be used with the provided API to 
    *   select the compensation of the humidity data.
    */
    #ifndef BME280_HUM_COMP
        #define BME280_HUM_COMP 1 << 2
    #endif
    
    /**
    *   \brief Macro for compensation selection
    *
    *   This macro can be used with the provided API to 
    *   select the compensation of the all (temperature, pressure,
    *   and humidity) data.
    */
    #ifndef BME280_ALL_COMP
        #define BME280_ALL_COMP 0x07
    #endif
    
    /**
    *   \brief Macro for status register check
    */
    #ifndef BM280_STATUS_IM_UPDATE
        #define BME280_STATUS_IM_UPDATE 0x01
    #endif
    
    /******************************************/
    /*              Typedefs                  */
    /******************************************/
    /**
    *   \brief Oversampling values.
    *
    *   This enum contains all the possible values of Pressure oversampling.
    */
    typedef enum {
        BME280_NO_OVERSAMPLING,       ///< Oversampling skipped, output set to 0x8000
        BME280_OVERSAMPLING_1X,       ///< Temperature oversampling x1
        BME280_OVERSAMPLING_2X,       ///< Temperature oversampling x2
        BME280_OVERSAMPLING_4X,       ///< Temperature oversampling x4
        BME280_OVERSAMPLING_8X,       ///< Temperature oversampling x8
        BME280_OVERSAMPLING_16X       ///< Temperature oversampling x16
    } BME280_Oversampling;
    
    /**
    *   \brief Inactive duration (tStanbdy) in normal mode.
    *
    *   This enum contains all the possible values of TStandby.
    *   For further information see #BME280_CONFIG_REG_ADDR .
    */
    typedef enum {
        BME280_TSTANBDY_0_5_MS,  ///< TStandby: 0.5 ms
        BME280_TSTANBDY_62_5_MS, ///< TStandby: 62.5 ms
        BME280_TSTANBDY_125_MS,  ///< TStandby: 125 ms
        BME280_TSTANBDY_250_MS,  ///< TStandby: 250 ms
        BME280_TSTANBDY_500_MS,  ///< TStandby: 500 ms
        BME280_TSTANBDY_1000_MS, ///< TStandby: 1000 ms
        BME280_TSTANBDY_10_MS,   ///< TStandby: 10 ms
        BME280_TSTANBDY_20_MS,   ///< TStandby: 20 ms
    } BME280_TStandby;
    
    /**
    *   \brief IIR Filter time constant
    *
    *   This enum contains all the possible settings for the IIR
    *   Filter time constant.
    *   For further information see #BME280_CONFIG_REG_ADDR .
    */
    typedef enum {
        BME280_FILTER_COEFF_OFF,  ///< Oversampling skipped, output set to 0x8000
        BME280_FILTER_COEFF_2,    ///< Temperature oversampling x1
        BME280_FILTER_COEFF_4,    ///< Temperature oversampling x2
        BME280_FILTER_COEFF_8,    ///< Temperature oversampling x4
        BME280_FILTER_COEFF_16    ///< Temperature oversampling x16
    } BME280_Filter;
    
    /**
    *   \brief Struct with calibration coefficients
    *
    *   This struct holds the calibration coefficients of the sensor
    *   that can be read from registers #BME280_CALIB_TEMP_PRESS_REG_ADDR and
    *   #BME280_CALIB_HUM_REG_ADDR.
    */
    typedef struct {
        uint16_t dig_T1;    ///< Temperature calibration coefficient T1
        int16_t  dig_T2;    ///< Temperature calibration coefficient T2
        int16_t  dig_T3;    ///< Temperature calibration coefficient T3
        uint16_t dig_P1;    ///< Pressure calibration coefficient P1
        int16_t  dig_P2;    ///< Pressure calibration coefficient P2
        int16_t  dig_P3;    ///< Pressure calibration coefficient P3
        int16_t  dig_P4;    ///< Pressure calibration coefficient P4
        int16_t  dig_P5;    ///< Pressure calibration coefficient P5
        int16_t  dig_P6;    ///< Pressure calibration coefficient P6
        int16_t  dig_P7;    ///< Pressure calibration coefficient P7
        int16_t  dig_P8;    ///< Pressure calibration coefficient P8
        int16_t  dig_P9;    ///< Pressure calibration coefficient P9
        uint8_t  dig_H1;    ///< Humidity calibration coefficient H1
        int16_t  dig_H2;    ///< Humidity calibration coefficient H2
        uint8_t  dig_H3;    ///< Humidity calibration coefficient H3
        int16_t  dig_H4;    ///< Humidity calibration coefficient H4
        int16_t  dig_H5;    ///< Humidity calibration coefficient H5
        int8_t   dig_H6;    ///< Humidity calibration coefficient H6
        int32_t  t_fine;    ///< Fine temperature value
    } BME280_Calib_Data;
    
    /**
    *   \brief Struct holding compensated data.
    *
    *   This structure allows to store the compensated values of
    *   pressure, temperature, and humidity.
    */
    typedef struct {
        uint32_t pressure;   ///< Compensated pressure
        int32_t temperature; ///< Compensated temperature
        uint32_t humidity;   ///< Compensated humidity
    } BME280_Data;
    
    /**
    *   \brief Struct holding uncompensated data.
    *
    *   This structure allows to store the uncompensated values of
    *   pressure, temperature, and humidity.
    */
    typedef struct {
        uint32_t pressure;   ///< Uncompensated pressure
        int32_t  temperature; ///< Uncompensated temperature
        uint32_t humidity;   ///< Uncompensated humidity
    } BME280_Uncomp_Data;
    
    /**
    *   \brief Struct for sensor settings.
    *
    *   This structure allows to store the settings for sensor mode,
    *   oversampling (temperature, pressure, and humidity), filter,
    *   and stanby time.
    */
    typedef struct {
        uint8_t mode;        ///< Sensor mode setting
        uint8_t osr_p;       ///< Pressure oversampling setting
        uint8_t osr_t;       ///< Temperature oversampling setting   
        uint8_t osr_h;       ///< Humidity oversampling setting
        uint8_t filter;      ///< Filter setting
        uint8_t stanby_time; ///< Standby time setting
        uint8_t spi_enable;  ///< SPI enabled
    } BME280_Settings;
    
    /**
    *   \brief BME280 Device structure that holds sensor settings and data.
    */
    typedef struct {
        uint8_t chip_id;                ///< Chip id of the device
        BME280_Calib_Data calib_data;   ///< Structure for calibration data
        BME280_Data data;               ///< Structure for sensor data
        BME280_Uncomp_Data uncomp_data; ///< Structure for uncompensated data
        BME280_Settings settings;       ///< Structure for sensor settings
    } BME280;
    
    /******************************************/
    /*          Function Prototypes           */
    /******************************************/
    /**
    *   \brief Start the BME280 sensor.
    *
    *   This function starts the BME280 sensor. In order to check if the
    *   device is connected on the I2C bus, this function checks if the
    *   device is connected by checking if a start condition is 
    *   acknowledged by the sensor. Then, it also reads the value of the
    *   #BME280_WHO_AM_I_REG_ADDR to check if the value is the expected one.
    *
    *   \param[in] bme280 : Pointer to device struct
    *
    *   \return Result of function execution 
    *   \retval #BME280_E_NULL_PTR -> Null pointer
    *   \retval #BME280_E_COMM_FAIL -> Error during I2C communication
    *   \retval #BME280_E_DEV_NOT_FOUND -> Device not found on I2C bus
    *   \retval #BME280_OK -> Success
    */
    BME280_ErrorCode BME280_Start(BME280* bme280);
    
    /**
    *   \brief Reset the sensor.
    *
    *   This function reset the sensor by writing a 0xB6 value to the 
    *   reset register. The reset is performed using the complete
    *   power-on reset procedure. 
    *
    *
    *   \param[in] bme280 : pointer to device struct
    *   \return Result of function execution 
    *   \retval #BME280_E_NULL_PTR -> Null pointer
    *   \retval #BME280_E_COMM_FAIL -> Error during I2C communication
    *   \retval #BME280_OK -> Success
    */
    BME280_ErrorCode BME280_Reset(BME280* bme280);
    
    /**
    *   \brief Read pressure, temperature and humidity from the sensor, compensate 
    *   them and store in device structures.
    *
    *   This function reads the pressure, temperature, and humidity values from the
    *   sensor, compensates them using the factory calibration data, and stores them
    *   in the device structure with the pointer passed as argument.
    *
    *   The value of sensor_comp determines which data to compensate:
    *
    *    sensor_comp |   Macros
    *   -------------|-------------------
    *        1       | BME280_PRESS
    *        2       | BME280_TEMP
    *        4       | BME280_HUM
    *        7       | BME280_ALL
    *
    *   \param[in] bme280 : pointer to device structure
    *   \param[in] sensor_comp : flag to select which data to be compensated
    *
    *   \return Result of function execution
    *   \retval #BME280_E_NULL_PTR -> Null pointer
    *   \retval #BME280_E_COMM_FAIL -> Error during I2C communication
    *   \retval #BME280_OK -> Success
    */
    BME280_ErrorCode BME280_ReadData(BME280* bme280, uint8_t sensor_comp);
    
    /**
    *   \brief Parse pressure, temperature, and humidity data.
    *
    *   This function parses pressure, temperature, and humidity data
    *   and stores them in the device structure.
    *
    *   \param[in] bme280 : Pointer to device struct
    *   \param[in] reg_data : Array with unparsed sensor data
    */
    void BME280_ParseSensorData(BME280* bme280, uint8_t* reg_data);
    
    /**
    *   \brief Compensate pressure and/or temperature and/or humidity data.
    *
    *   This function can be used to compensated the data of pressure and/or
    *   temperature and/or humidity according to the value of parameter sensor_comp.
    *
    *   \param[in] bme280 : pointer to device structure
    *   \param[in] sensor_comp : variable to select which values to compensate
    *
    *   \return Result of function execution
    *   \retval BME280_OK -> Success
    *   \retval BME280_ERROR -> Error
    */
    BME280_ErrorCode BME280_CompensateData(BME280* bme280, uint8_t sensor_comp);
    
    /**
    *   \brief Get current sensor mode.
    *
    *   This function retrieves the current sensor mode. The value is updated in
    *   the device struct.
    *
    *   \param[in] bme280 : Pointer to device struct.
    *   \return Result of function execution
    *   \retval BME280_OK -> Success
    *   \retval BME280_ERROR -> Error
    */
    BME280_ErrorCode BME280_GetSensorMode(BME280* bme280);
    
    /**
    *   \brief Set humidity oversampling value.
    *
    *   This function sets the value of humidity oversampling by setting the 
    *   appropriate bits in the #BME280_CTRL_HUM_REG_ADDR register. It also
    *   performs a write operation to the #BME280_CTRL_MEAS_REG_ADDR register
    *   because otherwise the changes won't become effective
    *
    *   \param[in] hos : new value of #BME280_Oversampling
    *   \param[in] bme280 : pointer to device struct
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetHumidityOversampling(BME280* bme280, BME280_Oversampling hos);
    
    /**
    *   \brief Set temperature oversampling value.
    *
    *   This function sets the value of temperature oversampling by setting the 
    *   appropriate bits in the #BME280_CTRL_MEAS_REG_ADDR register. 
    *
    *   \param[in] bme280 : pointer to device struct
    *   \param[in] tos : new value of #BME280_Oversampling
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetTemperatureOversampling(BME280* bme280, BME280_Oversampling tos);
    
    /**
    *   \brief Set pressure oversampling value.
    *
    *   This function sets the value of pressure oversampling by setting the 
    *   appropriate bits in the #BME280_CTRL_MEAS_REG_ADDR register. 
    *
    *   \param[in] bme280 : pointer to device struct
    *   \param[in] pos : new value of #BME280_Oversampling
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetPressureOversampling(BME280* bme280, BME280_Oversampling pos);
    
    
    /**
    *   \brief Read status register of the sensor.
    *
    *   This function reads the #BME280_STATUS_REG_ADDR, that contains two bit ([3] and [0])
    *   which indicate the status of the device.
    *
    *   \param[out] value : Value read from the status register
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_ReadStatusRegister(uint8_t* value);
    
    /**
    *   \brief Set device in sleep mode.
    *
    *   This function sets the device in sleep mode by setting the appropriate
    *   bits in the #BME280_CTRL_MEAS_REG_ADDR.
    *
    *   \param[in] bme280 : pointer to device struct
    *   
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetSleepMode(BME280* bme280);
    
    /**
    *   \brief Set device in forced mode.
    *
    *   This function sets the device in forced mode by setting the appropriate
    *   bits in the #BME280_CTRL_MEAS_REG_ADDR.
    *
    *   \param[in] bme280 : pointer to device struct
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetForcedMode(BME280* bme280);
    
    /**
    *   \brief Set device in normal mode.
    *
    *   This function sets the device in normal mode by setting the appropriate
    *   bits in the #BME280_CTRL_MEAS_REG_ADDR.
    *
    *   \param[in] bme280 : pointer to device struct
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetNormalMode(BME280* bme280);
    
    /**
    *   \brief Set the value of TStandby.
    *
    *   This function sets the new value for the inactive time (TStandby)
    *   during the normal mode. For futher information see the documentation
    *   for the register #BME280_CONFIG_REG_ADDR
    *
    *   \param[in] bme280 : pointer to device struct
    *   \param[in] t_standby : stanby time 
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetStandbyTime(BME280* bme280, BME280_TStandby t_standby);
    
    /**
    *   \brief Set the value of IIR Filter time constant.
    *
    *   This function sets the new value for the time constant of the 
    *   IIR filter. For futher information see the documentation
    *   for the register #BME280_CONFIG_REG_ADDR
    *
    *   \param[in] bme280 : pointer to device struct
    *   \param[in] filter : value for IIR filter
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_SetIIRFilter(BME280* bme280, BME280_Filter filter);
    
    /**
    *   \brief Enable the SPI interface of the sensor.
    *
    *   This function enables the SPI interface of the sensors.
    *
    *   \param[in] bme280 : pointer to device struct
    *
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_EnableSPI(BME280* bme280);
    
    /**
    *   \brief Disable the SPI Interface
    *
    *   \param[in] bme280 : pointer to device struct
    *
    *   This function disables the SPI interface of the sensors.
    *   \return Result of function execution 
    *   \retval BME280_I2C_ERROR -> Error during I2C communication
    *   \retval BME280_ERROR -> Generic error
    *   \retval BME280_OK -> Success
    */
    BME280_ErrorCode BME280_DisableSPI(BME280* bme280);
#endif


/* [] END OF FILE */
