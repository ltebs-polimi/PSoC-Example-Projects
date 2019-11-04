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

    #include "cytypes.h"

    /**
    *   \brief Success code returned by functions.
    */
    #define BME280_OK                    0
    
    /**
    *   \brief Null pointer error.
    */
    #define BME280_E_NULL_PTR           -1
    
    /**
    *   \brief Device not found error.
    */
    #define BME280_E_DEV_NOT_FOUND      -2
    
    /**
    *   \brief Invalid length error.
    */
    #define BME280_E_INVALID_LEN        -3
    
    /**
    *   \brief Communication error.
    */
    #define BME280_E_COMM_FAIL          -4
    
    /**
    *   \brief Sleep mode failed error.
    */
    #define BME280_E_SLEEP_MODE_FAIL    -5
    
    /**
    *   \brief NVM copy error.
    */
    #define BME280_E_NVM_COPY_FAILED    -6
    
    /**
    *   \brief Typedefs for error codes returned by functions.
    */
    typedef int8_t BME280_ErrorCode;
    
#endif
/* [] END OF FILE */