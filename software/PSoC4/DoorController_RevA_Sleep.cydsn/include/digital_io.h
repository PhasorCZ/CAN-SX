/*******************************************************************************
* \file         digital_io.h
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

#if !defined(DIGITAL_IO_H)
#define DIGITAL_IO_H
    
// -----------------------------------------------------------------------------
    
#include "cytypes.h"

// -----------------------------------------------------------------------------

typedef union
{
    uint8 byte;
    struct
    {
        uint8 pws_left_down_deb          : 1;
        uint8 pws_left_up_deb            : 1;
        uint8 pws_left_auto_deb          : 1;
        uint8 pws_right_down_deb         : 1;
        uint8 pws_right_up_deb           : 1;
        uint8 pws_right_lock_down_deb    : 1;
        uint8 pws_right_lock_up_deb      : 1;
        uint8 di_deb                     : 1;
    } bits;
} U8Bits;

// -----------------------------------------------------------------------------

void read_digital_inputs(U8Bits *dio);

// -----------------------------------------------------------------------------

#endif /* DIGITAL_IO_H */

/* [] END OF FILE */
