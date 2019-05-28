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
#include "TMUX1208.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    char message[30] = {'\0'};
    UART_1_Start();
    ADC_DelSig_1_Start();
    
    UART_1_PutString("** TMUX1208 Test**\r\n");
    
    UART_1_PutString("\r\nEnabling TMUX1208\r\n");
    TMUX1208_Start();

    uint16_t adc_value = 0;
    
    for(;;)
    {
        /* Place your application code here. */
        for (int channel = 0; channel < 8; channel++)
        {
            TMUX1208_SetChannel(channel);
            adc_value = (uint16_t) ADC_DelSig_1_Read32();
            sprintf(message, "Channel: %d Value: %d\r\n",
                channel + 1, ADC_DelSig_1_CountsTo_mVolts(adc_value));
            UART_1_PutString(message);
            CyDelay(500);
        }
        UART_1_PutCRLF('\t');
    }
}





/* [] END OF FILE */
