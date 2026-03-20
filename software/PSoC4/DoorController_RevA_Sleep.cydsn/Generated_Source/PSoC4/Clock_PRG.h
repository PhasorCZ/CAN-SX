/*******************************************************************************
* File Name: Clock_PRG.h
* Version 2.20
*
*  Description:
*   Provides the function and constant definitions for the clock component.
*
*  Note:
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_CLOCK_Clock_PRG_H)
#define CY_CLOCK_Clock_PRG_H

#include <cytypes.h>
#include <cyfitter.h>


/***************************************
*        Function Prototypes
***************************************/
#if defined CYREG_PERI_DIV_CMD

void Clock_PRG_StartEx(uint32 alignClkDiv);
#define Clock_PRG_Start() \
    Clock_PRG_StartEx(Clock_PRG__PA_DIV_ID)

#else

void Clock_PRG_Start(void);

#endif/* CYREG_PERI_DIV_CMD */

void Clock_PRG_Stop(void);

void Clock_PRG_SetFractionalDividerRegister(uint16 clkDivider, uint8 clkFractional);

uint16 Clock_PRG_GetDividerRegister(void);
uint8  Clock_PRG_GetFractionalDividerRegister(void);

#define Clock_PRG_Enable()                         Clock_PRG_Start()
#define Clock_PRG_Disable()                        Clock_PRG_Stop()
#define Clock_PRG_SetDividerRegister(clkDivider, reset)  \
    Clock_PRG_SetFractionalDividerRegister((clkDivider), 0u)
#define Clock_PRG_SetDivider(clkDivider)           Clock_PRG_SetDividerRegister((clkDivider), 1u)
#define Clock_PRG_SetDividerValue(clkDivider)      Clock_PRG_SetDividerRegister((clkDivider) - 1u, 1u)


/***************************************
*             Registers
***************************************/
#if defined CYREG_PERI_DIV_CMD

#define Clock_PRG_DIV_ID     Clock_PRG__DIV_ID

#define Clock_PRG_CMD_REG    (*(reg32 *)CYREG_PERI_DIV_CMD)
#define Clock_PRG_CTRL_REG   (*(reg32 *)Clock_PRG__CTRL_REGISTER)
#define Clock_PRG_DIV_REG    (*(reg32 *)Clock_PRG__DIV_REGISTER)

#define Clock_PRG_CMD_DIV_SHIFT          (0u)
#define Clock_PRG_CMD_PA_DIV_SHIFT       (8u)
#define Clock_PRG_CMD_DISABLE_SHIFT      (30u)
#define Clock_PRG_CMD_ENABLE_SHIFT       (31u)

#define Clock_PRG_CMD_DISABLE_MASK       ((uint32)((uint32)1u << Clock_PRG_CMD_DISABLE_SHIFT))
#define Clock_PRG_CMD_ENABLE_MASK        ((uint32)((uint32)1u << Clock_PRG_CMD_ENABLE_SHIFT))

#define Clock_PRG_DIV_FRAC_MASK  (0x000000F8u)
#define Clock_PRG_DIV_FRAC_SHIFT (3u)
#define Clock_PRG_DIV_INT_MASK   (0xFFFFFF00u)
#define Clock_PRG_DIV_INT_SHIFT  (8u)

#else 

#define Clock_PRG_DIV_REG        (*(reg32 *)Clock_PRG__REGISTER)
#define Clock_PRG_ENABLE_REG     Clock_PRG_DIV_REG
#define Clock_PRG_DIV_FRAC_MASK  Clock_PRG__FRAC_MASK
#define Clock_PRG_DIV_FRAC_SHIFT (16u)
#define Clock_PRG_DIV_INT_MASK   Clock_PRG__DIVIDER_MASK
#define Clock_PRG_DIV_INT_SHIFT  (0u)

#endif/* CYREG_PERI_DIV_CMD */

#endif /* !defined(CY_CLOCK_Clock_PRG_H) */

/* [] END OF FILE */
