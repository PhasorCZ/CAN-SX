/*******************************************************************************
* File Name: DI_DEB.c  
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
#include "DI_DEB.h"

static DI_DEB_BACKUP_STRUCT  DI_DEB_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DI_DEB_Sleep
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
*  \snippet DI_DEB_SUT.c usage_DI_DEB_Sleep_Wakeup
*******************************************************************************/
void DI_DEB_Sleep(void)
{
    #if defined(DI_DEB__PC)
        DI_DEB_backup.pcState = DI_DEB_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DI_DEB_backup.usbState = DI_DEB_CR1_REG;
            DI_DEB_USB_POWER_REG |= DI_DEB_USBIO_ENTER_SLEEP;
            DI_DEB_CR1_REG &= DI_DEB_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DI_DEB__SIO)
        DI_DEB_backup.sioState = DI_DEB_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DI_DEB_SIO_REG &= (uint32)(~DI_DEB_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DI_DEB_Wakeup
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
*  Refer to DI_DEB_Sleep() for an example usage.
*******************************************************************************/
void DI_DEB_Wakeup(void)
{
    #if defined(DI_DEB__PC)
        DI_DEB_PC = DI_DEB_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DI_DEB_USB_POWER_REG &= DI_DEB_USBIO_EXIT_SLEEP_PH1;
            DI_DEB_CR1_REG = DI_DEB_backup.usbState;
            DI_DEB_USB_POWER_REG &= DI_DEB_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DI_DEB__SIO)
        DI_DEB_SIO_REG = DI_DEB_backup.sioState;
    #endif
}


/* [] END OF FILE */
