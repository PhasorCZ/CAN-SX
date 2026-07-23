/*******************************************************************************
* File Name: AnalogIn1.h  
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

#if !defined(CY_PINS_AnalogIn1_H) /* Pins AnalogIn1_H */
#define CY_PINS_AnalogIn1_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AnalogIn1_aliases.h"


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
} AnalogIn1_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   AnalogIn1_Read(void);
void    AnalogIn1_Write(uint8 value);
uint8   AnalogIn1_ReadDataReg(void);
#if defined(AnalogIn1__PC) || (CY_PSOC4_4200L) 
    void    AnalogIn1_SetDriveMode(uint8 mode);
#endif
void    AnalogIn1_SetInterruptMode(uint16 position, uint16 mode);
uint8   AnalogIn1_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void AnalogIn1_Sleep(void); 
void AnalogIn1_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(AnalogIn1__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define AnalogIn1_DRIVE_MODE_BITS        (3)
    #define AnalogIn1_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AnalogIn1_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the AnalogIn1_SetDriveMode() function.
         *  @{
         */
        #define AnalogIn1_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define AnalogIn1_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define AnalogIn1_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define AnalogIn1_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define AnalogIn1_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define AnalogIn1_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define AnalogIn1_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define AnalogIn1_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define AnalogIn1_MASK               AnalogIn1__MASK
#define AnalogIn1_SHIFT              AnalogIn1__SHIFT
#define AnalogIn1_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AnalogIn1_SetInterruptMode() function.
     *  @{
     */
        #define AnalogIn1_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define AnalogIn1_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define AnalogIn1_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define AnalogIn1_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(AnalogIn1__SIO)
    #define AnalogIn1_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(AnalogIn1__PC) && (CY_PSOC4_4200L)
    #define AnalogIn1_USBIO_ENABLE               ((uint32)0x80000000u)
    #define AnalogIn1_USBIO_DISABLE              ((uint32)(~AnalogIn1_USBIO_ENABLE))
    #define AnalogIn1_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define AnalogIn1_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define AnalogIn1_USBIO_ENTER_SLEEP          ((uint32)((1u << AnalogIn1_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << AnalogIn1_USBIO_SUSPEND_DEL_SHIFT)))
    #define AnalogIn1_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << AnalogIn1_USBIO_SUSPEND_SHIFT)))
    #define AnalogIn1_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << AnalogIn1_USBIO_SUSPEND_DEL_SHIFT)))
    #define AnalogIn1_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(AnalogIn1__PC)
    /* Port Configuration */
    #define AnalogIn1_PC                 (* (reg32 *) AnalogIn1__PC)
#endif
/* Pin State */
#define AnalogIn1_PS                     (* (reg32 *) AnalogIn1__PS)
/* Data Register */
#define AnalogIn1_DR                     (* (reg32 *) AnalogIn1__DR)
/* Input Buffer Disable Override */
#define AnalogIn1_INP_DIS                (* (reg32 *) AnalogIn1__PC2)

/* Interrupt configuration Registers */
#define AnalogIn1_INTCFG                 (* (reg32 *) AnalogIn1__INTCFG)
#define AnalogIn1_INTSTAT                (* (reg32 *) AnalogIn1__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define AnalogIn1_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(AnalogIn1__SIO)
    #define AnalogIn1_SIO_REG            (* (reg32 *) AnalogIn1__SIO)
#endif /* (AnalogIn1__SIO_CFG) */

/* USBIO registers */
#if !defined(AnalogIn1__PC) && (CY_PSOC4_4200L)
    #define AnalogIn1_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define AnalogIn1_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define AnalogIn1_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define AnalogIn1_DRIVE_MODE_SHIFT       (0x00u)
#define AnalogIn1_DRIVE_MODE_MASK        (0x07u << AnalogIn1_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins AnalogIn1_H */


/* [] END OF FILE */
