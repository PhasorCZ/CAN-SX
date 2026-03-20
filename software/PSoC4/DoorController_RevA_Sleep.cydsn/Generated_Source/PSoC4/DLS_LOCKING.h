/*******************************************************************************
* File Name: DLS_LOCKING.h  
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

#if !defined(CY_PINS_DLS_LOCKING_H) /* Pins DLS_LOCKING_H */
#define CY_PINS_DLS_LOCKING_H

#include "cytypes.h"
#include "cyfitter.h"
#include "DLS_LOCKING_aliases.h"


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
} DLS_LOCKING_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   DLS_LOCKING_Read(void);
void    DLS_LOCKING_Write(uint8 value);
uint8   DLS_LOCKING_ReadDataReg(void);
#if defined(DLS_LOCKING__PC) || (CY_PSOC4_4200L) 
    void    DLS_LOCKING_SetDriveMode(uint8 mode);
#endif
void    DLS_LOCKING_SetInterruptMode(uint16 position, uint16 mode);
uint8   DLS_LOCKING_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void DLS_LOCKING_Sleep(void); 
void DLS_LOCKING_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(DLS_LOCKING__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define DLS_LOCKING_DRIVE_MODE_BITS        (3)
    #define DLS_LOCKING_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - DLS_LOCKING_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the DLS_LOCKING_SetDriveMode() function.
         *  @{
         */
        #define DLS_LOCKING_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define DLS_LOCKING_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define DLS_LOCKING_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define DLS_LOCKING_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define DLS_LOCKING_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define DLS_LOCKING_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define DLS_LOCKING_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define DLS_LOCKING_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define DLS_LOCKING_MASK               DLS_LOCKING__MASK
#define DLS_LOCKING_SHIFT              DLS_LOCKING__SHIFT
#define DLS_LOCKING_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in DLS_LOCKING_SetInterruptMode() function.
     *  @{
     */
        #define DLS_LOCKING_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define DLS_LOCKING_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define DLS_LOCKING_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define DLS_LOCKING_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(DLS_LOCKING__SIO)
    #define DLS_LOCKING_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(DLS_LOCKING__PC) && (CY_PSOC4_4200L)
    #define DLS_LOCKING_USBIO_ENABLE               ((uint32)0x80000000u)
    #define DLS_LOCKING_USBIO_DISABLE              ((uint32)(~DLS_LOCKING_USBIO_ENABLE))
    #define DLS_LOCKING_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define DLS_LOCKING_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define DLS_LOCKING_USBIO_ENTER_SLEEP          ((uint32)((1u << DLS_LOCKING_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << DLS_LOCKING_USBIO_SUSPEND_DEL_SHIFT)))
    #define DLS_LOCKING_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << DLS_LOCKING_USBIO_SUSPEND_SHIFT)))
    #define DLS_LOCKING_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << DLS_LOCKING_USBIO_SUSPEND_DEL_SHIFT)))
    #define DLS_LOCKING_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(DLS_LOCKING__PC)
    /* Port Configuration */
    #define DLS_LOCKING_PC                 (* (reg32 *) DLS_LOCKING__PC)
#endif
/* Pin State */
#define DLS_LOCKING_PS                     (* (reg32 *) DLS_LOCKING__PS)
/* Data Register */
#define DLS_LOCKING_DR                     (* (reg32 *) DLS_LOCKING__DR)
/* Input Buffer Disable Override */
#define DLS_LOCKING_INP_DIS                (* (reg32 *) DLS_LOCKING__PC2)

/* Interrupt configuration Registers */
#define DLS_LOCKING_INTCFG                 (* (reg32 *) DLS_LOCKING__INTCFG)
#define DLS_LOCKING_INTSTAT                (* (reg32 *) DLS_LOCKING__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define DLS_LOCKING_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(DLS_LOCKING__SIO)
    #define DLS_LOCKING_SIO_REG            (* (reg32 *) DLS_LOCKING__SIO)
#endif /* (DLS_LOCKING__SIO_CFG) */

/* USBIO registers */
#if !defined(DLS_LOCKING__PC) && (CY_PSOC4_4200L)
    #define DLS_LOCKING_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define DLS_LOCKING_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define DLS_LOCKING_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define DLS_LOCKING_DRIVE_MODE_SHIFT       (0x00u)
#define DLS_LOCKING_DRIVE_MODE_MASK        (0x07u << DLS_LOCKING_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins DLS_LOCKING_H */


/* [] END OF FILE */
