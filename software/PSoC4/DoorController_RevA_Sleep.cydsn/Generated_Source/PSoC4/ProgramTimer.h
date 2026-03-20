/*******************************************************************************
* File Name: ProgramTimer.h
* Version 2.10
*
* Description:
*  This file provides constants and parameter values for the ProgramTimer
*  component.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_TCPWM_ProgramTimer_H)
#define CY_TCPWM_ProgramTimer_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} ProgramTimer_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  ProgramTimer_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define ProgramTimer_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define ProgramTimer_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define ProgramTimer_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define ProgramTimer_QUAD_ENCODING_MODES            (0lu)
#define ProgramTimer_QUAD_AUTO_START                (1lu)

/* Signal modes */
#define ProgramTimer_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define ProgramTimer_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define ProgramTimer_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define ProgramTimer_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define ProgramTimer_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define ProgramTimer_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define ProgramTimer_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define ProgramTimer_TC_RUN_MODE                    (0lu)
#define ProgramTimer_TC_COUNTER_MODE                (0lu)
#define ProgramTimer_TC_COMP_CAP_MODE               (2lu)
#define ProgramTimer_TC_PRESCALER                   (0lu)

/* Signal modes */
#define ProgramTimer_TC_RELOAD_SIGNAL_MODE          (0lu)
#define ProgramTimer_TC_COUNT_SIGNAL_MODE           (3lu)
#define ProgramTimer_TC_START_SIGNAL_MODE           (0lu)
#define ProgramTimer_TC_STOP_SIGNAL_MODE            (0lu)
#define ProgramTimer_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define ProgramTimer_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define ProgramTimer_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define ProgramTimer_TC_START_SIGNAL_PRESENT        (0lu)
#define ProgramTimer_TC_STOP_SIGNAL_PRESENT         (0lu)
#define ProgramTimer_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ProgramTimer_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define ProgramTimer_PWM_KILL_EVENT                 (0lu)
#define ProgramTimer_PWM_STOP_EVENT                 (0lu)
#define ProgramTimer_PWM_MODE                       (4lu)
#define ProgramTimer_PWM_OUT_N_INVERT               (0lu)
#define ProgramTimer_PWM_OUT_INVERT                 (0lu)
#define ProgramTimer_PWM_ALIGN                      (0lu)
#define ProgramTimer_PWM_RUN_MODE                   (0lu)
#define ProgramTimer_PWM_DEAD_TIME_CYCLE            (0lu)
#define ProgramTimer_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define ProgramTimer_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define ProgramTimer_PWM_COUNT_SIGNAL_MODE          (3lu)
#define ProgramTimer_PWM_START_SIGNAL_MODE          (0lu)
#define ProgramTimer_PWM_STOP_SIGNAL_MODE           (0lu)
#define ProgramTimer_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define ProgramTimer_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define ProgramTimer_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define ProgramTimer_PWM_START_SIGNAL_PRESENT       (0lu)
#define ProgramTimer_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define ProgramTimer_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define ProgramTimer_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define ProgramTimer_TC_PERIOD_VALUE                (999lu)
#define ProgramTimer_TC_COMPARE_VALUE               (65535lu)
#define ProgramTimer_TC_COMPARE_BUF_VALUE           (65535lu)
#define ProgramTimer_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define ProgramTimer_PWM_PERIOD_VALUE               (65535lu)
#define ProgramTimer_PWM_PERIOD_BUF_VALUE           (65535lu)
#define ProgramTimer_PWM_PERIOD_SWAP                (0lu)
#define ProgramTimer_PWM_COMPARE_VALUE              (65535lu)
#define ProgramTimer_PWM_COMPARE_BUF_VALUE          (65535lu)
#define ProgramTimer_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define ProgramTimer__LEFT 0
#define ProgramTimer__RIGHT 1
#define ProgramTimer__CENTER 2
#define ProgramTimer__ASYMMETRIC 3

#define ProgramTimer__X1 0
#define ProgramTimer__X2 1
#define ProgramTimer__X4 2

#define ProgramTimer__PWM 4
#define ProgramTimer__PWM_DT 5
#define ProgramTimer__PWM_PR 6

#define ProgramTimer__INVERSE 1
#define ProgramTimer__DIRECT 0

#define ProgramTimer__CAPTURE 2
#define ProgramTimer__COMPARE 0

#define ProgramTimer__TRIG_LEVEL 3
#define ProgramTimer__TRIG_RISING 0
#define ProgramTimer__TRIG_FALLING 1
#define ProgramTimer__TRIG_BOTH 2

