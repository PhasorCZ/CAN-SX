/*******************************************************************************
* File Name: DoorLockSensorLeftLocking.h  
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

#if !defined(CY_PINS_DoorLockSensorLeftLocking_H) /* Pins DoorLockSensorLeftLocking_H */
#define CY_PINS_DoorLockSensorLeftLocking_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DoorLockSensorLeftLocking_aliases.h"


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
} DoorLockSensorLeftLocking_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DoorLockSensorLeftLocking_Read(void);
void    DoorLockSensorLeftLocking_Write(uint8 value);
uint8   DoorLockSensorLeftLocking_ReadDataReg(void);
#if defined(DoorLockSensorLeftLocking__PC) || (CY_PSOC4_4200L) 
    void    DoorLockSensorLeftLocking_SetDriveMode(uint8 mode);
#endif
void    DoorLockSensorLeftLocking_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorLockSensorLeftLocking_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DoorLockSensorLeftLocking_Sleep(void); 
void DoorLockSensorLeftLocking_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DoorLockSensorLeftLocking__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DoorLockSensorLeftLocking_DRIVE_MODE_BITS        (3)
    #define DoorLockSensorLeftLocking_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DoorLockSensorLeftLocking_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DoorLockSensorLeftLocking_SetDriveMode() function.
         *  @{
         */
        #define DoorLockSensorLeftLocking_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DoorLockSensorLeftLocking_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DoorLockSensorLeftLocking_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DoorLockSensorLeftLocking_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DoorLockSensorLeftLocking_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DoorLockSensorLeftLocking_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DoorLockSensorLeftLocking_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DoorLockSensorLeftLocking_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DoorLockSensorLeftLocking_MASK               DoorLockSensorLeftLocking__MASK
#define DoorLockSensorLeftLocking_SHIFT              DoorLockSensorLeftLocking__SHIFT
#define DoorLockSensorLeftLocking_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorLockSensorLeftLocking_SetInterruptMode() function.
     *  @{
     */
        #define DoorLockSensorLeftLocking_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DoorLockSensorLeftLocking_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DoorLockSensorLeftLocking_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DoorLockSensorLeftLocking_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DoorLockSensorLeftLocking__SIO)
    #define DoorLockSensorLeftLocking_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DoorLockSensorLeftLocking__PC) && (CY_PSOC4_4200L)
    #define DoorLockSensorLeftLocking_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DoorLockSensorLeftLocking_USBIO_DISABLE              ((uint32)(~DoorLockSensorLeftLocking_USBIO_ENABLE))
    #define DoorLockSensorLeftLocking_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DoorLockSensorLeftLocking_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DoorLockSensorLeftLocking_USBIO_ENTER_SLEEP          ((uint32)((1u << DoorLockSensorLeftLocking_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DoorLockSensorLeftLocking_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLockSensorLeftLocking_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DoorLockSensorLeftLocking_USBIO_SUSPEND_SHIFT)))
    #define DoorLockSensorLeftLocking_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DoorLockSensorLeftLocking_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLockSensorLeftLocking_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DoorLockSensorLeftLocking__PC)
    /* Port Configuration */
    #define DoorLockSensorLeftLocking_PC                 (* (reg32 *) DoorLockSensorLeftLocking__PC)
#endif
/* Pin State */
#define DoorLockSensorLeftLocking_PS                     (* (reg32 *) DoorLockSensorLeftLocking__PS)
/* Data Register */
#define DoorLockSensorLeftLocking_DR                     (* (reg32 *) DoorLockSensorLeftLocking__DR)
/* Input Buffer Disable Override */
#define DoorLockSensorLeftLocking_INP_DIS                (* (reg32 *) DoorLockSensorLeftLocking__PC2)

/* Interrupt configuration Registers */
#define DoorLockSensorLeftLocking_INTCFG                 (* (reg32 *) DoorLockSensorLeftLocking__INTCFG)
#define DoorLockSensorLeftLocking_INTSTAT                (* (reg32 *) DoorLockSensorLeftLocking__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DoorLockSensorLeftLocking_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DoorLockSensorLeftLocking__SIO)
    #define DoorLockSensorLeftLocking_SIO_REG            (* (reg32 *) DoorLockSensorLeftLocking__SIO)
#endif /* (DoorLockSensorLeftLocking__SIO_CFG) */

/* USBIO registers */
#if !defined(DoorLockSensorLeftLocking__PC) && (CY_PSOC4_4200L)
    #define DoorLockSensorLeftLocking_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DoorLockSensorLeftLocking_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DoorLockSensorLeftLocking_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DoorLockSensorLeftLocking_DRIVE_MODE_SHIFT       (0x00u)
#define DoorLockSensorLeftLocking_DRIVE_MODE_MASK        (0x07u << DoorLockSensorLeftLocking_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DoorLockSensorLeftLocking_H */


/* [] END OF FILE */
