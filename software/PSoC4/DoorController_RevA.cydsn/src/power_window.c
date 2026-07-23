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
#include "power_window.h"
#include "helpers.h"

// -----------------------------------------------------------------------------

static const uint16 POWER_WINDOW_MOTOR_PWM_PERIOD = 1000;

static const uint8 POWER_WINDOW_MOTOR_PWM_DUTY_MIN = 10;
static const uint8 POWER_WINDOW_MOTOR_PWM_DUTY_DOWN = 50;
static const uint8 POWER_WINDOW_MOTOR_PWM_DUTY_UP = 100;
static const uint8 POWER_WINDOW_MOTOR_PWM_DUTY_MAX = 100;

static const uint16 POWER_WINDOW_MOTOR_TIMEOUT_COUNT = 1000;

// -----------------------------------------------------------------------------

void power_window_init(void)
{
    PWM_DOWN_WritePeriod(POWER_WINDOW_MOTOR_PWM_PERIOD);
    PWM_UP_WritePeriod(POWER_WINDOW_MOTOR_PWM_PERIOD);
    
    pwm_down_write_compare(0);
    pwm_up_write_compare(0);
    
    POWER_WINDOW_MOTOR_DOWN_ENABLE();
    POWER_WINDOW_MOTOR_UP_ENABLE();
    
    PWM_DOWN_Start();
    PWM_UP_Start();
}

// -----------------------------------------------------------------------------

void power_window_sleep(void)
{
    POWER_WINDOW_MOTOR_DOWN_DISABLE();
    POWER_WINDOW_MOTOR_UP_DISABLE();
    
    PWM_DOWN_Sleep();
    PWM_UP_Sleep();
}

// -----------------------------------------------------------------------------

void power_window_wakeup(void)
{
    POWER_WINDOW_MOTOR_DOWN_ENABLE();
    POWER_WINDOW_MOTOR_UP_ENABLE();
    
    PWM_DOWN_Wakeup();
    PWM_UP_Wakeup();
}

// -----------------------------------------------------------------------------

void pwm_down_write_compare(uint8 pwm_duty_p100)
{
    if (pwm_duty_p100 == 0)
    {
        PWM_DOWN_WriteCompare(POWER_WINDOW_MOTOR_PWM_PERIOD);
    }
    else
    {
        uint32 pwm_duty_clamp_p100 = clamp_variable(pwm_duty_p100,
                                                    POWER_WINDOW_MOTOR_PWM_DUTY_MIN,
                                                    POWER_WINDOW_MOTOR_PWM_DUTY_MAX);
        
        uint16 compare = (uint16)(((100 - pwm_duty_clamp_p100) * POWER_WINDOW_MOTOR_PWM_PERIOD) / 100);
        compare = compare < POWER_WINDOW_MOTOR_PWM_PERIOD ? compare : POWER_WINDOW_MOTOR_PWM_PERIOD;
        
        PWM_DOWN_WriteCompare(compare);
    }
}

// -----------------------------------------------------------------------------

void pwm_up_write_compare(uint8 pwm_duty_p100)
{
    if (pwm_duty_p100 == 0)
    {
        PWM_UP_WriteCompare(POWER_WINDOW_MOTOR_PWM_PERIOD);
    }
    else
    {
        uint32 pwm_duty_clamp_p100 = clamp_variable(pwm_duty_p100,
                                                    POWER_WINDOW_MOTOR_PWM_DUTY_MIN,
                                                    POWER_WINDOW_MOTOR_PWM_DUTY_MAX);
        
        uint16 compare = (uint16)(((100 - pwm_duty_clamp_p100) * POWER_WINDOW_MOTOR_PWM_PERIOD) / 100);
        compare = compare < POWER_WINDOW_MOTOR_PWM_PERIOD ? compare : POWER_WINDOW_MOTOR_PWM_PERIOD;
        
        PWM_UP_WriteCompare(compare);
    }
}

// -----------------------------------------------------------------------------

void power_window_brake(void)
{
    pwm_down_write_compare(0);
    pwm_up_write_compare(0);
}

// -----------------------------------------------------------------------------

void power_window_down(uint8 pwm_duty_p100)
{
    pwm_down_write_compare(pwm_duty_p100);
    pwm_up_write_compare(0);
}

// -----------------------------------------------------------------------------

void power_window_up(uint8 pwm_duty_p100)
{
    pwm_down_write_compare(0);
    pwm_up_write_compare(pwm_duty_p100);
}

// -----------------------------------------------------------------------------

void power_window_statemachine( PowerWindowState   *power_window_state,
                                uint8               pws_down,
                                uint8               pws_up,
                                uint8               pws_auto,
                                uint8               sleep,
                                uint8               wake_up)
{
    static uint16 auto_counter = 0;
    
    switch (*power_window_state)
    {
        // .....................................................................
        case POWER_WINDOW_STATE_INIT:
        {
            power_window_init();
            power_window_brake();
            
            *power_window_state = POWER_WINDOW_STATE_IDLE;
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_IDLE:
        {
            if (sleep)
            {
                power_window_sleep();
                
                *power_window_state = POWER_WINDOW_STATE_SLEEP;
            }
            else if (pws_down && !pws_up)
            {
                power_window_down(POWER_WINDOW_MOTOR_PWM_DUTY_DOWN);
                
                if (pws_auto)
                {
                    auto_counter = POWER_WINDOW_MOTOR_TIMEOUT_COUNT;
                    
                    *power_window_state = POWER_WINDOW_STATE_OPENING_AUTO;
                }
                else
                {
                    *power_window_state = POWER_WINDOW_STATE_OPENING;
                }
            }
            else if (pws_up && !pws_down)
            {
                power_window_up(POWER_WINDOW_MOTOR_PWM_DUTY_UP);
                
                if (pws_auto)
                {
                    auto_counter = POWER_WINDOW_MOTOR_TIMEOUT_COUNT;
                    
                    *power_window_state = POWER_WINDOW_STATE_CLOSING_AUTO;
                }
                else
                {
                    *power_window_state = POWER_WINDOW_STATE_CLOSING;
                }
            }
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_OPENING:
        {
            if (!pws_down || pws_up)
            {
                power_window_brake();
                
                *power_window_state = POWER_WINDOW_STATE_STOP;
            }
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_OPENING_AUTO:
        {
            if (!auto_counter || !pws_auto || pws_up)
            {
                auto_counter = 0;
                power_window_brake();
                
                *power_window_state = POWER_WINDOW_STATE_STOP;
            }
            
            if (auto_counter > 0) auto_counter--;
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_CLOSING:
        {
            if (!pws_up || pws_down)
            {
                power_window_brake();
                
                *power_window_state = POWER_WINDOW_STATE_STOP;
            }
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_CLOSING_AUTO:
        {
            if (!auto_counter || !pws_auto || pws_down)
            {
                auto_counter = 0;
                power_window_brake();
                
                *power_window_state = POWER_WINDOW_STATE_STOP;
            }
            
            if (auto_counter > 0) auto_counter--;
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_STOP:
        {
            if (!pws_down && !pws_up)
            {
                *power_window_state = POWER_WINDOW_STATE_IDLE;
            }
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_SLEEP:
        {
            if(wake_up)
            {
                power_window_wakeup();
                
                *power_window_state = POWER_WINDOW_STATE_IDLE;
            }
            
            break;
        }
        // .....................................................................
        case POWER_WINDOW_STATE_ERROR:
        {
            power_window_brake();
            
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
