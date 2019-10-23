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
    * Bit [2:0] | Humidity oversampling
    * ----|----------------------------
    * 000 | Skipped (Output set to 0x8000)
    * 001 | Oversampling x 1
    * 010 | Oversampling x 2
    * 011 | Oversampling x 4
    * 100 | Oversampling x 8
    * 101, others | Oversampling  16
    */
    #ifndef BME280_CTRL_HUM_REG_ADDR
        #define BME280_CTRL_HUM_REG_ADDR 0xF2
    #endif
    
    /**
    *   \brief Status register.
    *
    *   The status register contains two bits which indicate the status of the device.
    *   
    *   Bit | Name | Description
    *   ----|------|------------
    *   3   | measuring[0] | Automatically set to 1 whenever a conversion is running. 0 when results have been transferred to registers.
    *   0   | im_update[0] | Automatically set to 1 when NVM data are being copied to register. 0 when copying is done.
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
    *   //TODO add register description
    */
    #ifndef BME280_CTRL_MEAS_REG_ADDR
        #define BME280_CTRL_MEAS_REG_ADDR 0xF4
    #endif
    
    /**
    *   \brief Humidity MSb.
    *
    *   This register contains LSb of the humidity measurement.
    */
    #ifndef BME280_HUM_MSB
        #define BME280_HUM_MSB 0xFD
    #endif
    
    /**
    *   \brief Humidity LSb.
    *
    *   This register contains LSb of the humidity measurement.
    */
    #ifndef BME280_HUM_LSB
        #define BME280_HUM_LSB 0xFE
    #endif
    
#endif

/* [] END OF FILE */
