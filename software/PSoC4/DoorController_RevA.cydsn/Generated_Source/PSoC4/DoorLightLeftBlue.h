/*******************************************************************************
* File Name: DoorLightLeftBlue.h  
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

#if !defined(CY_PINS_DoorLightLeftBlue_H) /* Pins DoorLightLeftBlue_H */
#define CY_PINS_DoorLightLeftBlue_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DoorLightLeftBlue_aliases.h"


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
} DoorLightLeftBlue_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DoorLightLeftBlue_Read(void);
void    DoorLightLeftBlue_Write(uint8 value);
uint8   DoorLightLeftBlue_ReadDataReg(void);
#if defined(DoorLightLeftBlue__PC) || (CY_PSOC4_4200L) 
    void    DoorLightLeftBlue_SetDriveMode(uint8 mode);
#endif
void    DoorLightLeftBlue_SetInterruptMode(uint16 position, uint16 mode);
uint8   DoorLightLeftBlue_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DoorLightLeftBlue_Sleep(void); 
void DoorLightLeftBlue_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DoorLightLeftBlue__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DoorLightLeftBlue_DRIVE_MODE_BITS        (3)
    #define DoorLightLeftBlue_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DoorLightLeftBlue_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DoorLightLeftBlue_SetDriveMode() function.
         *  @{
         */
        #define DoorLightLeftBlue_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DoorLightLeftBlue_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DoorLightLeftBlue_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DoorLightLeftBlue_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DoorLightLeftBlue_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DoorLightLeftBlue_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DoorLightLeftBlue_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DoorLightLeftBlue_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DoorLightLeftBlue_MASK               DoorLightLeftBlue__MASK
#define DoorLightLeftBlue_SHIFT              DoorLightLeftBlue__SHIFT
#define DoorLightLeftBlue_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DoorLightLeftBlue_SetInterruptMode() function.
     *  @{
     */
        #define DoorLightLeftBlue_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DoorLightLeftBlue_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DoorLightLeftBlue_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DoorLightLeftBlue_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DoorLightLeftBlue__SIO)
    #define DoorLightLeftBlue_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DoorLightLeftBlue__PC) && (CY_PSOC4_4200L)
    #define DoorLightLeftBlue_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DoorLightLeftBlue_USBIO_DISABLE              ((uint32)(~DoorLightLeftBlue_USBIO_ENABLE))
    #define DoorLightLeftBlue_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DoorLightLeftBlue_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DoorLightLeftBlue_USBIO_ENTER_SLEEP          ((uint32)((1u << DoorLightLeftBlue_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DoorLightLeftBlue_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLightLeftBlue_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DoorLightLeftBlue_USBIO_SUSPEND_SHIFT)))
    #define DoorLightLeftBlue_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DoorLightLeftBlue_USBIO_SUSPEND_DEL_SHIFT)))
    #define DoorLightLeftBlue_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DoorLightLeftBlue__PC)
    /* Port Configuration */
    #define DoorLightLeftBlue_PC                 (* (reg32 *) DoorLightLeftBlue__PC)
#endif
/* Pin State */
#define DoorLightLeftBlue_PS                     (* (reg32 *) DoorLightLeftBlue__PS)
/* Data Register */
#define DoorLightLeftBlue_DR                     (* (reg32 *) DoorLightLeftBlue__DR)
/* Input Buffer Disable Override */
#define DoorLightLeftBlue_INP_DIS                (* (reg32 *) DoorLightLeftBlue__PC2)

/* Interrupt configuration Registers */
#define DoorLightLeftBlue_INTCFG                 (* (reg32 *) DoorLightLeftBlue__INTCFG)
#define DoorLightLeftBlue_INTSTAT                (* (reg32 *) DoorLightLeftBlue__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DoorLightLeftBlue_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DoorLightLeftBlue__SIO)
    #define DoorLightLeftBlue_SIO_REG            (* (reg32 *) DoorLightLeftBlue__SIO)
#endif /* (DoorLightLeftBlue__SIO_CFG) */

/* USBIO registers */
#if !defined(DoorLightLeftBlue__PC) && (CY_PSOC4_4200L)
    #define DoorLightLeftBlue_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DoorLightLeftBlue_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DoorLightLeftBlue_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DoorLightLeftBlue_DRIVE_MODE_SHIFT       (0x00u)
#define DoorLightLeftBlue_DRIVE_MODE_MASK        (0x07u << DoorLightLeftBlue_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DoorLightLeftBlue_H */


/* [] END OF FILE */