#define ProgramTimer__INTR_MASK_TC 1
#define ProgramTimer__INTR_MASK_CC_MATCH 2
#define ProgramTimer__INTR_MASK_NONE 0
#define ProgramTimer__INTR_MASK_TC_CC 3

#define ProgramTimer__UNCONFIG 8
#define ProgramTimer__TIMER 1
#define ProgramTimer__QUAD 3
#define ProgramTimer__PWM_SEL 7

#define ProgramTimer__COUNT_UP 0
#define ProgramTimer__COUNT_DOWN 1
#define ProgramTimer__COUNT_UPDOWN0 2
#define ProgramTimer__COUNT_UPDOWN1 3


/* Prescaler */
#define ProgramTimer_PRESCALE_DIVBY1                ((uint32)(0u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY2                ((uint32)(1u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY4                ((uint32)(2u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY8                ((uint32)(3u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY16               ((uint32)(4u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY32               ((uint32)(5u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY64               ((uint32)(6u << ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_PRESCALE_DIVBY128              ((uint32)(7u << ProgramTimer_PRESCALER_SHIFT))

/* TCPWM set modes */
#define ProgramTimer_MODE_TIMER_COMPARE             ((uint32)(ProgramTimer__COMPARE         <<  \
                                                                  ProgramTimer_MODE_SHIFT))
#define ProgramTimer_MODE_TIMER_CAPTURE             ((uint32)(ProgramTimer__CAPTURE         <<  \
                                                                  ProgramTimer_MODE_SHIFT))
#define ProgramTimer_MODE_QUAD                      ((uint32)(ProgramTimer__QUAD            <<  \
                                                                  ProgramTimer_MODE_SHIFT))
#define ProgramTimer_MODE_PWM                       ((uint32)(ProgramTimer__PWM             <<  \
                                                                  ProgramTimer_MODE_SHIFT))
#define ProgramTimer_MODE_PWM_DT                    ((uint32)(ProgramTimer__PWM_DT          <<  \
                                                                  ProgramTimer_MODE_SHIFT))
#define ProgramTimer_MODE_PWM_PR                    ((uint32)(ProgramTimer__PWM_PR          <<  \
                                                                  ProgramTimer_MODE_SHIFT))

/* Quad Modes */
#define ProgramTimer_MODE_X1                        ((uint32)(ProgramTimer__X1              <<  \
                                                                  ProgramTimer_QUAD_MODE_SHIFT))
#define ProgramTimer_MODE_X2                        ((uint32)(ProgramTimer__X2              <<  \
                                                                  ProgramTimer_QUAD_MODE_SHIFT))
#define ProgramTimer_MODE_X4                        ((uint32)(ProgramTimer__X4              <<  \
                                                                  ProgramTimer_QUAD_MODE_SHIFT))

/* Counter modes */
#define ProgramTimer_COUNT_UP                       ((uint32)(ProgramTimer__COUNT_UP        <<  \
                                                                  ProgramTimer_UPDOWN_SHIFT))
#define ProgramTimer_COUNT_DOWN                     ((uint32)(ProgramTimer__COUNT_DOWN      <<  \
                                                                  ProgramTimer_UPDOWN_SHIFT))
#define ProgramTimer_COUNT_UPDOWN0                  ((uint32)(ProgramTimer__COUNT_UPDOWN0   <<  \
                                                                  ProgramTimer_UPDOWN_SHIFT))
#define ProgramTimer_COUNT_UPDOWN1                  ((uint32)(ProgramTimer__COUNT_UPDOWN1   <<  \
                                                                  ProgramTimer_UPDOWN_SHIFT))

/* PWM output invert */
#define ProgramTimer_INVERT_LINE                    ((uint32)(ProgramTimer__INVERSE         <<  \
                                                                  ProgramTimer_INV_OUT_SHIFT))
#define ProgramTimer_INVERT_LINE_N                  ((uint32)(ProgramTimer__INVERSE         <<  \
                                                                  ProgramTimer_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define ProgramTimer_TRIG_RISING                    ((uint32)ProgramTimer__TRIG_RISING)
#define ProgramTimer_TRIG_FALLING                   ((uint32)ProgramTimer__TRIG_FALLING)
#define ProgramTimer_TRIG_BOTH                      ((uint32)ProgramTimer__TRIG_BOTH)
#define ProgramTimer_TRIG_LEVEL                     ((uint32)ProgramTimer__TRIG_LEVEL)

