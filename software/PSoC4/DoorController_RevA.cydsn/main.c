/*******************************************************************************
* \file         bootloader_can.c
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

#include <stdlib.h>
    
#include "project.h"
#include "cyapicallbacks.h"
    
#include "main.h"
    
#include "can_handler.h"
#include "spi_handler.h"
#include "digital_io.h"
#include "analog_io.h"

// -----------------------------------------------------------------------------

//static uint32 get_time_ms(void);

// -----------------------------------------------------------------------------

CanRxQueue can_rx_queue;
U8Bits digital_in_debounced;

// -----------------------------------------------------------------------------
volatile uint8 dls_unlocking = 0;
volatile uint8 dls_locking = 0;

volatile uint16 program_counter = 0;
volatile uint16 can_counter = 0;
volatile uint16 led_counter = 0;
volatile uint16 adc_counter = 0;

#define PROGRAM_COUNT 10
#define CAN_COUNT 100
#define LED_COUNT 500
#define ADC_COUNT 1000

#define SLEEP_COUNT 1000

// -----------------------------------------------------------------------------
uint8 spi_rx_buff_size = 0;

uint8 sleep_request = 0;
uint8 wake_up_enabled = 0;

/* SDO/SEL;INA;INB;PWM;SEL;SEN_EN;SR;WD_EN */
uint8 BTM9021EP_1_data[1] = {0b00011000};
uint8 BTM9021EP_2_data[1] = {0b00011000};
uint8 BTM9021EP_3_data[1] = {0b00011100};

/* SDO/SEL=0;INA;INB;PWM;SEL;SEN_EN;SR;WD_EN */
/* SDO/SEL=1;OCA;OCB;OL;UV;TSDA;TSDB;WD_EN */
uint8 BTM9021EP_1_responce[1] = {0b00000000};
uint8 BTM9021EP_2_responce[1] = {0b00000000};
uint8 BTM9021EP_3_responce[1] = {0b00000000};

/* ADC results */
int16 is_down_ticks;
int16 is_up_ticks;
int16 is_spi_ticks;
int16 is_hb_ticks;
int16 ai_5_ticks;
int16 ai_6_ticks;
int16 die_temp_ticks;
int32 die_temp_degc;

// -----------------------------------------------------------------------------
/*
static uint32 get_time_ms(void)
{
    return ((CySysTickGetReload() - CySysTickGetValue()) * 1000u) / CYDEV_BCLK__SYSCLK__HZ;
}
*/
// -----------------------------------------------------------------------------

CY_ISR(isr_prg)
{
    program_counter++;
    
    can_counter++;
    led_counter++;
    adc_counter++;
    
    ISR_PRG_ClearPending();
    ProgramTimer_ClearInterrupt(ProgramTimer_TC_INTERRUPT_MASK);
}

// -----------------------------------------------------------------------------

CY_ISR(isr_dls)
{
    if (DOOR_LOCK_SENSOR_INTSTAT & (0x01u << DOOR_LOCK_SENSOR_SHIFT))
    {
        dls_unlocking = 1;
    }
    else
    {
        dls_locking = 1;
    }
    
    wake_up_enabled = 1;
    
    ISR_DLS_ClearPending();
    DOOR_LOCK_SENSOR_ClearInterrupt();
}

CY_ISR(isr_can_err)
{
    wake_up_enabled = 1;
    
    ISR_CAN_ERR_ClearPending();
    CAN_ERR_ClearInterrupt();
}

// -----------------------------------------------------------------------------

