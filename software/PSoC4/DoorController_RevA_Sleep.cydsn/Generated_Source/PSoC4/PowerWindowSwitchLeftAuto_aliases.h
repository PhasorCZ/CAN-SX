/*******************************************************************************
* File Name: PowerWindowSwitchLeftAuto.h  
* Version 2.20
*
* Description:
*  This file contains the Alias definitions for Per-Pin APIs in cypins.h. 
*  Information on using these APIs can be found in the System Reference Guide.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PowerWindowSwitchLeftAuto_ALIASES_H) /* Pins PowerWindowSwitchLeftAuto_ALIASES_H */
#define CY_PINS_PowerWindowSwitchLeftAuto_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PowerWindowSwitchLeftAuto_0			(PowerWindowSwitchLeftAuto__0__PC)
#define PowerWindowSwitchLeftAuto_0_PS		(PowerWindowSwitchLeftAuto__0__PS)
#define PowerWindowSwitchLeftAuto_0_PC		(PowerWindowSwitchLeftAuto__0__PC)
#define PowerWindowSwitchLeftAuto_0_DR		(PowerWindowSwitchLeftAuto__0__DR)
#define PowerWindowSwitchLeftAuto_0_SHIFT	(PowerWindowSwitchLeftAuto__0__SHIFT)
#define PowerWindowSwitchLeftAuto_0_INTR	((uint16)((uint16)0x0003u << (PowerWindowSwitchLeftAuto__0__SHIFT*2u)))

#define PowerWindowSwitchLeftAuto_INTR_ALL	 ((uint16)(PowerWindowSwitchLeftAuto_0_INTR))


#endif /* End Pins PowerWindowSwitchLeftAuto_ALIASES_H */


/* [] END OF FILE */
