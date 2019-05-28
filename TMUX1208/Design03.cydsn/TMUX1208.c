/* 
 * @brief Source file for TMUX1208 functions.
 * 
 * This source file contains function definitions
 * to interface the PSoC with a TMUX1208.
 *
 * @author: Davide Marzorati
 * @date 28 May, 2019
*/

#include "TMUX1208.h"
#include "Pin_EN.h"
#include "Pin_Address.h"

#define TMUX1208_LOW  0
#define TMUX1208_HIGH 1


void TMUX1208_Start(void) 
{
    TMUX1208_Enable();
    TMUX1208_SetChannel(0);
}
    
void TMUX1208_Enable(void)
{
    Pin_EN_Write(TMUX1208_HIGH);
}

void TMUX1208_Disable(void)
{
    Pin_EN_Write(TMUX1208_LOW);
}

void TMUX1208_Reset(void)
{
    TMUX1208_SetChannel(0);
}

void TMUX1208_SetChannel(uint8_t channel)
{
    if ( (channel < 0) || (channel > 7))
        return;
    
    Pin_Address_Write(channel);
}

uint8 TMUX1208_GetChannel(void)
{
    return Pin_Address_Read();
}
/* [] END OF FILE */
