/** 
 * \file BME280_I2C_Interface.h
 * \brief Hardware specific I2C interface.
 *
 * This is an interface to the I2C peripheral. If you need to port 
 * this C-code to another platform, you could simply replace this
 * interface and still use the code.
 *
 * \author Davide Marzorati
 * \date September 12, 2019
*/

#ifndef __BME280_I2C_Interface_H
    #define __BME280_I2C_Interface_H
    
    #include "cytypes.h"
    #include "BME280_ErrorCodes.h"
    
    /**
    *   \brief Value returned if device present on I2C bus.
    */
    #ifndef BME280_CONNECTED
        #define BME280_CONNECTED 1
    #endif

    /**
    *   \brief Value returned if device not present on I2C bus.
    */
    #ifndef BME280_UNCONNECTED
        #define BME280_UNCONNECTED 0
    #endif
    
    /** \brief Start the I2C peripheral.
    *   
    *   This function starts the I2C peripheral so that it is ready to work.
    */
    BME280_ErrorCode BME280_I2C_Interface_Start(void);
    
    /** \brief Stop the I2C peripheral.
    *   
    *   This function stops the I2C peripheral from working.
    */
    BME280_ErrorCode BME280_I2C_Interface_Stop(void);
    
    /**
    *   \brief Read one byte over I2C.
    *   
    *   This function performs a complete reading operation over I2C from a single
    *   register.
    *   \param[in] device_address I2C address of the device to talk to.
    *   \param[in] register_address Address of the register to be read.
    *   \param[out] data Pointer to a variable where the byte will be saved.
    */
    BME280_ErrorCode BME280_I2C_Interface_ReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data);
    
    /** 
    *   \brief Read multiple bytes over I2C.
    *   
    *   This function performs a complete reading operation over I2C from multiple
    *   registers.
    *   \param[in] device_address I2C address of the device to talk to.
    *   \param[in] register_address Address of the first register to be read.
    *   \param[in] register_count Number of registers we want to read.
    *   \param[out] data Pointer to an array where data will be saved.
    */
    BME280_ErrorCode BME280_I2C_Interface_ReadRegisterMulti(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data);
    /** 
    *   \brief Write a byte over I2C.
    *   
    *   This function performs a complete writing operation over I2C to a single 
    *   register.
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the register to be written.
    *   \param data Data to be written
    */
    BME280_ErrorCode BME280_I2C_Interface_WriteRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t data);
    
    /** 
    *   \brief Write multiple bytes over I2C.
    *   
    *   This function performs a complete writing operation over I2C to multiple
    *   registers
    *   \param device_address I2C address of the device to talk to.
    *   \param register_address Address of the first register to be written.
    *   \param register_count Number of registers that need to be written.
    *   \param data Array of data to be written
    */
    BME280_ErrorCode BME280_I2C_Interface_WriteRegisterMulti(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data);
    
    /**
    *   \brief Check if device is connected over I2C.
    *
    *   This function checks if a device is connected over the I2C lines.
    *   \param device_address I2C address of the device to be checked.
    *   \retval Returns true (>0) if device is connected.
    */
    uint8_t BME280_I2C_Interface_IsDeviceConnected(uint8_t device_address);
    
#endif // I2C_Interface_H
/* [] END OF FILE */
