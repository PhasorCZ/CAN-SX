/***************************************************************************//**
* \file SCB_SPI_UART.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI and UART modes.
*
* Note:
*
*******************************************************************************
* \copyright
* Copyright 2013-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SCB_PVT.h"
#include "SCB_SPI_UART_PVT.h"

/***************************************
*        SPI/UART Private Vars
***************************************/

#if(SCB_INTERNAL_RX_SW_BUFFER_CONST)
    /* Start index to put data into the software receive buffer.*/
    volatile uint32 SCB_rxBufferHead;
    /* Start index to get data from the software receive buffer.*/
    volatile uint32 SCB_rxBufferTail;
    /**
    * \addtogroup group_globals
    * \{
    */
    /** Sets when internal software receive buffer overflow
    *  was occurred.
    */
    volatile uint8  SCB_rxBufferOverflow;
    /** \} globals */
#endif /* (SCB_INTERNAL_RX_SW_BUFFER_CONST) */

#if(SCB_INTERNAL_TX_SW_BUFFER_CONST)
    /* Start index to put data into the software transmit buffer.*/
    volatile uint32 SCB_txBufferHead;
    /* Start index to get data from the software transmit buffer.*/
    volatile uint32 SCB_txBufferTail;
#endif /* (SCB_INTERNAL_TX_SW_BUFFER_CONST) */

#if(SCB_INTERNAL_RX_SW_BUFFER)
    /* Add one element to the buffer to receive full packet. One byte in receive buffer is always empty */
    volatile uint8 SCB_rxBufferInternal[SCB_INTERNAL_RX_BUFFER_SIZE];
#endif /* (SCB_INTERNAL_RX_SW_BUFFER) */

#if(SCB_INTERNAL_TX_SW_BUFFER)
    volatile uint8 SCB_txBufferInternal[SCB_TX_BUFFER_SIZE];
#endif /* (SCB_INTERNAL_TX_SW_BUFFER) */


#if(SCB_RX_DIRECTION)
    /*******************************************************************************
    * Function Name: SCB_SpiUartReadRxData
    ****************************************************************************//**
    *
    *  Retrieves the next data element from the receive buffer.
    *   - RX software buffer is disabled: Returns data element retrieved from
    *     RX FIFO. Undefined data will be returned if the RX FIFO is empty.
    *   - RX software buffer is enabled: Returns data element from the software
    *     receive buffer. Zero value is returned if the software receive buffer
    *     is empty.
    *
    * \return
    *  Next data element from the receive buffer. 
    *  The amount of data bits to be received depends on RX data bits selection 
    *  (the data bit counting starts from LSB of return value).
    *
    * \globalvars
    *  SCB_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  SCB_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 SCB_SpiUartReadRxData(void)
    {
        uint32 rxData = 0u;

    #if (SCB_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SCB_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SCB_CHECK_RX_SW_BUFFER)
        {
            if (SCB_rxBufferHead != SCB_rxBufferTail)
            {
                /* There is data in RX software buffer */

                /* Calculate index to read from */
                locTail = (SCB_rxBufferTail + 1u);

                if (SCB_INTERNAL_RX_BUFFER_SIZE == locTail)
                {
                    locTail = 0u;
                }

                /* Get data from RX software buffer */
                rxData = SCB_GetWordFromRxBuffer(locTail);

                /* Change index in the buffer */
                SCB_rxBufferTail = locTail;

                #if (SCB_CHECK_UART_RTS_CONTROL_FLOW)
                {
                    /* Check if RX Not Empty is disabled in the interrupt */
                    if (0u == (SCB_INTR_RX_MASK_REG & SCB_INTR_RX_NOT_EMPTY))
                    {
                        /* Enable RX Not Empty interrupt source to continue
                        * receiving data into software buffer.
                        */
                        SCB_INTR_RX_MASK_REG |= SCB_INTR_RX_NOT_EMPTY;
                    }
                }
                #endif

            }
        }
        #else
        {
            /* Read data from RX FIFO */
            rxData = SCB_RX_FIFO_RD_REG;
        }
        #endif

        return (rxData);
    }


    /*******************************************************************************
    * Function Name: SCB_SpiUartGetRxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of received data elements in the receive buffer.
    *   - RX software buffer disabled: returns the number of used entries in
    *     RX FIFO.
    *   - RX software buffer enabled: returns the number of elements which were
    *     placed in the receive buffer. This does not include the hardware RX FIFO.
    *
    * \return
    *  Number of received data elements.
    *
    * \globalvars
    *  SCB_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  SCB_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    uint32 SCB_SpiUartGetRxBufferSize(void)
    {
        uint32 size;
    #if (SCB_INTERNAL_RX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SCB_INTERNAL_RX_SW_BUFFER_CONST) */

        #if (SCB_CHECK_RX_SW_BUFFER)
        {
            locHead = SCB_rxBufferHead;

            if(locHead >= SCB_rxBufferTail)
            {
                size = (locHead - SCB_rxBufferTail);
            }
            else
            {
                size = (locHead + (SCB_INTERNAL_RX_BUFFER_SIZE - SCB_rxBufferTail));
            }
        }
        #else
        {
            size = SCB_GET_RX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SCB_SpiUartClearRxBuffer
    ****************************************************************************//**
    *
    *  Clears the receive buffer and RX FIFO.
    *
    * \globalvars
    *  SCB_rxBufferHead - the start index to put data into the 
    *  software receive buffer.
    *  SCB_rxBufferTail - the start index to get data from the 
    *  software receive buffer.
    *
    *******************************************************************************/
    void SCB_SpiUartClearRxBuffer(void)
    {
        #if (SCB_CHECK_RX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SCB_DisableInt();

            /* Flush RX software buffer */
            SCB_rxBufferHead = SCB_rxBufferTail;
            SCB_rxBufferOverflow = 0u;

            SCB_CLEAR_RX_FIFO;
            SCB_ClearRxInterruptSource(SCB_INTR_RX_ALL);

            #if (SCB_CHECK_UART_RTS_CONTROL_FLOW)
            {
                /* Enable RX Not Empty interrupt source to continue receiving
                * data into software buffer.
                */
                SCB_INTR_RX_MASK_REG |= SCB_INTR_RX_NOT_EMPTY;
            }
            #endif
            
            /* Release lock */
            SCB_EnableInt();
        }
        #else
        {
            SCB_CLEAR_RX_FIFO;
        }
        #endif
    }

