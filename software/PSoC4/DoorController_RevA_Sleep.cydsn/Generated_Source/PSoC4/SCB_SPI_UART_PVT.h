/***************************************************************************//**
* \file SCB_SPI_UART_PVT.h
* \version 4.0
*
* \brief
*  This private file provides constants and parameter values for the
*  SCB Component in SPI and UART modes.
*  Please do not use this file or its content in your project.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation. All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_SCB_SPI_UART_PVT_SCB_H)
#define CY_SCB_SPI_UART_PVT_SCB_H

#include "SCB_SPI_UART.h"


/***************************************
*     Internal Global Vars
***************************************/

#if (SCB_INTERNAL_RX_SW_BUFFER_CONST)
    extern volatile uint32  SCB_rxBufferHead;
    extern volatile uint32  SCB_rxBufferTail;
    
    /**
    * \addtogroup group_globals
    * @{
    */
    
    /** Sets when internal software receive buffer overflow
     *  was occurred.
    */  
    extern volatile uint8   SCB_rxBufferOverflow;
    /** @} globals */
#endif /* (SCB_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SCB_INTERNAL_TX_SW_BUFFER_CONST)
    extern volatile uint32  SCB_txBufferHead;
    extern volatile uint32  SCB_txBufferTail;
#endif /* (SCB_INTERNAL_TX_SW_BUFFER_CONST) */

#if (SCB_INTERNAL_RX_SW_BUFFER)
    extern volatile uint8 SCB_rxBufferInternal[SCB_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SCB_INTERNAL_RX_SW_BUFFER) */

#if (SCB_INTERNAL_TX_SW_BUFFER)
    extern volatile uint8 SCB_txBufferInternal[SCB_TX_BUFFER_SIZE];
#endif /* (SCB_INTERNAL_TX_SW_BUFFER) */


/***************************************
*     Private Function Prototypes
***************************************/

void SCB_SpiPostEnable(void);
void SCB_SpiStop(void);

#if (SCB_SCB_MODE_SPI_CONST_CFG)
    void SCB_SpiInit(void);
#endif /* (SCB_SCB_MODE_SPI_CONST_CFG) */

#if (SCB_SPI_WAKE_ENABLE_CONST)
    void SCB_SpiSaveConfig(void);
    void SCB_SpiRestoreConfig(void);
#endif /* (SCB_SPI_WAKE_ENABLE_CONST) */

void SCB_UartPostEnable(void);
void SCB_UartStop(void);

#if (SCB_SCB_MODE_UART_CONST_CFG)
    void SCB_UartInit(void);
#endif /* (SCB_SCB_MODE_UART_CONST_CFG) */

#if (SCB_UART_WAKE_ENABLE_CONST)
    void SCB_UartSaveConfig(void);
    void SCB_UartRestoreConfig(void);
#endif /* (SCB_UART_WAKE_ENABLE_CONST) */


/***************************************
*         UART API Constants
***************************************/

/* UART RX and TX position to be used in SCB_SetPins() */
#define SCB_UART_RX_PIN_ENABLE    (SCB_UART_RX)
#define SCB_UART_TX_PIN_ENABLE    (SCB_UART_TX)

/* UART RTS and CTS position to be used in  SCB_SetPins() */
#define SCB_UART_RTS_PIN_ENABLE    (0x10u)
#define SCB_UART_CTS_PIN_ENABLE    (0x20u)


/***************************************
* The following code is DEPRECATED and
* must not be used.
***************************************/

/* Interrupt processing */
#define SCB_SpiUartEnableIntRx(intSourceMask)  SCB_SetRxInterruptMode(intSourceMask)
#define SCB_SpiUartEnableIntTx(intSourceMask)  SCB_SetTxInterruptMode(intSourceMask)
uint32  SCB_SpiUartDisableIntRx(void);
uint32  SCB_SpiUartDisableIntTx(void);


#endif /* (CY_SCB_SPI_UART_PVT_SCB_H) */


/* [] END OF FILE */
