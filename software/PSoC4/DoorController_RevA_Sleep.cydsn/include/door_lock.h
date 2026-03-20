/*******************************************************************************
* \file         door_lock.h
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

#if !defined(DOOR_LOCK_H)
#define DOOR_LOCK_H
    
// -----------------------------------------------------------------------------
    
#include "cytypes.h"

// -----------------------------------------------------------------------------

typedef enum
{
    DOOR_LOCK_STATE_INIT,
    DOOR_LOCK_STATE_IDLE,
    DOOR_LOCK_STATE_UNLOCKING,
    DOOR_LOCK_STATE_UNLOCKED,
    DOOR_LOCK_STATE_LOCKING,
    DOOR_LOCK_STATE_LOCKED,
    DOOR_LOCK_STATE_SLEEP,
    DOOR_LOCK_STATE_ERROR
} DoorLockState;

// -----------------------------------------------------------------------------

void door_lock_idle(uint8 *BTM9021EP_3_data);

void door_lock_open(uint8 *BTM9021EP_3_data);

void door_lock_close(uint8 *BTM9021EP_3_data);

void door_lock_statemachine(DoorLockState  *state,
                            uint8          *BTM9021EP_3_data,
                            uint8           dls_unlocking,
                            uint8           dls_locking,
                            uint8           sleep,
                            uint8           wake_up);

// -----------------------------------------------------------------------------

#endif /* DOOR_LOCK_H */

/* [] END OF FILE */
