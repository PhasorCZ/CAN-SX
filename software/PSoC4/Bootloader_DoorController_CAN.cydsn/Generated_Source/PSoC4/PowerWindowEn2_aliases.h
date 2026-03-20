/*******************************************************************************
* File Name: PowerWindowEn2.h  
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

#if !defined(CY_PINS_PowerWindowEn2_ALIASES_H) /* Pins PowerWindowEn2_ALIASES_H */
#define CY_PINS_PowerWindowEn2_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PowerWindowEn2_0			(PowerWindowEn2__0__PC)
#define PowerWindowEn2_0_PS		(PowerWindowEn2__0__PS)
#define PowerWindowEn2_0_PC		(PowerWindowEn2__0__PC)
#define PowerWindowEn2_0_DR		(PowerWindowEn2__0__DR)
#define PowerWindowEn2_0_SHIFT	(PowerWindowEn2__0__SHIFT)
#define PowerWindowEn2_0_INTR	((uint16)((uint16)0x0003u << (PowerWindowEn2__0__SHIFT*2u)))

#define PowerWindowEn2_INTR_ALL	 ((uint16)(PowerWindowEn2_0_INTR))


#endif /* End Pins PowerWindowEn2_ALIASES_H */


/* [] END OF FILE */
