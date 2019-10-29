/*
*   This file includes all the required source code to interface
*   the I2C peripheral.
*
*   \author Davide Marzorati
*/

#include "BME280_I2C_Interface.h" 
#include "I2C_Master.h"

ErrorCode BME280_I2C_Interface_Start(void) 
{
    // Start I2C peripheral 
    I2C_Master_Start();
    // Return no error since start function does not return any error
    return NO_ERROR;
}


ErrorCode BME280_I2C_Interface_Stop(void)
{
    // Stop I2C peripheral
    I2C_Master_Stop();
    // Return no error since stop function does not return any error
    return NO_ERROR;
}

ErrorCode BME280_I2C_Interface_ReadRegister(uint8_t device_address, 
                                        uint8_t register_address,
                                        uint8_t* data)
{
    // Send start condition
    uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        // Write address of register to be read
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Send restart condition
            error = I2C_Master_MasterSendRestart(device_address, I2C_Master_READ_XFER_MODE);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                // Read data without acknowledgement
                *data = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
                // Send stop condition and return no error
                I2C_Master_MasterSendStop();
                return NO_ERROR;
            }
        }
    }
    // Send stop condition if something went wrong
    I2C_Master_MasterSendStop();
    // Return error code
    return BAD_PARAMETER;
}

ErrorCode BME280_I2C_Interface_ReadRegisterMulti(uint8_t device_address,
                                            uint8_t register_address,
                                            uint8_t register_count,
                                            uint8_t* data)
{
    // Send start condition
    uint8_t error = I2C_Master_MasterSendStart(device_address,I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        // Write address of register to be read with the MSB equal to 1
        register_address |= 0x80;
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Send restart condition
            error = I2C_Master_MasterSendRestart(device_address, I2C_Master_READ_XFER_MODE);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                // Continue reading until we have register to read
                uint8_t counter = register_count;
                while(counter>1)
                {
                    data[register_count-counter] =
                        I2C_Master_MasterReadByte(I2C_Master_ACK_DATA);
                    counter--;
                }
                // Read last data without acknowledgement
                data[register_count-1]
                    = I2C_Master_MasterReadByte(I2C_Master_NAK_DATA);
                // Send stop condition and return no error
                I2C_Master_MasterSendStop();
                return NO_ERROR;
            }
        }
    }
    // Send stop condition if something went wrong
    I2C_Master_MasterSendStop();
    // Return error code
    return BAD_PARAMETER;
}

ErrorCode BME280_I2C_Interface_WriteRegister(uint8_t device_address,
                                        uint8_t register_address,
                                        uint8_t data)
{
    // Send start condition
    uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        // Write register address
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Write byte of interest
            error = I2C_Master_MasterWriteByte(data);
            if (error == I2C_Master_MSTR_NO_ERROR)
            {
                // Send stop condition
                I2C_Master_MasterSendStop();
                // Return with no error
                return NO_ERROR;
            }
        }
    }
    // Send stop condition in case something didn't work out correctly
    I2C_Master_MasterSendStop();
    // Return error code
    return BAD_PARAMETER;
}

ErrorCode BME280_I2C_Interface_WriteRegisterMulti(uint8_t device_address,
                                        uint8_t register_address,
                                        uint8_t register_count,
                                        uint8_t* data)
{
    // Send start condition
    uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        // Write register address
        error = I2C_Master_MasterWriteByte(register_address);
        if (error == I2C_Master_MSTR_NO_ERROR)
        {
            // Continue writing until we have data to write
            uint8_t counter = register_count;
            while(counter >= 0)
            {
                 error =
                    I2C_Master_MasterWriteByte(data[register_count-counter]);
                if (error != I2C_Master_MSTR_NO_ERROR)
                {
                    // Send stop condition
                    I2C_Master_MasterSendStop();
                    // Return error code
                    return BAD_PARAMETER;
                }
                counter--;
            }
            // Send stop condition and return no error
            I2C_Master_MasterSendStop();
            return NO_ERROR;
        }
    }
    // Send stop condition in case something didn't work out correctly
    I2C_Master_MasterSendStop();
    // Return error code
    return BAD_PARAMETER;
}


uint8_t BME280_I2C_Interface_IsDeviceConnected(uint8_t device_address)
{
    // Send a start condition followed by a stop condition
    uint8_t error = I2C_Master_MasterSendStart(device_address, I2C_Master_WRITE_XFER_MODE);
    I2C_Master_MasterSendStop();
    // If no error generated during stop, device is connected
    if (error == I2C_Master_MSTR_NO_ERROR)
    {
        return BME280_CONNECTED;
    }
    return BME280_UNCONNECTED;
}

/* [] END OF FILE */
