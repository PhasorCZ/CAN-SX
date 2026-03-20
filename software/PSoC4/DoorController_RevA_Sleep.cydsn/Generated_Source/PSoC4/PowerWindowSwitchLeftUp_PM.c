/*******************************************************************************
* File Name: PowerWindowSwitchLeftUp.c  
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
#include "PowerWindowSwitchLeftUp.h"

static PowerWindowSwitchLeftUp_BACKUP_STRUCT  PowerWindowSwitchLeftUp_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PowerWindowSwitchLeftUp_Sleep
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
*  \snippet PowerWindowSwitchLeftUp_SUT.c usage_PowerWindowSwitchLeftUp_Sleep_Wakeup
*******************************************************************************/
void PowerWindowSwitchLeftUp_Sleep(void)
{
    #if defined(PowerWindowSwitchLeftUp__PC)
        PowerWindowSwitchLeftUp_backup.pcState = PowerWindowSwitchLeftUp_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PowerWindowSwitchLeftUp_backup.usbState = PowerWindowSwitchLeftUp_CR1_REG;
            PowerWindowSwitchLeftUp_USB_POWER_REG |= PowerWindowSwitchLeftUp_USBIO_ENTER_SLEEP;
            PowerWindowSwitchLeftUp_CR1_REG &= PowerWindowSwitchLeftUp_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PowerWindowSwitchLeftUp__SIO)
        PowerWindowSwitchLeftUp_backup.sioState = PowerWindowSwitchLeftUp_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PowerWindowSwitchLeftUp_SIO_REG &= (uint32)(~PowerWindowSwitchLeftUp_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PowerWindowSwitchLeftUp_Wakeup
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
*  Refer to PowerWindowSwitchLeftUp_Sleep() for an example usage.
*******************************************************************************/
void PowerWindowSwitchLeftUp_Wakeup(void)
{
    #if defined(PowerWindowSwitchLeftUp__PC)
        PowerWindowSwitchLeftUp_PC = PowerWindowSwitchLeftUp_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PowerWindowSwitchLeftUp_USB_POWER_REG &= PowerWindowSwitchLeftUp_USBIO_EXIT_SLEEP_PH1;
            PowerWindowSwitchLeftUp_CR1_REG = PowerWindowSwitchLeftUp_backup.usbState;
            PowerWindowSwitchLeftUp_USB_POWER_REG &= PowerWindowSwitchLeftUp_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PowerWindowSwitchLeftUp__SIO)
        PowerWindowSwitchLeftUp_SIO_REG = PowerWindowSwitchLeftUp_backup.sioState;
    #endif
}


/* [] END OF FILE */
