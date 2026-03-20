/*******************************************************************************
* File Name: MM_DEN.h  
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

#if !defined(CY_PINS_MM_DEN_H) /* Pins MM_DEN_H */
#define CY_PINS_MM_DEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "MM_DEN_aliases.h"


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
} MM_DEN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   MM_DEN_Read(void);
void    MM_DEN_Write(uint8 value);
uint8   MM_DEN_ReadDataReg(void);
#if defined(MM_DEN__PC) || (CY_PSOC4_4200L) 
    void    MM_DEN_SetDriveMode(uint8 mode);
#endif
void    MM_DEN_SetInterruptMode(uint16 position, uint16 mode);
uint8   MM_DEN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void MM_DEN_Sleep(void); 
void MM_DEN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(MM_DEN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define MM_DEN_DRIVE_MODE_BITS        (3)
    #define MM_DEN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - MM_DEN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the MM_DEN_SetDriveMode() function.
         *  @{
         */
        #define MM_DEN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define MM_DEN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define MM_DEN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define MM_DEN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define MM_DEN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define MM_DEN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define MM_DEN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define MM_DEN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define MM_DEN_MASK               MM_DEN__MASK
#define MM_DEN_SHIFT              MM_DEN__SHIFT
#define MM_DEN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in MM_DEN_SetInterruptMode() function.
     *  @{
     */
        #define MM_DEN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define MM_DEN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define MM_DEN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define MM_DEN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(MM_DEN__SIO)
    #define MM_DEN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(MM_DEN__PC) && (CY_PSOC4_4200L)
    #define MM_DEN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define MM_DEN_USBIO_DISABLE              ((uint32)(~MM_DEN_USBIO_ENABLE))
    #define MM_DEN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define MM_DEN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define MM_DEN_USBIO_ENTER_SLEEP          ((uint32)((1u << MM_DEN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << MM_DEN_USBIO_SUSPEND_DEL_SHIFT)))
    #define MM_DEN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << MM_DEN_USBIO_SUSPEND_SHIFT)))
    #define MM_DEN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << MM_DEN_USBIO_SUSPEND_DEL_SHIFT)))
    #define MM_DEN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(MM_DEN__PC)
    /* Port Configuration */
    #define MM_DEN_PC                 (* (reg32 *) MM_DEN__PC)
#endif
/* Pin State */
#define MM_DEN_PS                     (* (reg32 *) MM_DEN__PS)
/* Data Register */
#define MM_DEN_DR                     (* (reg32 *) MM_DEN__DR)
/* Input Buffer Disable Override */
#define MM_DEN_INP_DIS                (* (reg32 *) MM_DEN__PC2)

/* Interrupt configuration Registers */
#define MM_DEN_INTCFG                 (* (reg32 *) MM_DEN__INTCFG)
#define MM_DEN_INTSTAT                (* (reg32 *) MM_DEN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define MM_DEN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(MM_DEN__SIO)
    #define MM_DEN_SIO_REG            (* (reg32 *) MM_DEN__SIO)
#endif /* (MM_DEN__SIO_CFG) */

/* USBIO registers */
#if !defined(MM_DEN__PC) && (CY_PSOC4_4200L)
    #define MM_DEN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define MM_DEN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define MM_DEN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define MM_DEN_DRIVE_MODE_SHIFT       (0x00u)
#define MM_DEN_DRIVE_MODE_MASK        (0x07u << MM_DEN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins MM_DEN_H */


/* [] END OF FILE */
