/*******************************************************************************
* File Name: DLS_UNLOCKING.h  
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

#if !defined(CY_PINS_DLS_UNLOCKING_ALIASES_H) /* Pins DLS_UNLOCKING_ALIASES_H */
#define CY_PINS_DLS_UNLOCKING_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DLS_UNLOCKING_0			(DLS_UNLOCKING__0__PC)
#define DLS_UNLOCKING_0_PS		(DLS_UNLOCKING__0__PS)
#define DLS_UNLOCKING_0_PC		(DLS_UNLOCKING__0__PC)
#define DLS_UNLOCKING_0_DR		(DLS_UNLOCKING__0__DR)
#define DLS_UNLOCKING_0_SHIFT	(DLS_UNLOCKING__0__SHIFT)
#define DLS_UNLOCKING_0_INTR	((uint16)((uint16)0x0003u << (DLS_UNLOCKING__0__SHIFT*2u)))

#define DLS_UNLOCKING_INTR_ALL	 ((uint16)(DLS_UNLOCKING_0_INTR))


#endif /* End Pins DLS_UNLOCKING_ALIASES_H */


/* [] END OF FILE */
