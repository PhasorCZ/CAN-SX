/***************************************************************************//**
* \file SCB_SPI_UART_INT.c
* \version 4.0
*
* \brief
*  This file provides the source code to the Interrupt Service Routine for
*  the SCB Component in SPI and UART modes.
*
* Note:
*
********************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB_PVT.h"
#include "SCB_SPI_UART_PVT.h"
#include "cyapicallbacks.h"

#if (SCB_SCB_IRQ_INTERNAL)
/*******************************************************************************
* Function Name: SCB_SPI_UART_ISR
****************************************************************************//**
*
*  Handles the Interrupt Service Routine for the SCB SPI or UART modes.
*
*******************************************************************************/
CY_ISR(SCB_SPI_UART_ISR)
{
#if (SCB_INTERNAL_RX_SW_BUFFER_CONST)
    uint32 locHead;
#endif /* (SCB_INTERNAL_RX_SW_BUFFER_CONST) */

#if (SCB_INTERNAL_TX_SW_BUFFER_CONST)
    uint32 locTail;
#endif /* (SCB_INTERNAL_TX_SW_BUFFER_CONST) */

#ifdef SCB_SPI_UART_ISR_ENTRY_CALLBACK
    SCB_SPI_UART_ISR_EntryCallback();
#endif /* SCB_SPI_UART_ISR_ENTRY_CALLBACK */

    if (NULL != SCB_customIntrHandler)
    {
        SCB_customIntrHandler();
    }

    #if(SCB_CHECK_SPI_WAKE_ENABLE)
    {
        /* Clear SPI wakeup source */
        SCB_ClearSpiExtClkInterruptSource(SCB_INTR_SPI_EC_WAKE_UP);
    }
    #endif

    #if (SCB_CHECK_RX_SW_BUFFER)
    {
        if (SCB_CHECK_INTR_RX_MASKED(SCB_INTR_RX_NOT_EMPTY))
        {
            do
            {
                /* Move local head index */
                locHead = (SCB_rxBufferHead + 1u);

                /* Adjust local head index */
                if (SCB_INTERNAL_RX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                if (locHead == SCB_rxBufferTail)
                {
                    #if (SCB_CHECK_UART_RTS_CONTROL_FLOW)
                    {
                        /* There is no space in the software buffer - disable the
                        * RX Not Empty interrupt source. The data elements are
                        * still being received into the RX FIFO until the RTS signal
                        * stops the transmitter. After the data element is read from the
                        * buffer, the RX Not Empty interrupt source is enabled to
                        * move the next data element in the software buffer.
                        */
                        SCB_INTR_RX_MASK_REG &= ~SCB_INTR_RX_NOT_EMPTY;
                        break;
                    }
                    #else
                    {
                        /* Overflow: through away received data element */
                        (void) SCB_RX_FIFO_RD_REG;
                        SCB_rxBufferOverflow = (uint8) SCB_INTR_RX_OVERFLOW;
                    }
                    #endif
                }
                else
                {
                    /* Store received data */
                    SCB_PutWordInRxBuffer(locHead, SCB_RX_FIFO_RD_REG);

                    /* Move head index */
                    SCB_rxBufferHead = locHead;
                }
            }
            while(0u != SCB_GET_RX_FIFO_ENTRIES);

            SCB_ClearRxInterruptSource(SCB_INTR_RX_NOT_EMPTY);
        }
    }
    #endif


    #if (SCB_CHECK_TX_SW_BUFFER)
    {
        if (SCB_CHECK_INTR_TX_MASKED(SCB_INTR_TX_NOT_FULL))
        {
            do
            {
                /* Check for room in TX software buffer */
                if (SCB_txBufferHead != SCB_txBufferTail)
                {
                    /* Move local tail index */
                    locTail = (SCB_txBufferTail + 1u);

                    /* Adjust local tail index */
                    if (SCB_TX_BUFFER_SIZE == locTail)
                    {
                        locTail = 0u;
                    }

                    /* Put data into TX FIFO */
                    SCB_TX_FIFO_WR_REG = SCB_GetWordFromTxBuffer(locTail);

                    /* Move tail index */
                    SCB_txBufferTail = locTail;
                }
                else
                {
                    /* TX software buffer is empty: complete transfer */
                    SCB_DISABLE_INTR_TX(SCB_INTR_TX_NOT_FULL);
                    break;
                }
            }
            while (SCB_SPI_UART_FIFO_SIZE != SCB_GET_TX_FIFO_ENTRIES);

            SCB_ClearTxInterruptSource(SCB_INTR_TX_NOT_FULL);
        }
    }
    #endif

#ifdef SCB_SPI_UART_ISR_EXIT_CALLBACK
    SCB_SPI_UART_ISR_ExitCallback();
#endif /* SCB_SPI_UART_ISR_EXIT_CALLBACK */

}

#endif /* (SCB_SCB_IRQ_INTERNAL) */


/* [] END OF FILE */
