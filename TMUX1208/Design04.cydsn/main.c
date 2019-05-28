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

CY_ISR_PROTO(ISR_ADC);

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    UART_1_Start();
    ADC_DelSig_1_Start();
    isr_adc_StartEx(ISR_ADC);
    
    UART_1_PutString("** TMUX1208 Test**\r\n");
    
    UART_1_PutString("\r\nEnabling TMUX1208\r\n");
    Timer_1_Start();
    
    for(;;)
    {
    }
}

CY_ISR(ISR_ADC) 
{
    static uint8_t counter = 0;
    static uint16 adc_values[] = {0,0,0,0,0,0,0,0};
    adc_values[counter++] = ADC_DelSig_1_GetResult32();
    if (counter == 8)
    {
        ADC_DelSig_1_StopConvert();
        counter = 0;
        UART_1_PutString("Finished converting.\nValues:\r\n");
        char message[30] = {'\0'};
        for (int i = 0; i < 8; i++)
        {   
            sprintf(message, "%d\t%4d\r\n", i,
                ADC_DelSig_1_CountsTo_mVolts(adc_values[i]));
            UART_1_PutString(message);
        }
    }
}

/* [] END OF FILE */
