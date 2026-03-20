/*******************************************************************************
* File Name: PowerWindowSwitchRightDown.h  
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

#if !defined(CY_PINS_PowerWindowSwitchRightDown_H) /* Pins PowerWindowSwitchRightDown_H */
#define CY_PINS_PowerWindowSwitchRightDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PowerWindowSwitchRightDown_aliases.h"


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
} PowerWindowSwitchRightDown_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PowerWindowSwitchRightDown_Read(void);
void    PowerWindowSwitchRightDown_Write(uint8 value);
uint8   PowerWindowSwitchRightDown_ReadDataReg(void);
#if defined(PowerWindowSwitchRightDown__PC) || (CY_PSOC4_4200L) 
    void    PowerWindowSwitchRightDown_SetDriveMode(uint8 mode);
#endif
void    PowerWindowSwitchRightDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerWindowSwitchRightDown_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PowerWindowSwitchRightDown_Sleep(void); 
void PowerWindowSwitchRightDown_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PowerWindowSwitchRightDown__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PowerWindowSwitchRightDown_DRIVE_MODE_BITS        (3)
    #define PowerWindowSwitchRightDown_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PowerWindowSwitchRightDown_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PowerWindowSwitchRightDown_SetDriveMode() function.
         *  @{
         */
        #define PowerWindowSwitchRightDown_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PowerWindowSwitchRightDown_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PowerWindowSwitchRightDown_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PowerWindowSwitchRightDown_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PowerWindowSwitchRightDown_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PowerWindowSwitchRightDown_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PowerWindowSwitchRightDown_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PowerWindowSwitchRightDown_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PowerWindowSwitchRightDown_MASK               PowerWindowSwitchRightDown__MASK
#define PowerWindowSwitchRightDown_SHIFT              PowerWindowSwitchRightDown__SHIFT
#define PowerWindowSwitchRightDown_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerWindowSwitchRightDown_SetInterruptMode() function.
     *  @{
     */
        #define PowerWindowSwitchRightDown_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PowerWindowSwitchRightDown_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PowerWindowSwitchRightDown_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PowerWindowSwitchRightDown_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PowerWindowSwitchRightDown__SIO)
    #define PowerWindowSwitchRightDown_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PowerWindowSwitchRightDown__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchRightDown_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PowerWindowSwitchRightDown_USBIO_DISABLE              ((uint32)(~PowerWindowSwitchRightDown_USBIO_ENABLE))
    #define PowerWindowSwitchRightDown_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PowerWindowSwitchRightDown_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PowerWindowSwitchRightDown_USBIO_ENTER_SLEEP          ((uint32)((1u << PowerWindowSwitchRightDown_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PowerWindowSwitchRightDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchRightDown_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PowerWindowSwitchRightDown_USBIO_SUSPEND_SHIFT)))
    #define PowerWindowSwitchRightDown_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PowerWindowSwitchRightDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchRightDown_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PowerWindowSwitchRightDown__PC)
    /* Port Configuration */
    #define PowerWindowSwitchRightDown_PC                 (* (reg32 *) PowerWindowSwitchRightDown__PC)
#endif
/* Pin State */
#define PowerWindowSwitchRightDown_PS                     (* (reg32 *) PowerWindowSwitchRightDown__PS)
/* Data Register */
#define PowerWindowSwitchRightDown_DR                     (* (reg32 *) PowerWindowSwitchRightDown__DR)
/* Input Buffer Disable Override */
#define PowerWindowSwitchRightDown_INP_DIS                (* (reg32 *) PowerWindowSwitchRightDown__PC2)

/* Interrupt configuration Registers */
#define PowerWindowSwitchRightDown_INTCFG                 (* (reg32 *) PowerWindowSwitchRightDown__INTCFG)
#define PowerWindowSwitchRightDown_INTSTAT                (* (reg32 *) PowerWindowSwitchRightDown__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PowerWindowSwitchRightDown_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PowerWindowSwitchRightDown__SIO)
    #define PowerWindowSwitchRightDown_SIO_REG            (* (reg32 *) PowerWindowSwitchRightDown__SIO)
#endif /* (PowerWindowSwitchRightDown__SIO_CFG) */

/* USBIO registers */
#if !defined(PowerWindowSwitchRightDown__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchRightDown_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PowerWindowSwitchRightDown_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PowerWindowSwitchRightDown_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PowerWindowSwitchRightDown_DRIVE_MODE_SHIFT       (0x00u)
#define PowerWindowSwitchRightDown_DRIVE_MODE_MASK        (0x07u << PowerWindowSwitchRightDown_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PowerWindowSwitchRightDown_H */


/* [] END OF FILE */
