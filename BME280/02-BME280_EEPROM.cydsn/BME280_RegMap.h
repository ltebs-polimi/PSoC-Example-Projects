/**
*   \file BME280_RegMap.h
*
*   \brief Register map header for the BME280 sensor.
*
*   This header file contains all the macros for the registers of the
*   BME280 temperature, humidity, and pressure sensor. 
*
*   \author Davide Marzorati
*   \date October 18, 2019
*/

#ifndef __BME280_REG_MAP_H
    #define __BME280_REG_MAP_H
    

    /**
    *   \brief Who Am I register.
    *
    *   This register contains the chip ID for the BME280 sensor and can be read
    *   after the power on cycle of the sensor. It is a read-only register and
    *   contains the byte 0x60.
    */
    #ifndef BME280_WHO_AM_I_REG_ADDR
        #define BME280_WHO_AM_I_REG_ADDR 0xD0
    #endif
    
    /**
    *   \brief Reset register.
    *
    *   This register can be used to reset the sensor. If the value 0xB6 is written
    *   to the register, the device is reset using the complete power-on reset
    *   procedure. Writing other values than 0xB6 has no effect.
    */
    #ifndef BME280_RESET_REG_ADDR
        #define BME280_RESET_REG_ADDR 0xE0
    #endif
    
    /**
    *   \brief Configuration of humidity data acquisition.
    *
    *   The #BME280_CTRL_HUM_REG_ADDR register sets the humidity data acquisition options of the device. Changes
    *   to this register only becomes effective after a write operation to the register #BME280_CTRL_MEAS_REG_ADDR.
    *
    * |Bit [2:0]   | Humidity oversampling           |   
    * |:-----------:|---------------------------------|
    * |000         | Skipped (Output set to 0x8000)  |
    * |001         | Oversampling x 1                |
    * |010         | Oversampling x 2                |
    * |011         | Oversampling x 4                |
    * |100         | Oversampling x 8                |
    * |101, others | Oversampling  16                |
    */
    #ifndef BME280_CTRL_HUM_REG_ADDR
        #define BME280_CTRL_HUM_REG_ADDR 0xF2
    #endif
    
    /**
    *   \brief Status register.
    *
    *   The status register contains two bits which indicate the status of the device.
    *   
    *   | Bit | Name         | Description                                                                                                |
    *   |-----|--------------|------------------------------------------------------------------------------------------------------------|
    *   | 3   | measuring[0] | Automatically set to 1 whenever a conversion is running. 0 when results have been transferred to registers.|
    *   | 0   | im_update[0] | Automatically set to 1 when NVM data are being copied to register. 0 when copying is done.                 |
    */
    #ifndef BME280_STATUS_REG_ADDR
        #define BME280_STATUS_REG_ADDR 0xF3
    #endif
    
    /**
    *   \brief Pressure and temperature acquisistion options.
    *
    *   This register sets the pressure and temperature data acquisition options of the device. The register
    *   needs to be written after changing #BME280_CTRL_HUM_REG_ADDR for the changes to become effective.
    *   
    *   |Bit  | Name       | Description                             |
    *   |-----|------------|-----------------------------------------|
    *   |[7:5]|osrs_t[2:0] | Temperature data oversampling           |
    *   |[4:2]|osrs_p[2:0] | Pressure data oversampling              |
    *   |[1:0]|mode[1:0]   |Controls the sensor mode of the device   |
    *
    *   |osrs_t[2:0]    | Temperature oversampling       |
    *   |---------------|--------------------------------|
    *   |   000         | Skipped (output set to 0x80000)|
    *   |   001         | Oversampling x 1               |
    *   |   010         | Oversampling x 2               |   
    *   |   011         | Oversampling x 4               |
    *   |   100         | Oversampling x 8               | 
    *   |   101, others | Oversampling x 16              |   
    *
    *   |osrs_p[2:0]    | Pressure oversampling            |
    *   |---------------|----------------------------------|
    *   |   000         | Skipped (output set to 0x80000)  |
    *   |   001         | Oversampling x 1                 |
    *   |   010         | Oversampling x 2                 |
    *   |   011         | Oversampling x 4                 |
    *   |   100         | Oversampling x 8                 |
    *   |   101, others | Oversampling x 16                |
    *
    *   |mode[1:0]   | Mode       |
    *   |------------|------------|
    *   |    00      | Sleep mode |
    *   |  01 and 10 | Forced mode|
    *   |    11      | Normal mode|
    */
    #ifndef BME280_CTRL_MEAS_REG_ADDR
        #define BME280_CTRL_MEAS_REG_ADDR 0xF4
    #endif
    
    
    /**
    *   \brief Configuration register for the sensor.
    *
    *   The config register sets the rate, filter, and interface options of the 
    *   device. Writes to the config register in normal mode may be ignored. In
    *   sleep mode writes are not ignored.
    *
    *   |Bit  | Name      | Description                                      |
    *   |-----|-----------|--------------------------------------------------|
    *   |[7:5]|t_sb[2:0]  | Controls inactive time in normal mode            |
    *   |[4:2]|filter[2:0]| Controls the time constant of the IRR filter     |
    *   |[1]  |           | Reserved                                         |
    *   |[0]  |spi3w_en[0]|Enableds 3-wire SPI interface when set to 1.      |
    *
    *   |t_sb[2:0] | Stanby Time (ms)|
    *   |------------|-------------------------|
    *   |   000      | 0.5
    *   |   001      | 62.5
    *   |   010      | 125
    *   |   011      | 250
    *   |   100      | 500
    *   |   101      | 1000
    *   |   110      | 10
    *   |   111      | 20
    *
    *   |filter[2:0] | Filter coefficient       |
    *   |------------|------------------------- |
    *      000      | Filter off
    *      001      | 2
    *      010      | 4
    *      011      | 8
    *      100 and others     | 16
    */
    #ifndef BME280_CONFIG_REG_ADDR
        #define BME280_CONFIG_REG_ADDR 0xF5
    #endif
    
    /**
    *   \brief MSB of raw pressure measurement output data.
    *
    *   The press registers contains the raw pressure measurement output data [19:0]. 
    *
    *   | Register      | Name | Description |
    *   |---------------|------|-------------|
    *   | 0xF7          | press_msb[7:0] | MSB part up [19:12] of the raw pressure measurement data |
    *   | 0xF8          | press_lsb[7:0] | LSB part up [11:4] of the raw pressure measurement data  |
    *   | 0xF9 [7:4]    | press_xlsb[3:0]| XLSB part up[3:0] of the raw pressure measurement data   |
    */
    #ifndef BME280_PRESS_MSB_REG_ADDR
        #define BME280_PRESS_MSB_REG_ADDR 0xF7
    #endif
    
    /**
    *   \brief LSB of raw pressure measurement output data.
    */
    #ifndef BME280_PRESS_LSB_REG_ADDR
        #define BME280_PRESS_LSB_REG_ADDR 0xF8
    #endif
    
    /**
    *   \brief XLSB of raw pressure measurement output data.
    */
    #ifndef BME280_PRESS_XLSB_REG_ADDR
        #define BME280_PRESS_XLSB_REG_ADDR 0xF9
    #endif
    
    /**
    *   \brief MSB of raw temperature measurement output data.
    *
    *   The temp registers contains the raw temperature measurement output data [19:0]. 
    *
    *   | Register      | Name | Description |
    *   |---------------|------|-------------|
    *   | 0xFA          | temp_msb[7:0] | MSB part up [19:12] of the raw temperature measurement data |
    *   | 0xFB          | temp_lsb[7:0] | LSB part up [11:4] of the raw temperature measurement data  |
    *   | 0xFC [7:4]    | temp_xlsb[3:0]| XLSB part up[3:0] of the raw temperature measurement data   |
    */
    #ifndef BME280_TEMP_MSB_REG_ADDR
        #define BME280_TEMP_MSB_REG_ADDR 0xFA
    #endif
    
    /**
    *   \brief LSB of raw temperature measurement output data.
    */
    #ifndef BME280_TEMP_LSB_REG_ADDR
        #define BME280_TEMP_LSB_REG_ADDR 0xFB
    #endif
    
    /**
    *   \brief XLSB of raw temperature measurement output data.
    */
    #ifndef BME280_TEMP_XLSB_REG_ADDR
        #define BME280_TEMP_XLSB_REG_ADDR 0xFC
    #endif
    
    /**
    *   \brief MSB of raw humidity measurement output data.
    * 
    *   | Register      | Name | Description |
    *   |---------------|------|-------------|
    *   | 0xFD          | hum_msb[7:0] | MSB part up [15:8] of the raw humidity measurement data |
    *   | 0xFE          | hum_lsb[7:0] | LSB part up [7:0] of the raw humidity measurement data  |
    */
    #ifndef BME280_HUM_MSB_REG_ADDR
        #define BME280_HUM_MSB_REG_ADDR 0xFD
    #endif
    
    /**
    *   \brief LSB of raw humidity measurement output data.
    *
    */
    #ifndef BME280_HUM_LSB_REG_ADDR
        #define BME280_HUM_LSB_REG_ADDR 0xFE
    #endif
    
    /**
    *   \brief Temperature and pressure calibration register.
    *
    *   This is the base register address where temperature and pressure 
    *   calibration values are stored. The registers addresses are from 0xF0 to 0xE1.
    */
    #ifndef BME280_CALIB_TEMP_PRESS_REG_ADDR
        #define BME280_CALIB_TEMP_PRESS_REG_ADDR 0x88
    #endif

    /**
    *   \brief Humidity calibration register.
    *
    *   This is the base register address where humidity calibration values
    *   are stored. The registers addresses are from 0xA1 to 0x88.
    */
    #ifndef BME280_CALIB_HUM_REG_ADDR
        #define BME280_CALIB_HUM_REG_ADDR 0xE1
    #endif
    
#endif

/* [] END OF FILE */
