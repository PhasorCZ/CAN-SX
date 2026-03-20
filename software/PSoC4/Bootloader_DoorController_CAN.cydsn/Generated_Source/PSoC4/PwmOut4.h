/*******************************************************************************
* File Name: PwmOut4.h  
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

#if !defined(CY_PINS_PwmOut4_H) /* Pins PwmOut4_H */
#define CY_PINS_PwmOut4_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PwmOut4_aliases.h"


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
} PwmOut4_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PwmOut4_Read(void);
void    PwmOut4_Write(uint8 value);
uint8   PwmOut4_ReadDataReg(void);
#if defined(PwmOut4__PC) || (CY_PSOC4_4200L) 
    void    PwmOut4_SetDriveMode(uint8 mode);
#endif
void    PwmOut4_SetInterruptMode(uint16 position, uint16 mode);
uint8   PwmOut4_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PwmOut4_Sleep(void); 
void PwmOut4_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PwmOut4__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PwmOut4_DRIVE_MODE_BITS        (3)
    #define PwmOut4_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PwmOut4_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PwmOut4_SetDriveMode() function.
         *  @{
         */
        #define PwmOut4_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PwmOut4_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PwmOut4_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PwmOut4_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PwmOut4_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PwmOut4_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PwmOut4_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PwmOut4_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PwmOut4_MASK               PwmOut4__MASK
#define PwmOut4_SHIFT              PwmOut4__SHIFT
#define PwmOut4_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PwmOut4_SetInterruptMode() function.
     *  @{
     */
        #define PwmOut4_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PwmOut4_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PwmOut4_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PwmOut4_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PwmOut4__SIO)
    #define PwmOut4_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PwmOut4__PC) && (CY_PSOC4_4200L)
    #define PwmOut4_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PwmOut4_USBIO_DISABLE              ((uint32)(~PwmOut4_USBIO_ENABLE))
    #define PwmOut4_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PwmOut4_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PwmOut4_USBIO_ENTER_SLEEP          ((uint32)((1u << PwmOut4_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PwmOut4_USBIO_SUSPEND_DEL_SHIFT)))
    #define PwmOut4_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PwmOut4_USBIO_SUSPEND_SHIFT)))
    #define PwmOut4_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PwmOut4_USBIO_SUSPEND_DEL_SHIFT)))
    #define PwmOut4_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PwmOut4__PC)
    /* Port Configuration */
    #define PwmOut4_PC                 (* (reg32 *) PwmOut4__PC)
#endif
/* Pin State */
#define PwmOut4_PS                     (* (reg32 *) PwmOut4__PS)
/* Data Register */
#define PwmOut4_DR                     (* (reg32 *) PwmOut4__DR)
/* Input Buffer Disable Override */
#define PwmOut4_INP_DIS                (* (reg32 *) PwmOut4__PC2)

/* Interrupt configuration Registers */
#define PwmOut4_INTCFG                 (* (reg32 *) PwmOut4__INTCFG)
#define PwmOut4_INTSTAT                (* (reg32 *) PwmOut4__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PwmOut4_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PwmOut4__SIO)
    #define PwmOut4_SIO_REG            (* (reg32 *) PwmOut4__SIO)
#endif /* (PwmOut4__SIO_CFG) */

/* USBIO registers */
#if !defined(PwmOut4__PC) && (CY_PSOC4_4200L)
    #define PwmOut4_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PwmOut4_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PwmOut4_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PwmOut4_DRIVE_MODE_SHIFT       (0x00u)
#define PwmOut4_DRIVE_MODE_MASK        (0x07u << PwmOut4_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PwmOut4_H */


/* [] END OF FILE */