/* Interrupt mask */
#define ProgramTimer_INTR_MASK_TC                   ((uint32)ProgramTimer__INTR_MASK_TC)
#define ProgramTimer_INTR_MASK_CC_MATCH             ((uint32)ProgramTimer__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define ProgramTimer_CC_MATCH_SET                   (0x00u)
#define ProgramTimer_CC_MATCH_CLEAR                 (0x01u)
#define ProgramTimer_CC_MATCH_INVERT                (0x02u)
#define ProgramTimer_CC_MATCH_NO_CHANGE             (0x03u)
#define ProgramTimer_OVERLOW_SET                    (0x00u)
#define ProgramTimer_OVERLOW_CLEAR                  (0x04u)
#define ProgramTimer_OVERLOW_INVERT                 (0x08u)
#define ProgramTimer_OVERLOW_NO_CHANGE              (0x0Cu)
#define ProgramTimer_UNDERFLOW_SET                  (0x00u)
#define ProgramTimer_UNDERFLOW_CLEAR                (0x10u)
#define ProgramTimer_UNDERFLOW_INVERT               (0x20u)
#define ProgramTimer_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define ProgramTimer_PWM_MODE_LEFT                  (ProgramTimer_CC_MATCH_CLEAR        |   \
                                                         ProgramTimer_OVERLOW_SET           |   \
                                                         ProgramTimer_UNDERFLOW_NO_CHANGE)
#define ProgramTimer_PWM_MODE_RIGHT                 (ProgramTimer_CC_MATCH_SET          |   \
                                                         ProgramTimer_OVERLOW_NO_CHANGE     |   \
                                                         ProgramTimer_UNDERFLOW_CLEAR)
#define ProgramTimer_PWM_MODE_ASYM                  (ProgramTimer_CC_MATCH_INVERT       |   \
                                                         ProgramTimer_OVERLOW_SET           |   \
                                                         ProgramTimer_UNDERFLOW_CLEAR)

#if (ProgramTimer_CY_TCPWM_V2)
    #if(ProgramTimer_CY_TCPWM_4000)
        #define ProgramTimer_PWM_MODE_CENTER                (ProgramTimer_CC_MATCH_INVERT       |   \
                                                                 ProgramTimer_OVERLOW_NO_CHANGE     |   \
                                                                 ProgramTimer_UNDERFLOW_CLEAR)
    #else
        #define ProgramTimer_PWM_MODE_CENTER                (ProgramTimer_CC_MATCH_INVERT       |   \
                                                                 ProgramTimer_OVERLOW_SET           |   \
                                                                 ProgramTimer_UNDERFLOW_CLEAR)
    #endif /* (ProgramTimer_CY_TCPWM_4000) */
#else
    #define ProgramTimer_PWM_MODE_CENTER                (ProgramTimer_CC_MATCH_INVERT       |   \
                                                             ProgramTimer_OVERLOW_NO_CHANGE     |   \
                                                             ProgramTimer_UNDERFLOW_CLEAR)
#endif /* (ProgramTimer_CY_TCPWM_NEW) */

/* Command operations without condition */
#define ProgramTimer_CMD_CAPTURE                    (0u)
#define ProgramTimer_CMD_RELOAD                     (8u)
#define ProgramTimer_CMD_STOP                       (16u)
#define ProgramTimer_CMD_START                      (24u)

/* Status */
#define ProgramTimer_STATUS_DOWN                    (1u)
#define ProgramTimer_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   ProgramTimer_Init(void);
void   ProgramTimer_Enable(void);
void   ProgramTimer_Start(void);
void   ProgramTimer_Stop(void);

void   ProgramTimer_SetMode(uint32 mode);
void   ProgramTimer_SetCounterMode(uint32 counterMode);
void   ProgramTimer_SetPWMMode(uint32 modeMask);
void   ProgramTimer_SetQDMode(uint32 qdMode);

void   ProgramTimer_SetPrescaler(uint32 prescaler);
void   ProgramTimer_TriggerCommand(uint32 mask, uint32 command);
void   ProgramTimer_SetOneShot(uint32 oneShotEnable);
uint32 ProgramTimer_ReadStatus(void);

void   ProgramTimer_SetPWMSyncKill(uint32 syncKillEnable);
void   ProgramTimer_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   ProgramTimer_SetPWMDeadTime(uint32 deadTime);
void   ProgramTimer_SetPWMInvert(uint32 mask);

