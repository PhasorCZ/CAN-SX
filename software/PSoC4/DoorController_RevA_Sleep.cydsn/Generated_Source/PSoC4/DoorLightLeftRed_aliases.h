/*******************************************************************************
* File Name: DoorLightLeftRed.h  
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

#if !defined(CY_PINS_DoorLightLeftRed_ALIASES_H) /* Pins DoorLightLeftRed_ALIASES_H */
#define CY_PINS_DoorLightLeftRed_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DoorLightLeftRed_0			(DoorLightLeftRed__0__PC)
#define DoorLightLeftRed_0_PS		(DoorLightLeftRed__0__PS)
#define DoorLightLeftRed_0_PC		(DoorLightLeftRed__0__PC)
#define DoorLightLeftRed_0_DR		(DoorLightLeftRed__0__DR)
#define DoorLightLeftRed_0_SHIFT	(DoorLightLeftRed__0__SHIFT)
#define DoorLightLeftRed_0_INTR	((uint16)((uint16)0x0003u << (DoorLightLeftRed__0__SHIFT*2u)))

#define DoorLightLeftRed_INTR_ALL	 ((uint16)(DoorLightLeftRed_0_INTR))


#endif /* End Pins DoorLightLeftRed_ALIASES_H */


/* [] END OF FILE */
