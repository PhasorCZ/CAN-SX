/*******************************************************************************
* File Name: DLS_LOCKING.c  
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
#include "DLS_LOCKING.h"

static DLS_LOCKING_BACKUP_STRUCT  DLS_LOCKING_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DLS_LOCKING_Sleep
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
*  \snippet DLS_LOCKING_SUT.c usage_DLS_LOCKING_Sleep_Wakeup
*******************************************************************************/
void DLS_LOCKING_Sleep(void)
{
    #if defined(DLS_LOCKING__PC)
        DLS_LOCKING_backup.pcState = DLS_LOCKING_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DLS_LOCKING_backup.usbState = DLS_LOCKING_CR1_REG;
            DLS_LOCKING_USB_POWER_REG |= DLS_LOCKING_USBIO_ENTER_SLEEP;
            DLS_LOCKING_CR1_REG &= DLS_LOCKING_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DLS_LOCKING__SIO)
        DLS_LOCKING_backup.sioState = DLS_LOCKING_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DLS_LOCKING_SIO_REG &= (uint32)(~DLS_LOCKING_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DLS_LOCKING_Wakeup
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
*  Refer to DLS_LOCKING_Sleep() for an example usage.
*******************************************************************************/
void DLS_LOCKING_Wakeup(void)
{
    #if defined(DLS_LOCKING__PC)
        DLS_LOCKING_PC = DLS_LOCKING_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DLS_LOCKING_USB_POWER_REG &= DLS_LOCKING_USBIO_EXIT_SLEEP_PH1;
            DLS_LOCKING_CR1_REG = DLS_LOCKING_backup.usbState;
            DLS_LOCKING_USB_POWER_REG &= DLS_LOCKING_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DLS_LOCKING__SIO)
        DLS_LOCKING_SIO_REG = DLS_LOCKING_backup.sioState;
    #endif
}


/* [] END OF FILE */
