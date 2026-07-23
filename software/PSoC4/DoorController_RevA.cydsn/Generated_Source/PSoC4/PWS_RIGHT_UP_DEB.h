/*******************************************************************************
* File Name: PWS_RIGHT_UP_DEB.h  
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

#if !defined(CY_PINS_PWS_RIGHT_UP_DEB_H) /* Pins PWS_RIGHT_UP_DEB_H */
#define CY_PINS_PWS_RIGHT_UP_DEB_H

#include "cytypes.h"
#include "cyfitter.h"
#include "PWS_RIGHT_UP_DEB_aliases.h"


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
} PWS_RIGHT_UP_DEB_BACKUP_STRUCT;

/** @} structures */


/***************************************
*        Function Prototypes             
***************************************/
/**
* \addtogroup group_general
* @{
*/
uint8   PWS_RIGHT_UP_DEB_Read(void);
void    PWS_RIGHT_UP_DEB_Write(uint8 value);
uint8   PWS_RIGHT_UP_DEB_ReadDataReg(void);
#if defined(PWS_RIGHT_UP_DEB__PC) || (CY_PSOC4_4200L) 
    void    PWS_RIGHT_UP_DEB_SetDriveMode(uint8 mode);
#endif
void    PWS_RIGHT_UP_DEB_SetInterruptMode(uint16 position, uint16 mode);
uint8   PWS_RIGHT_UP_DEB_ClearInterrupt(void);
/** @} general */

/**
* \addtogroup group_power
* @{
*/
void PWS_RIGHT_UP_DEB_Sleep(void); 
void PWS_RIGHT_UP_DEB_Wakeup(void);
/** @} power */


/***************************************
*           API Constants        
***************************************/
#if defined(PWS_RIGHT_UP_DEB__PC) || (CY_PSOC4_4200L) 
    /* Drive Modes */
    #define PWS_RIGHT_UP_DEB_DRIVE_MODE_BITS        (3)
    #define PWS_RIGHT_UP_DEB_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - PWS_RIGHT_UP_DEB_DRIVE_MODE_BITS))

    /**
    * \addtogroup group_constants
    * @{
    */
        /** \addtogroup driveMode Drive mode constants
         * \brief Constants to be passed as "mode" parameter in the PWS_RIGHT_UP_DEB_SetDriveMode() function.
         *  @{
         */
        #define PWS_RIGHT_UP_DEB_DM_ALG_HIZ         (0x00u) /**< \brief High Impedance Analog   */
        #define PWS_RIGHT_UP_DEB_DM_DIG_HIZ         (0x01u) /**< \brief High Impedance Digital  */
        #define PWS_RIGHT_UP_DEB_DM_RES_UP          (0x02u) /**< \brief Resistive Pull Up       */
        #define PWS_RIGHT_UP_DEB_DM_RES_DWN         (0x03u) /**< \brief Resistive Pull Down     */
        #define PWS_RIGHT_UP_DEB_DM_OD_LO           (0x04u) /**< \brief Open Drain, Drives Low  */
        #define PWS_RIGHT_UP_DEB_DM_OD_HI           (0x05u) /**< \brief Open Drain, Drives High */
        #define PWS_RIGHT_UP_DEB_DM_STRONG          (0x06u) /**< \brief Strong Drive            */
        #define PWS_RIGHT_UP_DEB_DM_RES_UPDWN       (0x07u) /**< \brief Resistive Pull Up/Down  */
        /** @} driveMode */
    /** @} group_constants */
#endif

/* Digital Port Constants */
#define PWS_RIGHT_UP_DEB_MASK               PWS_RIGHT_UP_DEB__MASK
#define PWS_RIGHT_UP_DEB_SHIFT              PWS_RIGHT_UP_DEB__SHIFT
#define PWS_RIGHT_UP_DEB_WIDTH              1u

/**
* \addtogroup group_constants
* @{
*/
    /** \addtogroup intrMode Interrupt constants
     * \brief Constants to be passed as "mode" parameter in PWS_RIGHT_UP_DEB_SetInterruptMode() function.
     *  @{
     */
        #define PWS_RIGHT_UP_DEB_INTR_NONE      ((uint16)(0x0000u)) /**< \brief Disabled             */
        #define PWS_RIGHT_UP_DEB_INTR_RISING    ((uint16)(0x5555u)) /**< \brief Rising edge trigger  */
        #define PWS_RIGHT_UP_DEB_INTR_FALLING   ((uint16)(0xaaaau)) /**< \brief Falling edge trigger */
        #define PWS_RIGHT_UP_DEB_INTR_BOTH      ((uint16)(0xffffu)) /**< \brief Both edge trigger    */
    /** @} intrMode */
/** @} group_constants */

/* SIO LPM definition */
#if defined(PWS_RIGHT_UP_DEB__SIO)
    #define PWS_RIGHT_UP_DEB_SIO_LPM_MASK       (0x03u)
