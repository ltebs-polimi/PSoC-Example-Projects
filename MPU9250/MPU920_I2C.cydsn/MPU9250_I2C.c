
/*
 * @brief Function definitions for MPU9250 I2C communication.
 *
 * This file contains the definitions of the functions that can be used
 * to interface with the MPU9250 through the I2C protocol.
 *
 * @date January 19, 2019
 * @author Davide Marzorati
 */

#include "MPU9250_I2C.h"

/**
* @brief   0 bit useful when sending a start command. 
*    
* I2C Write operations require to specifiy a 0 when generating a start
* command. This define helps the programmer and reader to understand it better.
*/
#ifndef MPU9250_WRITE
    #define MPU9250_WRITE 0
#endif

/**
* @brief   1 bit useful when sending a start command 
*    
* I2C Read operations require to specifiy a 1 when generating a start
* command. This define helps the programmer and reader to understand it better.
*/
#ifndef MPU9250_READ
    #define MPU9250_READ  1
#endif

/**
* @brief   0 bit for response without acknowledgment.
*    
*/
#ifndef MPU9250_NACK
    #define MPU9250_NACK 0
#endif

/**
* @brief   1 bit for response with acknowledgment.
*    
*/
#ifndef MPU9250_ACK
    #define MPU9250_ACK  1
#endif

uint8_t MPU9250_I2C_Read(uint8_t address, uint8_t reg) {
    /*
        Standard I2C single byte read protocol
            - Send start signal requesting write operation
            - Write byte with register address
            - Send stop signal
            - Send start signal requesting read operation
            - Read byte without acknowledgement
            - Send stop
    */
    
    I2C_MPU9250_Master_MasterSendStart(address,MPU9250_WRITE);
    I2C_MPU9250_Master_MasterWriteByte(reg);
	I2C_MPU9250_Master_MasterSendStop();
	I2C_MPU9250_Master_MasterSendStart(address,MPU9250_READ);
    uint8_t data = I2C_MPU9250_Master_MasterReadByte(MPU9250_NACK);
    I2C_MPU9250_Master_MasterSendStop();
	return data;
}

void MPU9250_I2C_ReadMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	/*
        Standard I2C multi bytes read protocol
            - Send start signal requesting write operation
            - Write byte with first register address
            - Send restart signal
            - While loop with read byte and acknowledgement
            - Last byte read without acknowledgement
            - Send stop
    */
    I2C_MPU9250_Master_MasterSendStart(address,MPU9250_WRITE);
    I2C_MPU9250_Master_MasterWriteByte(reg);
    I2C_MPU9250_Master_MasterSendRestart(address,MPU9250_READ);
	while (count--) {
		if (!count) {
			/* Last byte */
			*data++ = I2C_MPU9250_Master_MasterReadByte(MPU9250_NACK); 
		} else {
			*data++ = I2C_MPU9250_Master_MasterReadByte(MPU9250_ACK);
		}
	}
    I2C_MPU9250_Master_MasterSendStop();
}

uint8_t MPU9250_I2C_ReadNoRegister(uint8_t address) {
    /*
        Standard I2C no register read protocol
            - Send start signal requesting read operation
            - Read without acknowledgement
            - Send stop
    */
	uint8_t data;
    I2C_MPU9250_Master_MasterSendStart(address,MPU9250_READ);
	/* Also stop condition happens */
	data = I2C_MPU9250_Master_MasterReadByte(MPU9250_NACK);
    I2C_MPU9250_Master_MasterSendStop();
	return data;
}

void MPU9250_I2C_ReadMultiNoRegister(uint8_t address, uint8_t* data, uint16_t count) {
	/*
        Standard I2C multi bytes no registers read protocol
            - Send start signal requesting read operation
            - While loop with read byte and acknowledgement
            - Last byte read without acknowledgement
            - Send stop
    */
    I2C_MPU9250_Master_MasterSendStart(address, MPU9250_READ);
	while (count--) {
		if (!count) {
			/* Last byte */
			*data = I2C_MPU9250_Master_MasterReadByte(MPU9250_NACK); 
		} else {
			*data = I2C_MPU9250_Master_MasterReadByte(MPU9250_ACK); 
		}
	}
    I2C_MPU9250_Master_MasterSendStop();
}

void MPU9250_I2C_Write(uint8_t address, uint8_t reg, uint8_t data) {
    /*
        Standard I2C single byte write protocol
            - Send start signal requesting write operation
            - Write register byte
            - Write data byte
            - Send stop
    */
    I2C_MPU9250_Master_MasterSendStart(address, MPU9250_WRITE);
    I2C_MPU9250_Master_MasterWriteByte(reg);
	I2C_MPU9250_Master_MasterWriteByte(data);
    I2C_MPU9250_Master_MasterSendStop();
}

void MPU9250_I2C_WriteMulti(uint8_t address, uint8_t reg, uint8_t* data, uint16_t count) {
	/*
        Standard I2C multi bytes write protocol
            - Send start signal requesting write operation
            - While loop with all data to be written
            - Send stop
    */
    I2C_MPU9250_Master_MasterSendStart(address,MPU9250_WRITE);
    I2C_MPU9250_Master_MasterWriteByte(reg);
	while (count--) {
        I2C_MPU9250_Master_MasterWriteByte(*data++);
	}
	I2C_MPU9250_Master_MasterSendStop();
}

void MPU9250_I2C_WriteNoRegister(uint8_t address, uint8_t data) {
    /*
        Standard I2C single byte no register write protocol
            - Send start signal requesting write operation
            - Write byte
            - Send stop
    */
    I2C_MPU9250_Master_MasterSendStart(address, MPU9250_WRITE);
	I2C_MPU9250_Master_MasterWriteByte(data);
	I2C_MPU9250_Master_MasterSendStop();
}

void MPU9250_I2C_WriteMultiNoRegister(uint8_t address, uint8_t* data, uint16_t count) {
	/*
        Standard I2C multi byte no registers write protocol
            - Send start signal requesting write operation
            - Write all bytes
            - Send stop
    */
    I2C_MPU9250_Master_MasterSendStart(address, MPU9250_WRITE);
	while (count--) {
        I2C_MPU9250_Master_MasterWriteByte(*data++);
	}
	I2C_MPU9250_Master_MasterSendStop();
}
/* [] END OF FILE */