/*******************************************************************************
* File Name: PwmOut5.c  
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
#include "PwmOut5.h"

static PwmOut5_BACKUP_STRUCT  PwmOut5_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PwmOut5_Sleep
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
*  \snippet PwmOut5_SUT.c usage_PwmOut5_Sleep_Wakeup
*******************************************************************************/
void PwmOut5_Sleep(void)
{
    #if defined(PwmOut5__PC)
        PwmOut5_backup.pcState = PwmOut5_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PwmOut5_backup.usbState = PwmOut5_CR1_REG;
            PwmOut5_USB_POWER_REG |= PwmOut5_USBIO_ENTER_SLEEP;
            PwmOut5_CR1_REG &= PwmOut5_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PwmOut5__SIO)
        PwmOut5_backup.sioState = PwmOut5_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PwmOut5_SIO_REG &= (uint32)(~PwmOut5_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PwmOut5_Wakeup
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
*  Refer to PwmOut5_Sleep() for an example usage.
*******************************************************************************/
void PwmOut5_Wakeup(void)
{
    #if defined(PwmOut5__PC)
        PwmOut5_PC = PwmOut5_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PwmOut5_USB_POWER_REG &= PwmOut5_USBIO_EXIT_SLEEP_PH1;
            PwmOut5_CR1_REG = PwmOut5_backup.usbState;
            PwmOut5_USB_POWER_REG &= PwmOut5_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PwmOut5__SIO)
        PwmOut5_SIO_REG = PwmOut5_backup.sioState;
    #endif
}


/* [] END OF FILE */
