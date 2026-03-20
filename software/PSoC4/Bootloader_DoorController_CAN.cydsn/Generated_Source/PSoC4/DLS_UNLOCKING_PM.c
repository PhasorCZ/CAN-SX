/*******************************************************************************
* File Name: DLS_UNLOCKING.c  
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
#include "DLS_UNLOCKING.h"

static DLS_UNLOCKING_BACKUP_STRUCT  DLS_UNLOCKING_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DLS_UNLOCKING_Sleep
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
*  \snippet DLS_UNLOCKING_SUT.c usage_DLS_UNLOCKING_Sleep_Wakeup
*******************************************************************************/
void DLS_UNLOCKING_Sleep(void)
{
    #if defined(DLS_UNLOCKING__PC)
        DLS_UNLOCKING_backup.pcState = DLS_UNLOCKING_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DLS_UNLOCKING_backup.usbState = DLS_UNLOCKING_CR1_REG;
            DLS_UNLOCKING_USB_POWER_REG |= DLS_UNLOCKING_USBIO_ENTER_SLEEP;
            DLS_UNLOCKING_CR1_REG &= DLS_UNLOCKING_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DLS_UNLOCKING__SIO)
        DLS_UNLOCKING_backup.sioState = DLS_UNLOCKING_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DLS_UNLOCKING_SIO_REG &= (uint32)(~DLS_UNLOCKING_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DLS_UNLOCKING_Wakeup
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
*  Refer to DLS_UNLOCKING_Sleep() for an example usage.
*******************************************************************************/
void DLS_UNLOCKING_Wakeup(void)
{
    #if defined(DLS_UNLOCKING__PC)
        DLS_UNLOCKING_PC = DLS_UNLOCKING_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DLS_UNLOCKING_USB_POWER_REG &= DLS_UNLOCKING_USBIO_EXIT_SLEEP_PH1;
            DLS_UNLOCKING_CR1_REG = DLS_UNLOCKING_backup.usbState;
            DLS_UNLOCKING_USB_POWER_REG &= DLS_UNLOCKING_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DLS_UNLOCKING__SIO)
        DLS_UNLOCKING_SIO_REG = DLS_UNLOCKING_backup.sioState;
    #endif
}


/* [] END OF FILE */
