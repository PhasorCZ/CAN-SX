/*******************************************************************************
* File Name: DoorLockSensorLeftUnlocking.h  
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

#if !defined(CY_PINS_DoorLockSensorLeftUnlocking_H) /* Pins DoorLockSensorLeftUnlocking_H */
#define CY_PINS_DoorLockSensorLeftUnlocking_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DoorLockSensorLeftUnlocking_aliases.h"


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
} DoorLockSensorLeftUnlocking_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DoorLockSensorLeftUnlocking_Read(void);
void    DoorLockSensorLeftUnlocking_Write(uint8 value);
uint8   DoorLockSensorLeftUnlocking_ReadDataReg(void);
#if defined(DoorLockSensorLeftUnlocking__PC) || (CY_PSOC4_4200L) 
    void    DoorLockSensorLeftUnlocking_SetDriveMode(uint8 mode);
#endif
void    DoorLockSensorLeftUnlocking_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorLockSensorLeftUnlocking_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DoorLockSensorLeftUnlocking_Sleep(void); 
void DoorLockSensorLeftUnlocking_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DoorLockSensorLeftUnlocking__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DoorLockSensorLeftUnlocking_DRIVE_MODE_BITS        (3)
    #define DoorLockSensorLeftUnlocking_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DoorLockSensorLeftUnlocking_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DoorLockSensorLeftUnlocking_SetDriveMode() function.
         *  @{
         */
        #define DoorLockSensorLeftUnlocking_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DoorLockSensorLeftUnlocking_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DoorLockSensorLeftUnlocking_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DoorLockSensorLeftUnlocking_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DoorLockSensorLeftUnlocking_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DoorLockSensorLeftUnlocking_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DoorLockSensorLeftUnlocking_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DoorLockSensorLeftUnlocking_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DoorLockSensorLeftUnlocking_MASK               DoorLockSensorLeftUnlocking__MASK
#define DoorLockSensorLeftUnlocking_SHIFT              DoorLockSensorLeftUnlocking__SHIFT
#define DoorLockSensorLeftUnlocking_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorLockSensorLeftUnlocking_SetInterruptMode() function.
     *  @{
     */
        #define DoorLockSensorLeftUnlocking_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DoorLockSensorLeftUnlocking_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DoorLockSensorLeftUnlocking_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DoorLockSensorLeftUnlocking_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DoorLockSensorLeftUnlocking__SIO)
    #define DoorLockSensorLeftUnlocking_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DoorLockSensorLeftUnlocking__PC) && (CY_PSOC4_4200L)
    #define DoorLockSensorLeftUnlocking_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DoorLockSensorLeftUnlocking_USBIO_DISABLE              ((uint32)(~DoorLockSensorLeftUnlocking_USBIO_ENABLE))
    #define DoorLockSensorLeftUnlocking_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DoorLockSensorLeftUnlocking_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DoorLockSensorLeftUnlocking_USBIO_ENTER_SLEEP          ((uint32)((1u << DoorLockSensorLeftUnlocking_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DoorLockSensorLeftUnlocking_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLockSensorLeftUnlocking_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DoorLockSensorLeftUnlocking_USBIO_SUSPEND_SHIFT)))
    #define DoorLockSensorLeftUnlocking_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DoorLockSensorLeftUnlocking_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLockSensorLeftUnlocking_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DoorLockSensorLeftUnlocking__PC)
    /* Port Configuration */
    #define DoorLockSensorLeftUnlocking_PC                 (* (reg32 *) DoorLockSensorLeftUnlocking__PC)
#endif
/* Pin State */
#define DoorLockSensorLeftUnlocking_PS                     (* (reg32 *) DoorLockSensorLeftUnlocking__PS)
/* Data Register */
#define DoorLockSensorLeftUnlocking_DR                     (* (reg32 *) DoorLockSensorLeftUnlocking__DR)
/* Input Buffer Disable Override */
#define DoorLockSensorLeftUnlocking_INP_DIS                (* (reg32 *) DoorLockSensorLeftUnlocking__PC2)

/* Interrupt configuration Registers */
#define DoorLockSensorLeftUnlocking_INTCFG                 (* (reg32 *) DoorLockSensorLeftUnlocking__INTCFG)
#define DoorLockSensorLeftUnlocking_INTSTAT                (* (reg32 *) DoorLockSensorLeftUnlocking__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DoorLockSensorLeftUnlocking_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DoorLockSensorLeftUnlocking__SIO)
    #define DoorLockSensorLeftUnlocking_SIO_REG            (* (reg32 *) DoorLockSensorLeftUnlocking__SIO)
#endif /* (DoorLockSensorLeftUnlocking__SIO_CFG) */

/* USBIO registers */
#if !defined(DoorLockSensorLeftUnlocking__PC) && (CY_PSOC4_4200L)
    #define DoorLockSensorLeftUnlocking_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DoorLockSensorLeftUnlocking_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DoorLockSensorLeftUnlocking_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DoorLockSensorLeftUnlocking_DRIVE_MODE_SHIFT       (0x00u)
#define DoorLockSensorLeftUnlocking_DRIVE_MODE_MASK        (0x07u << DoorLockSensorLeftUnlocking_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DoorLockSensorLeftUnlocking_H */


/* [] END OF FILE */
