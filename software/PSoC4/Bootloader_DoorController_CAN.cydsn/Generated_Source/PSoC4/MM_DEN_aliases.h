/*******************************************************************************
* File Name: MM_DEN.h  
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

#if !defined(CY_PINS_MM_DEN_ALIASES_H) /* Pins MM_DEN_ALIASES_H */
#define CY_PINS_MM_DEN_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define MM_DEN_0			(MM_DEN__0__PC)
#define MM_DEN_0_PS		(MM_DEN__0__PS)
#define MM_DEN_0_PC		(MM_DEN__0__PC)
#define MM_DEN_0_DR		(MM_DEN__0__DR)
#define MM_DEN_0_SHIFT	(MM_DEN__0__SHIFT)
#define MM_DEN_0_INTR	((uint16)((uint16)0x0003u << (MM_DEN__0__SHIFT*2u)))

#define MM_DEN_INTR_ALL	 ((uint16)(MM_DEN_0_INTR))


#endif /* End Pins MM_DEN_ALIASES_H */


/* [] END OF FILE */
