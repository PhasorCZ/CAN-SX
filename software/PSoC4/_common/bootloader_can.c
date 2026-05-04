/*******************************************************************************
* \file         bootloader_can.c
* \version      1.00
*
* \brief
*   Provides definitions of Bootloader API functions for custom interface
*   with CAN used as a transport layer. Compatible with PSoC3, PSoC4 and PSoC5.
*
*   CAN_RX_FRAME_ID -   command message received FROM external programmer
*   CAN_TX_FRAME_ID -   bootloader response send TO external programmer
*   CAN_ACK_FRAME_ID -  RX message acknowledge sent TO external programmer
*   CAN_DBG_FRAME_ID -  debug message sent TO external programmer
*
*   IMPORTANT:
*       Bootloader needs to have SysClk derived from internal master clock.
*       CAN component needs to run on external oscilator for timing precission.
*
*       For PSoC5 it is fine as it can use two different clocks, but PSoC4
*       cannot. We then need to switch between clock sources for flashing and
*       for CAN communication. CAN component needs to be stopped for PSoC4
*       during flashing to prevent system crash.
*
********************************************************************************
* \author       Tomas Kozak <pasorcz@gmail.com>
* \copyright    GNU Public License V3
*******************************************************************************/

#include "project.h"

/* How much do we wait between mailboxes checks */
#define RETRY_DELAY_MS 1u

/* Define the system clock frequency for PSoC5 */
#if (CY_PSOC5)
    #define SYSCLK_HZ 48000000u  /* set to your actual CPU clock frequency */
#endif /* CY_PSOC5 */

// -----------------------------------------------------------------------------

void prep_can_payload(  uint8   *data,
                        uint16  byte_0_1,
                        uint16  byte_2_3,
                        uint16  byte_4_5,
                        uint16  byte_6_7);

void can_send_message(  uint16  id,
                        uint8   *data,
                        uint8   dlc,
                        uint8   timeout_ms);

static uint32 get_time_ms(void);

// -----------------------------------------------------------------------------

/* Check if an RX mailbox is full */
#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_RX_MAILBOX_FULL(i)    ((CAN_RX[i].rxcmd.byte[0u] & CAN_RX_ACK_MSG) != 0)
#else  /* CY_PSOC4 */
    #define CAN_RX_MAILBOX_FULL(i)    ((CAN_RX_CMD_REG(i) & CAN_RX_ACK_MSG) != 0)
#endif /* CY_PSOC3 || CY_PSOC5 */

/** Mark an RX mailbox as "free", that is mark the message as processed */
#if (CY_PSOC3 || CY_PSOC5)
    #define CAN_RX_MAILBOX_FREE(i)    (CAN_RX[i].rxcmd.byte[0u] |= CAN_RX_ACK_MSG)
#else  /* CY_PSOC4 */
    #define CAN_RX_MAILBOX_FREE(i)    (CAN_RX_CMD_REG(i) |= CAN_RX_ACK_MSG)
#endif /* CY_PSOC3 || CY_PSOC5 */

// -----------------------------------------------------------------------------

static uint8 can_active = 0;

extern uint32 CAN_RX_FRAME_ID;
extern uint32 CAN_TX_FRAME_ID;
extern uint32 CAN_ACK_FRAME_ID;
extern uint32 CAN_DBG_FRAME_ID;

// -----------------------------------------------------------------------------

void CyBtldrCommStart(void)
{
    if (!can_active)
    {
        CyDelayUs(10);
        
        #if CY_PSOC4
            /* Switch to ECO for CAN timing precission */
            CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_ECO);
            CyDelayUs(10);
        #endif /* CY_PSOC4 */
        
        CAN_Start();
        can_active = 1;
    }
}

// -----------------------------------------------------------------------------

void CyBtldrCommStop(void)
{
    CAN_Stop();
    can_active = 0;
    
    CyDelayUs(10);
    
    #if CY_PSOC4
        /* Switch to IMO for flashing */
        CySysClkWriteHfclkDirect(CY_SYS_CLK_HFCLK_IMO);
        CyDelayUs(10);
    #endif /* CY_PSOC4 */
}

// -----------------------------------------------------------------------------

void CyBtldrCommReset(void)
{
    // Abort pending messages
    for (uint8 i = 0u; i < CAN_NUMBER_OF_TX_MAILBOXES; i++)
    {
        CAN_TxCancel(i);
        //CAN_RX_RTR_ABORT_MESSAGE(i);
    }
    
    CyBtldrCommStop();
    CyBtldrCommStart();
}

// -----------------------------------------------------------------------------