void   ProgramTimer_SetInterruptMode(uint32 interruptMask);
uint32 ProgramTimer_GetInterruptSourceMasked(void);
uint32 ProgramTimer_GetInterruptSource(void);
void   ProgramTimer_ClearInterrupt(uint32 interruptMask);
void   ProgramTimer_SetInterrupt(uint32 interruptMask);

void   ProgramTimer_WriteCounter(uint32 count);
uint32 ProgramTimer_ReadCounter(void);

uint32 ProgramTimer_ReadCapture(void);
uint32 ProgramTimer_ReadCaptureBuf(void);

void   ProgramTimer_WritePeriod(uint32 period);
uint32 ProgramTimer_ReadPeriod(void);
void   ProgramTimer_WritePeriodBuf(uint32 periodBuf);
uint32 ProgramTimer_ReadPeriodBuf(void);

void   ProgramTimer_WriteCompare(uint32 compare);
uint32 ProgramTimer_ReadCompare(void);
void   ProgramTimer_WriteCompareBuf(uint32 compareBuf);
uint32 ProgramTimer_ReadCompareBuf(void);

void   ProgramTimer_SetPeriodSwap(uint32 swapEnable);
void   ProgramTimer_SetCompareSwap(uint32 swapEnable);

void   ProgramTimer_SetCaptureMode(uint32 triggerMode);
void   ProgramTimer_SetReloadMode(uint32 triggerMode);
void   ProgramTimer_SetStartMode(uint32 triggerMode);
void   ProgramTimer_SetStopMode(uint32 triggerMode);
void   ProgramTimer_SetCountMode(uint32 triggerMode);

void   ProgramTimer_SaveConfig(void);
void   ProgramTimer_RestoreConfig(void);
void   ProgramTimer_Sleep(void);
void   ProgramTimer_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define ProgramTimer_BLOCK_CONTROL_REG              (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ProgramTimer_BLOCK_CONTROL_PTR              ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define ProgramTimer_COMMAND_REG                    (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ProgramTimer_COMMAND_PTR                    ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define ProgramTimer_INTRRUPT_CAUSE_REG             (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ProgramTimer_INTRRUPT_CAUSE_PTR             ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define ProgramTimer_CONTROL_REG                    (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__CTRL )
#define ProgramTimer_CONTROL_PTR                    ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__CTRL )
#define ProgramTimer_STATUS_REG                     (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__STATUS )
#define ProgramTimer_STATUS_PTR                     ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__STATUS )
#define ProgramTimer_COUNTER_REG                    (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__COUNTER )
#define ProgramTimer_COUNTER_PTR                    ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__COUNTER )
#define ProgramTimer_COMP_CAP_REG                   (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__CC )
#define ProgramTimer_COMP_CAP_PTR                   ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__CC )
#define ProgramTimer_COMP_CAP_BUF_REG               (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define ProgramTimer_COMP_CAP_BUF_PTR               ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__CC_BUFF )
#define ProgramTimer_PERIOD_REG                     (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__PERIOD )
#define ProgramTimer_PERIOD_PTR                     ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__PERIOD )
#define ProgramTimer_PERIOD_BUF_REG                 (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ProgramTimer_PERIOD_BUF_PTR                 ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define ProgramTimer_TRIG_CONTROL0_REG              (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ProgramTimer_TRIG_CONTROL0_PTR              ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define ProgramTimer_TRIG_CONTROL1_REG              (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ProgramTimer_TRIG_CONTROL1_PTR              ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define ProgramTimer_TRIG_CONTROL2_REG              (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ProgramTimer_TRIG_CONTROL2_PTR              ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define ProgramTimer_INTERRUPT_REQ_REG              (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR )
#define ProgramTimer_INTERRUPT_REQ_PTR              ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR )
#define ProgramTimer_INTERRUPT_SET_REG              (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define ProgramTimer_INTERRUPT_SET_PTR              ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR_SET )
#define ProgramTimer_INTERRUPT_MASK_REG             (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define ProgramTimer_INTERRUPT_MASK_PTR             ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR_MASK )
#define ProgramTimer_INTERRUPT_MASKED_REG           (*(reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR_MASKED )
#define ProgramTimer_INTERRUPT_MASKED_PTR           ( (reg32 *) ProgramTimer_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define ProgramTimer_MASK                           ((uint32)ProgramTimer_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define ProgramTimer_RELOAD_CC_SHIFT                (0u)
#define ProgramTimer_RELOAD_PERIOD_SHIFT            (1u)
#define ProgramTimer_PWM_SYNC_KILL_SHIFT            (2u)
#define ProgramTimer_PWM_STOP_KILL_SHIFT            (3u)
#define ProgramTimer_PRESCALER_SHIFT                (8u)
#define ProgramTimer_UPDOWN_SHIFT                   (16u)
#define ProgramTimer_ONESHOT_SHIFT                  (18u)
#define ProgramTimer_QUAD_MODE_SHIFT                (20u)
#define ProgramTimer_INV_OUT_SHIFT                  (20u)
#define ProgramTimer_INV_COMPL_OUT_SHIFT            (21u)
#define ProgramTimer_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define ProgramTimer_RELOAD_CC_MASK                 ((uint32)(ProgramTimer_1BIT_MASK        <<  \
                                                                            ProgramTimer_RELOAD_CC_SHIFT))
#define ProgramTimer_RELOAD_PERIOD_MASK             ((uint32)(ProgramTimer_1BIT_MASK        <<  \
                                                                            ProgramTimer_RELOAD_PERIOD_SHIFT))
