/*******************************************************************************
* File Name: PwmOut6.h  
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

#if !defined(CY_PINS_PwmOut6_H) /* Pins PwmOut6_H */
#define CY_PINS_PwmOut6_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PwmOut6_aliases.h"


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
} PwmOut6_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PwmOut6_Read(void);
void    PwmOut6_Write(uint8 value);
uint8   PwmOut6_ReadDataReg(void);
#if defined(PwmOut6__PC) || (CY_PSOC4_4200L) 
    void    PwmOut6_SetDriveMode(uint8 mode);
#endif
void    PwmOut6_SetInterruptMode(uint16 position, uint16 mode);
uint8   PwmOut6_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PwmOut6_Sleep(void); 
void PwmOut6_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PwmOut6__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PwmOut6_DRIVE_MODE_BITS        (3)
    #define PwmOut6_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PwmOut6_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PwmOut6_SetDriveMode() function.
         *  @{
         */
        #define PwmOut6_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PwmOut6_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PwmOut6_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PwmOut6_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PwmOut6_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PwmOut6_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PwmOut6_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PwmOut6_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PwmOut6_MASK               PwmOut6__MASK
#define PwmOut6_SHIFT              PwmOut6__SHIFT
#define PwmOut6_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PwmOut6_SetInterruptMode() function.
     *  @{
     */
        #define PwmOut6_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PwmOut6_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PwmOut6_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PwmOut6_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PwmOut6__SIO)
    #define PwmOut6_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PwmOut6__PC) && (CY_PSOC4_4200L)
    #define PwmOut6_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PwmOut6_USBIO_DISABLE              ((uint32)(~PwmOut6_USBIO_ENABLE))
    #define PwmOut6_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PwmOut6_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PwmOut6_USBIO_ENTER_SLEEP          ((uint32)((1u << PwmOut6_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PwmOut6_USBIO_SUSPEND_DEL_SHIFT)))
    #define PwmOut6_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PwmOut6_USBIO_SUSPEND_SHIFT)))
    #define PwmOut6_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PwmOut6_USBIO_SUSPEND_DEL_SHIFT)))
    #define PwmOut6_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PwmOut6__PC)
    /* Port Configuration */
    #define PwmOut6_PC                 (* (reg32 *) PwmOut6__PC)
#endif
/* Pin State */
#define PwmOut6_PS                     (* (reg32 *) PwmOut6__PS)
/* Data Register */
#define PwmOut6_DR                     (* (reg32 *) PwmOut6__DR)
/* Input Buffer Disable Override */
#define PwmOut6_INP_DIS                (* (reg32 *) PwmOut6__PC2)

/* Interrupt configuration Registers */
#define PwmOut6_INTCFG                 (* (reg32 *) PwmOut6__INTCFG)
#define PwmOut6_INTSTAT                (* (reg32 *) PwmOut6__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PwmOut6_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PwmOut6__SIO)
    #define PwmOut6_SIO_REG            (* (reg32 *) PwmOut6__SIO)
#endif /* (PwmOut6__SIO_CFG) */

/* USBIO registers */
#if !defined(PwmOut6__PC) && (CY_PSOC4_4200L)
    #define PwmOut6_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PwmOut6_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PwmOut6_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PwmOut6_DRIVE_MODE_SHIFT       (0x00u)
#define PwmOut6_DRIVE_MODE_MASK        (0x07u << PwmOut6_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PwmOut6_H */


/* [] END OF FILE */
