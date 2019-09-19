/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/
#include "project.h"
#include "stdio.h"
#include "HTS221.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_Debug_Start();
    UART_Debug_PutString("\n\n\n\nHTS221 Start\r\n");
    
    HTS221_Struct hts221;
    char str[30] = {'\0'};
    
    HTS221_Start(&hts221);
    
    
    
    HTS221_OneShot();
    CyDelay(100);
    
    HTS221_ReadTemperature(&hts221);
    HTS221_ReadHumidity(&hts221);
    sprintf(str, "Temp: %d\tHum: %d\r\n", hts221.temperature, hts221.humidity);
    UART_Debug_PutString(str);
    CyDelay(1000);
    
    HTS221_HeaterStart(&hts221);
    CyDelay(5000);
    
    HTS221_OneShot();
    CyDelay(100);
    
    HTS221_ReadTemperature(&hts221);
    HTS221_ReadHumidity(&hts221);
    sprintf(str, "Temp: %d\tHum: %d\r\n", hts221.temperature, hts221.humidity);
    UART_Debug_PutString(str);
    CyDelay(1000);
    
    HTS221_HeaterStop(&hts221);
    CyDelay(5000);
    
    HTS221_OneShot();
    CyDelay(100);
    
    HTS221_ReadTemperature(&hts221);
    HTS221_ReadHumidity(&hts221);
    sprintf(str, "Temp: %d\tHum: %d\r\n", hts221.temperature, hts221.humidity);
    UART_Debug_PutString(str);
    CyDelay(1000);
    
    for(;;)
    {
        HTS221_OneShot();
        CyDelay(100);
        
        HTS221_ReadTemperature(&hts221);
        HTS221_ReadHumidity(&hts221);
        sprintf(str, "Temp: %d\tHum: %d\r\n", hts221.temperature, hts221.humidity);
        UART_Debug_PutString(str);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
