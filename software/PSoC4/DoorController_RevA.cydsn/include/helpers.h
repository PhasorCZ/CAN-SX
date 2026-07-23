/*******************************************************************************
* \file         helpers.h
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

#if !defined(HELPERS_H)
#define HELPERS_H
    
// -----------------------------------------------------------------------------
    
#include "cytypes.h"
    
// -----------------------------------------------------------------------------

uint8 clamp_variable(   uint8   var,
                        uint8   min,
                        uint8   max);

// -----------------------------------------------------------------------------

#endif /* HELPERS_H */

/* [] END OF FILE */