#endif

/* USBIO definitions */
#if !defined(PWS_RIGHT_UP_DEB__PC) && (CY_PSOC4_4200L)
    #define PWS_RIGHT_UP_DEB_USBIO_ENABLE               ((uint32)0x80000000u)
    #define PWS_RIGHT_UP_DEB_USBIO_DISABLE              ((uint32)(~PWS_RIGHT_UP_DEB_USBIO_ENABLE))
    #define PWS_RIGHT_UP_DEB_USBIO_SUSPEND_SHIFT        CYFLD_USBDEVv2_USB_SUSPEND__OFFSET
    #define PWS_RIGHT_UP_DEB_USBIO_SUSPEND_DEL_SHIFT    CYFLD_USBDEVv2_USB_SUSPEND_DEL__OFFSET
    #define PWS_RIGHT_UP_DEB_USBIO_ENTER_SLEEP          ((uint32)((1u << PWS_RIGHT_UP_DEB_USBIO_SUSPEND_SHIFT) \
                                                        | (1u << PWS_RIGHT_UP_DEB_USBIO_SUSPEND_DEL_SHIFT)))
    #define PWS_RIGHT_UP_DEB_USBIO_EXIT_SLEEP_PH1       ((uint32)~((uint32)(1u << PWS_RIGHT_UP_DEB_USBIO_SUSPEND_SHIFT)))
    #define PWS_RIGHT_UP_DEB_USBIO_EXIT_SLEEP_PH2       ((uint32)~((uint32)(1u << PWS_RIGHT_UP_DEB_USBIO_SUSPEND_DEL_SHIFT)))
    #define PWS_RIGHT_UP_DEB_USBIO_CR1_OFF              ((uint32)0xfffffffeu)
#endif


/***************************************
*             Registers        
***************************************/
/* Main Port Registers */
#if defined(PWS_RIGHT_UP_DEB__PC)
    /* Port Configuration */
    #define PWS_RIGHT_UP_DEB_PC                 (* (reg32 *) PWS_RIGHT_UP_DEB__PC)
#endif
/* Pin State */
#define PWS_RIGHT_UP_DEB_PS                     (* (reg32 *) PWS_RIGHT_UP_DEB__PS)
/* Data Register */
#define PWS_RIGHT_UP_DEB_DR                     (* (reg32 *) PWS_RIGHT_UP_DEB__DR)
/* Input Buffer Disable Override */
#define PWS_RIGHT_UP_DEB_INP_DIS                (* (reg32 *) PWS_RIGHT_UP_DEB__PC2)

/* Interrupt configuration Registers */
#define PWS_RIGHT_UP_DEB_INTCFG                 (* (reg32 *) PWS_RIGHT_UP_DEB__INTCFG)
#define PWS_RIGHT_UP_DEB_INTSTAT                (* (reg32 *) PWS_RIGHT_UP_DEB__INTSTAT)

/* "Interrupt cause" register for Combined Port Interrupt (AllPortInt) in GSRef component */
#if defined (CYREG_GPIO_INTR_CAUSE)
    #define PWS_RIGHT_UP_DEB_INTR_CAUSE         (* (reg32 *) CYREG_GPIO_INTR_CAUSE)
#endif

/* SIO register */
#if defined(PWS_RIGHT_UP_DEB__SIO)
    #define PWS_RIGHT_UP_DEB_SIO_REG            (* (reg32 *) PWS_RIGHT_UP_DEB__SIO)
#endif /* (PWS_RIGHT_UP_DEB__SIO_CFG) */

/* USBIO registers */
#if !defined(PWS_RIGHT_UP_DEB__PC) && (CY_PSOC4_4200L)
    #define PWS_RIGHT_UP_DEB_USB_POWER_REG       (* (reg32 *) CYREG_USBDEVv2_USB_POWER_CTRL)
    #define PWS_RIGHT_UP_DEB_CR1_REG             (* (reg32 *) CYREG_USBDEVv2_CR1)
    #define PWS_RIGHT_UP_DEB_USBIO_CTRL_REG      (* (reg32 *) CYREG_USBDEVv2_USB_USBIO_CTRL)
#endif    
    
    
/***************************************
* The following code is DEPRECATED and 
* must not be used in new designs.
***************************************/
/**
* \addtogroup group_deprecated
* @{
*/
#define PWS_RIGHT_UP_DEB_DRIVE_MODE_SHIFT       (0x00u)
#define PWS_RIGHT_UP_DEB_DRIVE_MODE_MASK        (0x07u << PWS_RIGHT_UP_DEB_DRIVE_MODE_SHIFT)
/** @} deprecated */

#endif /* End Pins PWS_RIGHT_UP_DEB_H */


/* [] END OF FILE */