int main(void)
{
    static MainState            main_state          = MAIN_STATE_INIT;
    static DoorLockState        door_lock_state     = DOOR_LOCK_STATE_INIT;
    static PowerWindowState     power_window_state  = POWER_WINDOW_STATE_INIT;
    
    uint16 sleep_counter = 0;
    
    uint8 sleep = 0;
    uint8 wake_up = 0;
    
    /* Enable Interrupts */
    CyGlobalIntEnable;
    
    CAN_TX_DATA_LO_REG(0) = (uint16)(0xf0f0f0f0);
    CAN_TX_DATA_HI_REG(0) = (uint16)(0x00000000);
    CAN_SendMsg0();
    
    /* Start program timer */
    ISR_PRG_StartEx(isr_prg);
    ProgramTimer_Start();
    
    CAN_TX_DATA_LO_REG(0) = (uint16)(0x0f0f0f0f);
    CAN_TX_DATA_HI_REG(0) = (uint16)(0x00000000);
    CAN_SendMsg0();
    
// =============================================================================
    
    /* Main function */
    for(;;)
    {
        /* MAIN PROGRAM */
        if (program_counter >= PROGRAM_COUNT)
        {
            if (adc_counter >= ADC_COUNT)
            {
                adc_counter = 0;
                //ADC_SAR_Seq_EnableInjection();
                
                is_down_ticks = ADC_SAR_Seq_GetResult16(0);
                is_up_ticks = ADC_SAR_Seq_GetResult16(1);
                is_spi_ticks = ADC_SAR_Seq_GetResult16(2);
                is_hb_ticks = ADC_SAR_Seq_GetResult16(3);
                ai_5_ticks = ADC_SAR_Seq_GetResult16(4);
                ai_6_ticks = ADC_SAR_Seq_GetResult16(5);
                die_temp_ticks = ADC_SAR_Seq_GetResult16(6);
                die_temp_degc = DieTemp_CountsTo_Celsius(die_temp_ticks);
            }
            
// -----------------------------------------------------------------------------     
            
            can_rx_process_msg (&can_rx_queue);
            
            if (sleep_counter >= SLEEP_COUNT)
            {
                sleep_request = 1;
            }
            
// -----------------------------------------------------------------------------
            
            main_statemachine( &main_state,
                                power_window_state,
                                door_lock_state,
                               &sleep,
                               &wake_up);
            
            /* Door lock */
            door_lock_statemachine(&door_lock_state,
                                    BTM9021EP_3_data,
                                   &dls_unlocking,
                                   &dls_locking,
                                    sleep,
                                    wake_up);
            
            /* Power window */
            power_window_statemachine( &power_window_state,
                                        digital_in_debounced.bits.pws_left_down_deb,
                                        digital_in_debounced.bits.pws_left_up_deb,
                                        digital_in_debounced.bits.pws_left_auto_deb,
                                        sleep,
                                        wake_up);
            
// -----------------------------------------------------------------------------
            
            if (door_lock_state == DOOR_LOCK_STATE_LOCKED)
            {
                sleep_counter++;
            }
            else
            {
                sleep_counter = 0;
            }
            
// -----------------------------------------------------------------------------
            
            send_spi_data(  BTM9021EP_1_data,
                            BTM9021EP_2_data,
                            BTM9021EP_3_data,
                            BTM9021EP_1_responce,
                            BTM9021EP_2_responce,
                            BTM9021EP_3_responce);
            
// -----------------------------------------------------------------------------     
            
            CAN_TX_DATA_LO_REG(0) = 0xffff0000 |
                                    program_counter;
            CAN_TX_DATA_HI_REG(0) = can_counter << 16 |
                                    led_counter;
            CAN_SendMsg0();
            
            program_counter = 0;
            
            CAN_TX_DATA_LO_REG(1) = 0xff000000 |
                                    main_state << 16 |
                                    power_window_state << 8 |
                                    door_lock_state << 0;
            CAN_TX_DATA_HI_REG(1) = digital_in_debounced.bits.pws_left_down_deb         << 28 |
                                    digital_in_debounced.bits.pws_left_up_deb           << 24 |
                                    digital_in_debounced.bits.pws_left_auto_deb         << 20 |
                                    digital_in_debounced.bits.pws_right_down_deb        << 16 |
                                    digital_in_debounced.bits.pws_right_up_deb          << 12 |
                                    digital_in_debounced.bits.pws_right_lock_down_deb   << 8 |
                                    digital_in_debounced.bits.pws_right_lock_up_deb     << 4 |
                                    digital_in_debounced.bits.di_deb;
            CAN_SendMsg1();
            
            if ((can_counter >= CAN_COUNT))
            {
                can_counter = 0;
                
                CAN_TX_DATA_LO_REG(2) = (uint16)(is_down_ticks);
                CAN_TX_DATA_HI_REG(2) = (uint16)(is_up_ticks);
                CAN_SendMsg2();
                
                CAN_TX_DATA_LO_REG(3) = (uint16)(is_spi_ticks);
                CAN_TX_DATA_HI_REG(3) = (uint16)(is_hb_ticks);
                CAN_SendMsg3();
                
                CAN_TX_DATA_LO_REG(4) = ai_5_ticks;
                CAN_TX_DATA_HI_REG(4) = ai_6_ticks;
                CAN_SendMsg4();
                
                CAN_TX_DATA_LO_REG(5) = *BTM9021EP_1_responce;
                CAN_TX_DATA_HI_REG(5) = *BTM9021EP_2_responce;
                CAN_SendMsg5();
                
                CAN_TX_DATA_LO_REG(6) = *BTM9021EP_3_responce;
                CAN_TX_DATA_HI_REG(6) = die_temp_degc;
                CAN_SendMsg6();
            }
        }
        
// =============================================================================
        
        CyDelayUs(100);
    }
}

