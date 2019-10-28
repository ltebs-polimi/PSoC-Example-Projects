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
    #include "ErrorCodes.h"
    
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
    *   \brief Error Codes for BME280 functions.
    *
    *   This is a list of error codes that may be returned by the
    *   BME280 Interface.
    */
    typedef enum {
        BME280_I2C_ERROR,   ///< Error during I2C communication with the sensor
        BME280_ERROR,       ///< Generic error
        BME280_OK           ///< No error generated
    } BME280_ErrorCode;
    
    /**
    *   \brief Humidity oversampling values.
    *
    *   This enum contains all the possible values of humidity oversampling.
    */
    typedef enum {
        BME280_HOS_SKIPPED,  ///< Oversampling skipped, output set to 0x8000
        BME280_HOS_x1,       ///< Humidity oversampling x1
        BME280_HOS_x2,       ///< Humidity oversampling x2
        BME280_HOS_x4,       ///< Humidity oversampling x4
        BME280_HOS_x8,       ///< Humidity oversampling x8
        BME280_HOS_x16       ///< Humidity oversampling x16
    } BME280_HumidityOversampling;
    
    /**
    *   \brief Temperature oversampling values.
    *
    *   This enum contains all the possible values of Temperature oversampling.
    */
    typedef enum {
        BME280_TOS_SKIPPED,  ///< Oversampling skipped, output set to 0x8000
        BME280_TOS_x1,       ///< Temperature oversampling x1
        BME280_TOS_x2,       ///< Temperature oversampling x2
        BME280_TOS_x4,       ///< Temperature oversampling x4
        BME280_TOS_x8,       ///< Temperature oversampling x8
        BME280_TOS_x16       ///< Temperature oversampling x16
    } BME280_TemperatureOversampling;
    
    /**
    *   \brief Pressure oversampling values.
    *
    *   This enum contains all the possible values of Pressure oversampling.
    */
    typedef enum {
        BME280_POS_SKIPPED,  ///< Oversampling skipped, output set to 0x8000
        BME280_POS_x1,       ///< Temperature oversampling x1
        BME280_POS_x2,       ///< Temperature oversampling x2
        BME280_POS_x4,       ///< Temperature oversampling x4
        BME280_POS_x8,       ///< Temperature oversampling x8
        BME280_POS_x16       ///< Temperature oversampling x16
    } BME280_PressureOversampling;
    
    
    /**
    *   \brief Start the BME280 sensor.
    *
    *   This function starts the BME280 sensor. In order to check if the
    *   device is connected on the I2C bus, this function checks if the
    *   device is connected by checking if a start condition is 
    *   acknowledged by the sensor. Then, it also reads the value of the
    *   #BME280_WHO_AM_I_REG_ADDR to check if the value is the expected one.
    *
    *   \return #BME280_ErrorCode depending on error generated
    */
    BME280_ErrorCode BME280_Start(void);
    
    /**
    *   \brief Reset the sensor.
    *
    *   This function reset the sensor by writing a 0xB6 value to the 
    *   reset register. The reset is performed using the complete
    *   power-on reset procedure. 
    */
    BME280_ErrorCode BME280_Reset(void);
    
    /**
    *   \brief Read Who Am I register value.
    *
    *   This function reads the value of the Who Am I register.
    *   If everything is set up correctly, you should read 0x60
    *   from it.
    */
    BME280_ErrorCode BME280_ReadWhoAmI(uint8_t* value);
    
    /**
    *   \brief Set humidity oversampling value.
    *
    *   This function sets the value of humidity oversampling by setting the 
    *   appropriate bits in the #BME280_CTRL_HUM_REG_ADDR register. It also
    *   performs a write operation to the #BME280_CTRL_MEAS_REG_ADDR register
    *   because otherwise the changes won't become effective
    *
    *   \param hos new value of #BME280_HumidityOversampling
    */
    BME280_ErrorCode BME280_SetHumidityOversampling(BME280_HumidityOversampling hos);
    
    /**
    *   \brief Set temperature oversampling value.
    *
    *   This function sets the value of temperature oversampling by setting the 
    *   appropriate bits in the #BME280_CTRL_MEAS_REG_ADDR register. 
    *
    *   \param tos new value of #BME280_TemperatureOversampling
    */
    BME280_ErrorCode BME280_SetTemperatureOversampling(BME280_TemperatureOversampling tos);
    
    /**
    *   \brief Set pressure oversampling value.
    *
    *   This function sets the value of pressure oversampling by setting the 
    *   appropriate bits in the #BME280_CTRL_MEAS_REG_ADDR register. 
    *
    *   \param tos new value of #BME280_PressureOversampling
    */
    BME280_ErrorCode BME280_SetPressureOversampling(BME280_PressureOversampling pos);
    
    
    /**
    *   \brief Read status register of the sensor.
    *
    *   This function reads the #BME280_STATUS_REG_ADDR, that contains two bit ([3] and [0])
    *   which indicate the status of the device.
    */
    BME280_ErrorCode BME280_ReadStatusRegister(void);
    
#endif


/* [] END OF FILE */
