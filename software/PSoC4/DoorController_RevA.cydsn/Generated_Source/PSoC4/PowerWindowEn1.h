/*******************************************************************************
* File Name: PowerWindowEn1.h  
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

#if !defined(CY_PINS_PowerWindowEn1_H) /* Pins PowerWindowEn1_H */
#define CY_PINS_PowerWindowEn1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PowerWindowEn1_aliases.h"


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
} PowerWindowEn1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PowerWindowEn1_Read(void);
void    PowerWindowEn1_Write(uint8 value);
uint8   PowerWindowEn1_ReadDataReg(void);
#if defined(PowerWindowEn1__PC) || (CY_PSOC4_4200L) 
    void    PowerWindowEn1_SetDriveMode(uint8 mode);
#endif
void    PowerWindowEn1_SetInterruptMode(uint16 position, uint16 mode);
uint8   PowerWindowEn1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PowerWindowEn1_Sleep(void); 
void PowerWindowEn1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PowerWindowEn1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PowerWindowEn1_DRIVE_MODE_BITS        (3)
    #define PowerWindowEn1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PowerWindowEn1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PowerWindowEn1_SetDriveMode() function.
         *  @{
         */
        #define PowerWindowEn1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PowerWindowEn1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PowerWindowEn1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PowerWindowEn1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PowerWindowEn1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PowerWindowEn1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PowerWindowEn1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PowerWindowEn1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PowerWindowEn1_MASK               PowerWindowEn1__MASK
#define PowerWindowEn1_SHIFT              PowerWindowEn1__SHIFT
#define PowerWindowEn1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PowerWindowEn1_SetInterruptMode() function.
     *  @{
     */
        #define PowerWindowEn1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PowerWindowEn1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PowerWindowEn1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PowerWindowEn1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PowerWindowEn1__SIO)
    #define PowerWindowEn1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PowerWindowEn1__PC) && (CY_PSOC4_4200L)
    #define PowerWindowEn1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PowerWindowEn1_USBIO_DISABLE              ((uint32)(~PowerWindowEn1_USBIO_ENABLE))
    #define PowerWindowEn1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PowerWindowEn1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PowerWindowEn1_USBIO_ENTER_SLEEP          ((uint32)((1u << PowerWindowEn1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PowerWindowEn1_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowEn1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PowerWindowEn1_USBIO_SUSPEND_SHIFT)))
    #define PowerWindowEn1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PowerWindowEn1_USBIO_SUSPEND_DEL_SHIFT)))
    #define PowerWindowEn1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PowerWindowEn1__PC)
    /* Port Configuration */
    #define PowerWindowEn1_PC                 (* (reg32 *) PowerWindowEn1__PC)
#endif
/* Pin State */
#define PowerWindowEn1_PS                     (* (reg32 *) PowerWindowEn1__PS)
/* Data Register */
#define PowerWindowEn1_DR                     (* (reg32 *) PowerWindowEn1__DR)
/* Input Buffer Disable Override */
#define PowerWindowEn1_INP_DIS                (* (reg32 *) PowerWindowEn1__PC2)

/* Interrupt configuration Registers */
#define PowerWindowEn1_INTCFG                 (* (reg32 *) PowerWindowEn1__INTCFG)
#define PowerWindowEn1_INTSTAT                (* (reg32 *) PowerWindowEn1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PowerWindowEn1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PowerWindowEn1__SIO)
    #define PowerWindowEn1_SIO_REG            (* (reg32 *) PowerWindowEn1__SIO)
#endif /* (PowerWindowEn1__SIO_CFG) */

/* USBIO registers */
#if !defined(PowerWindowEn1__PC) && (CY_PSOC4_4200L)
    #define PowerWindowEn1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PowerWindowEn1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PowerWindowEn1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PowerWindowEn1_DRIVE_MODE_SHIFT       (0x00u)
#define PowerWindowEn1_DRIVE_MODE_MASK        (0x07u << PowerWindowEn1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PowerWindowEn1_H */


/* [] END OF FILE */
