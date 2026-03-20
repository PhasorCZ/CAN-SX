/*******************************************************************************
* File Name: PowerWindowSwitchLeftDown.h  
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

#if !defined(CY_PINS_PowerWindowSwitchLeftDown_H) /* Pins PowerWindowSwitchLeftDown_H */
#define CY_PINS_PowerWindowSwitchLeftDown_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PowerWindowSwitchLeftDown_aliases.h"


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
} PowerWindowSwitchLeftDown_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PowerWindowSwitchLeftDown_Read(void);
void    PowerWindowSwitchLeftDown_Write(uint8 value);
uint8   PowerWindowSwitchLeftDown_ReadDataReg(void);
#if defined(PowerWindowSwitchLeftDown__PC) || (CY_PSOC4_4200L) 
    void    PowerWindowSwitchLeftDown_SetDriveMode(uint8 mode);
#endif
void    PowerWindowSwitchLeftDown_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerWindowSwitchLeftDown_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PowerWindowSwitchLeftDown_Sleep(void); 
void PowerWindowSwitchLeftDown_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PowerWindowSwitchLeftDown__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PowerWindowSwitchLeftDown_DRIVE_MODE_BITS        (3)
    #define PowerWindowSwitchLeftDown_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PowerWindowSwitchLeftDown_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PowerWindowSwitchLeftDown_SetDriveMode() function.
         *  @{
         */
        #define PowerWindowSwitchLeftDown_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PowerWindowSwitchLeftDown_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PowerWindowSwitchLeftDown_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PowerWindowSwitchLeftDown_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PowerWindowSwitchLeftDown_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PowerWindowSwitchLeftDown_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PowerWindowSwitchLeftDown_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PowerWindowSwitchLeftDown_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PowerWindowSwitchLeftDown_MASK               PowerWindowSwitchLeftDown__MASK
#define PowerWindowSwitchLeftDown_SHIFT              PowerWindowSwitchLeftDown__SHIFT
#define PowerWindowSwitchLeftDown_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerWindowSwitchLeftDown_SetInterruptMode() function.
     *  @{
     */
        #define PowerWindowSwitchLeftDown_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PowerWindowSwitchLeftDown_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PowerWindowSwitchLeftDown_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PowerWindowSwitchLeftDown_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PowerWindowSwitchLeftDown__SIO)
    #define PowerWindowSwitchLeftDown_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PowerWindowSwitchLeftDown__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchLeftDown_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PowerWindowSwitchLeftDown_USBIO_DISABLE              ((uint32)(~PowerWindowSwitchLeftDown_USBIO_ENABLE))
    #define PowerWindowSwitchLeftDown_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PowerWindowSwitchLeftDown_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PowerWindowSwitchLeftDown_USBIO_ENTER_SLEEP          ((uint32)((1u << PowerWindowSwitchLeftDown_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PowerWindowSwitchLeftDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchLeftDown_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PowerWindowSwitchLeftDown_USBIO_SUSPEND_SHIFT)))
    #define PowerWindowSwitchLeftDown_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PowerWindowSwitchLeftDown_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowSwitchLeftDown_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PowerWindowSwitchLeftDown__PC)
    /* Port Configuration */
    #define PowerWindowSwitchLeftDown_PC                 (* (reg32 *) PowerWindowSwitchLeftDown__PC)
#endif
/* Pin State */
#define PowerWindowSwitchLeftDown_PS                     (* (reg32 *) PowerWindowSwitchLeftDown__PS)
/* Data Register */
#define PowerWindowSwitchLeftDown_DR                     (* (reg32 *) PowerWindowSwitchLeftDown__DR)
/* Input Buffer Disable Override */
#define PowerWindowSwitchLeftDown_INP_DIS                (* (reg32 *) PowerWindowSwitchLeftDown__PC2)

/* Interrupt configuration Registers */
#define PowerWindowSwitchLeftDown_INTCFG                 (* (reg32 *) PowerWindowSwitchLeftDown__INTCFG)
#define PowerWindowSwitchLeftDown_INTSTAT                (* (reg32 *) PowerWindowSwitchLeftDown__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PowerWindowSwitchLeftDown_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PowerWindowSwitchLeftDown__SIO)
    #define PowerWindowSwitchLeftDown_SIO_REG            (* (reg32 *) PowerWindowSwitchLeftDown__SIO)
#endif /* (PowerWindowSwitchLeftDown__SIO_CFG) */

/* USBIO registers */
#if !defined(PowerWindowSwitchLeftDown__PC) && (CY_PSOC4_4200L)
    #define PowerWindowSwitchLeftDown_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PowerWindowSwitchLeftDown_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PowerWindowSwitchLeftDown_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PowerWindowSwitchLeftDown_DRIVE_MODE_SHIFT       (0x00u)
#define PowerWindowSwitchLeftDown_DRIVE_MODE_MASK        (0x07u << PowerWindowSwitchLeftDown_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PowerWindowSwitchLeftDown_H */


/* [] END OF FILE */
