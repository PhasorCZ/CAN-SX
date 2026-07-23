/*******************************************************************************
* File Name: AnalogIn4.h  
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

#if !defined(CY_PINS_AnalogIn4_ALIASES_H) /* Pins AnalogIn4_ALIASES_H */
#define CY_PINS_AnalogIn4_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AnalogIn4_0			(AnalogIn4__0__PC)
#define AnalogIn4_0_PS		(AnalogIn4__0__PS)
#define AnalogIn4_0_PC		(AnalogIn4__0__PC)
#define AnalogIn4_0_DR		(AnalogIn4__0__DR)
#define AnalogIn4_0_SHIFT	(AnalogIn4__0__SHIFT)
#define AnalogIn4_0_INTR	((uint16)((uint16)0x0003u << (AnalogIn4__0__SHIFT*2u)))

#define AnalogIn4_INTR_ALL	 ((uint16)(AnalogIn4_0_INTR))


#endif /* End Pins AnalogIn4_ALIASES_H */


/* [] END OF FILE */
