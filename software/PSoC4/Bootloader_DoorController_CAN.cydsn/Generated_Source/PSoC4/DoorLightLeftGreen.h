/*******************************************************************************
* File Name: DoorLightLeftGreen.h  
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

#if !defined(CY_PINS_DoorLightLeftGreen_H) /* Pins DoorLightLeftGreen_H */
#define CY_PINS_DoorLightLeftGreen_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DoorLightLeftGreen_aliases.h"


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
} DoorLightLeftGreen_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DoorLightLeftGreen_Read(void);
void    DoorLightLeftGreen_Write(uint8 value);
uint8   DoorLightLeftGreen_ReadDataReg(void);
#if defined(DoorLightLeftGreen__PC) || (CY_PSOC4_4200L) 
    void    DoorLightLeftGreen_SetDriveMode(uint8 mode);
#endif
void    DoorLightLeftGreen_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorLightLeftGreen_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DoorLightLeftGreen_Sleep(void); 
void DoorLightLeftGreen_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DoorLightLeftGreen__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DoorLightLeftGreen_DRIVE_MODE_BITS        (3)
    #define DoorLightLeftGreen_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DoorLightLeftGreen_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DoorLightLeftGreen_SetDriveMode() function.
         *  @{
         */
        #define DoorLightLeftGreen_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DoorLightLeftGreen_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DoorLightLeftGreen_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DoorLightLeftGreen_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DoorLightLeftGreen_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DoorLightLeftGreen_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DoorLightLeftGreen_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DoorLightLeftGreen_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DoorLightLeftGreen_MASK               DoorLightLeftGreen__MASK
#define DoorLightLeftGreen_SHIFT              DoorLightLeftGreen__SHIFT
#define DoorLightLeftGreen_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorLightLeftGreen_SetInterruptMode() function.
     *  @{
     */
        #define DoorLightLeftGreen_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DoorLightLeftGreen_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DoorLightLeftGreen_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DoorLightLeftGreen_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DoorLightLeftGreen__SIO)
    #define DoorLightLeftGreen_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DoorLightLeftGreen__PC) && (CY_PSOC4_4200L)
    #define DoorLightLeftGreen_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DoorLightLeftGreen_USBIO_DISABLE              ((uint32)(~DoorLightLeftGreen_USBIO_ENABLE))
    #define DoorLightLeftGreen_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DoorLightLeftGreen_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DoorLightLeftGreen_USBIO_ENTER_SLEEP          ((uint32)((1u << DoorLightLeftGreen_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DoorLightLeftGreen_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLightLeftGreen_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DoorLightLeftGreen_USBIO_SUSPEND_SHIFT)))
    #define DoorLightLeftGreen_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DoorLightLeftGreen_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLightLeftGreen_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DoorLightLeftGreen__PC)
    /* Port Configuration */
    #define DoorLightLeftGreen_PC                 (* (reg32 *) DoorLightLeftGreen__PC)
#endif
/* Pin State */
#define DoorLightLeftGreen_PS                     (* (reg32 *) DoorLightLeftGreen__PS)
/* Data Register */
#define DoorLightLeftGreen_DR                     (* (reg32 *) DoorLightLeftGreen__DR)
/* Input Buffer Disable Override */
#define DoorLightLeftGreen_INP_DIS                (* (reg32 *) DoorLightLeftGreen__PC2)

/* Interrupt configuration Registers */
#define DoorLightLeftGreen_INTCFG                 (* (reg32 *) DoorLightLeftGreen__INTCFG)
#define DoorLightLeftGreen_INTSTAT                (* (reg32 *) DoorLightLeftGreen__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DoorLightLeftGreen_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DoorLightLeftGreen__SIO)
    #define DoorLightLeftGreen_SIO_REG            (* (reg32 *) DoorLightLeftGreen__SIO)
#endif /* (DoorLightLeftGreen__SIO_CFG) */

/* USBIO registers */
#if !defined(DoorLightLeftGreen__PC) && (CY_PSOC4_4200L)
    #define DoorLightLeftGreen_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DoorLightLeftGreen_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DoorLightLeftGreen_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DoorLightLeftGreen_DRIVE_MODE_SHIFT       (0x00u)
#define DoorLightLeftGreen_DRIVE_MODE_MASK        (0x07u << DoorLightLeftGreen_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DoorLightLeftGreen_H */


/* [] END OF FILE */
