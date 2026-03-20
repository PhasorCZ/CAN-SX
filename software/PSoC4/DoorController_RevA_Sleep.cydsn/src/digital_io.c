/*******************************************************************************
* \file         digital_io.c
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

#include "digital_io.h"

// -----------------------------------------------------------------------------

void read_digital_inputs (U8Bits *dio)
{
    dio->bits.pws_left_down_deb          = !PWS_LEFT_DOWN_DEB_Read();
    dio->bits.pws_left_up_deb            = !PWS_LEFT_UP_DEB_Read();
    dio->bits.pws_left_auto_deb          = !PWS_LEFT_AUTO_DEB_Read();
    dio->bits.pws_right_down_deb         =  PWS_RIGHT_DOWN_DEB_Read();
    dio->bits.pws_right_up_deb           =  PWS_RIGHT_UP_DEB_Read();
    dio->bits.pws_right_lock_down_deb    =  PWS_RIGHT_LOCK_DOWN_DEB_Read();
    dio->bits.pws_right_lock_up_deb      =  PWS_RIGHT_LOCK_UP_DEB_Read();
    dio->bits.di_deb                     = !DI_DEB_Read();
}

// -----------------------------------------------------------------------------
/* [] END OF FILE */