cystatus CyBtldrCommWrite(uint8* buffer, uint16 size, uint16* count, uint8 timeout)
{
    uint32 start_time = get_time_ms();
    const uint32 timeout_ms = 10 * timeout;
    
    uint16 pointer = 0;
    
    uint8 data[8];
    
    CAN_TX_MSG msg;
    CAN_DATA_BYTES_MSG payload;
    
    /* Start CAN component */
    CyBtldrCommStart();
    
    /* Indicate bootloader WRITE request */
    LED_Write(1);
    
    prep_can_payload(   data,
                        0xffff,
                        (uint16)timeout_ms,
                        *count,
                        size);
    
    can_send_message(   CAN_DBG_FRAME_ID,
                        data,
                        8,
                        10);
    
    /* Nothing to send */
    if ((size == 0) || (count == 0))
    {
        return CYRET_BAD_PARAM;
    }
    
    /* Definition of CAN_TX_FRAME */
    msg.id = CAN_TX_FRAME_ID;
    msg.rtr = CAN_STANDARD_MESSAGE;
    msg.ide = CAN_STANDARD_MESSAGE;
    msg.irq = CAN_TRANSMIT_INT_DISABLE;
    msg.msg = &payload;

    /* Split payload to multiple CAN frames and send them one by one */
    while ((pointer < size) && ((get_time_ms() - start_time) < timeout_ms))
    {
        msg.dlc = ((size - pointer) > CAN_TX_DLC_MAX_VALUE) ? CAN_TX_DLC_MAX_VALUE : (size - pointer);
        
        /* Copy payload to payload buffer */
        memcpy(payload.byte, buffer + pointer, msg.dlc);
        
        /* Inrement pointer for next CAN frame */
        pointer += msg.dlc;
        
        /* Send CAN_TX_FRAME */
        while ((CAN_SendMsg(&msg) != CYRET_SUCCESS) && ((get_time_ms() - start_time) < timeout_ms))
        {
            CyDelay(RETRY_DELAY_MS);
        }
        
        CyDelay(RETRY_DELAY_MS);
    }

    if ((get_time_ms() - start_time) < timeout_ms)
    {
        return CYRET_TIMEOUT;
    }

    return CYRET_SUCCESS;
}

// -----------------------------------------------------------------------------
cystatus CyBtldrCommRead(uint8* buffer, uint16 size, uint16* count, uint8 timeout)
{
    uint32 start_time = get_time_ms();
    const uint32 timeout_ms = 10 * timeout;
    
    uint16 mailbox;
    
    uint32 frame_id;
    uint8 dlc;
    uint8 data[8];
    
    uint16 payload_length = 0;
    uint16 total_length = 0;
    
    /* Make sure the CAN component is active */
    CyBtldrCommStart();
    
    /* Indicate bootloader READ request */
    LED_Write(0);
    
    prep_can_payload(   data,
                        0x0000,
                        (uint16)timeout_ms,
                        *count,
                        size);
    
    can_send_message(   CAN_DBG_FRAME_ID,
                        data,
                        8,
                        10);
    
    /* Reset command buffer pointer */
    *count = 0;
    
    /* Check if the buffer provided is big enough for at least one full CAN frame */
    if (size < CAN_TX_DLC_MAX_VALUE)
    {
        return CYRET_BAD_PARAM;
    }
    
    /* Prepare command buffer and initialize count */
    memset(buffer, 0, size);

    /* Wait for the full command to be received */
    while ((get_time_ms() - start_time) < timeout_ms)
    {
        /* Go through mailboxes one by one an look for messages */
        for (mailbox = 0; mailbox < CAN_NUMBER_OF_RX_MAILBOXES; mailbox++)
        {
            /*  */
            if (!CAN_RX_MAILBOX_FULL(mailbox))
            {
                continue;
            }
            
            /* Get current RX frame ID */
            frame_id = CAN_GET_RX_ID(mailbox);
            
            /* Check if the frame has correct ID */
            if (frame_id != CAN_RX_FRAME_ID)
            {
                CAN_RX_MAILBOX_FREE(mailbox);
                continue;
            }
            
            /* Get payload size for current RX frame */
            dlc = CAN_GET_DLC(mailbox);
            
            /* Clear frame payload buffr */
            memset(data, 0, 8);
            
            /* Copy frame payload */
            #if (CY_PSOC3 || CY_PSOC5)
                for (uint8 j = 0; j < dlc; j++)
                {
                    data[j] = CAN_RX_DATA_BYTE(mailbox, j);
                }
            #else  /* CY_PSOC4 */
                uint32 lo = CAN_RX_DATA_LO_REG(mailbox);
                uint32 hi = CAN_RX_DATA_HI_REG(mailbox);

                for (uint8 j = 0; j < dlc; j++)
                {
                    uint32 reg = (j < 4) ? lo : hi;
                    uint8 shift = 24 - 8 * (j & 3);
                    data[j] = (uint8)(reg >> shift);
                }
            #endif /* CY_PSOC3 || CY_PSOC5 */
            
            /* Free current mailbox */
            CAN_RX_MAILBOX_FREE(mailbox);
            
            /* Check if there is enough space left in the command buffer */
            if ((*count + dlc) > size)
            {
                CAN_RX_MAILBOX_FREE(mailbox);
                return CYRET_BAD_DATA;
            }
            
            /* Append payload to command buffer */
            for (uint8 j = 0; j < dlc; j++)
            {
                buffer[*count + j] = data[j];
            }
            
            /* Increment command buffer pointer */
            *count += dlc;
            
            /* Echo RX frame as an acknowledge to host that RX data are in command buffer */
            can_send_message(   CAN_ACK_FRAME_ID,
                                data,
                                dlc,
                                10);

            /* Extract expected length of bootloader command once available */
            if (*count >= 4 && payload_length == 0)
            {
                payload_length = buffer[2] | (buffer[3] << 8);
                
                /* SOP + CMD + LEN(2) + PAYLOAD + CRC(2) + EOP */
                total_length = 1 + 1 + 2 + payload_length + 2 + 1;
            }
            
            /* Check if we have the full command in buffer already */
            if (*count == total_length)
            {
                /* Check if the command has correct SOP and EOP */
                if ((buffer[0] == Bootloader_SOP)           &&
                    (buffer[*count - 1] == Bootloader_EOP))
                {
                    /* Stop CAN component for flash write operations */
                    if( (buffer[1] == Bootloader_COMMAND_ERASE)     ||
                        (buffer[1] == Bootloader_COMMAND_PROGRAM))
                    {
                        CyBtldrCommStop();
                    }
                    
                    return CYRET_SUCCESS;
                }
                else
                {
                    return CYRET_BAD_DATA;
                }
            }
        }
        
        /* Small delay to avoid busy-waiting and then try again */
        CyDelayUs(100);
    }
    
    return CYRET_TIMEOUT;
}

