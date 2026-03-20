/*******************************************************************************
* File Name: CAN_STB.c  
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
#include "CAN_STB.h"

static CAN_STB_BACKUP_STRUCT  CAN_STB_backup = {0u, 0u, 0u};


/*******************************************************************************
* Function Name: CAN_STB_Sleep
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
*  \snippet CAN_STB_SUT.c usage_CAN_STB_Sleep_Wakeup
*******************************************************************************/
void CAN_STB_Sleep(void)
{
    #if defined(CAN_STB__PC)
        CAN_STB_backup.pcState = CAN_STB_PC;
    #else
        #if (CY_PSOC4_4200L)
            /* Save the regulator state and put the PHY into suspend mode */
            CAN_STB_backup.usbState = CAN_STB_CR1_REG;
            CAN_STB_USB_POWER_REG |= CAN_STB_USBIO_ENTER_SLEEP;
            CAN_STB_CR1_REG &= CAN_STB_USBIO_CR1_OFF;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CAN_STB__SIO)
        CAN_STB_backup.sioState = CAN_STB_SIO_REG;
        /* SIO requires unregulated output buffer and single ended input buffer */
        CAN_STB_SIO_REG &= (uint32)(~CAN_STB_SIO_LPM_MASK);
    #endif  
}


/*******************************************************************************
* Function Name: CAN_STB_Wakeup
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
*  Refer to CAN_STB_Sleep() for an example usage.
*******************************************************************************/
void CAN_STB_Wakeup(void)
{
    #if defined(CAN_STB__PC)
        CAN_STB_PC = CAN_STB_backup.pcState;
    #else
        #if (CY_PSOC4_4200L)
            /* Restore the regulator state and come out of suspend mode */
            CAN_STB_USB_POWER_REG &= CAN_STB_USBIO_EXIT_SLEEP_PH1;
            CAN_STB_CR1_REG = CAN_STB_backup.usbState;
            CAN_STB_USB_POWER_REG &= CAN_STB_USBIO_EXIT_SLEEP_PH2;
        #endif
    #endif
    #if defined(CYIPBLOCK_m0s8ioss_VERSION) && defined(CAN_STB__SIO)
        CAN_STB_SIO_REG = CAN_STB_backup.sioState;
    #endif
}


/* [] END OF FILE */
