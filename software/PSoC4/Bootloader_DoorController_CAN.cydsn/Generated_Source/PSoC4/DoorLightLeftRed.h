/*******************************************************************************
* File Name: DoorLightLeftRed.h  
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

#if !defined(CY_PINS_DoorLightLeftRed_H) /* Pins DoorLightLeftRed_H */
#define CY_PINS_DoorLightLeftRed_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DoorLightLeftRed_aliases.h"


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
} DoorLightLeftRed_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DoorLightLeftRed_Read(void);
void    DoorLightLeftRed_Write(uint8 value);
uint8   DoorLightLeftRed_ReadDataReg(void);
#if defined(DoorLightLeftRed__PC) || (CY_PSOC4_4200L) 
    void    DoorLightLeftRed_SetDriveMode(uint8 mode);
#endif
void    DoorLightLeftRed_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorLightLeftRed_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DoorLightLeftRed_Sleep(void); 
void DoorLightLeftRed_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DoorLightLeftRed__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DoorLightLeftRed_DRIVE_MODE_BITS        (3)
    #define DoorLightLeftRed_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DoorLightLeftRed_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DoorLightLeftRed_SetDriveMode() function.
         *  @{
         */
        #define DoorLightLeftRed_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DoorLightLeftRed_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DoorLightLeftRed_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DoorLightLeftRed_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DoorLightLeftRed_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DoorLightLeftRed_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DoorLightLeftRed_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DoorLightLeftRed_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DoorLightLeftRed_MASK               DoorLightLeftRed__MASK
#define DoorLightLeftRed_SHIFT              DoorLightLeftRed__SHIFT
#define DoorLightLeftRed_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorLightLeftRed_SetInterruptMode() function.
     *  @{
     */
        #define DoorLightLeftRed_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DoorLightLeftRed_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DoorLightLeftRed_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DoorLightLeftRed_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DoorLightLeftRed__SIO)
    #define DoorLightLeftRed_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DoorLightLeftRed__PC) && (CY_PSOC4_4200L)
    #define DoorLightLeftRed_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DoorLightLeftRed_USBIO_DISABLE              ((uint32)(~DoorLightLeftRed_USBIO_ENABLE))
    #define DoorLightLeftRed_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DoorLightLeftRed_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DoorLightLeftRed_USBIO_ENTER_SLEEP          ((uint32)((1u << DoorLightLeftRed_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DoorLightLeftRed_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLightLeftRed_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DoorLightLeftRed_USBIO_SUSPEND_SHIFT)))
    #define DoorLightLeftRed_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DoorLightLeftRed_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLightLeftRed_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DoorLightLeftRed__PC)
    /* Port Configuration */
    #define DoorLightLeftRed_PC                 (* (reg32 *) DoorLightLeftRed__PC)
#endif
/* Pin State */
#define DoorLightLeftRed_PS                     (* (reg32 *) DoorLightLeftRed__PS)
/* Data Register */
#define DoorLightLeftRed_DR                     (* (reg32 *) DoorLightLeftRed__DR)
/* Input Buffer Disable Override */
#define DoorLightLeftRed_INP_DIS                (* (reg32 *) DoorLightLeftRed__PC2)

/* Interrupt configuration Registers */
#define DoorLightLeftRed_INTCFG                 (* (reg32 *) DoorLightLeftRed__INTCFG)
#define DoorLightLeftRed_INTSTAT                (* (reg32 *) DoorLightLeftRed__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DoorLightLeftRed_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DoorLightLeftRed__SIO)
    #define DoorLightLeftRed_SIO_REG            (* (reg32 *) DoorLightLeftRed__SIO)
#endif /* (DoorLightLeftRed__SIO_CFG) */

/* USBIO registers */
#if !defined(DoorLightLeftRed__PC) && (CY_PSOC4_4200L)
    #define DoorLightLeftRed_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DoorLightLeftRed_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DoorLightLeftRed_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DoorLightLeftRed_DRIVE_MODE_SHIFT       (0x00u)
#define DoorLightLeftRed_DRIVE_MODE_MASK        (0x07u << DoorLightLeftRed_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DoorLightLeftRed_H */


/* [] END OF FILE */
