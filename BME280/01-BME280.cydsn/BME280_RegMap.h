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
    
#endif

/* [] END OF FILE */
