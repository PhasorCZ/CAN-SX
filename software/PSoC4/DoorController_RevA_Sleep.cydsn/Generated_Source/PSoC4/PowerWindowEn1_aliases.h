/*******************************************************************************
* File Name: PowerWindowEn1.h  
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

#if !defined(CY_PINS_PowerWindowEn1_ALIASES_H) /* Pins PowerWindowEn1_ALIASES_H */
#define CY_PINS_PowerWindowEn1_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PowerWindowEn1_0			(PowerWindowEn1__0__PC)
#define PowerWindowEn1_0_PS		(PowerWindowEn1__0__PS)
#define PowerWindowEn1_0_PC		(PowerWindowEn1__0__PC)
#define PowerWindowEn1_0_DR		(PowerWindowEn1__0__DR)
#define PowerWindowEn1_0_SHIFT	(PowerWindowEn1__0__SHIFT)
#define PowerWindowEn1_0_INTR	((uint16)((uint16)0x0003u << (PowerWindowEn1__0__SHIFT*2u)))

#define PowerWindowEn1_INTR_ALL	 ((uint16)(PowerWindowEn1_0_INTR))


#endif /* End Pins PowerWindowEn1_ALIASES_H */


/* [] END OF FILE */
