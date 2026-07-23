/*******************************************************************************
* \file         can_handler.h
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

#if !defined(CAN_HANDLER_H)
#define CAN_HANDLER_H

// -----------------------------------------------------------------------------

#include "project.h"

// -----------------------------------------------------------------------------

#define CAN_RX_QUEUE_SIZE 64

typedef struct
{
    uint32  id;
    uint8   dlc;
    uint8   data[8];
} CanRxMsg;

typedef struct
{
    volatile uint8  head;
    volatile uint8  tail;
    volatile uint32 overflow_count;
    CanRxMsg        msg[CAN_RX_QUEUE_SIZE];
} CanRxQueue;

// -----------------------------------------------------------------------------

//static inline uint8 can_rx_id_allowed(uint32 id);

uint8 can_rx_filter_msg(uint8 rxMailbox);

void can_rx_store_msg( uint8       rx_mailbox,
                       CanRxQueue *queue    );
    
void can_rx_process_msg(CanRxQueue *queue);

// -----------------------------------------------------------------------------

#endif /* CAN_HANDLER_H */

/* [] END OF FILE */
