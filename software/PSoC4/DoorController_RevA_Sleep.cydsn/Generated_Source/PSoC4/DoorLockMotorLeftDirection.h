/*******************************************************************************
* File Name: DoorLockMotorLeftDirection.h  
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

#if !defined(CY_PINS_DoorLockMotorLeftDirection_H) /* Pins DoorLockMotorLeftDirection_H */
#define CY_PINS_DoorLockMotorLeftDirection_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DoorLockMotorLeftDirection_aliases.h"


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
} DoorLockMotorLeftDirection_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DoorLockMotorLeftDirection_Read(void);
void    DoorLockMotorLeftDirection_Write(uint8 value);
uint8   DoorLockMotorLeftDirection_ReadDataReg(void);
#if defined(DoorLockMotorLeftDirection__PC) || (CY_PSOC4_4200L) 
    void    DoorLockMotorLeftDirection_SetDriveMode(uint8 mode);
#endif
void    DoorLockMotorLeftDirection_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorLockMotorLeftDirection_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DoorLockMotorLeftDirection_Sleep(void); 
void DoorLockMotorLeftDirection_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DoorLockMotorLeftDirection__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DoorLockMotorLeftDirection_DRIVE_MODE_BITS        (3)
    #define DoorLockMotorLeftDirection_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DoorLockMotorLeftDirection_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DoorLockMotorLeftDirection_SetDriveMode() function.
         *  @{
         */
        #define DoorLockMotorLeftDirection_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DoorLockMotorLeftDirection_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DoorLockMotorLeftDirection_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DoorLockMotorLeftDirection_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DoorLockMotorLeftDirection_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DoorLockMotorLeftDirection_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DoorLockMotorLeftDirection_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DoorLockMotorLeftDirection_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DoorLockMotorLeftDirection_MASK               DoorLockMotorLeftDirection__MASK
#define DoorLockMotorLeftDirection_SHIFT              DoorLockMotorLeftDirection__SHIFT
#define DoorLockMotorLeftDirection_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorLockMotorLeftDirection_SetInterruptMode() function.
     *  @{
     */
        #define DoorLockMotorLeftDirection_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DoorLockMotorLeftDirection_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DoorLockMotorLeftDirection_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DoorLockMotorLeftDirection_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DoorLockMotorLeftDirection__SIO)
    #define DoorLockMotorLeftDirection_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DoorLockMotorLeftDirection__PC) && (CY_PSOC4_4200L)
    #define DoorLockMotorLeftDirection_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DoorLockMotorLeftDirection_USBIO_DISABLE              ((uint32)(~DoorLockMotorLeftDirection_USBIO_ENABLE))
    #define DoorLockMotorLeftDirection_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DoorLockMotorLeftDirection_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DoorLockMotorLeftDirection_USBIO_ENTER_SLEEP          ((uint32)((1u << DoorLockMotorLeftDirection_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DoorLockMotorLeftDirection_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLockMotorLeftDirection_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DoorLockMotorLeftDirection_USBIO_SUSPEND_SHIFT)))
    #define DoorLockMotorLeftDirection_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DoorLockMotorLeftDirection_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLockMotorLeftDirection_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DoorLockMotorLeftDirection__PC)
    /* Port Configuration */
    #define DoorLockMotorLeftDirection_PC                 (* (reg32 *) DoorLockMotorLeftDirection__PC)
#endif
/* Pin State */
#define DoorLockMotorLeftDirection_PS                     (* (reg32 *) DoorLockMotorLeftDirection__PS)
/* Data Register */
#define DoorLockMotorLeftDirection_DR                     (* (reg32 *) DoorLockMotorLeftDirection__DR)
/* Input Buffer Disable Override */
#define DoorLockMotorLeftDirection_INP_DIS                (* (reg32 *) DoorLockMotorLeftDirection__PC2)

/* Interrupt configuration Registers */
#define DoorLockMotorLeftDirection_INTCFG                 (* (reg32 *) DoorLockMotorLeftDirection__INTCFG)
#define DoorLockMotorLeftDirection_INTSTAT                (* (reg32 *) DoorLockMotorLeftDirection__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DoorLockMotorLeftDirection_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DoorLockMotorLeftDirection__SIO)
    #define DoorLockMotorLeftDirection_SIO_REG            (* (reg32 *) DoorLockMotorLeftDirection__SIO)
#endif /* (DoorLockMotorLeftDirection__SIO_CFG) */

/* USBIO registers */
#if !defined(DoorLockMotorLeftDirection__PC) && (CY_PSOC4_4200L)
    #define DoorLockMotorLeftDirection_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DoorLockMotorLeftDirection_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DoorLockMotorLeftDirection_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DoorLockMotorLeftDirection_DRIVE_MODE_SHIFT       (0x00u)
#define DoorLockMotorLeftDirection_DRIVE_MODE_MASK        (0x07u << DoorLockMotorLeftDirection_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DoorLockMotorLeftDirection_H */


/* [] END OF FILE */
