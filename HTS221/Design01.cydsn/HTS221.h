/**
*   \file HTS221.h
*
*   This header file contains all the macros and function
*   declarations required to communicate with a HTS221
*   temperature and relative humidity sensor using I2C
*   protocol. This interface depends on the I2C_Interface,
*   so you can easily change that functions and leave the 
*   one implemented here if your hardware is different.
*   
*   \author Davide Marzorati
*   \date September 12, 2019
*/
#ifndef __HTS221_H
    #define __HTS221_H
    
    #include "cytypes.h"
    #include "ErrorCodes.h"
    
    /******************************************************/
    /*                  I2C MACROS                        */
    /******************************************************/
    /**
    *   \brief 7-bit I2C address of HTS221.
    */
    #ifndef HTS221_I2C_ADDRESS
        #define HTS221_I2C_ADDRESS 0x5F
    #endif
        
    /******************************************************/
    /*                  Registers                         */
    /******************************************************/

    /**
    *   \brief WHO AM I Register address.
    *   
    *   This read only register contains the device identifier, set to 0xBC.
    *
    *  7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 
    * ---|---|---|---|---|---|---|---
    *  1 | 0 | 1 | 1 | 1 | 1 | 0 | 0
    */
    #ifndef HTS221_WHO_AM_I_REG
        #define HTS221_WHO_AM_I_REG 0x0F
    #endif
    
    /**
    *   \brief WHO AM I Register value.
    */
    #ifndef HTS221_WHO_AM_I
        #define HTS221_WHO_AM_I 0xBC
    #endif

    /**
    *   \brief Resolution configuration register address.
    *
    *   This register is used to set humidity and temperature resolution resolution.
    *
    * Bytes | Description
    * ------|-------------
    * [7:6] | Reserved
    * [5:3] | AVGT2-0: To select the numbers of averaged temperature samples (2-256)
    * [2:0] | AVGH2-0: To select the numbers of averaged humidity samples (4-512)
    *
    * See Table 16 of device datasheet.
    *
    */
    #ifndef HTS221_AV_CONF_REG
        #define HTS221_AV_CONF_REG 0x10
    #endif

    /**
    *   \brief Control register 1 address.
    *
    *   This is the first of three control register.
    *
    *   Bytes | Description
    *   ------|-------------
    *   [7]   |  PD: power-down control (0: power-down mode; 1: active mode)
    *   [6:3] |  Reserved
    *   [2]   |  BDU: block-data update
    *   [1:0] |  ODR1, ODR0: output data rate selection (see Table below)
    *
    *   The BDU bit is used to inhibit the output register update between the reading of the
    *   upper and lower register parts. In default mode (BDU=0), the lower and upper register
    *   parts are updated continuously. If it is not certain whether the read will be faster than
    *   output data rate, it is reccomended to set the BDU bit to 1.
    *
    *   ODR1 | ORD0 | Humidity (Hz) | Temperature (Hz)
    *   -----|------|---------------|------------------
    *   0    |  0   |   One-shot                     ||
    *   0    |  1   |   1 Hz | 1 Hz |
    *   1    |  0   |   7 Hz | 7 Hz |
    *   1    |  1   |   12.5 Hz | 12.5 Hz |

    */
    #ifndef HTS221_CTRL_REG_1
        #define HTS221_CTRL_REG_1 0x20
    #endif

    /**
    *   \brief Control register 2 address.
    *
    *   This is the second contorl register.
    *
    *   Bytes | Description
    *   ------|-------------
    *   [7]   |  BOOT: Reboot memory content (0: normal mode, 1: reboot content)
    *   [6:2] |  Reserved
    *   [1]   |  Heater (0: heater disable; 1: heater enable)
    *   [0]   |  One-shot enable (0: waiting for start of conversion; 1: start for a new dataset)
    *   
    *   The **BOOT** bit is used to refresh the content of the internal registers stored in the
    *   Flash memory block. At device power-up, the content of the Flash memory block is 
    *   transferred to the internal registers related to trimming functions to permit good
    *   behaviour of the device itself. If, for any reason, the content of the trimming 
    *   registers is modified, it is sufficient to use this bit to restore the correct values.
    *
    *   The **ONE_SHOT** bit is used to start a new conversion. In this situation a single
    *   acquisition of temperature and humidity is started when the ONE_SHOT bit is set to 1. 
    *   At the end of conversion the new data are available in the output registers, the 
    *   STATUS_REG[1:0] are set to 1 and the ONE_SHOT bit comes back to 0 by hardware.
    *
    *   The **Heater** bit is used to control an internal heating element that can effectively
    *   be used to speed up the sensor recovery time in case of condensation. Humidity and 
    *   temperature should not be read during the heating cycle; valid data can be read out once
    *   the heater has been turned off, after the completion of the heatin cycle.
    */
    #ifndef HTS221_CTRL_REG_2
        #define HTS221_CTRL_REG_2 0x21
    #endif

    /**
    *   \brief Control register 3 address.
    *
    *   Third, and last, control register.
    *   Bytes | Description
    *   ------|------------
    *   [7]    | DRDY_H_L: Data Ready output signal active high, low (0: active high)
    *   [6]    | PP_OD: Push-pull / Open Drain selection on DRDY (0: push-pull)
    *   [5:3]  | Reserved
    *   [2]    | DRDY_EN: Data Ready enable (0: Data Ready disabled)
    *   [1:0]  | Reserved
    *
    *   The **DRDY_EN** bit enables the DRDY signal on pin 3. Normally inactive, the DRDY output
    *   signal becomes active on new data available: logical OR of the bits STATUS_REG[1] and
    *   STATUS_REG[0] for humidity and temperature, respectively. The DRDY signal returns
    *   inactive after both HUMIDITY_OUT_H and TEMP_OUT_H register are read.
    */
    #ifndef HTS221_CTRL_REG_3
        #define HTS221_CTRL_REG_3 0x22
    #endif

    /**
    *   \brief Status register address.
    *
    *   The content of this register is updated every one-shot reading, and after 
    *   completion of every ODR cycle, regardless of the BDU value in
    *   #HTS221_CTRL_REG_1.
    * 
    *   Bytes | Description
    *   ------|------------
    *   [7:2]  | Reserved
    *   [1]    | H_DA: Humidity data available.
    *   [0]    | T_DA: Temperature data available.
    *
    *   H_DA: 0 if new data for humidity is not yet available; 
    *   1 if new data for humidity is available. H_DA is cleared anytime
    *   #HTS221_HUMIDITY_OUT_H_REG register is read.
    *
    *   T_DA: 0 if new data for temperature is not yet available; 1 if new data 
    *   for temperature is available. T_DA is cleared
    *   anytime #HTS221_TEMP_OUT_H_REG register is read.
    */
    #ifndef HTS221_STATUS_REG
        #define HTS221_STATUS_REG 0x27
    #endif

    /**
    *   \brief Relative humidity LSB register address
    */
    #ifndef HTS221_HUMIDITY_OUT_L_REG
        #define HTS221_HUMIDITY_OUT_L_REG 0x28
    #endif

    /**
    *   \brief Relative humidity MSB register address
    */
    #ifndef HTS221_HUMIDITY_OUT_H_REG
        #define HTS221_HUMIDITY_OUT_H_REG 0x29
    #endif

    /**
    *   \brief Temperature LSB register address
    */
    #ifndef HTS221_TEMP_OUT_L_REG
        #define HTS221_TEMP_OUT_L_REG 0x2A
    #endif

    /**
    *   \brief Temperature MSB register address
    */
    #ifndef HTS221_TEMP_OUT_H_REG
        #define HTS221_TEMP_OUT_H_REG 0x2B
    #endif

    /*****   Calibration Coefficients Registers     *****/

    /**
    *   \brief Calibration register for value H0_rH_x2.
    */
    #ifndef HTS221_H0_rH_x2_REG
        #define HTS221_H0_rH_x2_REG 0x30
    #endif

    /**
    *   \brief Calibration register for value H1_rH_x2.
    */
    #ifndef HTS221_H1_rH_x2_REG
        #define HTS221_H1_rH_x2_REG 0x31
    #endif

    /**
    *   \brief Calibration register for value T0_degC_x8.
    */
    #ifndef HTS221_T0_degC_x8_REG
        #define HTS221_T0_degC_x8_REG 0x32
    #endif

    /**
    *   \brief Calibration register for value T1_degC_x8.
    */
    #ifndef HTS221_T1_degC_x8_REG
        #define HTS221_T1_degC_x8_REG 0x33
    #endif

    /**
    *   \brief Calibration register for value T1/T0 msb.
    */
    #ifndef HTS221_T1_T0_MSB_REG
        #define HTS221_T1_T0_MSB_REG 0x35
    #endif

    /**
    *   \brief Calibration register for MSb value H0_T0_OUT.
    */
    #ifndef HTS221_H0_T0_OUT_L_REG
        #define HTS221_H0_T0_OUT_L_REG 0x36
    #endif

    /**
    *   \brief Calibration register for LSb value H0_T0_OUT.
    */
    #ifndef HTS221_H0_T0_OUT_H_REG
        #define HTS221_H0_T0_OUT_H_REG 0x37
    #endif

    /**
    *   \brief Calibration register for MSb value H1_T0_OUT.
    */
    #ifndef HTS221_H1_T0_OUT_L_REG
        #define HTS221_H1_T0_OUT_L_REG 0x3A
    #endif

    /**
    *   \brief Calibration register for LSb value H1_T0_OUT.
    */
    #ifndef HTS221_H1_T0_OUT_H_REG
        #define HTS221_H1_T0_OUT_H_REG 0x3B
    #endif

    /**
    *   \brief Calibration register for MSb value T0_OUT.
    */
    #ifndef HTS221_T0_OUT_L_REG
        #define HTS221_T0_OUT_L_REG 0x3C
    #endif

    /**
    *   \brief Calibration register for LSb value T0_OUT.
    */
    #ifndef HTS221_T0_OUT_H_REG
        #define HTS221_T0_OUT_H_REG 0x3D
    #endif
    
    /**
    *   \brief Calibration register for MSb value T0_OUT.
    */
    #ifndef HTS221_T1_OUT_L_REG
        #define HTS221_T1_OUT_L_REG 0x3E
    #endif

    /**
    *   \brief Calibration register for LSb value T0_OUT.
    */
    #ifndef HTS221_T1_OUT_H_REG
        #define HTS221_T1_OUT_H_REG 0x3F
    #endif

    /******************************************************/
    /*                   TypeDefs                         */
    /******************************************************/

    /**
    *   \brief Error codes returned by functions
    */
    typedef enum 
    {
        HTS221_OK,      //< Everything ok
        HTS221_ERROR    //< Error
    } HTS221_Error;
    
    /**
    *   \brief Data update values
    */
    typedef enum 
    {
        HTS221_UPDATE_BLOCKED,      //< Data update blocked
        HTS221_UPDATE_CONTINUOUS    //< Data update continuous
    } HTS221_DataUpdate;
    
    /**
    *   \brief Codes returned to determine if measurement is ready
    */
    typedef enum 
    {
        HTS221_MEAS_READY,       //< New measurement is ready
        HTS221_MEAS_NOT_READY    //< New measurement is not ready
    } HTS221_Measurement_Ready;
    
    /**
    *   \brief Possible configuration settings for DRDY signal
    */
    typedef enum 
    {
        HTS221_DRDY_ACTIVE_HIGH,  //< DRDY signal active high
        HTS221_DRDY_ACTIVE_LOW    //< DRDY signal active low
    } HTS221_DRDY_Level;
    
    /**
    *   \brief Possible configuration settings for DRDY signal
    */
    typedef enum 
    {
        HTS221_DRDY_PUSH_PULL,    //< DRDY push pull
        HTS221_DRDY_OPEN_DRAIN    //< DRDY open drain
    } HTS221_DRDY_Configuration;
    
    /**
    *   \brief Possible configuration settings for DRDY signal
    */
    typedef enum 
    {
        HTS221_DRDY_ENABLED,    //< DRDY enabled
        HTS221_DRDY_DISABLED    //< DRDY disabled
    } HTS221_DRDY_Enable;
    
    /**
    *   \brief Codes to store if heater is on or off
    */
    typedef enum 
    {
        HTS221_HEATER_ON,       //< Heater ON
        HTS221_HEATER_OFF       //< Heater OFF
    } HTS221_Heater;
    
    /**
    *   \brief Codes to store if sensor is active or not
    */
    typedef enum 
    {
        HTS221_POWER_ON,       //< Power ON
        HTS221_POWER_OFF       //< Power OFF
    } HTS221_Power;
    
    /**
    *   \brief Resolution mode for temperature.
    */
    typedef enum 
    {
        HTS221_AVGT_2,     ///< 2 averaged samples
        HTS221_AVGT_4,     ///< 4 averaged samples
        HTS221_AVGT_8,     ///< 8 averaged samples
        HTS221_AVGT_16,    ///< 16 averaged samples
        HTS221_AVGT_32,    ///< 32 averaged samples
        HTS221_AVGT_64,    ///< 64 averaged samples
        HTS221_AVGT_128,   ///< 128 averaged samples
        HTS221_AVGT_256    ///< 256 averaged samples
    } HTS221_AVGTemperature;

    /**
    *   \brief Resolution mode for humidity.
    */
    typedef enum 
    {
        HTS221_AVGH_4,     ///< 4 averaged samples
        HTS221_AVGH_8,     ///< 8 averaged samples
        HTS221_AVGH_16,    ///< 16 averaged samples
        HTS221_AVGH_32,    ///< 32 averaged samples
        HTS221_AVGH_64,    ///< 64 averaged samples
        HTS221_AVGH_128,   ///< 128 averaged samples
        HTS221_AVGH_256,   ///< 256 averaged samples
        HTS221_AVGH_512,   ///< 512 averaged samples
    } HTS221_AVGHumidity;

    /**
    *   \brief Output data rate choices.
    *
    *   The four choices available for output data rate.
    */
    typedef enum 
    {
        HTS221_ODR_OneShot,    ///< One Shot measurement 
        HTS221_ODR_1Hz,        ///< 1 Hz output data rate update
        HTS221_ODR_7Hz,        ///< 7 Hz output data rate update
        HTS221_ODR_12_5Hz      ///< 12.5 Hz output data rate update
    } HTS221_ODR;

    /**
    *   \brief New data type with HTS221 calibration coefficients.
    *
    *   This struct allows to store HTS221 calibration coefficients
    *   in an unique variable.
    */
    typedef struct {
        uint8_t H0_rH;      ///< H0_rH calibration coefficient
        uint8_t H1_rH;      ///< H1_rH calibration coefficient
        int16_t T0_degC;    ///< T0_degC calibration coefficient
        int16_t T1_degC;    ///< T1_degC calibration coefficient
        int16_t H0_T0_OUT;  ///< H0_T0_OUT calibration coefficient
        int16_t H1_T0_OUT;  ///< H1_T0_OUT calibration coefficient
        int16_t T0_OUT;     ///< T0_OUT calibration coefficient
        int16_t T1_OUT;     ///< T1_OUT calibration coefficient
    } HTS221_CalCoeff;
        
    /**
    *   \brief New data type for HTS221-related data.
    *
    *   This struct allows to store data related to a HTS221 sensor.
    *   It allows to have multiple HTS221 sensors in the same design.
    *   This could happen if you implement or have an I2C multiplexer.
    */
    typedef struct {
        HTS221_CalCoeff coeff;                  ///< Calibration coefficients
        int32_t temperature;                    ///< Temperature value
        uint16_t humidity;                      ///< Humidity value
        HTS221_AVGHumidity avgHum;              ///< Humidity resolution mode
        HTS221_AVGTemperature avgTemp;          ///< Temperature resolution mode
        HTS221_Measurement_Ready measReady;     ///< Flag for measurement ready
        HTS221_Heater heater;                   ///< Flag for heater
        HTS221_Power power;                     ///< Flag for power up
        HTS221_ODR odr;                         ///< Output data rate value
        HTS221_DataUpdate du;                   ///< Data update setting
        HTS221_DRDY_Level drdy_level;           ///< DRDY Signal level
        HTS221_DRDY_Configuration drdy_config;  ///< DRDY Pin Configuration
        HTS221_DRDY_Enable drdy_enable;         ///< DRDY Enable flag
        uint8_t who_am_i_check;                 ///< Flag for who am i check
    } HTS221_Struct;
    
    

    /******************************************************/
    /*              Function Prototypes                   */
    /******************************************************/

    /**
    *   \brief Start the HTS221 sensor.
    *
    *   This function starts the HTS221 by performing the following
    *   operations:
    *   - power up the sensor
    *   - set default resolution mode for temperature
    *   - set default resolution mode for humidity
    *   - set default output data rate
    *   - set the data ready signal
    *   - read calibration coefficients
    *   \return ::HTS221_Error depending on the error generated
    */
    HTS221_Error HTS221_Start(HTS221_Struct* hts221);

    /**
    *   \brief Stop the HTS221 sensor.
    *
    *   This function powers down the HTS221 sensor.
    *   \return ::HTS221_Error depending on the error generated
    */
    HTS221_Error HTS221_Stop(HTS221_Struct* hts221);
    
    /******************************************************/
    /*          Measurement related functions             */
    /******************************************************/
    
    /**
    *   \brief Perform one-shot temperature measurement.
    *   
    *   This function starts a one-shot measurement, waits until the appropriate
    *   bits in the status register have been set (or the specified timeout has
    *   expired), and stores the converted temperature value in the ::HTS221_Struct
    *   passed as parameter. The value of temperature needs to be divided by 10
    *   in order to get the correct value.
    *   \param hts221 a valid pointer to a ::HTS221_Struct 
    *   \param timeout timeout for returning if status register not updated
    *   \return ::HTS221_Error depending on the error generated
    */
    HTS221_Error HTS221_MeasureTemperature(HTS221_Struct* hts221, uint16_t timeout);
    
    /**
    *   \brief Perform one-shot humidity measurement.
    *   
    *   This function starts a one-shot measurement, waits until the appropriate
    *   bits in the status register have been set (or the specified timeout has
    *   expired), and stores the converted and updated humidity value
    *   in the ::HTS221_Struct passed as parameter. The value of humidity 
    *   needs to be divided by 10 in order to get the correct value.
    *   \param hts221 a valid pointer to a ::HTS221_Struct 
    *   \param timeout timeout for returning if status register not updated
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_MeasureHumidity(HTS221_Struct* hts221, uint16_t timeout);
    
    /**
    *   \brief Perform one-shot temperature and humidity measurement.
    *   
    *   This function starts a one-shot measurement, waits until the appropriate
    *   bits in the status register have been set (or the specified timeout has
    *   expired), and stores the converted and updated temperature and humidity values
    *   in the ::HTS221_Struct passed as parameter. The values of temperature and humidity 
    *   need to be divided by 10 in order to get the correct values.
    *   \param hts221 a valid pointer to a ::HTS221_Struct 
    *   \param timeout timeout for returning if status register not updated
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_MeasureTemperatureHumidity(HTS221_Struct* hts221, uint16_t timeout);
    
    /**
    *   \brief Read and convert temperature value.
    *   
    *   This function reads the raw temperature value, converts
    *   it and stores the converted value in the 
    *   ::HTS221_Struct passed in as parameter.
    *   \param hts221 a valid pointer to a ::HTS221_Struct 
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_ReadTemperature(HTS221_Struct* hts221);

    /**
    *   \brief Read and convert humidity value.
    *   
    *   This function reads the raw humidity value, converts
    *   it and stores the converted value in the 
    *   ::HTS221_Struct passed in as parameter.
    *   \param hts221 a valid pointer to a ::HTS221_Struct 
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_ReadHumidity(HTS221_Struct* hts221);
    
    /**
    *   \brief Read and convert temperature and humidity values.
    *   
    *   This function reads the raw temperature and humidity values, converts
    *   them and stores the converted values in the ::HTS221_Struct passed
    *   in as parameter.
    *   \param hts221 a valid pointer to a ::HTS221_Struct 
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_ReadTemperatureHumidity(HTS221_Struct* hts221);
    
    /**
    *   \brief Start one-shot acquisition.
    *
    *   This function enables to perform a one-shot acquisition of temperature
    *   and humidity data.
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_StartOneShot(void);

    /**
    *   \brief Check if a new measurement is ready.
    *
    *   This function checks whether there is a new measurement ready to be read.
    *   \param meas_ready the function will set this to the appropriate value
    *       depending on the HTS221 status register.
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_IsMeasurementReady(HTS221_Measurement_Ready* meas_ready);

    /**
    *   \brief Set the temperature resolution mode.
    *   
    *   This function allows to set the resolution mode for the
    *   temperature measurements. It requires that you specify
    *   the resolution mode. For additional information you can
    *   check Table 16 of the device datasheet.
    *   \param hts221 pointer to HTS221 valid struct
    *   \param avgTemp desired value of average temperature samples to be set
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_SetTemperatureResolution(HTS221_Struct* hts221, 
                                            HTS221_AVGTemperature avgTemp);

    /**
    *   \brief Set the humidity resolution mode.
    *   
    *   This function allows to set the resolution mode for the
    *   humidity measurements. It requires that you specify
    *   the resolution mode. For additional information you can
    *   check Table 16 of the device datasheet.
    *   \param hts221 pointer to HTS221 valid struct
    *   \param avgHum desired value of average humidity samples to be set
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_SetHumidityResolution(HTS221_Struct* hts221,
                                        HTS221_AVGHumidity avgHum);
    
    

    /**
    *   \brief Set the sensor output data rate.
    *   
    *   This function allows to set the output data rate of the sensor.
    *   The choices are defined by the ::HTS221_ODR enum (OneShot, 1, 7, 12.5 Hz).
    *   \param hts221 a valid pointer to a ::HTS221_Struct
    *   \param odr the desired value of output data rate
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_SetOutputDataRate(HTS221_Struct* hts221, HTS221_ODR odr);

    /**
    *   \brief Enable update of data.
    *
    *   This function enables the update of temperature and humidity data
    *   in the output register. This way, the output registers
    *   are continuously updated regardless of whether the MSB and LSB were
    *   read or not.
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_EnableDataupdate(HTS221_Struct* hts221);

    /**
    *   \brief Enable update of data.
    *
    *   This function enables the update of temperature and humidity data
    *   in the output register. This way, the output registers are not 
    *   updated until MSB and LSB reading. Useful it is not certain wheter
    *   the read will be faster than output data rate.
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_BlockDataUpdate(HTS221_Struct* hts221);

    /**
    *   \brief Turn on the internal heating element.
    *
    *   This function turns on the internal heating element of the sensor.
    *   \param hts221 valid pointer to hts221 struct
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_HeaterStart(HTS221_Struct* hts221);

    /**
    *   \brief Turn off the internal heating element.
    *
    *   This function turns off the internal heating element of the sensor.
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong 
    */
    HTS221_Error HTS221_HeaterStop(HTS221_Struct* hts221);

    /**
    *   \brief Read calibration coefficients stored in sensor memory.
    *
    *   This function reads the calibration coefficients stored in the flash memory
    *   of the sensor.
    *   \param hts221 Pointer to a valid ::HTS221_Struct
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_ReadCalibrationCoefficients(HTS221_Struct* hts221);
    
    /**
    *   \brief Reboot memory content.
    *
    *   This function refreshes the content of the internal registers stored in 
    *   the Flash memory block.
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_RebootMemoryContent(void);
    
    /**
    *   \brief Read WHO AM I Register
    *
    *   This function reads the content of the WHO AM I register so that it is 
    *   possible to check if sensor is properly communicating with the MCU.
    *   \param hts221 pointer to valid HTS221 struct
    *   \param reg_val Pointer to a byte where we will store the value read from the register
    *   \return ::HTS221_Error error code
    *       - HTS221_OK if everything was OK
    *       - HTS221_ERROR if something went wrong
    */
    HTS221_Error HTS221_ReadWhoAmI(HTS221_Struct* hts221, uint8_t* reg_val);

    /****************************/
    /****** DRDY Settings  ******/
    /****************************/
    
    /**
    *   \brief Configure DRDY as active low or high.
    *
    *   This function allows to configure the DRDY signal as active low or high.
    *   \param hts221 pointer to valid HTS221 struct
    *   \param drdy_level desired level value for drdy signal (high or low)
    *   \return ::HTS221_Error depending on error generated
    */
    HTS221_Error HTS221_ConfigureDRDYLevel(HTS221_Struct* hts221, HTS221_DRDY_Level drdy_level);
    
    /**
    *   \brief Configure DRDY Pin.
    *
    *   This function allows to configure the DRDY pin as push-pull or open drain.
    *   \param hts221 pointer to valid HTS221 struct
    *   \param drdy_config desired configuration value for the pin
    *   \return ::HTS221_Error depending on error generated
    */
    HTS221_Error HTS221_ConfigureDRDYPin(HTS221_Struct* hts221, HTS221_DRDY_Configuration drdy_config);
    
    /**
    *   \brief Enable Data Ready signal.
    *
    *   This function allows to enable DRDY signal available on pin 3.
    *   \param hts221 pointer to valid HTS221 struct
    *   \return ::HTS221_Error depending on error generated
    */
    HTS221_Error HTS221_EnableDRDY(HTS221_Struct* hts221);
    
    /**
    *   \brief Disable Data Ready signal.
    *
    *   This function allows to disable DRDY signal available on pin 3.
    *   \param hts221 pointer to valid HTS221 struct
    *   \return ::HTS221_Error depending on error generated
    */
    HTS221_Error HTS221_DisableDRDY(HTS221_Struct* hts221);
    
    

#endif
/* [] END OF FILE */
