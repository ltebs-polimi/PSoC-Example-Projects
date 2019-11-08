/**
*   \file BME280_Logging.h
*
*   \brief Logging system for logging useful information.
*
*   This header file contains function declarations to be used
*   with the logging system to print out useful information
*   throughout the program.
*
*   \author Davide Marzorati
*   \date November 8, 2019
*/

#ifndef __BME280_LOGGING_H
    #define __BME280_LOGGING_H
    
    #include "BME280.h"
    
    void BME280_Logging_Start(void);
    
    void BME280_Logging_Stop(void);
    
    void BME280_Logging_PrintWelcomeMessage(void);
    
    void BME280_Logging_PrintData(BME280* bme280);
    
    void BME280_Logging_PrintTemperature(BME280* bme280);
    
    void BME280_Logging_PrintHumidity(BME280* bme280);
    
    void BME280_Logging_PrintPressure(BME280* bme280);
    
    
#endif


/* [] END OF FILE */
