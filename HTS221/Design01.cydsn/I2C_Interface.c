/*
* This file includes all the required source code to interface
* the I2C peripheral.
*
*/

#warning // Replace I2C_Master with the name of the I2C peripheral 

#define I2C_Peripheral_Name_Header_File "I2C_Master.h"
#define I2C_Peripheral_Name(fn) I2C_Master_ ## fn

#ifndef I2C_WRITE
    #define I2C_WRITE 0
#endif

#ifndef I2C_READ
    #define I2C_READ 1
#endif

#ifndef I2C_NACK
    #define I2C_NACK 0
#endif

#ifndef I2C_ACK
    #define I2C_ACK 1
#endif

#include "I2C_Interface.h"
#include I2C_Peripheral_Name_Header_File

    ErrorCode I2C_Peripheral_Start(void) 
    {
        // Start I2C peripheral
        I2C_Peripheral_Name(Start)();  
        return NO_ERROR;
    }
    
    
    ErrorCode I2C_Peripheral_Stop(void)
    {
        // Stop I2C peripheral
        I2C_Peripheral_Name(Stop)();
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
            error = I2C_Peripheral_Name(MasterWriteByte)(register_address);
            if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
            {
                error = I2C_Peripheral_Name(MasterSendRestart)(device_address, I2C_READ);
                if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
                {
                    *data = I2C_Peripheral_Name(MasterReadByte)(I2C_NACK);
                    I2C_Peripheral_Name(MasterSendStop)();
                    return NO_ERROR;
                }
            }
        }
        I2C_Peripheral_Name(MasterSendStop)();
        return BAD_PARAMETER;
    }
    
    ErrorCode I2C_Peripheral_ReadRegisterMulti(uint8_t device_address,
                                                uint8_t register_address,
                                                uint8_t register_count,
                                                uint8_t* data,
                                                uint8_t restart);
    
    ErrorCode I2C_Peripheral_WriteRegister(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t data)
    {
        // Send start condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address, I2C_WRITE);
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            error = I2C_Peripheral_Name(MasterWriteByte)(register_address);
            if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
            {
                error = I2C_Peripheral_Name(MasterWriteByte)(data);
                if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
                {
                    I2C_Peripheral_Name(MasterSendStop)();
                    return NO_ERROR;
                }
            }
        }
        I2C_Peripheral_Name(MasterSendStop);
        return BAD_PARAMETER;
    }
    
    
    
    uint8_t I2C_Peripheral_IsDeviceConnected(uint8_t device_address)
    {
        // Send a start condition followed by a stop condition
        uint8_t error = I2C_Peripheral_Name(MasterSendStart)(device_address, I2C_WRITE);
        I2C_Peripheral_Name(MasterSendStop)();
        // If no error generated during stop, device is connected
        if (error == I2C_Peripheral_Name(MSTR_NO_ERROR))
        {
            return 1;
        }
        return 0;
    }

/* [] END OF FILE */
