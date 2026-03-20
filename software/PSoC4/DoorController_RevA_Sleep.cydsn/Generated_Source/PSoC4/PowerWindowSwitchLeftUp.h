/*******************************************************************************
* File Name: PowerWindowSwitchLeftUp.h  
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

#if !defined(CY_PINS_PowerWindowSwitchLeftUp_H) /* Pins PowerWindowSwitchLeftUp_H */
#define CY_PINS_PowerWindowSwitchLeftUp_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PowerWindowSwitchLeftUp_aliases.h"


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
} PowerWindowSwitchLeftUp_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PowerWindowSwitchLeftUp_Read(void);
void    PowerWindowSwitchLeftUp_Write(uint8 value);
uint8   PowerWindowSwitchLeftUp_ReadDataReg(void);
#if defined(PowerWindowSwitchLeftUp__PC) || (CY_PSOC4_4200L) 
    void    PowerWindowSwitchLeftUp_SetDriveMode(uint8 mode);
#endif
void    PowerWindowSwitchLeftUp_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerWindowSwitchLeftUp_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PowerWindowSwitchLeftUp_Sleep(void); 
void PowerWindowSwitchLeftUp_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PowerWindowSwitchLeftUp__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PowerWindowSwitchLeftUp_DRIVE_MODE_BITS        (3)
    #define PowerWindowSwitchLeftUp_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PowerWindowSwitchLeftUp_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PowerWindowSwitchLeftUp_SetDriveMode() function.
         *  @{
         */
        #define PowerWindowSwitchLeftUp_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PowerWindowSwitchLeftUp_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PowerWindowSwitchLeftUp_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PowerWindowSwitchLeftUp_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PowerWindowSwitchLeftUp_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PowerWindowSwitchLeftUp_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PowerWindowSwitchLeftUp_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PowerWindowSwitchLeftUp_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PowerWindowSwitchLeftUp_MASK               PowerWindowSwitchLeftUp__MASK
#define PowerWindowSwitchLeftUp_SHIFT              PowerWindowSwitchLeftUp__SHIFT
#define PowerWindowSwitchLeftUp_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerWindowSwitchLeftUp_SetInterruptMode() function.
     *  @{
     */
        #define PowerWindowSwitchLeftUp_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PowerWindowSwitchLeftUp_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PowerWindowSwitchLeftUp_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PowerWindowSwitchLeftUp_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PowerWindowSwitchLeftUp__SIO)
    #define PowerWindowSwitchLeftUp_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PowerWindowSwitchLeftUp__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchLeftUp_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PowerWindowSwitchLeftUp_USBIO_DISABLE              ((uint32)(~PowerWindowSwitchLeftUp_USBIO_ENABLE))
    #define PowerWindowSwitchLeftUp_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PowerWindowSwitchLeftUp_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PowerWindowSwitchLeftUp_USBIO_ENTER_SLEEP          ((uint32)((1u << PowerWindowSwitchLeftUp_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PowerWindowSwitchLeftUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchLeftUp_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PowerWindowSwitchLeftUp_USBIO_SUSPEND_SHIFT)))
    #define PowerWindowSwitchLeftUp_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PowerWindowSwitchLeftUp_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchLeftUp_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PowerWindowSwitchLeftUp__PC)
    /* Port Configuration */
    #define PowerWindowSwitchLeftUp_PC                 (* (reg32 *) PowerWindowSwitchLeftUp__PC)
#endif
/* Pin State */
#define PowerWindowSwitchLeftUp_PS                     (* (reg32 *) PowerWindowSwitchLeftUp__PS)
/* Data Register */
#define PowerWindowSwitchLeftUp_DR                     (* (reg32 *) PowerWindowSwitchLeftUp__DR)
/* Input Buffer Disable Override */
#define PowerWindowSwitchLeftUp_INP_DIS                (* (reg32 *) PowerWindowSwitchLeftUp__PC2)

/* Interrupt configuration Registers */
#define PowerWindowSwitchLeftUp_INTCFG                 (* (reg32 *) PowerWindowSwitchLeftUp__INTCFG)
#define PowerWindowSwitchLeftUp_INTSTAT                (* (reg32 *) PowerWindowSwitchLeftUp__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PowerWindowSwitchLeftUp_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PowerWindowSwitchLeftUp__SIO)
    #define PowerWindowSwitchLeftUp_SIO_REG            (* (reg32 *) PowerWindowSwitchLeftUp__SIO)
#endif /* (PowerWindowSwitchLeftUp__SIO_CFG) */

/* USBIO registers */
#if !defined(PowerWindowSwitchLeftUp__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchLeftUp_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PowerWindowSwitchLeftUp_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PowerWindowSwitchLeftUp_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PowerWindowSwitchLeftUp_DRIVE_MODE_SHIFT       (0x00u)
#define PowerWindowSwitchLeftUp_DRIVE_MODE_MASK        (0x07u << PowerWindowSwitchLeftUp_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PowerWindowSwitchLeftUp_H */


/* [] END OF FILE */
