/*******************************************************************************
* File Name: DOOR_LOCK_SENSOR.c  
* Version 2.20
*
* Description:
*  This file contains APIs to set up the Pins component for low power modes.
*
* Note:
*
********************************************************************************
* Copyright 2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "DOOR_LOCK_SENSOR.h"

static DOOR_LOCK_SENSOR_BACKUP_STRUCT  DOOR_LOCK_SENSOR_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DOOR_LOCK_SENSOR_Sleep
****************************************************************************//**
*
* \brief Stores the pin configuration and prepares the pin for entering chip 
*  deep-sleep/hibernate modes. This function applies only to SIO and USBIO pins.
*  It should not be called for GPIO or GPIO_OVT pins.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None 
*  
* \sideeffect
*  For SIO pins, this function configures the pin input threshold to CMOS and
*  drive level to Vddio. This is needed for SIO pins when in device 
*  deep-sleep/hibernate modes.
*
* \funcusage
*  \snippet DOOR_LOCK_SENSOR_SUT.c usage_DOOR_LOCK_SENSOR_Sleep_Wakeup
*******************************************************************************/
void DOOR_LOCK_SENSOR_Sleep(void)
{
    #if defined(DOOR_LOCK_SENSOR__PC)
        DOOR_LOCK_SENSOR_backup.pcState = DOOR_LOCK_SENSOR_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DOOR_LOCK_SENSOR_backup.usbState = DOOR_LOCK_SENSOR_CR1_REG;
            DOOR_LOCK_SENSOR_USB_POWER_REG |= DOOR_LOCK_SENSOR_USBIO_ENTER_SLEEP;
            DOOR_LOCK_SENSOR_CR1_REG &= DOOR_LOCK_SENSOR_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DOOR_LOCK_SENSOR__SIO)
        DOOR_LOCK_SENSOR_backup.sioState = DOOR_LOCK_SENSOR_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DOOR_LOCK_SENSOR_SIO_REG &= (uint32)(~DOOR_LOCK_SENSOR_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DOOR_LOCK_SENSOR_Wakeup
****************************************************************************//**
*
* \brief Restores the pin configuration that was saved during Pin_Sleep(). This 
* function applies only to SIO and USBIO pins. It should not be called for
* GPIO or GPIO_OVT pins.
*
* For USBIO pins, the wakeup is only triggered for falling edge interrupts.
*
* <b>Note</b> This function is available in PSoC 4 only.
*
* \return 
*  None
*  
* \funcusage
*  Refer to DOOR_LOCK_SENSOR_Sleep() for an example usage.
*******************************************************************************/
void DOOR_LOCK_SENSOR_Wakeup(void)
{
    #if defined(DOOR_LOCK_SENSOR__PC)
        DOOR_LOCK_SENSOR_PC = DOOR_LOCK_SENSOR_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DOOR_LOCK_SENSOR_USB_POWER_REG &= DOOR_LOCK_SENSOR_USBIO_EXIT_SLEEP_PH1;
            DOOR_LOCK_SENSOR_CR1_REG = DOOR_LOCK_SENSOR_backup.usbState;
            DOOR_LOCK_SENSOR_USB_POWER_REG &= DOOR_LOCK_SENSOR_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DOOR_LOCK_SENSOR__SIO)
        DOOR_LOCK_SENSOR_SIO_REG = DOOR_LOCK_SENSOR_backup.sioState;
    #endif
}


/* [] END OF FILE */
