/*******************************************************************************
* File Name: HB_2_DEN.c  
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
#include "HB_2_DEN.h"

static HB_2_DEN_BACKUP_STRUCT  HB_2_DEN_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: HB_2_DEN_Sleep
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
*  \snippet HB_2_DEN_SUT.c usage_HB_2_DEN_Sleep_Wakeup
*******************************************************************************/
void HB_2_DEN_Sleep(void)
{
    #if defined(HB_2_DEN__PC)
        HB_2_DEN_backup.pcState = HB_2_DEN_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            HB_2_DEN_backup.usbState = HB_2_DEN_CR1_REG;
            HB_2_DEN_USB_POWER_REG |= HB_2_DEN_USBIO_ENTER_SLEEP;
            HB_2_DEN_CR1_REG &= HB_2_DEN_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HB_2_DEN__SIO)
        HB_2_DEN_backup.sioState = HB_2_DEN_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        HB_2_DEN_SIO_REG &= (uint32)(~HB_2_DEN_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: HB_2_DEN_Wakeup
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
*  Refer to HB_2_DEN_Sleep() for an example usage.
*******************************************************************************/
void HB_2_DEN_Wakeup(void)
{
    #if defined(HB_2_DEN__PC)
        HB_2_DEN_PC = HB_2_DEN_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            HB_2_DEN_USB_POWER_REG &= HB_2_DEN_USBIO_EXIT_SLEEP_PH1;
            HB_2_DEN_CR1_REG = HB_2_DEN_backup.usbState;
            HB_2_DEN_USB_POWER_REG &= HB_2_DEN_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(HB_2_DEN__SIO)
        HB_2_DEN_SIO_REG = HB_2_DEN_backup.sioState;
    #endif
}


/* [] END OF FILE */
