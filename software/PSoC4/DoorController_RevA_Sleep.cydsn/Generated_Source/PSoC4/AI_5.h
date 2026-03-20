/*******************************************************************************
* File Name: AI_5.h  
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

#if !defined(CY_PINS_AI_5_H) /* Pins AI_5_H */
#define CY_PINS_AI_5_H

#include "cytypes.h"
#include "cyfitter.h"
#include "AI_5_aliases.h"


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
} AI_5_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   AI_5_Read(void);
void    AI_5_Write(uint8 value);
uint8   AI_5_ReadDataReg(void);
#if defined(AI_5__PC) || (CY_PSOC4_4200L) 
    void    AI_5_SetDriveMode(uint8 mode);
#endif
void    AI_5_SetInterruptMode(uint16 position, uint16 mode);
uint8   AI_5_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void AI_5_Sleep(void); 
void AI_5_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(AI_5__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define AI_5_DRIVE_MODE_BITS        (3)
    #define AI_5_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - AI_5_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the AI_5_SetDriveMode() function.
         *  @{
         */
        #define AI_5_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define AI_5_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define AI_5_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define AI_5_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define AI_5_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define AI_5_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define AI_5_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define AI_5_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define AI_5_MASK               AI_5__MASK
#define AI_5_SHIFT              AI_5__SHIFT
#define AI_5_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in AI_5_SetInterruptMode() function.
     *  @{
     */
        #define AI_5_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define AI_5_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define AI_5_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define AI_5_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(AI_5__SIO)
    #define AI_5_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(AI_5__PC) && (CY_PSOC4_4200L)
    #define AI_5_USBIO_ENABLE               ((uint32)0x80000000u)
    #define AI_5_USBIO_DISABLE              ((uint32)(~AI_5_USBIO_ENABLE))
    #define AI_5_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define AI_5_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define AI_5_USBIO_ENTER_SLEEP          ((uint32)((1u << AI_5_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << AI_5_USBIO_SUSPEND_DEL_SHIFT)))
    #define AI_5_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << AI_5_USBIO_SUSPEND_SHIFT)))
    #define AI_5_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << AI_5_USBIO_SUSPEND_DEL_SHIFT)))
    #define AI_5_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(AI_5__PC)
    /* Port Configuration */
    #define AI_5_PC                 (* (reg32 *) AI_5__PC)
#endif
/* Pin State */
#define AI_5_PS                     (* (reg32 *) AI_5__PS)
/* Data Register */
#define AI_5_DR                     (* (reg32 *) AI_5__DR)
/* Input Buffer Disable Override */
#define AI_5_INP_DIS                (* (reg32 *) AI_5__PC2)

/* Interrupt configuration Registers */
#define AI_5_INTCFG                 (* (reg32 *) AI_5__INTCFG)
#define AI_5_INTSTAT                (* (reg32 *) AI_5__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define AI_5_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(AI_5__SIO)
    #define AI_5_SIO_REG            (* (reg32 *) AI_5__SIO)
#endif /* (AI_5__SIO_CFG) */

/* USBIO registers */
#if !defined(AI_5__PC) && (CY_PSOC4_4200L)
    #define AI_5_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define AI_5_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define AI_5_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define AI_5_DRIVE_MODE_SHIFT       (0x00u)
#define AI_5_DRIVE_MODE_MASK        (0x07u << AI_5_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins AI_5_H */


/* [] END OF FILE */
