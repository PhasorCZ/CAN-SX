/*******************************************************************************
* File Name: HB_2_DEN.h  
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

#if !defined(CY_PINS_HB_2_DEN_H) /* Pins HB_2_DEN_H */
#define CY_PINS_HB_2_DEN_H

#include "cytypes.h"
#include "cyfitter.h"
#include "HB_2_DEN_aliases.h"


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
} HB_2_DEN_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   HB_2_DEN_Read(void);
void    HB_2_DEN_Write(uint8 value);
uint8   HB_2_DEN_ReadDataReg(void);
#if defined(HB_2_DEN__PC) || (CY_PSOC4_4200L) 
    void    HB_2_DEN_SetDriveMode(uint8 mode);
#endif
void    HB_2_DEN_SetInterruptMode(uint16 position, uint16 mode);
uint8   HB_2_DEN_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void HB_2_DEN_Sleep(void); 
void HB_2_DEN_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(HB_2_DEN__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define HB_2_DEN_DRIVE_MODE_BITS        (3)
    #define HB_2_DEN_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - HB_2_DEN_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the HB_2_DEN_SetDriveMode() function.
         *  @{
         */
        #define HB_2_DEN_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define HB_2_DEN_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define HB_2_DEN_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define HB_2_DEN_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define HB_2_DEN_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define HB_2_DEN_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define HB_2_DEN_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define HB_2_DEN_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define HB_2_DEN_MASK               HB_2_DEN__MASK
#define HB_2_DEN_SHIFT              HB_2_DEN__SHIFT
#define HB_2_DEN_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in HB_2_DEN_SetInterruptMode() function.
     *  @{
     */
        #define HB_2_DEN_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define HB_2_DEN_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define HB_2_DEN_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define HB_2_DEN_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(HB_2_DEN__SIO)
    #define HB_2_DEN_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(HB_2_DEN__PC) && (CY_PSOC4_4200L)
    #define HB_2_DEN_USBIO_ENABLE               ((uint32)0x80000000u)
    #define HB_2_DEN_USBIO_DISABLE              ((uint32)(~HB_2_DEN_USBIO_ENABLE))
    #define HB_2_DEN_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define HB_2_DEN_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define HB_2_DEN_USBIO_ENTER_SLEEP          ((uint32)((1u << HB_2_DEN_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << HB_2_DEN_USBIO_SUSPEND_DEL_SHIFT)))
    #define HB_2_DEN_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << HB_2_DEN_USBIO_SUSPEND_SHIFT)))
    #define HB_2_DEN_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << HB_2_DEN_USBIO_SUSPEND_DEL_SHIFT)))
    #define HB_2_DEN_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(HB_2_DEN__PC)
    /* Port Configuration */
    #define HB_2_DEN_PC                 (* (reg32 *) HB_2_DEN__PC)
#endif
/* Pin State */
#define HB_2_DEN_PS                     (* (reg32 *) HB_2_DEN__PS)
/* Data Register */
#define HB_2_DEN_DR                     (* (reg32 *) HB_2_DEN__DR)
/* Input Buffer Disable Override */
#define HB_2_DEN_INP_DIS                (* (reg32 *) HB_2_DEN__PC2)

/* Interrupt configuration Registers */
#define HB_2_DEN_INTCFG                 (* (reg32 *) HB_2_DEN__INTCFG)
#define HB_2_DEN_INTSTAT                (* (reg32 *) HB_2_DEN__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define HB_2_DEN_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(HB_2_DEN__SIO)
    #define HB_2_DEN_SIO_REG            (* (reg32 *) HB_2_DEN__SIO)
#endif /* (HB_2_DEN__SIO_CFG) */

/* USBIO registers */
#if !defined(HB_2_DEN__PC) && (CY_PSOC4_4200L)
    #define HB_2_DEN_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define HB_2_DEN_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define HB_2_DEN_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define HB_2_DEN_DRIVE_MODE_SHIFT       (0x00u)
#define HB_2_DEN_DRIVE_MODE_MASK        (0x07u << HB_2_DEN_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins HB_2_DEN_H */


/* [] END OF FILE */
