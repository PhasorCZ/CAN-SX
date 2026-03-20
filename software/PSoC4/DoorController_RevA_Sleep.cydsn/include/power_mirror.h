/*******************************************************************************
* \file         power_mirror.h
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

#if !defined(POWER_MIRROR_H)
#define POWER_MIRROR_H
    
// -----------------------------------------------------------------------------
    
#include "cytypes.h"

// -----------------------------------------------------------------------------

enum PowerMirrorState
{
    POWER_MIRROR_STATE_INIT,
    POWER_MIRROR_STATE_IDLE,
    POWER_MIRROR_STATE_DOWN,
    POWER_MIRROR_STATE_UP,
    POWER_MIRROR_STATE_RIGHT,
    POWER_MIRROR_STATE_LEFT,
    POWER_MIRROR_STATE_STOP,
    POWER_MIRROR_STATE_ERROR
};

// -----------------------------------------------------------------------------

void power_mirror_init(void);

void power_mirror_deinit(void);

void power_mirror_brake(void);

void power_mirror_statemachine( enum PowerMirrorState  *state,
                                uint8                   pms_down,
                                uint8                   pms_up,
                                uint8                   pms_right,
                                uint8                   pms_left);

// -----------------------------------------------------------------------------

#endif /* POWER_MIRROR_H */

/* [] END OF FILE */
