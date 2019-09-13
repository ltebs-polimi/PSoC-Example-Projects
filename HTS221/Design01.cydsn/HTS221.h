/**
*   \file HTS221.h
*
*   This header file contains all the macros and function
*   declarations required to communicate with a HTS221
*   temperature and relative humidity sensor using I2C
*   protocol. This interface depends on the I2C_Interface,
*   so you can easily change that functions and leave the 
*   one implemented here if your hardware is different.
*   
*   \see I2C_Interface
*   \author Davide Marzorati
*   \date September 12, 2019
*/

/******************************************************/
/*                  Registers                         */
/******************************************************/

/**
*   \brief WHO AM I Register address
*/
#ifndef HTS221_WHO_AM_I_REG
    #define HTS221_WHO_AM_I_REG 0x0F
#endif

/**
*   \brief Resolution configuration register address
*/
#ifndef HTS221_AV_CONF_REG
    #define HTS221_AV_CONF_REG 0x10
#endif

/**
*   \brief Control register 1 address
*/
#ifndef HTS221_CTRL_REG_1
    #define HTS221_CTRL_REG_1 0x20
#endif

/**
*   \brief Control register 2 address
*/
#ifndef HTS221_CTRL_REG_2
    #define HTS221_CTRL_REG_2 0x21
#endif

/**
*   \brief Control register 3 address
*/
#ifndef HTS221_CTRL_REG_3
    #define HTS221_CTRL_REG_3 0x22
#endif

/**
*   \brief Status register address
*/
#ifndef HTS221_STATUS_REG
    #define HTS221_STATUS_REG 0x27
#endif

/**
*   \brief Relative humidity LSB register address
*/
#ifndef HTS221_HUMIDITY_OUT_L_REG
    #define HTS221_HUMIDITY_OUT_L_REG 0x28
#endif

/**
*   \brief Relative humidity MSB register address
*/
#ifndef HTS221_HUMIDITY_OUT_H_REG
    #define HTS221_HUMIDITY_OUT_H_REG 0x29
#endif

/**
*   \brief Temperature LSB register address
*/
#ifndef HTS221_TEMP_OUT_L_REG
    #define HTS221_TEMP_OUT_L_REG 0x2A
#endif

/**
*   \brief Temperature MSB register address
*/
#ifndef HTS221_TEMP_OUT_H_REG
    #define HTS221_TEMP_OUT_H_REG 0x2B
#endif

void HTS221_Start(void);

void HTS221_Stop(void);


/* [] END OF FILE */
