/*******************************************************************************
* File Name: HB_3_DEN.h  
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

#if !defined(CY_PINS_HB_3_DEN_ALIASES_H) /* Pins HB_3_DEN_ALIASES_H */
#define CY_PINS_HB_3_DEN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define HB_3_DEN_0			(HB_3_DEN__0__PC)
#define HB_3_DEN_0_PS		(HB_3_DEN__0__PS)
#define HB_3_DEN_0_PC		(HB_3_DEN__0__PC)
#define HB_3_DEN_0_DR		(HB_3_DEN__0__DR)
#define HB_3_DEN_0_SHIFT	(HB_3_DEN__0__SHIFT)
#define HB_3_DEN_0_INTR	((uint16)((uint16)0x0003u << (HB_3_DEN__0__SHIFT*2u)))

#define HB_3_DEN_INTR_ALL	 ((uint16)(HB_3_DEN_0_INTR))


#endif /* End Pins HB_3_DEN_ALIASES_H */


/* [] END OF FILE */
