/*******************************************************************************
* \file         bootloader_can.c
* \version      1.00
*
* \brief
*   Provides definitions of Bootloader API functions for custom interface
*   with CAN used as a transport layer. Compatible with PSoC3, PSoC4 and PSoC5.
*
*   CAN_RX_FRAME_ID -   command message received FROM external programmer
*
********************************************************************************
* \author       Tomas Kozak <pasorcz@gmail.com>
* \copyright    GNU Public License V3
*******************************************************************************/

#include "project.h"

// -----------------------------------------------------------------------------

#define LIGHT_OFF                       (0u)
#define LIGHT_ON                        (1u)

uint8 counter = 0;

// -----------------------------------------------------------------------------

CY_ISR(isr_dls)
{
    /* Clear pin Interrupt */
    DLS_LOCKING_ClearInterrupt();
};

// -----------------------------------------------------------------------------

int main(void)
{
    /* Set initial state (off) for LED */
    LED_Write(LIGHT_OFF);
    
    /* Interrupt handlers */
    ISR_DLS_StartEx(isr_dls);
    
    /* Enable Interrupts */
    CyGlobalIntEnable;
    
    /* Indicate enter active mode */
    LED_Write(LIGHT_ON);
    CyDelay(1000);
    
    RTC_Start();
    
// =============================================================================
    
    /* Main function */
    for(;;)
    {
        if (LED_Read())
        {
            LED_Write(LIGHT_OFF);
        }
        CyDelay(500);
        
        if ((counter >= 5) & (DLS_LOCKING_Read() == 1u))
        {
            counter = 0;
            
            DLS_LOCKING_ClearInterrupt();
            ISR_DLS_ClearPending();

            CyDelayUs(10);
            
            CySysPmDeepSleep();
            
            CyDelayUs(10);
        }
        else
        {
            counter++;
        }
        
        LED_Write(LIGHT_ON);
        CyDelay(500);
    }
}

// -----------------------------------------------------------------------------
/* [] END OF FILE */
