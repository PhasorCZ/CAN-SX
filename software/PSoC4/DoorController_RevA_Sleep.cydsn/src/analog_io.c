/*******************************************************************************
* \file         analog_io.c
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

#include "analog_io.h"

// -----------------------------------------------------------------------------

/* Current sense resistor [Ohm] */
const uint16 R_SENSE_BTN9990LV =    845;
const uint16 R_SENSE_BTN70301EPA =  430;
const uint16 R_SENSE_BTM9021EP =    330;

/* Current sense ratio */
const uint16 K_ILIS_BTN9990LV =     50000;
const uint16 K_ILIS_BTN70301EPA =   4300;
const uint16 K_ILIS_BTM9021EP_HI =  4800;
const uint16 K_ILIS_BTM9021EP_LO =  6000;

#define K_IS_BTN9990LV K_ILIS_BTN9990LV / R_SENSE_BTN9990LV

/* Current sense offset [mA] */
const float IS_OFFSET_BTN9990LV = 0.1;

// -----------------------------------------------------------------------------



// -----------------------------------------------------------------------------

/* [] END OF FILE */
