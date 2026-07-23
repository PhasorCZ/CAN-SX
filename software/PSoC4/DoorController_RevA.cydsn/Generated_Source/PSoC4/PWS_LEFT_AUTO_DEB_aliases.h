/*******************************************************************************
* File Name: PWS_LEFT_AUTO_DEB.h  
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

#if !defined(CY_PINS_PWS_LEFT_AUTO_DEB_ALIASES_H) /* Pins PWS_LEFT_AUTO_DEB_ALIASES_H */
#define CY_PINS_PWS_LEFT_AUTO_DEB_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define PWS_LEFT_AUTO_DEB_0			(PWS_LEFT_AUTO_DEB__0__PC)
#define PWS_LEFT_AUTO_DEB_0_PS		(PWS_LEFT_AUTO_DEB__0__PS)
#define PWS_LEFT_AUTO_DEB_0_PC		(PWS_LEFT_AUTO_DEB__0__PC)
#define PWS_LEFT_AUTO_DEB_0_DR		(PWS_LEFT_AUTO_DEB__0__DR)
#define PWS_LEFT_AUTO_DEB_0_SHIFT	(PWS_LEFT_AUTO_DEB__0__SHIFT)
#define PWS_LEFT_AUTO_DEB_0_INTR	((uint16)((uint16)0x0003u << (PWS_LEFT_AUTO_DEB__0__SHIFT*2u)))

#define PWS_LEFT_AUTO_DEB_INTR_ALL	 ((uint16)(PWS_LEFT_AUTO_DEB_0_INTR))


#endif /* End Pins PWS_LEFT_AUTO_DEB_ALIASES_H */


/* [] END OF FILE */
