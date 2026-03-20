/*******************************************************************************
* File Name: DI7.h  
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

#if !defined(CY_PINS_DI7_ALIASES_H) /* Pins DI7_ALIASES_H */
#define CY_PINS_DI7_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DI7_0			(DI7__0__PC)
#define DI7_0_PS		(DI7__0__PS)
#define DI7_0_PC		(DI7__0__PC)
#define DI7_0_DR		(DI7__0__DR)
#define DI7_0_SHIFT	(DI7__0__SHIFT)
#define DI7_0_INTR	((uint16)((uint16)0x0003u << (DI7__0__SHIFT*2u)))

#define DI7_INTR_ALL	 ((uint16)(DI7_0_INTR))


#endif /* End Pins DI7_ALIASES_H */


/* [] END OF FILE */
