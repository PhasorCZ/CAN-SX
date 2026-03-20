/*******************************************************************************
* File Name: HB_IS.c  
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
#include "HB_IS.h"

static HB_IS_BACKUP_STRUCT  HB_IS_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: HB_IS_Sleep
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
*  \snippet HB_IS_SUT.c usage_HB_IS_Sleep_Wakeup
*******************************************************************************/
void HB_IS_Sleep(void)
{
    #if defined(HB_IS__PC)
        HB_IS_backup.pcState = HB_IS_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            HB_IS_backup.usbState = HB_IS_CR1_REG;
            HB_IS_USB_POWER_REG |= HB_IS_USBIO_ENTER_SLEEP;
            HB_IS_CR1_REG &= HB_IS_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HB_IS__SIO)
        HB_IS_backup.sioState = HB_IS_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        HB_IS_SIO_REG &= (uint32)(~HB_IS_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: HB_IS_Wakeup
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
*  Refer to HB_IS_Sleep() for an example usage.
*******************************************************************************/
void HB_IS_Wakeup(void)
{
    #if defined(HB_IS__PC)
        HB_IS_PC = HB_IS_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            HB_IS_USB_POWER_REG &= HB_IS_USBIO_EXIT_SLEEP_PH1;
            HB_IS_CR1_REG = HB_IS_backup.usbState;
            HB_IS_USB_POWER_REG &= HB_IS_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HB_IS__SIO)
        HB_IS_SIO_REG = HB_IS_backup.sioState;
    #endif
}


/* [] END OF FILE */
