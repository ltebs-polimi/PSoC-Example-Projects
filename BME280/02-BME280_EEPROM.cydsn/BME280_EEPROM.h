/**
*   \file BME280_EEPROM.h
*
*   \brief Header file with function declarations to write BME280 data to EEPROM.
*
*   \author Davide Marzorati
*   \date November 7, 2019
*/
#ifndef __BME_EEPROM_H
    #define __BME_EEPROM_H

    #include "BME280.h"
    #include "EEPROM_ErrorCodes.h"
    
    EEPROM_ErrorCode BME280_EEPROM_Start(void);
    
    EEPROM_ErrorCode BME280_EEPROM_Stop(void);
    
    EEPROM_ErrorCode BME280_EEPROM_WriteData(BME280* bme280);
    
#endif

/* [] END OF FILE */
