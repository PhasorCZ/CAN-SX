/*******************************************************************************
* File Name: MM_EN.h  
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

#if !defined(CY_PINS_MM_EN_ALIASES_H) /* Pins MM_EN_ALIASES_H */
#define CY_PINS_MM_EN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MM_EN_0			(MM_EN__0__PC)
#define MM_EN_0_PS		(MM_EN__0__PS)
#define MM_EN_0_PC		(MM_EN__0__PC)
#define MM_EN_0_DR		(MM_EN__0__DR)
#define MM_EN_0_SHIFT	(MM_EN__0__SHIFT)
#define MM_EN_0_INTR	((uint16)((uint16)0x0003u << (MM_EN__0__SHIFT*2u)))

#define MM_EN_INTR_ALL	 ((uint16)(MM_EN_0_INTR))


#endif /* End Pins MM_EN_ALIASES_H */


/* [] END OF FILE */
