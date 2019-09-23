/*
* This file includes all the required source code to interface
* the I2C peripheral.
* 
* Since it is intended to be general and flexible, you need to replace
* the macro definition of I2C_Peripheral_Name by providing the correct
* name of your I2C interface.
*
*/

#warning // Replace I2C_Master with the name of the I2C peripheral in your designTE
#define I2C_Peripheral_Name(fn) I2C_Master_ ## fn
#define I2C_Peripheral_Name_Header_File "I2C_Master.h"

/**
*   \brief I2C Write operation for start condition.
*/
#ifndef I2C_WRITE
    #define I2C_WRITE 0
#endif

/**
*   \brief I2C Read operation for start condition.
*/
#ifndef I2C_READ
    #define I2C_READ 1
#endif

/**
*   \brief No master acknowledgement in reading operations.
*/
#ifndef I2C_NACK
    #define I2C_NACK 0
#endif

/**
*   \brief Master acknowledgement in reading operations.
*/
#ifndef I2C_ACK
    #define I2C_ACK 1
#endif

/**
*   \brief Value returned if device present on I2C bus.
*/
#ifndef DEVICE_CONNECTED
    #define DEVICE_CONNECTED 1
#endif

/**
*   \brief Value returned if device not present on I2C bus.
*/
#ifndef DEVICE_UNCONNECTED
    #define DEVICE_UNCONNECTED 0
#endif

#include "I2C_Interface.h" 
#include I2C_Peripheral_Name_Header_File

    ErrorCode I2C_Peripheral_Start(void) 
    {
        // Start I2C peripheral
        I2C_Peripheral_Name(Start)();  
        I2C_Peripheral_Name(Start)();
        // Return no error since start function does not return any error
        return NO_ERROR;
    }
    
    
    ErrorCode I2C_Peripheral_Stop(void)
    {
        // Stop I2C peripheral
        I2C_Peripheral_Name(Stop)();
        // Return no error since stop function does not return any error
        return NO_ERROR;
    }

    ErrorCode I2C_Peripheral_ReadRegister(uint8_t device_address, 
                                            uint8_t register_address,
                                            uint8_t* data)
    {
        // Send start condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address,I2C_WRITE);
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            // Write address of register to be read
            error = I2C_Peripheral_Name(MasterWriteByte)(register_address);
            if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
            {
                // Send restart condition
                error = I2C_Peripheral_Name(MasterSendRestart)(device_address, I2C_READ);
                if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
                {
                    // Read data without acknowledgement
                    *data = I2C_Peripheral_Name(MasterReadByte)(I2C_NACK);
                    // Send stop condition and return no error
                    I2C_Peripheral_Name(MasterSendStop)();
                    return NO_ERROR;
                }
            }
        }
        // Send stop condition if something went wrong
        I2C_Peripheral_Name(MasterSendStop)();
        // Return error code
        return BAD_PARAMETER;
    }
    
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data)
    {
        // Send start condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address,I2C_WRITE);
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            // Write address of register to be read with the MSB equal to 1
            register_address |= 0x80;
            error = I2C_Peripheral_Name(MasterWriteByte)(register_address);
            if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
            {
                // Send restart condition
                error = I2C_Peripheral_Name(MasterSendRestart)(device_address, I2C_READ);
                if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
                {
                    // Continue reading until we have register to read
                    uint8_t counter = register_count;
                    while(counter>1)
                    {
                        data[register_count-counter] =
                            I2C_Peripheral_Name(MasterReadByte)(I2C_ACK);
                        counter--;
                    }
                    // Read last data without acknowledgement
                    data[register_count-1]
                        = I2C_Peripheral_Name(MasterReadByte)(I2C_NACK);
                    // Send stop condition and return no error
                    I2C_Peripheral_Name(MasterSendStop)();
                    return NO_ERROR;
                }
            }
        }
        // Send stop condition if something went wrong
        I2C_Peripheral_Name(MasterSendStop)();
        // Return error code
        return BAD_PARAMETER;
    }
    
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t data)
    {
        // Send start condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address, I2C_WRITE);
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            // Write register address
            error = I2C_Peripheral_Name(MasterWriteByte)(register_address);
            if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
            {
                // Write byte of interest
                error = I2C_Peripheral_Name(MasterWriteByte)(data);
                if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
                {
                    // Send stop condition
                    I2C_Peripheral_Name(MasterSendStop)();
                    // Return with no error
                    return NO_ERROR;
                }
            }
        }
        // Send stop condition in case something didn't work out correctly
        I2C_Peripheral_Name(MasterSendStop);
        // Return error code
        return BAD_PARAMETER;
    }
    
    ErrorCode I2C_Peripheral_WriteRegisterMulti(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data)
    {
        // Send start condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address, I2C_WRITE);
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            // Write register address
            error = I2C_Peripheral_Name(MasterWriteByte)(register_address);
            if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
            {
                // Continue writing until we have data to write
                uint8_t counter = register_count;
                while(counter >= 0)
                {
                     error =
                        I2C_Peripheral_Name(MasterWriteByte)(data[register_count-counter]);
                    if (error != I2C_Peripheral_Name(MSTR_NO_ERROR))
                    {
                        // Send stop condition
                        I2C_Peripheral_Name(MasterSendStop);
                        // Return error code
                        return BAD_PARAMETER;
                    }
                    counter--;
                }
                // Send stop condition and return no error
                I2C_Peripheral_Name(MasterSendStop)();
                return NO_ERROR;
            }
        }
        // Send stop condition in case something didn't work out correctly
        I2C_Peripheral_Name(MasterSendStop);
        // Return error code
        return BAD_PARAMETER;
    }
    
    
    uint8_t I2C_Peripheral_IsDeviceConnected(uint8_t device_address)
    {
        // Send a start condition followed by a stop condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address, I2C_READ);
        I2C_Peripheral_Name(MasterSendStop)();
        // If no error generated during stop, device is connected
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            return DEVICE_CONNECTED;
        }
        return DEVICE_UNCONNECTED;
    }

/* [] END OF FILE */