#endif /* (SCB_RX_DIRECTION) */


#if(SCB_TX_DIRECTION)
    /*******************************************************************************
    * Function Name: SCB_SpiUartWriteTxData
    ****************************************************************************//**
    *
    *  Places a data entry into the transmit buffer to be sent at the next available
    *  bus time.
    *  This function is blocking and waits until there is space available to put the
    *  requested data in the transmit buffer.
    *
    *  \param txDataByte: the data to be transmitted.
    *   The amount of data bits to be transmitted depends on TX data bits selection 
    *   (the data bit counting starts from LSB of txDataByte).
    *
    * \globalvars
    *  SCB_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  SCB_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void SCB_SpiUartWriteTxData(uint32 txData)
    {
    #if (SCB_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locHead;
    #endif /* (SCB_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SCB_CHECK_TX_SW_BUFFER)
        {
            /* Put data directly into the TX FIFO */
            if ((SCB_txBufferHead == SCB_txBufferTail) &&
                (SCB_SPI_UART_FIFO_SIZE != SCB_GET_TX_FIFO_ENTRIES))
            {
                /* TX software buffer is empty: put data directly in TX FIFO */
                SCB_TX_FIFO_WR_REG = txData;
            }
            /* Put data into TX software buffer */
            else
            {
                /* Head index to put data */
                locHead = (SCB_txBufferHead + 1u);

                /* Adjust TX software buffer index */
                if (SCB_TX_BUFFER_SIZE == locHead)
                {
                    locHead = 0u;
                }

                /* Wait for space in TX software buffer */
                while (locHead == SCB_txBufferTail)
                {
                }

                /* TX software buffer has at least one room */

                /* Clear old status of INTR_TX_NOT_FULL. It sets at the end of transfer when TX FIFO is empty. */
                SCB_ClearTxInterruptSource(SCB_INTR_TX_NOT_FULL);

                SCB_PutWordInTxBuffer(locHead, txData);

                SCB_txBufferHead = locHead;

                /* Check if TX Not Full is disabled in interrupt */
                if (0u == (SCB_INTR_TX_MASK_REG & SCB_INTR_TX_NOT_FULL))
                {
                    /* Enable TX Not Full interrupt source to transmit from software buffer */
                    SCB_INTR_TX_MASK_REG |= (uint32) SCB_INTR_TX_NOT_FULL;
                }
            }
        }
        #else
        {
            /* Wait until TX FIFO has space to put data element */
            while (SCB_SPI_UART_FIFO_SIZE == SCB_GET_TX_FIFO_ENTRIES)
            {
            }

            SCB_TX_FIFO_WR_REG = txData;
        }
        #endif
    }


    /*******************************************************************************
    * Function Name: SCB_SpiUartPutArray
    ****************************************************************************//**
    *
    *  Places an array of data into the transmit buffer to be sent.
    *  This function is blocking and waits until there is a space available to put
    *  all the requested data in the transmit buffer. The array size can be greater
    *  than transmit buffer size.
    *
    * \param wrBuf: pointer to an array of data to be placed in transmit buffer. 
    *  The width of the data to be transmitted depends on TX data width selection 
    *  (the data bit counting starts from LSB for each array element).
    * \param count: number of data elements to be placed in the transmit buffer.
    *
    * \globalvars
    *  SCB_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  SCB_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void SCB_SpiUartPutArray(const uint8 wrBuf[], uint32 count)
    {
        uint32 i;

        for (i=0u; i < count; i++)
        {
            SCB_SpiUartWriteTxData((uint32) wrBuf[i]);
        }
    }


    /*******************************************************************************
    * Function Name: SCB_SpiUartGetTxBufferSize
    ****************************************************************************//**
    *
    *  Returns the number of elements currently in the transmit buffer.
    *   - TX software buffer is disabled: returns the number of used entries in
    *     TX FIFO.
    *   - TX software buffer is enabled: returns the number of elements currently
    *     used in the transmit buffer. This number does not include used entries in
    *     the TX FIFO. The transmit buffer size is zero until the TX FIFO is
    *     not full.
    *
    * \return
    *  Number of data elements ready to transmit.
    *
    * \globalvars
    *  SCB_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  SCB_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    uint32 SCB_SpiUartGetTxBufferSize(void)
    {
        uint32 size;
    #if (SCB_INTERNAL_TX_SW_BUFFER_CONST)
        uint32 locTail;
    #endif /* (SCB_INTERNAL_TX_SW_BUFFER_CONST) */

        #if (SCB_CHECK_TX_SW_BUFFER)
        {
            /* Get current Tail index */
            locTail = SCB_txBufferTail;

            if (SCB_txBufferHead >= locTail)
            {
                size = (SCB_txBufferHead - locTail);
            }
            else
            {
                size = (SCB_txBufferHead + (SCB_TX_BUFFER_SIZE - locTail));
            }
        }
        #else
        {
            size = SCB_GET_TX_FIFO_ENTRIES;
        }
        #endif

        return (size);
    }


    /*******************************************************************************
    * Function Name: SCB_SpiUartClearTxBuffer
    ****************************************************************************//**
    *
    *  Clears the transmit buffer and TX FIFO.
    *
    * \globalvars
    *  SCB_txBufferHead - the start index to put data into the 
    *  software transmit buffer.
    *  SCB_txBufferTail - start index to get data from the software
    *  transmit buffer.
    *
    *******************************************************************************/
    void SCB_SpiUartClearTxBuffer(void)
    {
        #if (SCB_CHECK_TX_SW_BUFFER)
        {
            /* Lock from component interruption */
            SCB_DisableInt();

            /* Flush TX software buffer */
            SCB_txBufferHead = SCB_txBufferTail;

            SCB_INTR_TX_MASK_REG &= (uint32) ~SCB_INTR_TX_NOT_FULL;
            SCB_CLEAR_TX_FIFO;
            SCB_ClearTxInterruptSource(SCB_INTR_TX_ALL);

            /* Release lock */
            SCB_EnableInt();
        }
        #else
        {
            SCB_CLEAR_TX_FIFO;
        }
        #endif
    }

