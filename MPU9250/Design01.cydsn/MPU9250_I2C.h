/** @file MPU9250_I2C.h
 * @brief Header file for I2C communication.
 *    
 * This header file contains macros and function
 * prototypes to perform I2C communication with 
 * the MPU9250.
 *
 * @author Davide Marzorati
 * @date 29 March, 2019
*/
  
#ifndef __MPU9250_I2C_H_
    
    #define __MPU9250_I2C_H_
    
    // Include required libraries
    
    #include "cytypes.h"
    #include "I2C_MPU9250_Master.h"

    /*
    * Function prototypes
    */

    /**
     * @brief  Read a single byte from a slave.
     * 
     * This function reads a single byte from the slave with the address
     *         passed as a parameter from the specified register.
     * @param[in] address: 7 bit slave address, right aligned, bits 6:0 are used
     * @param[in] reg: register address to read from
     * @return the byte read from the slave register
     */
    uint8_t MPU9250_I2C_Read(uint8_t address, uint8_t reg);

    /**
     * @brief  Read multi bytes from a slave.
     *
     * This function reads multiple bytes from the slave with the address
     *         passed as a parameter from the specified register. The number of bytes 
     *         to read is specified by parameter count
     * @param[in]   address: 7 bit slave address, right aligned, bits 6:0 are used
     * @param[in]   reg: register address to read from
     * @param[out]  *data: address of data array where data are stored
     * @param[in]   count: number of bytes to be read
     * @return Nothing
     */
    void MPU9250_I2C_ReadMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

    /**
     * @brief  Read byte from slave without specifying register address
     * 
     * This function reads a single byte from the slave with the address
     *         passed as a parameter without specififying the address of the register
     * @param[in]  address: 7 bit slave address, right aligned, bits 6:0 are used
     * @return  Data from slave
     */
    uint8_t MPU9250_I2C_ReadNoRegister(uint8_t address);

    /**
     * @brief  Read multiple bytes from slave without specifying start register address
     *
     * This function reads multiple bytes from the slave with the address
     *         passed as a parameter without specififying the address of the register
     * @param[in]  address: 7 bit slave address, right aligned, bits 6:0 are used
     * @param[out] *data: pointer to data array to store data from slave
     * @param[in]  count: number of bytes to be read
     * @return Nothing
     */
    void MPU9250_I2C_ReadMultiNoRegister(uint8_t address, uint8_t* data, uint16_t count);

    /**
     * @brief  Write single byte to slave
     * 
     * This function writes a single byte to the slave with the address
     *         passed as a parameter to the register address specified as a parameter
     * @param[in]  address: 7 bit slave address, right aligned, bits 6:0 are used
     * @param[in]  reg: register address to write to
     * @param[in]  data: data to be written
     * @return Nothing
     */
    void MPU9250_I2C_Write(uint8_t address, uint8_t reg, uint8_t data);

    /**
     * @brief  Write multi bytes to slave
     * 
     * This function writes multiple bytes to the slave with the address
     *         passed as a parameter to the register address specified as a parameter
     * @param[in]  address: 7 bit slave address, right aligned, bits 6:0 are used
     * @param[in]  reg: register address to write to
     * @param[in]  *data: pointer to data array to be written
     * @param[in]  count: number of bytes to be written
     * @return Nothing
     */
    void MPU9250_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t *data, uint16_t count);

    /**
     * @brief  Writes byte to slave without specifying register address
     * 
     *  This function writes a single byte to the slave with the address passed
     *  as a parameter without specifiying the register address
     *  Useful if you have I2C device to read like that:
     *      - I2C START
     *      - SEND DEVICE ADDRESS
     *      - SEND DATA BYTE
     *      - I2C STOP
     *
     * @param  address: 7 bit slave address, left aligned, bits 6:0 are used
     * @param  data: data byte which will be send to device
     * @return Nothing
     */
    void MPU9250_I2C_WriteNoRegister(uint8_t address, uint8_t data);

    /**
     * @brief  Writes multiple bytes to slave without setting start register address
     * 
     *  This function writes multiple bytes to the slave with the address passed
     *  as a parameter without specifiying the register address to start from
     *  Useful if you have I2C device to read like that:
     *    - I2C START
     *    - SEND DEVICE ADDRESS
     *    - SEND DATA BYTE
     *    - I2C STOP
     *
     * @param[in]  address: 7 bit slave address, left aligned, bits 6:0 are used, LSB bit is not used
     * @param[in]  *data: pointer to data array to write data to slave
     * @param[in]  count: number of bytes to be written
     * @return Nothing
     */
    void MPU9250_I2C_WriteMultiNoRegister(uint8_t address, uint8_t* data, uint16_t count);

    #endif
/* [] END OF FILE */
