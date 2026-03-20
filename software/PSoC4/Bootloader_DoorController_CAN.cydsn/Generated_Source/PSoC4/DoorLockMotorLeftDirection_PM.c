/*******************************************************************************
* File Name: DoorLockMotorLeftDirection.c  
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
#include "DoorLockMotorLeftDirection.h"

static DoorLockMotorLeftDirection_BACKUP_STRUCT  DoorLockMotorLeftDirection_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DoorLockMotorLeftDirection_Sleep
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
*  \snippet DoorLockMotorLeftDirection_SUT.c usage_DoorLockMotorLeftDirection_Sleep_Wakeup
*******************************************************************************/
void DoorLockMotorLeftDirection_Sleep(void)
{
    #if defined(DoorLockMotorLeftDirection__PC)
        DoorLockMotorLeftDirection_backup.pcState = DoorLockMotorLeftDirection_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DoorLockMotorLeftDirection_backup.usbState = DoorLockMotorLeftDirection_CR1_REG;
            DoorLockMotorLeftDirection_USB_POWER_REG |= DoorLockMotorLeftDirection_USBIO_ENTER_SLEEP;
            DoorLockMotorLeftDirection_CR1_REG &= DoorLockMotorLeftDirection_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DoorLockMotorLeftDirection__SIO)
        DoorLockMotorLeftDirection_backup.sioState = DoorLockMotorLeftDirection_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DoorLockMotorLeftDirection_SIO_REG &= (uint32)(~DoorLockMotorLeftDirection_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DoorLockMotorLeftDirection_Wakeup
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
*  Refer to DoorLockMotorLeftDirection_Sleep() for an example usage.
*******************************************************************************/
void DoorLockMotorLeftDirection_Wakeup(void)
{
    #if defined(DoorLockMotorLeftDirection__PC)
        DoorLockMotorLeftDirection_PC = DoorLockMotorLeftDirection_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DoorLockMotorLeftDirection_USB_POWER_REG &= DoorLockMotorLeftDirection_USBIO_EXIT_SLEEP_PH1;
            DoorLockMotorLeftDirection_CR1_REG = DoorLockMotorLeftDirection_backup.usbState;
            DoorLockMotorLeftDirection_USB_POWER_REG &= DoorLockMotorLeftDirection_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DoorLockMotorLeftDirection__SIO)
        DoorLockMotorLeftDirection_SIO_REG = DoorLockMotorLeftDirection_backup.sioState;
    #endif
}


/* [] END OF FILE */
