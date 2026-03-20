/*******************************************************************************
* File Name: DOOR_LOCK_SENSOR.h  
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

#if !defined(CY_PINS_DOOR_LOCK_SENSOR_ALIASES_H) /* Pins DOOR_LOCK_SENSOR_ALIASES_H */
#define CY_PINS_DOOR_LOCK_SENSOR_ALIASES_H

#include "cytypes.h"
#include "cyfitter.h"
#include "cypins.h"


/***************************************
*              Constants        
***************************************/
#define DOOR_LOCK_SENSOR_0			(DOOR_LOCK_SENSOR__0__PC)
#define DOOR_LOCK_SENSOR_0_PS		(DOOR_LOCK_SENSOR__0__PS)
#define DOOR_LOCK_SENSOR_0_PC		(DOOR_LOCK_SENSOR__0__PC)
#define DOOR_LOCK_SENSOR_0_DR		(DOOR_LOCK_SENSOR__0__DR)
#define DOOR_LOCK_SENSOR_0_SHIFT	(DOOR_LOCK_SENSOR__0__SHIFT)
#define DOOR_LOCK_SENSOR_0_INTR	((uint16)((uint16)0x0003u << (DOOR_LOCK_SENSOR__0__SHIFT*2u)))

#define DOOR_LOCK_SENSOR_INTR_ALL	 ((uint16)(DOOR_LOCK_SENSOR_0_INTR))
#define DOOR_LOCK_SENSOR_UNLOCKING			(DOOR_LOCK_SENSOR__UNLOCKING__PC)
#define DOOR_LOCK_SENSOR_UNLOCKING_PS		(DOOR_LOCK_SENSOR__UNLOCKING__PS)
#define DOOR_LOCK_SENSOR_UNLOCKING_PC		(DOOR_LOCK_SENSOR__UNLOCKING__PC)
#define DOOR_LOCK_SENSOR_UNLOCKING_DR		(DOOR_LOCK_SENSOR__UNLOCKING__DR)
#define DOOR_LOCK_SENSOR_UNLOCKING_SHIFT	(DOOR_LOCK_SENSOR__UNLOCKING__SHIFT)
#define DOOR_LOCK_SENSOR_UNLOCKING_INTR	((uint16)((uint16)0x0003u << (DOOR_LOCK_SENSOR__0__SHIFT*2u)))


#endif /* End Pins DOOR_LOCK_SENSOR_ALIASES_H */


/* [] END OF FILE */
