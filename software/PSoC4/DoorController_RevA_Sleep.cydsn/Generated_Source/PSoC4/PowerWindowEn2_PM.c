/*******************************************************************************
* File Name: PowerWindowEn2.c  
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
#include "PowerWindowEn2.h"

static PowerWindowEn2_BACKUP_STRUCT  PowerWindowEn2_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: PowerWindowEn2_Sleep
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
*  \snippet PowerWindowEn2_SUT.c usage_PowerWindowEn2_Sleep_Wakeup
*******************************************************************************/
void PowerWindowEn2_Sleep(void)
{
    #if defined(PowerWindowEn2__PC)
        PowerWindowEn2_backup.pcState = PowerWindowEn2_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            PowerWindowEn2_backup.usbState = PowerWindowEn2_CR1_REG;
            PowerWindowEn2_USB_POWER_REG |= PowerWindowEn2_USBIO_ENTER_SLEEP;
            PowerWindowEn2_CR1_REG &= PowerWindowEn2_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PowerWindowEn2__SIO)
        PowerWindowEn2_backup.sioState = PowerWindowEn2_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        PowerWindowEn2_SIO_REG &= (uint32)(~PowerWindowEn2_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: PowerWindowEn2_Wakeup
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
*  Refer to PowerWindowEn2_Sleep() for an example usage.
*******************************************************************************/
void PowerWindowEn2_Wakeup(void)
{
    #if defined(PowerWindowEn2__PC)
        PowerWindowEn2_PC = PowerWindowEn2_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            PowerWindowEn2_USB_POWER_REG &= PowerWindowEn2_USBIO_EXIT_SLEEP_PH1;
            PowerWindowEn2_CR1_REG = PowerWindowEn2_backup.usbState;
            PowerWindowEn2_USB_POWER_REG &= PowerWindowEn2_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(PowerWindowEn2__SIO)
        PowerWindowEn2_SIO_REG = PowerWindowEn2_backup.sioState;
    #endif
}


/* [] END OF FILE */
