/*******************************************************************************
* File Name: DoorLightLeftBlue.c  
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
#include "DoorLightLeftBlue.h"

static DoorLightLeftBlue_BACKUP_STRUCT  DoorLightLeftBlue_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: DoorLightLeftBlue_Sleep
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
*  \snippet DoorLightLeftBlue_SUT.c usage_DoorLightLeftBlue_Sleep_Wakeup
*******************************************************************************/
void DoorLightLeftBlue_Sleep(void)
{
    #if defined(DoorLightLeftBlue__PC)
        DoorLightLeftBlue_backup.pcState = DoorLightLeftBlue_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            DoorLightLeftBlue_backup.usbState = DoorLightLeftBlue_CR1_REG;
            DoorLightLeftBlue_USB_POWER_REG |= DoorLightLeftBlue_USBIO_ENTER_SLEEP;
            DoorLightLeftBlue_CR1_REG &= DoorLightLeftBlue_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DoorLightLeftBlue__SIO)
        DoorLightLeftBlue_backup.sioState = DoorLightLeftBlue_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        DoorLightLeftBlue_SIO_REG &= (uint32)(~DoorLightLeftBlue_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: DoorLightLeftBlue_Wakeup
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
*  Refer to DoorLightLeftBlue_Sleep() for an example usage.
*******************************************************************************/
void DoorLightLeftBlue_Wakeup(void)
{
    #if defined(DoorLightLeftBlue__PC)
        DoorLightLeftBlue_PC = DoorLightLeftBlue_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            DoorLightLeftBlue_USB_POWER_REG &= DoorLightLeftBlue_USBIO_EXIT_SLEEP_PH1;
            DoorLightLeftBlue_CR1_REG = DoorLightLeftBlue_backup.usbState;
            DoorLightLeftBlue_USB_POWER_REG &= DoorLightLeftBlue_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(DoorLightLeftBlue__SIO)
        DoorLightLeftBlue_SIO_REG = DoorLightLeftBlue_backup.sioState;
    #endif
}


/* [] END OF FILE */
