/*******************************************************************************
* File Name: HB_1_IN.h  
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

#if !defined(CY_PINS_HB_1_IN_ALIASES_H) /* Pins HB_1_IN_ALIASES_H */
#define CY_PINS_HB_1_IN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HB_1_IN_0			(HB_1_IN__0__PC)
#define HB_1_IN_0_PS		(HB_1_IN__0__PS)
#define HB_1_IN_0_PC		(HB_1_IN__0__PC)
#define HB_1_IN_0_DR		(HB_1_IN__0__DR)
#define HB_1_IN_0_SHIFT	(HB_1_IN__0__SHIFT)
#define HB_1_IN_0_INTR	((uint16)((uint16)0x0003u << (HB_1_IN__0__SHIFT*2u)))

#define HB_1_IN_INTR_ALL	 ((uint16)(HB_1_IN_0_INTR))


#endif /* End Pins HB_1_IN_ALIASES_H */


/* [] END OF FILE */
