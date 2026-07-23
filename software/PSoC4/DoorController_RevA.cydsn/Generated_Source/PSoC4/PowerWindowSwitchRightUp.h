/*******************************************************************************
* File Name: PowerWindowSwitchRightUp.h  
* Version 2.20
*
* Description:
*  This file contains Pin function prototypes and register defines
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_PowerWindowSwitchRightUp_H) /* Pins PowerWindowSwitchRightUp_H */
#define CY_PINS_PowerWindowSwitchRightUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PowerWindowSwitchRightUp_aliases.h"


/***************************************
*     Data Struct Definitions
***************************************/

/**
* \addtogroup group_structures
* @{
*/
    
/* Structure for sleep mode support */
typedef struct
{
    uint32 pcState; /**< State of the port control register */
    uint32 sioState; /**< State of the SIO configuration */
    uint32 usbState; /**< State of the USBIO regulator */
} PowerWindowSwitchRightUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PowerWindowSwitchRightUp_Read(void);
void    PowerWindowSwitchRightUp_Write(uint8 value);
uint8   PowerWindowSwitchRightUp_ReadDataReg(void);
#if defined(PowerWindowSwitchRightUp__PC) || (CY_PSOC4_4200L) 
    void    PowerWindowSwitchRightUp_SetDriveMode(uint8 mode);
#endif
void    PowerWindowSwitchRightUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerWindowSwitchRightUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PowerWindowSwitchRightUp_Sleep(void); 
void PowerWindowSwitchRightUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PowerWindowSwitchRightUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PowerWindowSwitchRightUp_DRIVE_MODE_BITS        (3)
    #define PowerWindowSwitchRightUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PowerWindowSwitchRightUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PowerWindowSwitchRightUp_SetDriveMode() function.
         *  @{
         */
        #define PowerWindowSwitchRightUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PowerWindowSwitchRightUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PowerWindowSwitchRightUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PowerWindowSwitchRightUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PowerWindowSwitchRightUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PowerWindowSwitchRightUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PowerWindowSwitchRightUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PowerWindowSwitchRightUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PowerWindowSwitchRightUp_MASK               PowerWindowSwitchRightUp__MASK
#define PowerWindowSwitchRightUp_SHIFT              PowerWindowSwitchRightUp__SHIFT
#define PowerWindowSwitchRightUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerWindowSwitchRightUp_SetInterruptMode() function.
     *  @{
     */
        #define PowerWindowSwitchRightUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PowerWindowSwitchRightUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PowerWindowSwitchRightUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PowerWindowSwitchRightUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PowerWindowSwitchRightUp__SIO)
    #define PowerWindowSwitchRightUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PowerWindowSwitchRightUp__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchRightUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PowerWindowSwitchRightUp_USBIO_DISABLE              ((uint32)(~PowerWindowSwitchRightUp_USBIO_ENABLE))
    #define PowerWindowSwitchRightUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PowerWindowSwitchRightUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PowerWindowSwitchRightUp_USBIO_ENTER_SLEEP          ((uint32)((1u << PowerWindowSwitchRightUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PowerWindowSwitchRightUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchRightUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PowerWindowSwitchRightUp_USBIO_SUSPEND_SHIFT)))
    #define PowerWindowSwitchRightUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PowerWindowSwitchRightUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchRightUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PowerWindowSwitchRightUp__PC)
    /* Port Configuration */
    #define PowerWindowSwitchRightUp_PC                 (* (reg32 *) PowerWindowSwitchRightUp__PC)
#endif
/* Pin State */
#define PowerWindowSwitchRightUp_PS                     (* (reg32 *) PowerWindowSwitchRightUp__PS)
/* Data Register */
#define PowerWindowSwitchRightUp_DR                     (* (reg32 *) PowerWindowSwitchRightUp__DR)
/* Input Buffer Disable Override */
#define PowerWindowSwitchRightUp_INP_DIS                (* (reg32 *) PowerWindowSwitchRightUp__PC2)

/* Interrupt configuration Registers */
#define PowerWindowSwitchRightUp_INTCFG                 (* (reg32 *) PowerWindowSwitchRightUp__INTCFG)
#define PowerWindowSwitchRightUp_INTSTAT                (* (reg32 *) PowerWindowSwitchRightUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PowerWindowSwitchRightUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PowerWindowSwitchRightUp__SIO)
    #define PowerWindowSwitchRightUp_SIO_REG            (* (reg32 *) PowerWindowSwitchRightUp__SIO)
#endif /* (PowerWindowSwitchRightUp__SIO_CFG) */

/* USBIO registers */
#if !defined(PowerWindowSwitchRightUp__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchRightUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PowerWindowSwitchRightUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PowerWindowSwitchRightUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PowerWindowSwitchRightUp_DRIVE_MODE_SHIFT       (0x00u)
#define PowerWindowSwitchRightUp_DRIVE_MODE_MASK        (0x07u << PowerWindowSwitchRightUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PowerWindowSwitchRightUp_H */


/* [] END OF FILE */
