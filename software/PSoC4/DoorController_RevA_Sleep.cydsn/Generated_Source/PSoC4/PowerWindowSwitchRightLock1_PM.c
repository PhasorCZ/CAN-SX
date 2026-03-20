/*******************************************************************************
* File Name: PowerWindowSwitchRightLock1.c  
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
#include "PowerWindowSwitchRightLock1.h"

static PowerWindowSwitchRightLock1_BACKUP_STRUCT  PowerWindowSwitchRightLock1_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PowerWindowSwitchRightLock1_Sleep
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
*  \snippet PowerWindowSwitchRightLock1_SUT.c usage_PowerWindowSwitchRightLock1_Sleep_Wakeup
*******************************************************************************/
void PowerWindowSwitchRightLock1_Sleep(void)
{
    #if defined(PowerWindowSwitchRightLock1__PC)
        PowerWindowSwitchRightLock1_backup.pcState = PowerWindowSwitchRightLock1_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PowerWindowSwitchRightLock1_backup.usbState = PowerWindowSwitchRightLock1_CR1_REG;
            PowerWindowSwitchRightLock1_USB_POWER_REG |= PowerWindowSwitchRightLock1_USBIO_ENTER_SLEEP;
            PowerWindowSwitchRightLock1_CR1_REG &= PowerWindowSwitchRightLock1_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PowerWindowSwitchRightLock1__SIO)
        PowerWindowSwitchRightLock1_backup.sioState = PowerWindowSwitchRightLock1_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PowerWindowSwitchRightLock1_SIO_REG &= (uint32)(~PowerWindowSwitchRightLock1_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PowerWindowSwitchRightLock1_Wakeup
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
*  Refer to PowerWindowSwitchRightLock1_Sleep() for an example usage.
*******************************************************************************/
void PowerWindowSwitchRightLock1_Wakeup(void)
{
    #if defined(PowerWindowSwitchRightLock1__PC)
        PowerWindowSwitchRightLock1_PC = PowerWindowSwitchRightLock1_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PowerWindowSwitchRightLock1_USB_POWER_REG &= PowerWindowSwitchRightLock1_USBIO_EXIT_SLEEP_PH1;
            PowerWindowSwitchRightLock1_CR1_REG = PowerWindowSwitchRightLock1_backup.usbState;
            PowerWindowSwitchRightLock1_USB_POWER_REG &= PowerWindowSwitchRightLock1_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PowerWindowSwitchRightLock1__SIO)
        PowerWindowSwitchRightLock1_SIO_REG = PowerWindowSwitchRightLock1_backup.sioState;
    #endif
}


/* [] END OF FILE */
