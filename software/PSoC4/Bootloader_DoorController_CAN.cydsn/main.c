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

uint32 CAN_RX_FRAME_ID =    0x101;
uint32 CAN_TX_FRAME_ID =    0x102;
uint32 CAN_ACK_FRAME_ID =   0x103;
uint32 CAN_DBG_FRAME_ID =   0x104;

int main(void)
{
    /* Enable Interrupts */
    CyGlobalIntEnable;

    /* Enable CAN driver */
    CAN_STB_Write(1);
    CAN_EN_Write(1);
    CyDelay(10);
    
    /* Indication LED */
    LED_Write(1);
    
    /* Start bootloader routine */
    Bootloader_Start();
}   /* end main */

/* [] END OF FILE */
