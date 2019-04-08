/**
 * @file MPU9250.h
 * @brief Functions required to interface with an MPU9250.
 * 
 * This header file contains macros and function prototypes to interface
 * with a MPU250.
 *
 * @author Davide Marzorati
 * @date 29 March, 2019
*/

#ifndef __MPU9250__H
    #define __MPU9250__H
    
    #include <cytypes.h>
    #include <I2C_MPU9250_Master.h>
    
    
    /* ========= MACROS ========= */
    
    /**
    * @brief I2C address of the MPU9250.
    *
    * This is the I2C address of the MPU9250. It can be either 0x68 or 0x69.
    */
    #define MPU9250_I2C_ADDRESS 0x68

    /**
    * @brief Value of the WHO AM I register.
    *
    * This is the expected value of the #MPU9250_WHO_AM_I_REG register of the MPU9250.
    */
    #define MPU9250_WHO_AM_I 0x71
    
    /**
    * @brief I2C address of the AK8963 magnetometer.
    *
    * This is the I2C address of the  AK8963 magnetometer.
    */
    #define AK8963_I2C_ADDRESS 0x0C
    
    /* ========= TYPE DEFS ========= */
    
    /** 
     * @brief Values of accelerometer full scale range.
    **/
    typedef enum {
        /** ±2g accelerometer full scale range **/
        MPU9250_Acc_FS_2g, 
        /** ±4g accelerometer full scale range **/
        MPU9250_Acc_FS_4g,
        /** ±8g accelerometer full scale range **/
        MPU9250_Acc_FS_8g,
        /** ±16g accelerometer full scale range **/
        MPU9250_Acc_FS_16g
    } MPU9250_Acc_FS; 
    
    /** 
     * @brief Values of gyroscope full scale range.
    **/
    typedef enum {
        /** +250 DPS gyroscope full scale range **/
        MPU9250_Gyro_FS_250,
        /** +500 DPS gyroscope full scale range **/
        MPU9250_Gyro_FS_500,
        /** +1000 DPS gyroscope full scale range **/
        MPU9250_Gyro_FS_1000,
        /** +2000 DPS gyroscope full scale range **/
        MPU9250_Gyro_FS_2000
    } MPU9250_Gyro_FS;
    
    /* ========= FUNCTIONS DECLARATIONS ========= */
    
    /**
    * @brief Start the component.
    *
    * This function starts the I2C master component, if not already started. This check
    * is done on the initVar of the I2C master component.
    */
    void MPU9250_Start(void);
    
    /**
    * @brief Enter sleep mode.
    *
    * This function puts the MPU9250 into sleep mode. See register #MPU9250_PWR_MGMT_1_REG.
    */
    void MPU9250_Sleep(void);
    
    /**
    * @brief Exit sleep mode.
    *
    * This function wakes up the MPU9250, exiting sleep mode. See register #MPU9250_PWR_MGMT_1_REG.
    */
    void MPU9250_WakeUp(void);
    
    /**
    * @brief Check I2C connection with MPU9250.
    *
    * This function checks if the MPU9250 is connected on the I2C bus.
    * @return Connection status:
    *            - 0: Device is not connected
    *            - > 0: Device is connected
    */
    uint8_t MPU9250_IsConnected(void);
    
    /**
    * @brief Read MPU9250 WHO AM I register.
    *
    * This function reads the #MPU9250_WHO_AM_I_REG register of the 
    * MPU9250. The expected value returned by this function is 
    * #MPU9250_WHO_AM_I
    *
    * @return the value of the WHO AM I register of the MPU9250.
    */
    uint8_t MPU9250_ReadWhoAmI(void);
    
    /**
    * @brief Read the magnetometer WHO AM I register.
    *
    */
    uint8_t MPU9250_ReadMagWhoAmI(void);
    
    /**
    * @brief Read accelerometer values.
    *
    * This function reads the accelerometer values on the three
    * axis (x, y, and z). 
    * @param[out] acc: accelerometer values (x, y, and z).
    *
    */
    void MPU9250_ReadAcc(int16_t* acc);
    
    /**
    * @brief Read accelerometer raw values.
    *
    * This function reads the accelerometer values on the three
    * axis (x, y, and z) and returns the raw values. 
    * @param[out] acc: accelerometer values (xH, xL, yH, yL, zH, zL).
    *
    */
    void MPU9250_ReadAccRaw(uint8_t* acc);
    
    /**
    * @brief Read gyroscope values.
    *
    * This function reads the gyroscope values on the three
    * axis (x, y, and z). 
    * @param[out] gyro: gyroscope values (x, y, and z).
    *
    */
    void MPU9250_ReadGyro(int16_t* gyro);
    
    /**
    * @brief Read gyroscope raw values.
    *
    * This function reads the gyroscope values on the three
    * axis (x, y, and z) and returns the raw values. 
    * @param[out] gyro: gyroscope raw values (xH, xL, yH, yL, zH, zL).
    *
    */
    void MPU9250_ReadGyroRaw(uint8_t* gyro);
    
    /**
    * @brief Read temperature.
    *
    * This function reads the temperature value.
    * @param[out] temp: temperature value.
    *
    */
    void MPU9250_ReadTemp(int16_t* temp);
    
    
    /**
    * @brief Read accelerometer and gyroscope values.
    *
    * This function reads the accelerometer and gyroscope values on the three
    * axis (x, y, and z). 
    * @param[out] acc: accelerometer values (x, y, and z).
    * @param[out] gyro: gyroscope values (x, y, and z).
    *
    */
    void MPU9250_ReadAccGyro(int16_t* acc, int16_t* gyro);
    
    /**
    * @brief Read accelerometer and gyroscope raw values.
    *
    * This function reads the accelerometer and gyroscope values on the three
    * axis (x, y, and z). 
    * @param[out] data: accelerometer and gyro raw values (xH, xL, yH, yL, zH, zL).
    *
    */
    void MPU9250_ReadAccGyroRaw(uint8_t* data);
    
    /*
    void MPU9250_ReadMag(void);
    */
    
    void MPU9250_ReadSelfTestGyro(uint8_t* self_test_gyro);
    void MPU9250_ReadSelfTestAcc(uint8_t* self_test_acc);
    
    /**
    * @brief Perform self test of accelerometer and gyroscope.
    * 
    * This function performs a self test of the MPU9250. The returned values 
    * represent percent deviation from factory trim values. For a more detailed
    * explanation please check the MPU-9250 Accelerometer, Gyroscope and
    * Compass Self-Test Implementation application.
    */
    void MPU9250_SelfTest(float* deviation);
    
    /**
    * \brief Perform magnetometer self test.
    *
    */
    void MPU9250_SelfTestMag(float deviation);
    
    /**
    * @brief Enable accelerometer.
    *
    * Activate accelerometer updates. See register #MPU9250_PWR_MGMT_2_REG.
    *
    */
    void MPU9250_EnableAcc(void);
    
    /**
    * @brief Enable gyroscope.
    *
    * Activate gyroscope updates. See register #MPU9250_PWR_MGMT_2_REG.
    *
    */
    void MPU9250_EnableGyro(void);
    
    void MPU9250_EnableMag(void);
    
    /**
    * @brief Disable accelerometer.
    *
    * Disable accelerometer updates. See register #MPU9250_PWR_MGMT_2_REG.
    *
    */
    void MPU9250_DisableAcc(void);
    
    /**
    * @brief Disable gyroscope.
    *
    * Activate gyroscope updates. See register #MPU9250_PWR_MGMT_2_REG.
    *
    */
    void MPU9250_DisableGyro(void);
    
    void MPU9250_DisableMag(void);
    
    
    /**
    * @brief Set the accelerometer full scale range.
    *
    * This function sets accelerometer full scale range for the
    * accelerometer. See #MPU9250_Acc_FS and #MPU9250_ACCEL_CONFIG_REG
    *
    * @param fs: the new full scale range value to be used.
    **/
    void MPU9250_SetAccFS(MPU9250_Acc_FS fs);
    
    /**
    * @brief Get the accelerometer full scale range.
    *
    * This function gets accelerometer full scale rang. 
    * See #MPU9250_Acc_FS and #MPU9250_ACCEL_CONFIG_REG
    *
    * @return the accelerometer full scale range.
    **/
    MPU9250_Acc_FS MPU9250_GetAccFS(void);
    
    /**
    * @brief Set the gyroscope full scale range.
    *
    * This function sets the full scale range for the
    * gyroscope. See #MPU9250_Gyro_FS and #MPU9250_GYRO_CONFIG_REG
    *
    * @param fs: the new full scale range value to be used.
    **/
    void MPU9250_SetGyroFS(MPU9250_Gyro_FS fs);
    
    /**
    * @brief Get the gyroscope full scale range.
    *
    * This function gets the gyroscope full scale range.
    * See #MPU9250_Gyro_FS and #MPU9250_GYRO_CONFIG_REG
    *
    * @return the gyroscope full scale range.
    **/
    MPU9250_Gyro_FS MPU9250_GetGyroFS(void);
    
    /**
    * @brief Set sample rate divider.
    *
    * This function sets the divider for the internal sample rate (see also register 
    * #MPU9250_CONFIG_REG) to generate the sample rate that controls data
    * output rate, FIFO sample rate. This register is only effective when 
    * Fchoice = 2'b11 (fchoice_b register bits are 2'b00) and (0 < dlpf_cfg < 7), 
    * such that the averate filter's output is selected. 
    *
    * SAMPLE RATE = Internal_Sample_Rate / ( 1 + SMPLRT_DIV)
    **/
    void MPU9250_SetSampleRateDivider(uint8_t smplrt);
    
    /**
    * @brief Read accelerometer offset values.
    *
    * This function reads the accelerometer offset values on all the axis (x, y, and z).
    * @param[out] acc_offset: array where the 3 offset values will be stored
    **/
    void MPU9250_ReadAccelerometerOffset(int16_t *acc_offset);
    
    /**
    * @brief Enable interrupt on raw sensor data ready.
    *
    * This function eables raw sensor data ready interrupt to propagate to interrupt
    * pin. The timing of the interrupt can vary depending on the setting in register
    * 36 #I2C_MST_CTRL , bit[6] WAIT_FOR_ES
    **/
    void MPU9250_EnableRawDataInterrupt(void);
    
    /**
    * @brief Disable interrupt on raw sensor data ready.
    **/
    void MPU9250_DisableRawDataInterrupt(void);
    
    /**
    * @brief Enable Fsync interrupt to propagate to interrupt pin.
    */
    void MPU9250_EnableFsyncInterrupt(void);
    
    /**
    * @brief Disbale Fsync interrupt to propagate to interrupt pin.
    */
    void MPU9250_DisableFsyncInterrupt(void);
    
    /**
    * @brief Enable interrupt for fifo overflow to propagate to interrupt pin.
    */
    void MPU9250_EnableFifoOverflowInterrupt(void);
    
     /**
    * @brief Disable interrupt for fifo overflow to propagate to interrupt pin.
    */
    void MPU9250_DisableFifoOverflowInterrupt(void);
    
    /**
    * @brief Enable interrupt for wake on motion to propagate to interrupt pin.
    */
    void MPU9250_EnableWomInterrupt(void);
    
    /**
    * @brief Disable interrupt for wake on motion to propagate to interrupt pin.
    */
    void MPU9250_DisableWomInterrupt(void);
    
    /**
    * @brief Read interrupt status register.
    * 
    * This function reads the interrupt status register. For additional information
    * check register #MPU9250_INT_STATUS_REG
    * @return value of the interrupt status register.
    */
    uint8_t MPU9250_ReadInterruptStatus(void);
    
    
    /**
    * @brief Set interrupt pin as active high.
    *
    * This function sets the interrupt logic level as active high.
    */
    void MPU9250_SetInterruptActiveHigh(void);
    
    /**
    * @brief Set interrupt pin as active low.
    *
    * This function sets the interrupt logic low as active high.
    */
    void MPU9250_SetInterruptActiveLow(void);
    
    /**
    * @brief Set interrupt pin as open drain.
    *
    * This function sets the interrupt pin in open drain configuration.
    */
    void MPU9250_SetInterruptOpenDrain(void);
    
    /**
    * @brief Set interrupt pin as push pull.
    *
    * This function sets the interrupt pin in push - pull configuration.
    */
    void MPU9250_SetInterruptPushPull(void);
    
    /**
    * @brief Enable I2C bypass.
    *
    * This function enable the I2C bypass. This way, the I2C master interface pins
    * will go into bypass mode when the I2C master interface is disabled. This pins 
    * will float high due to the internal pull-up if not enabled and the I2C 
    * master interface is disabled.
    */
    void MPU9250_EnableI2CBypass(void);
    
    /**
    * @brief Disable I2C bypass.
    *
    */
    void MPU9250_DisableI2CBypass(void);
    
    /**
    * @brief Held interrupt pin until interrupt status is cleared.
    *
    * This function sets up the interrupt to be held until the interrupt status is cleared.
    */
    void MPU9250_HeldInterruptPin(void);
    
    /**
    * @brief Interrupt pin pulse.
    *
    * This function sets up the interrupt to a 50 us pulse.
    */
    void MPU9250_InterruptPinPulse(void);
    
    /**
    * @brief Clear interrupt on any read operation.
    *
    * This function enables the interrupt to be cleared when any read operation is
    * performed.
    */
    void MPU9250_ClearInterruptAny(void);
    
    /**
    * @brief Clear interrupt only when reading status register.
    *
    * This function enables the interrupt to be cleared only when the status register
    * is read.
    */
    void MPU9250_ClearInterruptStatusReg(void);
    
#endif

/* [] END OF FILE */
