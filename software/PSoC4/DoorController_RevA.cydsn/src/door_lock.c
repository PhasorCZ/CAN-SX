/*******************************************************************************
* \file         door_lock.c
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

#include "door_lock.h"

// -----------------------------------------------------------------------------

static const uint16 DOOR_LOCK_TIMEOUT_COUNT = 100;

// -----------------------------------------------------------------------------

void door_lock_idle(uint8 *BTM9021EP_3_data)
{
    *BTM9021EP_3_data = *BTM9021EP_3_data & 0b10011111;
}

// -----------------------------------------------------------------------------

void door_lock_open(uint8 *BTM9021EP_3_data)
{
    
    *BTM9021EP_3_data = *BTM9021EP_3_data & 0b10111111;
    *BTM9021EP_3_data = *BTM9021EP_3_data | 0b01000000;
}

// -----------------------------------------------------------------------------

void door_lock_close(uint8 *BTM9021EP_3_data)
{
    *BTM9021EP_3_data = *BTM9021EP_3_data & 0b10111111;
    *BTM9021EP_3_data = *BTM9021EP_3_data | 0b00100000;
}

// -----------------------------------------------------------------------------

void door_lock_statemachine(DoorLockState  *state,
                            uint8          *BTM9021EP_3_data,
                            volatile uint8          *unlocking,
                            volatile uint8          *locking,
                            uint8           sleep,
                            uint8           wake_up)
{
    static uint16 dls_counter = 0;
    
    switch (*state)
    {
        // .....................................................................
        case DOOR_LOCK_STATE_INIT:
        {
            door_lock_idle(BTM9021EP_3_data);
            
            *state = DOOR_LOCK_STATE_IDLE;
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_IDLE:
        {
            if (*unlocking)
            {
                door_lock_open(BTM9021EP_3_data);
                
                dls_counter = DOOR_LOCK_TIMEOUT_COUNT;
                
                *state = DOOR_LOCK_STATE_UNLOCKING;
            }
            else if (*locking)
            {
                door_lock_close(BTM9021EP_3_data);
                
                dls_counter = DOOR_LOCK_TIMEOUT_COUNT;
                
                *state = DOOR_LOCK_STATE_LOCKING;
            }
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_UNLOCKING:
        {
            *unlocking = 0;
            *locking = 0;
            
            if (!dls_counter)
            {
                door_lock_idle(BTM9021EP_3_data);
                
                *state = DOOR_LOCK_STATE_UNLOCKED;
            }
            
            if(dls_counter > 0) dls_counter--;
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_UNLOCKED:
        {
            if (*locking)
            {
                door_lock_close(BTM9021EP_3_data);
                
                dls_counter = DOOR_LOCK_TIMEOUT_COUNT;
                
                *state = DOOR_LOCK_STATE_LOCKING;
            }
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_LOCKING:
        {
            *unlocking = 0;
            *locking = 0;
            
            if (!dls_counter)
            {
                door_lock_idle(BTM9021EP_3_data);
                
                *state = DOOR_LOCK_STATE_LOCKED;
            }
            
            if(dls_counter > 0) dls_counter--;
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_LOCKED:
        {
            if (sleep)
            {
                *state = DOOR_LOCK_STATE_SLEEP;
            }
            else if (*unlocking)
            {
                door_lock_open(BTM9021EP_3_data);
                
                dls_counter = DOOR_LOCK_TIMEOUT_COUNT;
                
                *state = DOOR_LOCK_STATE_UNLOCKING;
            }
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_SLEEP:
        {
            if (wake_up)
            {
                *state = DOOR_LOCK_STATE_IDLE;
            }
            
            break;
        }
        // .....................................................................
        case DOOR_LOCK_STATE_ERROR:
        {
            break;
        }
        // .....................................................................
        default:
        {
            break;
        }
    }
}

// -----------------------------------------------------------------------------
/* [] END OF FILE */
