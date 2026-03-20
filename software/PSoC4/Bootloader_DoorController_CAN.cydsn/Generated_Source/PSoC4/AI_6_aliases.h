/*******************************************************************************
* File Name: AI_6.h  
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

#if !defined(CY_PINS_AI_6_ALIASES_H) /* Pins AI_6_ALIASES_H */
#define CY_PINS_AI_6_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define AI_6_0			(AI_6__0__PC)
#define AI_6_0_PS		(AI_6__0__PS)
#define AI_6_0_PC		(AI_6__0__PC)
#define AI_6_0_DR		(AI_6__0__DR)
#define AI_6_0_SHIFT	(AI_6__0__SHIFT)
#define AI_6_0_INTR	((uint16)((uint16)0x0003u << (AI_6__0__SHIFT*2u)))

#define AI_6_INTR_ALL	 ((uint16)(AI_6_0_INTR))


#endif /* End Pins AI_6_ALIASES_H */


/* [] END OF FILE */
