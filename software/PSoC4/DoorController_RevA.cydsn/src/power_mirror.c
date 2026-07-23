/*******************************************************************************
* \file         power_window.c
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
#include "power_mirror.h"
#include "helpers.h"

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

void power_mirror_init(void)
{

}

// -----------------------------------------------------------------------------

void power_mirror_deinit(void)
{

}

// -----------------------------------------------------------------------------

void power_mirror_brake(void)
{

}

// -----------------------------------------------------------------------------

void power_mirror_statemachine( enum PowerMirrorState  *state,
                                uint8                   pms_down,
                                uint8                   pms_up,
                                uint8                   pms_right,
                                uint8                   pms_left)
{
    static uint16 auto_counter = 0;
    
    switch (*state)
    {
        // .....................................................................
        case POWER_MIRROR_STATE_INIT:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_IDLE:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_DOWN:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_UP:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_RIGHT:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_LEFT:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_STOP:
        {
            break;
        }
        // .....................................................................
        case POWER_MIRROR_STATE_ERROR:
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
