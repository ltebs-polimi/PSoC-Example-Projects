/**
 * @file MPU9250_RegMap.h
 * @brief MPU9250 Register Map.
 * 
 * This header file contains all the
 * definitions of the MPU9250 registers 
 * that can be addressed with I2C protocol.
 * @author Davide Marzorati
 * @date 29 March, 2019
*/

#ifndef __MPU9250__REGMAP_H
    #define __MPU9250__REGMAP_H
    
    /**
    * @brief Self test value gyroscope x axis.
    *
    * The value in this register indicates the self test output generated
    * during manufacturing tests. This value is to be used to check
    * against subsequent self test outputs performed by the end user.
    * For details of the MPU-9250 self-test implementation, please refer 
    * to the following document: ANMPU-9250A-03, MPU-9250 Accelerometer, 
    * Gyroscope and Compass Self-Test Implementation.
    * 
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_SELF_TEST_X_GYRO_REG
        #define MPU9250_SELF_TEST_X_GYRO_REG 0x00
    #endif
    
    /**
    * @brief Self test value gyroscope y axis.
    *
    * The value in this register indicates the self test output generated
    * during manufacturing tests. This value is to be used to check
    * against subsequent self test outputs performed by the end user.
    * For details of the MPU-9250 self-test implementation, please refer 
    * to the following document: ANMPU-9250A-03, MPU-9250 Accelerometer, 
    * Gyroscope and Compass Self-Test Implementation.
    * 
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_SELF_TEST_Y_GYRO_REG
        #define MPU9250_SELF_TEST_Y_GYRO_REG 0x01
    #endif
    
    /**
    * @brief Self test value gyroscope z axis.
    *
    * The value in this register indicates the self test output generated
    * during manufacturing tests. This value is to be used to check
    * against subsequent self test outputs performed by the end user.
    * For details of the MPU-9250 self-test implementation, please refer 
    * to the following document: ANMPU-9250A-03, MPU-9250 Accelerometer, 
    * Gyroscope and Compass Self-Test Implementation.
    * 
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_SELF_TEST_Z_GYRO_REG
        #define MPU9250_SELF_TEST_Z_GYRO_REG 0x02
    #endif
    
    /**
    * @brief Self test value accelerometer x axis.
    *
    * The value in this register indicates the self test output generated
    * during manufacturing tests. This value is to be used to check
    * against subsequent self test outputs performed by the end user.
    * For details of the MPU-9250 self-test implementation, please refer 
    * to the following document: ANMPU-9250A-03, MPU-9250 Accelerometer, 
    * Gyroscope and Compass Self-Test Implementation.
    * 
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_SELF_TEST_X_ACCEL_REG
        #define MPU9250_SELF_TEST_X_ACCEL_REG 0x0D
    #endif
    
    /**
    * @brief Self test value accelerometer y axis.
    *
    * The value in this register indicates the self test output generated
    * during manufacturing tests. This value is to be used to check
    * against subsequent self test outputs performed by the end user.
    * For details of the MPU-9250 self-test implementation, please refer 
    * to the following document: ANMPU-9250A-03, MPU-9250 Accelerometer, 
    * Gyroscope and Compass Self-Test Implementation.
    * 
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_SELF_TEST_Y_ACCEL_REG
        #define MPU9250_SELF_TEST_Y_ACCEL_REG 0x0E
    #endif
    
    /**
    * @brief Self test value accelerometer z axis.
    *
    * The value in this register indicates the self test output generated
    * during manufacturing tests. This value is to be used to check
    * against subsequent self test outputs performed by the end user.
    * For details of the MPU-9250 self-test implementation, please refer 
    * to the following document: ANMPU-9250A-03, MPU-9250 Accelerometer, 
    * Gyroscope and Compass Self-Test Implementation.
    * 
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_SELF_TEST_Z_ACCEL_REG
        #define MPU9250_SELF_TEST_Z_ACCEL_REG 0x0F
    #endif
    
    /**
    * @brief X axis gyro offset register high byte.
    *
    * High bytes, low bytes in #MPU9250_XG_OFFSET_L_REG.
    * The value in this register and in #MPU9250_XG_OFFSET_L_REG are used to remove DC bias from the 
    * gyro sensor data output for X axis.
    * The values in these registers are subtracted from the gyro sensor values before going into the
    * sensor registers. Please refer to registers 67 to 72 for units.
    * 
    * Description    | Value
    * ---------------|-------
    * OffsetLSB | X_OFFS_USR * 4 / 2^FS_SEL
    * OffsetDPS | X_OFFS_USR * 4 / 2^FS_SEL / Gyro_Sensitivity
    * Nominal Conditions | Gyro_Sensitivity = 2^16 LSB / 500dps
    *   ^                | FS_SEL = 0
    * Max  | 999.969 dps
    * Min  | -1000 dps
    * Step | 0.0305 dps
    *
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_XG_OFFSET_H_REG
        #define MPU9250_XG_OFFSET_H_REG 0x13
    #endif
    
    /**
    * @brief X axis gyro offset register low byte.
    * 
    * Low byte, high byte in USR register #MPU9250_XG_OFFSET_H_REG
    *
    */
    #ifndef MPU9250_XG_OFFSET_L_REG
        #define MPU9250_XG_OFFSET_L_REG 0x14
    #endif
    
    /**
    * @brief Y axis gyro offset register high byte.
    *
    * High byte, low byte in #MPU9250_YG_OFFSET_L_REG.
    * The value in this register and in #MPU9250_YG_OFFSET_L_REG are used to remove DC bias from the 
    * gyro sensor data output for Y axis.
    * The values in these registers are subtracted from the gyro sensor values before going into the
    * sensor registers. Please refer to registers 67 to 72 for units.
    * 
    * Description    | Value
    * ---------------|-------
    * OffsetLSB | Y_OFFS_USR * 4 / 2^FS_SEL
    * OffsetDPS | Y_OFFS_USR * 4 / 2^FS_SEL / Gyro_Sensitivity
    * Nominal Conditions | Gyro_Sensitivity = 2^16 LSB / 500dps
    *   ^                | FS_SEL = 0
    * Max  | 999.969 dps
    * Min  | -1000 dps
    * Step | 0.0305 dps
    *
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_YG_OFFSET_H_REG
        #define MPU9250_YG_OFFSET_H_REG 0x15
    #endif
    
    /**
    * @brief Y axis gyro offset register low bytes.
    * 
    * Low byte, high byte in USR register #MPU9250_YG_OFFSET_H_REG
    *
    */
    #ifndef MPU9250_YG_OFFSET_L_REG
        #define MPU9250_YG_OFFSET_L_REG 0x16
    #endif
    
    /**
    * @brief Z axis gyro offset register high byte.
    *
    * High byte, low byte in #MPU9250_ZG_OFFSET_L_REG.
    * The value in this register and in #MPU9250_ZG_OFFSET_L_REG are used to remove DC bias from the 
    * gyro sensor data output for Z axis.
    * The values in these registers are subtracted from the gyro sensor values before going into the
    * sensor registers. Please refer to registers 67 to 72 for units.
    * 
    * Description    | Value
    * ---------------|-------
    * OffsetLSB | Y_OFFS_USR * 4 / 2^FS_SEL
    * OffsetDPS | Y_OFFS_USR * 4 / 2^FS_SEL / Gyro_Sensitivity
    * Nominal Conditions | Gyro_Sensitivity = 2^16 LSB / 500dps
    *   ^                | FS_SEL = 0
    * Max  | 999.969 dps
    * Min  | -1000 dps
    * Step | 0.0305 dps
    *
    * Serial IF: R/W
    * 
    * Reset value: 0x00
    */
    #ifndef MPU9250_ZG_OFFSET_H_REG
        #define MPU9250_ZG_OFFSET_H_REG 0x17
    #endif
    
    /**
    * @brief Z axis gyro offset register low bytes.
    * 
    * Low byte, high byte in USR register #MPU9250_ZG_OFFSET_H_REG
    *
    */
    #ifndef MPU9250_ZG_OFFSET_L_REG
        #define MPU9250_ZG_OFFSET_L_REG 0x18
    #endif
    
    /**
    * @brief Internal sample rate divider.
    *
    * Divides the internal sample rate (see #MPU9250_CONFIG_REG) to generate the
    * sample rate that controls sensor data output rate, FIFO sample rate.
    * 
    * *NOTE*: This register is only effective when Fchoice = 2’b11 (fchoice_b
    * register bits are 2’b00), and (0 < dlpf_cfg < 7), such that the average filter’s
    * output is selected (see chart below).
    * This is the update rate of sensor register.
    *
    * **SAMPLE_RATE** = Internal_Sample_Rate / (1 + SMPLRT_DIV)
    *
    * Data should be sampled at or above sample rate; SMPLRT_DIV is only used for1kHz internal sampling.
    * 
    * Serial IF: R/W
    *
    * Reset value: 0x00
    */
   
    #ifndef MPU9250_SMPLRT_DIV_REG
        #define MPU9250_SMPLRT_DIV_REG 0x19
    #endif
    
    /**
    * @brief Configuration register.
    *
    * | BIT |  NAME  | FUNCTION |
    * |-----|:------:|---------| 
    * | [7] |   -    | Reserved
    * | [6] | FIFO_MODE | When set to ‘1’, when the fifo is full, additional writes will not be written to fifo. When set to ‘0’, when the fifo is full, additional writes will be written to the fifo, replacing the oldest data.
    * | [5:3] | EXT_SYNC_SET[2:0] | Enables the FSYNC pin data to be sampled. 
    * | [2:0] | DLPF_CFG[2:0] | For the DLPF to be used, fchoice[1:0] must be set to 2’b11, fchoice_b[1:0] is 2’b00.
    *
    * The DLPF is configured by DLPF_CFG, when FCHOICE_B [1:0] = 2b’00. The gyroscope and
    * temperature sensor are filtered according to the value of DLPF_CFG and FCHOICE_B as shown in
    * the table below. Note that FCHOICE mentioned in the table below is the inverted value of
    * FCHOICE_B (e.g. FCHOICE=2b’00 is same as FCHOICE_B=2b’11).
    *
    *
    * | FCHOICE  || DLPF_CFG   |                Gyroscope             |||     Temperature Sensor     ||
    * |-----|-----|:----------:|----------------|------------|----------|----------------|------------|
    * | <1> | <0> |           | Bandwidth (Hz) | Delay (ms) | Fs (kHz) | Bandwidth (Hz) | Delay (ms) |
    * |  x  |  0  |    x      |     8800       |    0.064   |    32    |     4000       |   0.04     |  
    * |  1  |  1  |    x      |     3600       |     0.11   |    32    |     4000       |   0.04     |  
    * |  1  |  1  |    0      |      250       |     0.97   |    8     |     4000       |   0.04     | 
    * |  1  |  1  |    1      |      184       |      2.9   |    1     |      188       |    1.9     |
    * |  1  |  1  |    2      |       92       |      3.9   |    1     |       98       |    2.8     |
    * |  1  |  1  |    3      |       41       |      5.9   |    1     |       42       |    4.8     |
    * |  1  |  1  |    4      |       20       |      9.9   |    1     |       20       |    8.3     |
    * |  1  |  1  |    5      |       10       |    17.85   |    1     |       10       |   13.4     |
    * |  1  |  1  |    6      |        5       |    33.48   |    1     |        5       |   18.6     |
    * |  1  |  1  |    7      |     3600       |     0.17   |    8     |     4000       |   0.04     |
    *  
    *
    */
    
    #ifndef MPU9250_CONFIG_REG
        #define MPU9250_CONFIG_REG 0x1A
    #endif
    
    /**
    * @brief Gyro configuration register.
    */
    #ifndef MPU9250_GYRO_CONFIG_REG
        #define MPU9250_GYRO_CONFIG_REG 0x1B
    #endif
    
    /**
    * @brief Accelerometer configuration register.
    * 
    * This register configures the accelerometer. The description of each bit is
    * as follows:
    *
    * | BIT | NAME | FUNCTION |
    * |:-----:|------|---------| 
    * | 7 | ax_st_en | X Accel self-test |
    * | 6 | ay_st_en | Y Accel self-test |
    * | 5 | az_st_en | Z Accel self-test |
    * | [4:3] | ACCEL_FS_SEL[1:] | Accel Full Scale Select: |
    * | ^    |         ^         | 2g (00), 4g (01), 8g (10), 16g (11) |
    * | [2:0] | - | Reserved |
    
    */
    #ifndef MPU9250_ACCEL_CONFIG_REG
        #define MPU9250_ACCEL_CONFIG_REG 0x1C
    #endif
    
    /**
    * @brief Accelerometer configuration 2 register.
    *
    * | BIT | NAME | FUNCTION |
    * |:-----:|------|---------| 
    * | [7:6] | - | Reserved |
    * | [5:4] | - | Reserved |
    * | 3 | accel_fchoice_b | Used to bypass DLPF. This register contains accel_fchoice_b (inverted of accel_fchoice) |
    * | [2:0] | A_DLPFCGF | Accelerometer low pass filter setting as shown in table. |
    */
    #ifndef MPU9250_ACCEL_CONFIG_2_REG
        #define MPU9250_ACCEL_CONFIG_2_REG 0x1D
    #endif
    
    /**
    * @brief Low Power Accelerometer ODR Control.
    *
    * The lowest four bits of this register are used to configure the accelerometer output 
    * data rate in low power mode.
    *
    * | BIT | NAME | FUNCTION |
    * |:-----:|------|---------| 
    * | [7:4] | - | Reserved |
    * | [3:0] | lposc_clksel[3:0] | Sets the frequency of waking up the chip. See table below.|
    *
    * The bits set the frequency of waking up the chip to take a sample of accel data - the lower power
    * accel Output Data Rate.
    *
    * | Lpsoc_clksel | Output Frequency (Hz) |
    * |:------------:|:---------------------:|
    * | 0  | 0.24  |
    * | 1  | 0.49  |
    * | 2  | 0.98  |
    * | 3  | 1.95  |
    * | 4  | 3.91  |
    * | 5  | 7.81  |
    * | 6  | 15.63 |
    * | 7  | 31.25 |
    * | 8  | 62.50 |
    * | 9  | 125   |
    * | 10 | 250   |
    * | 11 | 500   |
    * | 12 - 15 | Reserved |
    
    */
    #ifndef MPU9250_LP_ACCEL_ODR_REG
        #define MPU9250_LP_ACCEL_ODR_REG 0x1E
    #endif
    
    /**
    * @brief Wake-on Motion Threshold register.
    *
    * This register holds the threshold value for the Wake on Motion Interrupt
    * for accel x/y/z axes. LSB = 4 mg. Range is 0mg to 1020mg.
    * For more details on how to configure the Wake-on-Motion interrupt,
    * please refer to section 5 in the MPU-9250 Product Specification document.
    */
    #ifndef MPU9250_WOM_THR_REG
        #define MPU9250_WOM_THR_REG 0x1F
    #endif
    
    /**
    * @brief FIFO Enable register.
    *
    * *Note*: For further information regarding the association of EXT_SENS_DATA registers to particular
    * slave devices, please refer to Registers 73 to 96. 
    *
    * - [7] - TEMP_OUT | 1 - Write TEMP_OUT_H and TEMP_OUT_L to the FIFO at the sample rate; If enabled
    *                        buffering of data occurs even if data path is in standy.
    *                    0 - Function is disabled
    * - [6] - GYRO_XOUT | 1 - Write GYRO_XOUT_H and GYRO_XOUT_L to the FIFO at the sample rate; If enabled
    *                        buffering of data occurs even if data path is in standy.
    *                     0 - Function is disabled
    * - [5] - GYRO_YOUT | 1 - Write GYRO_YOUT_H and GYRO_YOUT_L to the FIFO at the sample rate; If enabled
    *                        buffering of data occurs even if data path is in standy.
    *                     0 - Function is disabled
    * - [4] - GYRO_ZOUT | 1 - Write GYRO_ZOUT_H and GYRO_ZOUT_L to the FIFO at the sample rate; If enabled
    *                        buffering of data occurs even if data path is in standy.
    *                     0 - Function is disabled
    * - [3] - ACCEL | 1 - Write ACCEL_XOUT_H, ACCEL_XOUT_L, ACCEL_YOU_H, ACCEL_YOUT_L, ACCEL_ZOUT_H,
    *                     and ACCEL_ZOUT_L to the FIFO at the sample rate; If enabled
    *                     buffering of data occurs even if data path is in standy.
    *                 0 - Function is disabled
    * - [2] - SLV_2 | 1 - Write EXT_SENS_DATA registers associated to SLV_2 (as determined by I2C_SLV0_CTRL,
    *                     I2C_SLV1_CTROL, and I2C_SLV2_CTRL) to the FIFO at the sample rate; If enabled
    *                     buffering of data occurs even if data path is in standy.
    *                 0 - Function is disabled
    * - [1] - SLV_1 | 1 - Write EXT_SENS_DATA registers associated to SLV_1 (as determined by I2C_SLV0_CTRL,
    *                     I2C_SLV1_CTROL, and I2C_SLV2_CTRL) to the FIFO at the sample rate; If enabled
    *                     buffering of data occurs even if data path is in standy.
    *                 0 - Function is disabled
    * - [0] - SLV_0 | 1 - Write EXT_SENS_DATA registers associated to SLV_0 (as determined by I2C_SLV0_CTRL,
    *                     I2C_SLV1_CTROL, and I2C_SLV2_CTRL) to the FIFO at the sample rate; If enabled
    *                     buffering of data occurs even if data path is in standy.
    *                 0 - Function is disabled
    */
    #ifndef MPU9250_FIFO_EN_REG
        #define MPU9250_FIFO_EN_REG 0x23
    #endif
    
    /**
    * @brief I2C Master Control register.
    *
    * *Note*: For further information regarding the association of EXT_SENS_DATA registers to particular
    * slave devices, please refer to Registers 73 to 96. 
    *
    * - [7] - MULT_MST_EN: Enables multi-master capability. When disabled, clocking to the I2C_MST_IF
    *                      can be disabled when not in use and the logic to detect lost arbitration is
    *                      disabled.
    * - [6] - WAIT_FOR_ES: Delays the data ready interrupt until external sensor data is loaded. If
    *        I2C_MST_IF is disabled, the interrupt will still occur.
    * - [5] - SLV_3_FIFO_EN: 1 write EXT_SENS_DATA registers associated to SLV_3 (as determined by I2C_SLV0_CTRL,
    *                        I2C_SLV1_CTRL, and I2C_SLV2_CTRL) to the FIFO at the sample rate;
    *                        0 function is disabled
    * - [4] - I2C_MST_P_NSR: This bit controls the I2C Master's transition from one slave read to the next slave
    *                        read. If 0, there is a restart between reads. If 1, there is a stop between reads.
    * - [3:0] - I2C_MST_CLK[3:0]: I2C_MST_CLK is a 4 bit unsigned value which configures a divider on the MPU-9250
    *                             internal 8MHz clock. It sets the I2C master clock speed according to the 
    *                             following table:
    *
    * | I2C_MST_CLK | I2C Master Clock Speed | 8 MHz Clock Divider |
    * |:-----------:|:----------------------:|:-------------------:|
    * | 0 | 348 kHz | 23 |
    * | 1 | 333 kHz | 24 |
    * | 2 | 320 kHz | 25 |
    * | 3 | 308 kHz | 26 |
    * | 4 | 296 kHz | 27 |
    * | 5 | 286 kHz | 28 |
    * | 6 | 276 kHz | 29 |
    * | 7 | 267 kHz | 30 |
    * | 8 | 258 kHz | 31 |
    * | 9 | 500 kHz | 16 |
    * | 10 | 471 kHz | 17 |
    * | 11 | 444 kHz | 18 |
    * | 12 | 421 kHz | 19 |
    * | 13 | 400 kHz | 20 |
    * | 14 | 381 kHz | 21 |
    * | 15 | 364 kHz | 22 |
    */
    #ifndef MPU9250_I2C_MST_CTRL_REG
        #define MPU9250_I2C_MST_CTRL_REG 0x24
    #endif
    
    /**
    * @brief I2C Slave 0 Address register.
    *
    * | BIT | NAME | FUNCTION |
    * |:-----:|------|---------| 
    * | [7] | I2C_SLV0_RNW | 1 if transfer is a read, 0 if transfer is a write |
    * | [6:0] | I2C_ID_0[6:0] | Physical address of I2C slave 0 |
    */
    #ifndef MPU9250_I2C_SLV0_ADDR_REG
        #define MPU9250_I2C_SLV0_ADDR_REG 0x25
    #endif
    
    /**
    * @brief I2C Slave 0 Register register.
    *
    * | BIT | NAME | FUNCTION |
    * |:-----:|------|---------| 
    * | [7:0] | I2C_SLV0_REG[7:0] | I2C slave register address from where to begin data transfer |
    */
    #ifndef MPU9250_I2C_SLV0_REG_REG
        #define MPU9250_I2C_SLV0_REG_REG 0x26
    #endif
    
    /**
    * @brief I2C Slave 0 Control register.
    *
    */
    #ifndef MPU9250_I2C_SLV0_CTRL_REG
        #define MPU9250_I2C_SLV0_CTRL_REG 0x27
    #endif
    
    /**
    * @brief I2C Slave 1 Address register.
    *
    */
    #ifndef MPU9250_I2C_SLV1_ADDR_REG
        #define MPU9250_I2C_SLV1_ADDR_REG 0x28
    #endif
    
    /**
    * @brief I2C Slave 1 Register register.
    *
    */
    #ifndef MPU9250_I2C_SLV1_REG_REG
        #define MPU9250_I2C_SLV1_REG_REG 0x29
    #endif
    
    /**
    * @brief I2C Slave 1 Control register.
    *
    */
    #ifndef MPU9250_I2C_SLV1_CTRL_REG
        #define MPU9250_I2C_SLV1_CTRL_REG 0x2A
    #endif
    
    /**
    * @brief I2C Slave 2 Address register.
    *
    */
    #ifndef MPU9250_I2C_SLV2_ADDR_REG
        #define MPU9250_I2C_SLV2_ADDR_REG 0x2B
    #endif
    
    /**
    * @brief I2C Slave 2 Register register.
    *
    */
    #ifndef MPU9250_I2C_SLV2_REG_REG
        #define MPU9250_I2C_SLV2_REG_REG 0x2C
    #endif
    
    /**
    * @brief I2C Slave 2 Control register.
    *
    */
    #ifndef MPU9250_I2C_SLV2_CTRL_REG
        #define MPU9250_I2C_SLV2_CTRL_REG 0x2D
    #endif
    
    /**
    * @brief I2C Slave 3 Address register.
    *
    */
    #ifndef MPU9250_I2C_SLV3_ADDR_REG
        #define MPU9250_I2C_SLV3_ADDR_REG 0x2E
    #endif
    
    /**
    * @brief I2C Slave 3 Register register.
    *
    */
    #ifndef MPU9250_I2C_SLV3_REG_REG
        #define MPU9250_I2C_SLV3_REG_REG 0x2F
    #endif
    
    /**
    * @brief I2C Slave 3 Control register.
    *
    */
    #ifndef MPU9250_I2C_SLV3_CTRL_REG
        #define MPU9250_I2C_SLV3_CTRL_REG 0x30
    #endif
    
    /**
    * @brief I2C Slave 4 Address register.
    *
    */
    #ifndef MPU9250_I2C_SLV4_ADDR_REG
        #define MPU9250_I2C_SLV4_ADDR_REG 0x31
    #endif
    
    /**
    * @brief I2C Slave 4 Register register.
    *
    */
    #ifndef MPU9250_I2C_SLV4_REG_REG
        #define MPU9250_I2C_SLV4_REG_REG 0x32
    #endif
    
    /**
    * @brief I2C Slave 4 Data Output register.
    *
    */
    #ifndef MPU9250_I2C_SLV4_DO_REG
        #define MPU9250_I2C_SLV4_DO_REG 0x33
    #endif
    
    /**
    * @brief I2C Slave 4 Control register.
    *
    */
    #ifndef MPU9250_I2C_SLV4_CTRL_REG
        #define MPU9250_I2C_SLV4_CTRL_REG 0x34
    #endif
    
    /**
    * @brief I2C Slave 4 Data In register.
    *
    */
    #ifndef MPU9250_I2C_SLV4_DI_REG
        #define MPU9250_I2C_SLV4_DI_REG 0x35
    #endif
    
    /**
    * @brief I2C Master Status register.
    *
    */
    #ifndef MPU9250_I2C_MST_STATUS_REG
        #define MPU9250_I2C_MST_STATUS_REG 0x36
    #endif
    
    /**
    * @brief Interrupt pin configuration register.
    *
    */
    #ifndef MPU9250_INT_PIN_CFG_REG
        #define MPU9250_INT_PIN_CFG_REG 0x37
    #endif
    
    /**
    * @brief Interrupt enable register.
    *
    */
    #ifndef MPU9250_INT_ENABLE_REG
        #define MPU9250_INT_ENABLE_REG 0x38
    #endif
    
    /**
    * @brief Interrupt status register.
    *
    */
    #ifndef MPU9250_INT_STATUS_REG
        #define MPU9250_INT_STATUS_REG 0x3A
    #endif
   
    /**
    * @brief Accelerometer x axis high byte register.
    */
    #ifndef MPU9250_ACCEL_XOUT_H_REG
        #define MPU9250_ACCEL_XOUT_H_REG 0x3B
    #endif
    
    /**
    * @brief Accelerometer x axis low byte register.
    */
    #ifndef MPU9250_ACCEL_XOUT_L_REG
        #define MPU9250_ACCEL_XOUT_L_REG 0x3C
    #endif
    
    /**
    * @brief Accelerometer y axis high byte register.
    */
    #ifndef MPU9250_ACCEL_YOUT_H_REG
        #define MPU9250_ACCEL_YOUT_H_REG 0x3D
    #endif
    
    /**
    * @brief Accelerometer y axis low byte register.
    */
    #ifndef MPU9250_ACCEL_YOUT_L_REG
        #define MPU9250_ACCEL_YOUT_L_REG 0x3E
    #endif
    
    /**
    * @brief Accelerometer z axis high byte register.
    */
    #ifndef MPU9250_ACCEL_ZOUT_H_REG
        #define MPU9250_ACCEL_ZOUT_H_REG 0x3F
    #endif
    
    /**
    * @brief Accelerometer z axis low byte register.
    */
    #ifndef MPU9250_ACCEL_ZOUT_L_REG
        #define MPU9250_ACCEL_ZOUT_L_REG 0x40
    #endif
    
    /**
    * @brief Temperature high byte register.
    */
    #ifndef MPU9250_TEMP_OUT_H_REG
        #define MPU9250_TEMP_OUT_H_REG 0x41
    #endif
    
    /**
    * @brief Temperature low byte register.
    */
    #ifndef MPU9250_TEMP_OUT_L_REG
        #define MPU9250_TEMP_OUT_L_REG 0x42
    #endif
   
    /**
    * @brief Gyro x axis high byte register.
    */
    #ifndef MPU9250_GYRO_XOUT_H_REG
        #define MPU9250_GYRO_XOUT_H_REG 0x43
    #endif
    
    /**
    * @brief Gyro x axis low byte register.
    */
    #ifndef MPU9250_GYRO_XOUT_L_REG
        #define MPU9250_GYRO_XOUT_L_REG 0x44
    #endif
    
    /**
    * @brief Gyro y axis high byte register.
    */
    #ifndef MPU9250_GYRO_YOUT_H_REG
        #define MPU9250_GYRO_YOUT_H_REG 0x45
    #endif
    
    /**
    * @brief Gyro y axis low byte register.
    */
    #ifndef MPU9250_GYRO_YOUT_L_REG
        #define MPU9250_GYRO_YOUT_L_REG 0x46
    #endif
    
    /**
    * @brief Gyro z axis high byte register.
    */
    #ifndef MPU9250_GYRO_ZOUT_H_REG
        #define MPU9250_GYRO_ZOUT_H_REG 0x47
    #endif
    
    /**
    * @brief Gyro z axis low byte register.
    */
    #ifndef MPU9250_GYRO_ZOUT_L_REG
        #define MPU9250_GYRO_ZOUT_L_REG 0x48
    #endif
    
    /**
    * @brief External sensor data 00 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_00_REG
        #define MPU9250_EXT_SENS_DATA_00_REG 0x49
    #endif
    
    /**
    * @brief External sensor data 01 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_01_REG
        #define MPU9250_EXT_SENS_DATA_01_REG 0x4A
    #endif
    
    /**
    * @brief External sensor data 02 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_02_REG
        #define MPU9250_EXT_SENS_DATA_02_REG 0x4B
    #endif
    
    /**
    * @brief External sensor data 03 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_03_REG
        #define MPU9250_EXT_SENS_DATA_03_REG 0x4C
    #endif
    
    /**
    * @brief External sensor data 04 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_04_REG
        #define MPU9250_EXT_SENS_DATA_04_REG 0x4D
    #endif
    
    /**
    * @brief External sensor data 05 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_05_REG
        #define MPU9250_EXT_SENS_DATA_05_REG 0x4E
    #endif
    
    /**
    * @brief External sensor data 06 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_06_REG
        #define MPU9250_EXT_SENS_DATA_06_REG 0x4F
    #endif
    
    /**
    * @brief External sensor data 07 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_07_REG
        #define MPU9250_EXT_SENS_DATA_07_REG 0x50
    #endif
    
    /**
    * @brief External sensor data 08 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_08_REG
        #define MPU9250_EXT_SENS_DATA_08_REG 0x51
    #endif
    
    /**
    * @brief External sensor data 09 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_09_REG
        #define MPU9250_EXT_SENS_DATA_09_REG 0x52
    #endif
    
    /**
    * @brief External sensor data 10 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_10_REG
        #define MPU9250_EXT_SENS_DATA_10_REG 0x53
    #endif
    
    /**
    * @brief External sensor data 11 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_11_REG
        #define MPU9250_EXT_SENS_DATA_11_REG 0x54
    #endif
    
    /**
    * @brief External sensor data 12 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_12_REG
        #define MPU9250_EXT_SENS_DATA_12_REG 0x55
    #endif
    
    /**
    * @brief External sensor data 13 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_13_REG
        #define MPU9250_EXT_SENS_DATA_13_REG 0x56
    #endif
    
    /**
    * @brief External sensor data 14 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_14_REG
        #define MPU9250_EXT_SENS_DATA_14_REG 0x57
    #endif
    
    /**
    * @brief External sensor data 15 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_15_REG
        #define MPU9250_EXT_SENS_DATA_15_REG 0x58
    #endif
    
    /**
    * @brief External sensor data 16 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_16_REG
        #define MPU9250_EXT_SENS_DATA_16_REG 0x59
    #endif
    
    /**
    * @brief External sensor data 17 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_17_REG
        #define MPU9250_EXT_SENS_DATA_17_REG 0x5A
    #endif
    
    /**
    * @brief External sensor data 18 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_18_REG
        #define MPU9250_EXT_SENS_DATA_18_REG 0x5B
    #endif
    
    /**
    * @brief External sensor data 19 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_19_REG
        #define MPU9250_EXT_SENS_DATA_19_REG 0x5C
    #endif
    
    /**
    * @brief External sensor data 20 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_20_REG
        #define MPU9250_EXT_SENS_DATA_20_REG 0x5D
    #endif
    
    /**
    * @brief External sensor data 21 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_21_REG
        #define MPU9250_EXT_SENS_DATA_21_REG 0x5E
    #endif
    
    /**
    * @brief External sensor data 22 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_22_REG
        #define MPU9250_EXT_SENS_DATA_22_REG 0x5F
    #endif
    
    /**
    * @brief External sensor data 23 register.
    */
    #ifndef MPU9250_EXT_SENS_DATA_23_REG
        #define MPU9250_EXT_SENS_DATA_23_REG 0x60
    #endif
    
    /**
    * @brief I2C Slave 0 Data Output register.
    */
    #ifndef MPU9250_I2C_SLV0_DO_REG
        #define MPU9250_I2C_SLV0_DO_REG 0x63
    #endif
    
    /**
    * @brief I2C Slave 1 Data Output register.
    */
    #ifndef MPU9250_I2C_SLV1_DO_REG
        #define MPU9250_I2C_SLV1_DO_REG 0x64
    #endif
    
    /**
    * @brief I2C Slave 2 Data Output register.
    */
    #ifndef MPU9250_I2C_SLV2_DO_REG
        #define MPU9250_I2C_SLV2_DO_REG 0x65
    #endif
    
    /**
    * @brief I2C Slave 3 Data Output register.
    */
    #ifndef MPU9250_I2C_SLV3_DO_REG
        #define MPU9250_I2C_SLV3_DO_REG 0x66
    #endif
    
    /**
    * @brief I2C Master delay control register.
    */
    #ifndef MPU9250_I2C_MST_DELAY_CTRL_REG
        #define MPU9250_I2C_MST_DELAY_CTRL_REG 0x67
    #endif
    
    /**
    * @brief Signal path reset register.
    */
    #ifndef MPU9250_SIGNAL_PATH_RESET_REG
        #define MPU9250_SIGNAL_PATH_RESET_REG 0x68
    #endif
    
    /**
    * @brief Wake on motion detection register.
    */
    #ifndef MPU9250_MOT_DETECT_REG
        #define MPU9250_MOT_DETECT_REG 0x69
    #endif
    
    /**
    * @brief User control register.
    */
    #ifndef MPU9250_USER_CTRL_REG
        #define MPU9250_USER_CTRL_REG 0x6A
    #endif
    
    /**
    * @brief Power management 1 register.
    */
    #ifndef MPU9250_PWR_MGMT_1_REG
        #define MPU9250_PWR_MGMT_1_REG 0x6B
    #endif
    
    /**
    * @brief Power management 2 register.
    */
    #ifndef MPU9250_PWR_MGMT_2_REG
        #define MPU9250_PWR_MGMT_2_REG 0x6C
    #endif
    
    /**
    * @brief Fifo count high byte register.
    */
    #ifndef MPU9250_FIFO_COUNTH_REG
        #define MPU9250_FIFO_COUNTH_REG 0x72
    #endif
    
    /**
    * @brief Fifo count low byte register.
    */
    #ifndef MPU9250_FIFO_COUNTL_REG
        #define MPU9250_FIFO_COUNTL_REG 0x73
    #endif
    
    /**
    * @brief Fifo read/write register.
    */
    #ifndef MPU9250_FIFO_R_W_REG
        #define MPU9250_FIFO_R_W_REG 0x74
    #endif
    
    /**
    * @brief Who Am I register.
    */
    #ifndef MPU9250_WHO_AM_I_REG
        #define MPU9250_WHO_AM_I_REG 0x75
    #endif
    
    /**
    * @brief Accelerometer x axis offset high byte register.
    */
    #ifndef MPU9250_XA_OFFSET_H_REG
        #define MPU9250_XA_OFFSET_H_REG 0x77
    #endif
    
    /**
    * @brief Accelerometer x axis offset low byte register.
    */
    #ifndef MPU9250_XA_OFFSET_L_REG
        #define MPU9250_XA_OFFSET_L_REG 0x78
    #endif
    
    /**
    * @brief Accelerometer y axis offset high byte register.
    */
    #ifndef MPU9250_YA_OFFSET_H_REG
        #define MPU9250_YA_OFFSET_H_REG 0x7A
    #endif
    
    /**
    * @brief Accelerometer y axis offset low byte register.
    */
    #ifndef MPU9250_YA_OFFSET_L_REG
        #define MPU9250_YA_OFFSET_L_REG 0x7B
    #endif
    
    /**
    * @brief Accelerometer z axis offset high byte register.
    */
    #ifndef MPU9250_ZA_OFFSET_H_REG
        #define MPU9250_ZA_OFFSET_H_REG 0x7D
    #endif
    
    /**
    * @brief Accelerometer z axis offset low byte register.
    */
    #ifndef MPU9250_ZA_OFFSET_L_REG
        #define MPU9250_ZA_OFFSET_L_REG 0x7E
    #endif

    /*******************************************************/
    /************   MAGNETOMETER REGISTRER MAP  ************/
    /*******************************************************/
    /**
    * @brief Magnetometer Device ID registrer.
    */
    #ifndef MPU9250_MAG_DEV_ID_REG
        #define MPU9250_MAG_DEV_ID_REG 0x00
    #endif
    
    /**
    * @brief Magnetometer Information registrer.
    */
    #ifndef MPU9250_MAG_INFO_REG
        #define MPU9250_MAG_INFO_REG 0x01
    #endif
    
    /**
    * @brief Magnetometer STATUS 1 registrer.
    */
    #ifndef MPU9250_MAG_ST1
        #define MPU9250_MAG_ST1 0x02
    #endif
    
    /**
    * @brief Magnetometer x axis out (high byte) registrer.
    */
    #ifndef MPU9250_MAG_XOUT_H_REG
        #define MPU9250_MAG_XOUT_H_REG 0x03
    #endif
    
    /**
    * @brief Magnetometer x axis out (low byte) registrer.
    */
    #ifndef MPU9250_MAG_XOUT_L_REG
        #define MPU9250_MAG_XOUT_L_REG 0x04
    #endif
    
    /**
    * @brief Magnetometer y axis out (high byte) registrer.
    */
    #ifndef MPU9250_MAG_YOUT_H_REG
        #define MPU9250_MAG_YOUT_H_REG 0x05
    #endif

    /**
    * @brief Magnetometer y axis out (low byte) registrer.
    */
    #ifndef MPU9250_MAG_YOUT_L_REG
        #define MPU9250_MAG_YOUT_L_REG 0x06
    #endif
    
    /**
    * @brief Magnetometer Z axis out (high byte) registrer.
    */
    #ifndef MPU9250_MAG_ZOUT_H_REG
        #define MPU9250_MAG_ZOUT_H_REG 0x07
    #endif

    /**
    * @brief Magnetometer Z axis out (low byte) registrer.
    */
    #ifndef MPU9250_MAG_ZOUT_L_REG
        #define MPU9250_MAG_ZOUT_L_REG 0x08
    #endif
    
    /**
    * @brief Magnetometer STATUS 2 registrer.
    */
    #ifndef MPU9250_MAG_ST2_REG
        #define MPU9250_MAG_ST2_REG 0x09
    #endif
    
    /**
    * @brief Magnetometer CONTROL1 reg.
    */
    #ifndef MPU9250_MAG_CNTL1_REG
        #define MPU9250_MAG_CNTL1_REG 0x0A
    #endif
    
    
#endif

/* [] END OF FILE */
