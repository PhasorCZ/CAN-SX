/*******************************************************************************
* \file         power_window.h
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

#if !defined(POWER_WINDOW_H)
#define POWER_WINDOW_H
    
// -----------------------------------------------------------------------------

#include "cytypes.h"

// -----------------------------------------------------------------------------

typedef enum
{
    POWER_WINDOW_STATE_INIT,
    POWER_WINDOW_STATE_IDLE,
    POWER_WINDOW_STATE_OPENING,
    POWER_WINDOW_STATE_OPENING_AUTO,
    POWER_WINDOW_STATE_CLOSING,
    POWER_WINDOW_STATE_CLOSING_AUTO,
    POWER_WINDOW_STATE_STOP,
    POWER_WINDOW_STATE_SLEEP,
    POWER_WINDOW_STATE_ERROR
} PowerWindowState;

// -----------------------------------------------------------------------------

void power_window_init(void);

void power_window_sleep(void);

void power_window_wakeup(void);

void pwm_down_write_compare(uint8 duty_p100);

void pwm_up_write_compare(uint8 duty_p100);

void power_window_brake(void);

void power_window_down(uint8 duty_p100);

void power_window_up(uint8 duty_p100);

void power_window_statemachine( PowerWindowState   *power_window_state,
                                uint8               pws_down,
                                uint8               pws_up,
                                uint8               pws_auto,
                                uint8               sleep,
                                uint8               wake_up);

// -----------------------------------------------------------------------------

#endif /* POWER_WINDOW_H */

/* [] END OF FILE */
