/**
*   \file BME280_ErrorCodes.h
*   \brief Error codes definition.
*   
*   This file contains several definition of error codes to be used throughout
*   the project to be consisted with the written firmware.
*
*   \author Davide Marzorati
*   \date September 12, 2019
*/

#ifndef __BME280_ERRORCODES_H
    #define __BME280_ERRORCODES_H

    /**
    *   \brief Error Codes for BME280 functions.
    *
    *   This is a list of error codes that may be returned by the
    *   BME280 Interface.
    */
    typedef enum {
        BME280_I2C_ERROR,        ///< Error during I2C communication with the sensor
        BME280_DEVICE_NOT_FOUND, ///< Device was not found on I2C bus.
        BME280_ERROR,            ///< Generic error
        BME280_OK                ///< No error generated
    } BME280_ErrorCode;
#endif
/* [] END OF FILE */