#define ProgramTimer_PWM_SYNC_KILL_MASK             ((uint32)(ProgramTimer_1BIT_MASK        <<  \
                                                                            ProgramTimer_PWM_SYNC_KILL_SHIFT))
#define ProgramTimer_PWM_STOP_KILL_MASK             ((uint32)(ProgramTimer_1BIT_MASK        <<  \
                                                                            ProgramTimer_PWM_STOP_KILL_SHIFT))
#define ProgramTimer_PRESCALER_MASK                 ((uint32)(ProgramTimer_8BIT_MASK        <<  \
                                                                            ProgramTimer_PRESCALER_SHIFT))
#define ProgramTimer_UPDOWN_MASK                    ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                            ProgramTimer_UPDOWN_SHIFT))
#define ProgramTimer_ONESHOT_MASK                   ((uint32)(ProgramTimer_1BIT_MASK        <<  \
                                                                            ProgramTimer_ONESHOT_SHIFT))
#define ProgramTimer_QUAD_MODE_MASK                 ((uint32)(ProgramTimer_3BIT_MASK        <<  \
                                                                            ProgramTimer_QUAD_MODE_SHIFT))
#define ProgramTimer_INV_OUT_MASK                   ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                            ProgramTimer_INV_OUT_SHIFT))
#define ProgramTimer_MODE_MASK                      ((uint32)(ProgramTimer_3BIT_MASK        <<  \
                                                                            ProgramTimer_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define ProgramTimer_CAPTURE_SHIFT                  (0u)
#define ProgramTimer_COUNT_SHIFT                    (2u)
#define ProgramTimer_RELOAD_SHIFT                   (4u)
#define ProgramTimer_STOP_SHIFT                     (6u)
#define ProgramTimer_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define ProgramTimer_CAPTURE_MASK                   ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                  ProgramTimer_CAPTURE_SHIFT))
#define ProgramTimer_COUNT_MASK                     ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                  ProgramTimer_COUNT_SHIFT))
#define ProgramTimer_RELOAD_MASK                    ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                  ProgramTimer_RELOAD_SHIFT))
#define ProgramTimer_STOP_MASK                      ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                  ProgramTimer_STOP_SHIFT))
#define ProgramTimer_START_MASK                     ((uint32)(ProgramTimer_2BIT_MASK        <<  \
                                                                  ProgramTimer_START_SHIFT))

/* MASK */
#define ProgramTimer_1BIT_MASK                      ((uint32)0x01u)
#define ProgramTimer_2BIT_MASK                      ((uint32)0x03u)
#define ProgramTimer_3BIT_MASK                      ((uint32)0x07u)
#define ProgramTimer_6BIT_MASK                      ((uint32)0x3Fu)
#define ProgramTimer_8BIT_MASK                      ((uint32)0xFFu)
#define ProgramTimer_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define ProgramTimer_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define ProgramTimer_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(ProgramTimer_QUAD_ENCODING_MODES     << ProgramTimer_QUAD_MODE_SHIFT))       |\
         ((uint32)(ProgramTimer_CONFIG                  << ProgramTimer_MODE_SHIFT)))

#define ProgramTimer_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(ProgramTimer_PWM_STOP_EVENT          << ProgramTimer_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(ProgramTimer_PWM_OUT_INVERT          << ProgramTimer_INV_OUT_SHIFT))         |\
         ((uint32)(ProgramTimer_PWM_OUT_N_INVERT        << ProgramTimer_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(ProgramTimer_PWM_MODE                << ProgramTimer_MODE_SHIFT)))