// -----------------------------------------------------------------------------

void prep_can_payload(  uint8   *data,
                        uint16  byte_0_1,
                        uint16  byte_2_3,
                        uint16  byte_4_5,
                        uint16  byte_6_7)
{
    data[0] = byte_0_1 >> 8;
    data[1] = byte_0_1 & 0xff;
    data[2] = byte_2_3 >> 8;
    data[3] = byte_2_3 & 0xff;
    data[4] = byte_4_5 >> 8;
    data[5] = byte_4_5 & 0xff;
    data[6] = byte_6_7 >> 8;
    data[7] = byte_6_7 & 0xff;
}

// -----------------------------------------------------------------------------

void can_send_message(  uint16  id,
                        uint8   *data,
                        uint8   dlc,
                        uint8   timeout_ms)
{
    uint32 start_time = get_time_ms();
    
    CAN_TX_MSG msg;
    CAN_DATA_BYTES_MSG payload;
    
    /* Definition of CAN_TX_FRAME */
    msg.id = id;
    msg.rtr = CAN_STANDARD_MESSAGE;
    msg.ide = CAN_STANDARD_MESSAGE;
    msg.irq = CAN_TRANSMIT_INT_DISABLE;
    msg.dlc = dlc;
    
    msg.msg = &payload;
    
    memcpy(payload.byte, data, msg.dlc);
    
    while ((CAN_SendMsg(&msg) != CYRET_SUCCESS) && ((get_time_ms() - start_time) < timeout_ms))
    {
        CyDelay(RETRY_DELAY_MS);
    }
}

// -----------------------------------------------------------------------------

static uint32 get_time_ms(void)
{
#if (CY_PSOC3)
    return CyGetTickCount();
    
#elif (CY_PSOC4)
    return ((CySysTickGetReload() - CySysTickGetValue()) * 1000u) / CYDEV_BCLK__SYSCLK__HZ;

#elif (CY_PSOC5)
    uint32 reload = SysTick->LOAD + 1;
    uint32 current = SysTick->VAL;
    static uint32 last = 0;
    static uint32 ms = 0;

    uint32 elapsed;
    if (current <= last)
        elapsed = last - current;
    else
        elapsed = reload - (current - last);  /* handle wrap */

    ms += (elapsed * 1000u);
    last = current;
    
    return ms;
#endif /* CY_PSOC3 */
}
/* [] END OF FILE */
