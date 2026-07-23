/*******************************************************************************
* File Name: AnalogIn5.h  
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

#if !defined(CY_PINS_AnalogIn5_ALIASES_H) /* Pins AnalogIn5_ALIASES_H */
#define CY_PINS_AnalogIn5_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AnalogIn5_0			(AnalogIn5__0__PC)
#define AnalogIn5_0_PS		(AnalogIn5__0__PS)
#define AnalogIn5_0_PC		(AnalogIn5__0__PC)
#define AnalogIn5_0_DR		(AnalogIn5__0__DR)
#define AnalogIn5_0_SHIFT	(AnalogIn5__0__SHIFT)
#define AnalogIn5_0_INTR	((uint16)((uint16)0x0003u << (AnalogIn5__0__SHIFT*2u)))

#define AnalogIn5_INTR_ALL	 ((uint16)(AnalogIn5_0_INTR))


#endif /* End Pins AnalogIn5_ALIASES_H */


/* [] END OF FILE */
