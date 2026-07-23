/*******************************************************************************
* File Name: AnalogIn3.h  
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

#if !defined(CY_PINS_AnalogIn3_ALIASES_H) /* Pins AnalogIn3_ALIASES_H */
#define CY_PINS_AnalogIn3_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AnalogIn3_0			(AnalogIn3__0__PC)
#define AnalogIn3_0_PS		(AnalogIn3__0__PS)
#define AnalogIn3_0_PC		(AnalogIn3__0__PC)
#define AnalogIn3_0_DR		(AnalogIn3__0__DR)
#define AnalogIn3_0_SHIFT	(AnalogIn3__0__SHIFT)
#define AnalogIn3_0_INTR	((uint16)((uint16)0x0003u << (AnalogIn3__0__SHIFT*2u)))

#define AnalogIn3_INTR_ALL	 ((uint16)(AnalogIn3_0_INTR))


#endif /* End Pins AnalogIn3_ALIASES_H */


/* [] END OF FILE */