// -----------------------------------------------------------------------------

void main_statemachine( MainState          *main_state,
                        PowerWindowState    power_window_state,
                        DoorLockState       door_lock_state,
                        uint8              *sleep,
                        uint8              *wake_up)
{
    switch (*main_state)
    {
        case MAIN_STATE_INIT:
        {
            activate_hardware();
            *main_state = MAIN_STATE_ACTIVE;
            break;
        }
        case MAIN_STATE_STANDBY:
        {
            break;
        }
        case MAIN_STATE_ACTIVE:
        {
            read_digital_inputs (&digital_in_debounced);
            
            if (sleep_request)
            {
                sleep_request = 0;
                *sleep = 1;
                
                *main_state = MAIN_STATE_POWER_DOWN;
            }
            
            if (led_counter >= LED_COUNT)
            {
                led_counter = 0;
                
                if (LED_Read() == 0)
                {
                    LED_Write(1);
                }
                else
                {
                    LED_Write(0);
                }
            }
            
            break;
        }
        case MAIN_STATE_POWER_DOWN:
        {
            if ((door_lock_state    == DOOR_LOCK_STATE_SLEEP) &
                (power_window_state == POWER_WINDOW_STATE_SLEEP))
            {
                *sleep = 0;
                
                *main_state = MAIN_STATE_SLEEP;
            }
            
            LED_Write(0);
            
            break;
        }
        case MAIN_STATE_SLEEP:
        {
            sleep_hardware();
            
            CyDelay(1000);
            
            wake_up_enabled = 0;
            
            while (!wake_up_enabled)
            {
                //CySysPmSleep();
                CySysPmDeepSleep();
            }
            
            wakeup_hardware();

            *wake_up = 1;
            
            *main_state = MAIN_STATE_WAKE_UP;
            
            break;
        }
        case MAIN_STATE_WAKE_UP:
        {
            if ((door_lock_state    != DOOR_LOCK_STATE_SLEEP) &
                (power_window_state != POWER_WINDOW_STATE_SLEEP))
            {
                *wake_up = 0;
                
                *main_state = MAIN_STATE_ACTIVE;
            }
            
            LED_Write(1);
            
            break;
        }
        case MAIN_STATE_ERROR:
        {
            break;
        }
    }
}

// -----------------------------------------------------------------------------

void activate_hardware()
{
    /* Init CAN RX queue*/
    can_rx_queue.head = 0;
    can_rx_queue.tail = 0;
    can_rx_queue.overflow_count = 0;
    
    //const float K_IS_BTN9990LV = K_ILIS_BTN9990LV / R_SENSE_BTN9990LV;
    //const float K_IS_BTN70301EPA = K_ILIS_BTN70301EPA / R_SENSE_BTN70301EPA;
    //const float K_IS_BTM9021EP_HI = K_ILIS_BTM9021EP_HI / R_SENSE_BTM9021EP;
    //const float K_IS_BTM9021EP_LO = K_ILIS_BTM9021EP_LO / R_SENSE_BTM9021EP;
    
    /* Interrupt handlers */
    DOOR_LOCK_SENSOR_ClearInterrupt();
    ISR_DLS_StartEx(isr_dls);
    
    /* Start RTC */
    RTC_Start();
    
    /* Enable CAN driver and start CAN component */
    CAN_STB_Write(1);
    CAN_EN_Write(1);
    CyDelayUs(100);
    CAN_Start();
    
    /* Start ADC */
    Opamp_1_Start();
    Opamp_2_Start();
    CyDelayUs(100);
    ADC_SAR_Seq_Start();
    CyDelayUs(100);
    ADC_SAR_Seq_StartConvert();
    
    /* Enable inputs */
    COMPARATOR_REFFERENCE_ENABLE();
    COMPARATOR_AND_DEBOUNCER_ENABLE();
    VARIABLE_RESISTOR_VCC_ENABLE();
    POWER_WINDOW_SWITCH_VCC_ENABLE();
    
    /* Start SPI */
    SCB_Start();
    
    /* Start smart IO */
    //SmartIO_Start();
}