#define ProgramTimer_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(ProgramTimer_PWM_RUN_MODE         << ProgramTimer_ONESHOT_SHIFT))
            
#define ProgramTimer_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(ProgramTimer_PWM_ALIGN            << ProgramTimer_UPDOWN_SHIFT))

#define ProgramTimer_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(ProgramTimer_PWM_KILL_EVENT      << ProgramTimer_PWM_SYNC_KILL_SHIFT))

#define ProgramTimer_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(ProgramTimer_PWM_DEAD_TIME_CYCLE  << ProgramTimer_PRESCALER_SHIFT))

#define ProgramTimer_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(ProgramTimer_PWM_PRESCALER        << ProgramTimer_PRESCALER_SHIFT))

#define ProgramTimer_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(ProgramTimer_TC_PRESCALER            << ProgramTimer_PRESCALER_SHIFT))       |\
         ((uint32)(ProgramTimer_TC_COUNTER_MODE         << ProgramTimer_UPDOWN_SHIFT))          |\
         ((uint32)(ProgramTimer_TC_RUN_MODE             << ProgramTimer_ONESHOT_SHIFT))         |\
         ((uint32)(ProgramTimer_TC_COMP_CAP_MODE        << ProgramTimer_MODE_SHIFT)))
        
#define ProgramTimer_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(ProgramTimer_QUAD_PHIA_SIGNAL_MODE   << ProgramTimer_COUNT_SHIFT))           |\
         ((uint32)(ProgramTimer_QUAD_INDEX_SIGNAL_MODE  << ProgramTimer_RELOAD_SHIFT))          |\
         ((uint32)(ProgramTimer_QUAD_STOP_SIGNAL_MODE   << ProgramTimer_STOP_SHIFT))            |\
         ((uint32)(ProgramTimer_QUAD_PHIB_SIGNAL_MODE   << ProgramTimer_START_SHIFT)))

#define ProgramTimer_PWM_SIGNALS_MODES                                                              \
        (((uint32)(ProgramTimer_PWM_SWITCH_SIGNAL_MODE  << ProgramTimer_CAPTURE_SHIFT))         |\
         ((uint32)(ProgramTimer_PWM_COUNT_SIGNAL_MODE   << ProgramTimer_COUNT_SHIFT))           |\
         ((uint32)(ProgramTimer_PWM_RELOAD_SIGNAL_MODE  << ProgramTimer_RELOAD_SHIFT))          |\
         ((uint32)(ProgramTimer_PWM_STOP_SIGNAL_MODE    << ProgramTimer_STOP_SHIFT))            |\
         ((uint32)(ProgramTimer_PWM_START_SIGNAL_MODE   << ProgramTimer_START_SHIFT)))

#define ProgramTimer_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(ProgramTimer_TC_CAPTURE_SIGNAL_MODE  << ProgramTimer_CAPTURE_SHIFT))         |\
         ((uint32)(ProgramTimer_TC_COUNT_SIGNAL_MODE    << ProgramTimer_COUNT_SHIFT))           |\
         ((uint32)(ProgramTimer_TC_RELOAD_SIGNAL_MODE   << ProgramTimer_RELOAD_SHIFT))          |\
         ((uint32)(ProgramTimer_TC_STOP_SIGNAL_MODE     << ProgramTimer_STOP_SHIFT))            |\
         ((uint32)(ProgramTimer_TC_START_SIGNAL_MODE    << ProgramTimer_START_SHIFT)))
        
#define ProgramTimer_TIMER_UPDOWN_CNT_USED                                                          \
                ((ProgramTimer__COUNT_UPDOWN0 == ProgramTimer_TC_COUNTER_MODE)                  ||\
                 (ProgramTimer__COUNT_UPDOWN1 == ProgramTimer_TC_COUNTER_MODE))

#define ProgramTimer_PWM_UPDOWN_CNT_USED                                                            \
                ((ProgramTimer__CENTER == ProgramTimer_PWM_ALIGN)                               ||\
                 (ProgramTimer__ASYMMETRIC == ProgramTimer_PWM_ALIGN))               
        
#define ProgramTimer_PWM_PR_INIT_VALUE              (1u)
#define ProgramTimer_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_ProgramTimer_H */

/* [] END OF FILE */
