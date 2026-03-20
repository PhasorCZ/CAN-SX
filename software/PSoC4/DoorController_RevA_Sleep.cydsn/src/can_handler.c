/*******************************************************************************
* \file         can_handler.c
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
#include "can_handler.h"
#include "spi_handler.h"

extern uint8 sleep_request;

// -----------------------------------------------------------------------------
    
static const uint32 can_rx_id_whitelist[] = {   0x101,
                                                0x200,
                                                0x201,
                                                0x202,
                                                0x212,
                                                0x222   };

#define CAN_ID_COUNT (sizeof(can_rx_id_whitelist) / sizeof(can_rx_id_whitelist[0]))

// -----------------------------------------------------------------------------

static inline uint8 can_rx_id_allowed(uint32 id)
{
    for (uint8 i = 0; i < CAN_ID_COUNT; i++)
    {
        if (can_rx_id_whitelist[i] == id)
            return 1;
    }
    return 0;
}

// -----------------------------------------------------------------------------

uint8 can_rx_filter_msg(uint8 rxMailbox)
{
    uint32 id;
    
    /* Read CAN ID */
    id = CAN_GET_RX_ID(rxMailbox);
    
    if (!can_rx_id_allowed(id))
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

// -----------------------------------------------------------------------------

void can_rx_store_msg( uint8       rx_mailbox,
                       CanRxQueue *queue    )
{
    uint32 id;
    uint8  dlc;
    uint8  next_head;

    /* Read CAN ID */
    id = CAN_GET_RX_ID(rx_mailbox);
    
    /* Check if ID is allowed */
    if (!can_rx_id_allowed(id))
    {
        return;
    }
    
    /* Calculate next head */
    next_head = (queue->head + 1) % CAN_RX_QUEUE_SIZE;
    
    /* Check if queue is full */
    if (next_head == queue->tail)
    {
        /* Optional: increment overflow counter */
        queue->overflow_count++;
        return;
    }
    
    /* Read DLC */
    dlc = (uint8)CAN_GET_DLC(rx_mailbox);
    
    /* Clamp DLC for safety */
    if (dlc > 8)
    {
        dlc = 8;
    }
    
    /* Store message */
    queue->msg[queue->head].id = id;
    queue->msg[queue->head].dlc = dlc;
    
    for (uint8 i = 0; i < dlc; i++)
    {
        queue->msg[queue->head].data[i] = CAN_RX_DATA_BYTE(rx_mailbox, i);
    }
    
    /* Advance head */
    queue->head = next_head;
}

// -----------------------------------------------------------------------------

void can_rx_process_msg (CanRxQueue *queue)
{
    CanRxMsg rx_msg;
    uint8 head = queue->head;
    
    while (queue->tail != head)
    {
        /* Pop rx message from ring buffer */
        rx_msg = queue->msg[queue->tail];
        
        /* Advance tail */
        queue->tail = (queue->tail + 1u) % CAN_RX_QUEUE_SIZE;
        
        CAN_TX_DATA_LO_REG(6) = 0x0f0f0f0f;
        CAN_TX_DATA_HI_REG(6) = rx_msg.id << 16 | 
                                queue->head << 8 |
                                queue->tail;
        
        while (CAN_SendMsg6() != CYRET_SUCCESS)
        {
            CyDelayUs(10);
        }
        
        /* Dispatch by ID */
        switch (rx_msg.id)
        {
            case 0x101:
            {
                CAN_TX_DATA_LO_REG(0) = 0x0f0f0f0f;
                CAN_TX_DATA_HI_REG(0) = 0x0f0f0f0f;
                CAN_SendMsg0();
                CyDelay(1);
                
                EN_1_Write(0);
                EN_2_Write(0);
                EN_3_Write(0);
                EN_4_Write(0);
                
                /* Stop outputs 20A */
                PWM_DOWN_INH_Write(0);
                PWM_UP_INH_Write(0);
                /*
                PWM_DOWN_WriteCompare(0);
                PWM_DOWN_Stop();
                
                PWM_UP_WriteCompare(100);
                PWM_UP_Stop();
                */
                PWM_DOWN_IN_Write(0);
                PWM_UP_IN_Write(0);
                
                /* Stop outputs 10A */
                MM_EN_Write(0);
                HB_1_EN_Write(0);
                HB_2_EN_Write(0);
                
                MM_IN_Write(0);     // DEN
                HB_1_IN_Write(0);   // DEN
                HB_2_IN_Write(0);   // DEN
                
                MM_DEN_Write(0);    // IN
                HB_1_DEN_Write(0);  // IN
                HB_2_DEN_Write(0);  // IN
                
                //PWM_MM_Start();
                //PWM_HB_1_Start();
                //PWM_HB_2_Start();
                
                /* Stop outputs 5A */
                /*
                uint8 tx = 0b00011000;
                
                send_spi_data(  &tx,
                                &tx,
                                &tx,
                                NULL,
                                NULL,
                                NULL);
                */
                
                /* Stop SPI */
                //SCB_Stop();
                
                CAN_TX_DATA_LO_REG(0) = 0x0f0f0f0f;
                CAN_TX_DATA_HI_REG(0) = 0x0f0f0f0f;
                CAN_SendMsg0();
                CyDelay(1);
                
                /* Stop CAN */
                CAN_Stop();
                
                Bootloadable_SET_RUN_TYPE(Bootloadable_SCHEDULE_BTLDR);
                CySoftwareReset();
                break;
            }
            case 0x200:
            {
                sleep_request = 1;
                break;
            }
            case 0x201:
            {
                break;
            }
            case 0x202:
            {
                if (rx_msg.data[0] == 0x00)
                {
                    MM_EN_Write(0);
                    HB_1_EN_Write(0);
                    HB_2_EN_Write(0);
                }
                else
                {
                    MM_EN_Write(1);
                    HB_1_EN_Write(1);
                    HB_2_EN_Write(1);
                }
                break;
            }
            case 0x222:
            {
                if (rx_msg.data[0] == 0x00)
                {
                    PWM_DOWN_INH_Write(0);
                    PWM_UP_INH_Write(0);
                }
                else
                {
                    PWM_DOWN_INH_Write(1);
                    PWM_UP_INH_Write(1);
                }
                
                break;
            }
            default:
            {
                CAN_DATA_BYTES_MSG payload;
                CAN_TX_MSG tx_msg;
                
                /* Definition of CAN_TX_FRAME */
                tx_msg.id = rx_msg.id + 1;
                tx_msg.rtr = CAN_STANDARD_MESSAGE;
                tx_msg.ide = CAN_STANDARD_MESSAGE;
                tx_msg.irq = CAN_TRANSMIT_INT_DISABLE;
                tx_msg.dlc = rx_msg.dlc;
                
                tx_msg.msg = &payload;
                
                memcpy(payload.byte, rx_msg.data, tx_msg.dlc);
                
                while ((CAN_SendMsg(&tx_msg) != CYRET_SUCCESS))
                {
                    CyDelayUs(10);
                }
                break;
            }
        }
    }
}

// -----------------------------------------------------------------------------

/* [] END OF FILE */