#endif /* (SCB_TX_DIRECTION) */


/*******************************************************************************
* Function Name: SCB_SpiUartDisableIntRx
****************************************************************************//**
*
*  Disables the RX interrupt sources.
*
*  \return
*   Returns the RX interrupt sources enabled before the function call.
*
*******************************************************************************/
uint32 SCB_SpiUartDisableIntRx(void)
{
    uint32 intSource;

    intSource = SCB_GetRxInterruptMode();

    SCB_SetRxInterruptMode(SCB_NO_INTR_SOURCES);

    return (intSource);
}


/*******************************************************************************
* Function Name: SCB_SpiUartDisableIntTx
****************************************************************************//**
*
*  Disables TX interrupt sources.
*
*  \return
*   Returns TX interrupt sources enabled before function call.
*
*******************************************************************************/
uint32 SCB_SpiUartDisableIntTx(void)
{
    uint32 intSourceMask;

    intSourceMask = SCB_GetTxInterruptMode();

    SCB_SetTxInterruptMode(SCB_NO_INTR_SOURCES);

    return (intSourceMask);
}


#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG)
    /*******************************************************************************
    * Function Name: SCB_PutWordInRxBuffer
    ****************************************************************************//**
    *
    *  Stores a byte/word into the RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param index:      index to store data byte/word in the RX buffer.
    *  \param rxDataByte: byte/word to store.
    *
    *******************************************************************************/
    void SCB_PutWordInRxBuffer(uint32 idx, uint32 rxDataByte)
    {
        /* Put data in buffer */
        if (SCB_ONE_BYTE_WIDTH == SCB_rxDataBits)
        {
            SCB_rxBuffer[idx] = ((uint8) rxDataByte);
        }
        else
        {
            SCB_rxBuffer[(uint32)(idx << 1u)]      = LO8(LO16(rxDataByte));
            SCB_rxBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(rxDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SCB_GetWordFromRxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from RX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \return
    *   Returns byte/word read from RX buffer.
    *
    *******************************************************************************/
    uint32 SCB_GetWordFromRxBuffer(uint32 idx)
    {
        uint32 value;

        if (SCB_ONE_BYTE_WIDTH == SCB_rxDataBits)
        {
            value = SCB_rxBuffer[idx];
        }
        else
        {
            value  = (uint32) SCB_rxBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32)SCB_rxBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }


    /*******************************************************************************
    * Function Name: SCB_PutWordInTxBuffer
    ****************************************************************************//**
    *
    *  Stores byte/word into the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx:        index to store data byte/word in the TX buffer.
    *  \param txDataByte: byte/word to store.
    *
    *******************************************************************************/
    void SCB_PutWordInTxBuffer(uint32 idx, uint32 txDataByte)
    {
        /* Put data in buffer */
        if (SCB_ONE_BYTE_WIDTH == SCB_txDataBits)
        {
            SCB_txBuffer[idx] = ((uint8) txDataByte);
        }
        else
        {
            SCB_txBuffer[(uint32)(idx << 1u)]      = LO8(LO16(txDataByte));
            SCB_txBuffer[(uint32)(idx << 1u) + 1u] = HI8(LO16(txDataByte));
        }
    }


    /*******************************************************************************
    * Function Name: SCB_GetWordFromTxBuffer
    ****************************************************************************//**
    *
    *  Reads byte/word from the TX buffer.
    *  Only available in the Unconfigured operation mode.
    *
    *  \param idx: index to get data byte/word from the TX buffer.
    *
    *  \return
    *   Returns byte/word read from the TX buffer.
    *
    *******************************************************************************/
    uint32 SCB_GetWordFromTxBuffer(uint32 idx)
    {
        uint32 value;

        if (SCB_ONE_BYTE_WIDTH == SCB_txDataBits)
        {
            value = (uint32) SCB_txBuffer[idx];
        }
        else
        {
            value  = (uint32) SCB_txBuffer[(uint32)(idx << 1u)];
            value |= (uint32) ((uint32) SCB_txBuffer[(uint32)(idx << 1u) + 1u] << 8u);
        }

        return (value);
    }

#endif /* (SCB_SCB_MODE_UNCONFIG_CONST_CFG) */


/* [] END OF FILE */
