/*******************************************************************************
* File Name: PowerWindowSwitchLeftDown.h  
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

#if !defined(CY_PINS_PowerWindowSwitchLeftDown_ALIASES_H) /* Pins PowerWindowSwitchLeftDown_ALIASES_H */
#define CY_PINS_PowerWindowSwitchLeftDown_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PowerWindowSwitchLeftDown_0			(PowerWindowSwitchLeftDown__0__PC)
#define PowerWindowSwitchLeftDown_0_PS		(PowerWindowSwitchLeftDown__0__PS)
#define PowerWindowSwitchLeftDown_0_PC		(PowerWindowSwitchLeftDown__0__PC)
#define PowerWindowSwitchLeftDown_0_DR		(PowerWindowSwitchLeftDown__0__DR)
#define PowerWindowSwitchLeftDown_0_SHIFT	(PowerWindowSwitchLeftDown__0__SHIFT)
#define PowerWindowSwitchLeftDown_0_INTR	((uint16)((uint16)0x0003u << (PowerWindowSwitchLeftDown__0__SHIFT*2u)))

#define PowerWindowSwitchLeftDown_INTR_ALL	 ((uint16)(PowerWindowSwitchLeftDown_0_INTR))


#endif /* End Pins PowerWindowSwitchLeftDown_ALIASES_H */


/* [] END OF FILE */
