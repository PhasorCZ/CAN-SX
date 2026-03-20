/*******************************************************************************
* File Name: MM_DEN.c  
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
#include "MM_DEN.h"

static MM_DEN_BACKUP_STRUCT  MM_DEN_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: MM_DEN_Sleep
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
*  \snippet MM_DEN_SUT.c usage_MM_DEN_Sleep_Wakeup
*******************************************************************************/
void MM_DEN_Sleep(void)
{
    #if defined(MM_DEN__PC)
        MM_DEN_backup.pcState = MM_DEN_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            MM_DEN_backup.usbState = MM_DEN_CR1_REG;
            MM_DEN_USB_POWER_REG |= MM_DEN_USBIO_ENTER_SLEEP;
            MM_DEN_CR1_REG &= MM_DEN_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MM_DEN__SIO)
        MM_DEN_backup.sioState = MM_DEN_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        MM_DEN_SIO_REG &= (uint32)(~MM_DEN_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: MM_DEN_Wakeup
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
*  Refer to MM_DEN_Sleep() for an example usage.
*******************************************************************************/
void MM_DEN_Wakeup(void)
{
    #if defined(MM_DEN__PC)
        MM_DEN_PC = MM_DEN_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            MM_DEN_USB_POWER_REG &= MM_DEN_USBIO_EXIT_SLEEP_PH1;
            MM_DEN_CR1_REG = MM_DEN_backup.usbState;
            MM_DEN_USB_POWER_REG &= MM_DEN_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(MM_DEN__SIO)
        MM_DEN_SIO_REG = MM_DEN_backup.sioState;
    #endif
}


/* [] END OF FILE */