// -----------------------------------------------------------------------------

void sleep_hardware()
{
    /* Interrupt handlers */
    DOOR_LOCK_SENSOR_ClearInterrupt();
    //ISR_DLS_Stop();
    
    /* Disable CAN driver and start CAN component */
    CAN_STB_Write(0);
    CyDelayUs(100);
    CAN_Sleep();
    
    /* Start ADC */
    ADC_SAR_Seq_Sleep();
    Opamp_1_Sleep();
    Opamp_2_Sleep();
    
    /* Enable inputs */
    COMPARATOR_REFFERENCE_DISABLE();
    COMPARATOR_AND_DEBOUNCER_DISABLE();
    VARIABLE_RESISTOR_VCC_DISABLE();
    POWER_WINDOW_SWITCH_VCC_DISABLE();
    
    /* Stop SPI */
    SCB_Sleep();
    
    /* Wake-up interrupt */
    ISR_CAN_ERR_ClearPending();
    ISR_CAN_ERR_StartEx(isr_can_err);
    CAN_ERR_ClearInterrupt();
    
    /* Stop program counter */
    ISR_PRG_Stop();
    ProgramTimer_Sleep();
}

// -----------------------------------------------------------------------------

void wakeup_hardware()
{
    /* Interrupt handlers */
    DOOR_LOCK_SENSOR_ClearInterrupt();
    //ISR_DLS_StartEx(isr_dls);
    
    /* Disable CAN driver and start CAN component */
    CAN_STB_Write(1);
    CyDelayUs(100);
    CAN_Wakeup();
    
    /* Start ADC */
    Opamp_1_Wakeup();
    Opamp_2_Wakeup();
    CyDelayUs(100);
    ADC_SAR_Seq_Wakeup();
    CyDelayUs(100);
    ADC_SAR_Seq_StartConvert();
    
    /* Enable inputs */
    COMPARATOR_REFFERENCE_ENABLE();
    COMPARATOR_AND_DEBOUNCER_ENABLE();
    VARIABLE_RESISTOR_VCC_ENABLE();
    POWER_WINDOW_SWITCH_VCC_ENABLE();
    
    /* Stop SPI */
    SCB_Wakeup();
    
    /* Wake-up interrupt */
    ISR_CAN_ERR_Stop();
    
    /* Start program timer */
    ISR_CAN_ERR_ClearPending();
    ISR_PRG_StartEx(isr_prg);
    ProgramTimer_Start();
}

// -----------------------------------------------------------------------------

void deactivate_hardware()
{
    /* Interrupt handlers */
    ISR_DLS_Stop();
    
    /* Schedule bootloadable to run after reset */
    Bootloadable_SET_RUN_TYPE(0x00);
    
    /* Disable CAN driver and start CAN component */
    CAN_STB_Write(1);
    CAN_EN_Write(0);
    CyDelay(1);
    CAN_Stop();
    
    /* Stop ADC */
    ADC_SAR_Seq_Stop();
    Opamp_1_Stop();
    Opamp_2_Stop();
    CyDelayUs(100);
    
    /* Disable inputs */
    COMPARATOR_REFFERENCE_DISABLE();
    COMPARATOR_AND_DEBOUNCER_DISABLE();
    VARIABLE_RESISTOR_VCC_DISABLE();
    POWER_WINDOW_SWITCH_VCC_DISABLE();
    
    /* Stop SPI */
    SCB_Stop();
    
    /* Start smart IO */
    //SmartIO_Stop();
}

// -----------------------------------------------------------------------------
/* [] END OF FILE */
