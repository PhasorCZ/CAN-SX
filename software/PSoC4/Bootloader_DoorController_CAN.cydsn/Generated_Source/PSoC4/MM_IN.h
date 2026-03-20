/*******************************************************************************
* File Name: MM_IN.h  
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

#if !defined(CY_PINS_MM_IN_H) /* Pins MM_IN_H */
#define CY_PINS_MM_IN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MM_IN_aliases.h"


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
} MM_IN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MM_IN_Read(void);
void    MM_IN_Write(uint8 value);
uint8   MM_IN_ReadDataReg(void);
#if defined(MM_IN__PC) || (CY_PSOC4_4200L) 
    void    MM_IN_SetDriveMode(uint8 mode);
#endif
void    MM_IN_SetInterruptMode(uint16 position, uint16 mode);
uint8   MM_IN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MM_IN_Sleep(void); 
void MM_IN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MM_IN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MM_IN_DRIVE_MODE_BITS        (3)
    #define MM_IN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MM_IN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MM_IN_SetDriveMode() function.
         *  @{
         */
        #define MM_IN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MM_IN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MM_IN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MM_IN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MM_IN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MM_IN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MM_IN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MM_IN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MM_IN_MASK               MM_IN__MASK
#define MM_IN_SHIFT              MM_IN__SHIFT
#define MM_IN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MM_IN_SetInterruptMode() function.
     *  @{
     */
        #define MM_IN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MM_IN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MM_IN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MM_IN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MM_IN__SIO)
    #define MM_IN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MM_IN__PC) && (CY_PSOC4_4200L)
    #define MM_IN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MM_IN_USBIO_DISABLE              ((uint32)(~MM_IN_USBIO_ENABLE))
    #define MM_IN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MM_IN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MM_IN_USBIO_ENTER_SLEEP          ((uint32)((1u << MM_IN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MM_IN_USBIO_SUSPEND_DEL_SHIFT)))
    #define MM_IN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MM_IN_USBIO_SUSPEND_SHIFT)))
    #define MM_IN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MM_IN_USBIO_SUSPEND_DEL_SHIFT)))
    #define MM_IN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MM_IN__PC)
    /* Port Configuration */
    #define MM_IN_PC                 (* (reg32 *) MM_IN__PC)
#endif
/* Pin State */
#define MM_IN_PS                     (* (reg32 *) MM_IN__PS)
/* Data Register */
#define MM_IN_DR                     (* (reg32 *) MM_IN__DR)
/* Input Buffer Disable Override */
#define MM_IN_INP_DIS                (* (reg32 *) MM_IN__PC2)

/* Interrupt configuration Registers */
#define MM_IN_INTCFG                 (* (reg32 *) MM_IN__INTCFG)
#define MM_IN_INTSTAT                (* (reg32 *) MM_IN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MM_IN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MM_IN__SIO)
    #define MM_IN_SIO_REG            (* (reg32 *) MM_IN__SIO)
#endif /* (MM_IN__SIO_CFG) */

/* USBIO registers */
#if !defined(MM_IN__PC) && (CY_PSOC4_4200L)
    #define MM_IN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MM_IN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MM_IN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MM_IN_DRIVE_MODE_SHIFT       (0x00u)
#define MM_IN_DRIVE_MODE_MASK        (0x07u << MM_IN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MM_IN_H */


/* [] END OF FILE */
