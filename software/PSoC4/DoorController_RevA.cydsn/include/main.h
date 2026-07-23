/*******************************************************************************
* \file         main.h
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

#if !defined(MAIN_H)
#define MAIN_H
    
// -----------------------------------------------------------------------------

#include "door_lock.h"
#include "power_window.h"

// -----------------------------------------------------------------------------

typedef enum
{
    MAIN_STATE_INIT,
    MAIN_STATE_STANDBY,
    MAIN_STATE_ACTIVE,
    MAIN_STATE_POWER_DOWN,
    MAIN_STATE_SLEEP,
    MAIN_STATE_WAKE_UP,
    MAIN_STATE_ERROR
} MainState;

// -----------------------------------------------------------------------------

void main_statemachine( MainState          *main_state,
                        PowerWindowState    power_window_state,
                        DoorLockState       door_lock_state,
                        uint8              *sleep,
                        uint8              *wake_up);

void activate_hardware();
void sleep_hardware();
void wakeup_hardware();
void deactivate_hardware();

// -----------------------------------------------------------------------------

#endif /* MAIN_H */

/* [] END OF FILE */
