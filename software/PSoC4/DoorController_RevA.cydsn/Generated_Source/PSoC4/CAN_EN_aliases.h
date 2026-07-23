/*******************************************************************************
* File Name: CAN_EN.h  
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

#if !defined(CY_PINS_CAN_EN_ALIASES_H) /* Pins CAN_EN_ALIASES_H */
#define CY_PINS_CAN_EN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define CAN_EN_0			(CAN_EN__0__PC)
#define CAN_EN_0_PS		(CAN_EN__0__PS)
#define CAN_EN_0_PC		(CAN_EN__0__PC)
#define CAN_EN_0_DR		(CAN_EN__0__DR)
#define CAN_EN_0_SHIFT	(CAN_EN__0__SHIFT)
#define CAN_EN_0_INTR	((uint16)((uint16)0x0003u << (CAN_EN__0__SHIFT*2u)))

#define CAN_EN_INTR_ALL	 ((uint16)(CAN_EN_0_INTR))


#endif /* End Pins CAN_EN_ALIASES_H */


/* [] END OF FILE */
