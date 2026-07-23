/***************************************************************************//**
* \file SCB_SPI.c
* \version 4.0
*
* \brief
*  This file provides the source code to the API for the SCB Component in
*  SPI mode.
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

#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    /***************************************
    *  Configuration Structure Initialization
    ***************************************/

    const SCB_SPI_INIT_STRUCT SCB_configSpi =
    {
        SCB_SPI_MODE,
        SCB_SPI_SUB_MODE,
        SCB_SPI_CLOCK_MODE,
        SCB_SPI_OVS_FACTOR,
        SCB_SPI_MEDIAN_FILTER_ENABLE,
        SCB_SPI_LATE_MISO_SAMPLE_ENABLE,
        SCB_SPI_WAKE_ENABLE,
        SCB_SPI_RX_DATA_BITS_NUM,
        SCB_SPI_TX_DATA_BITS_NUM,
        SCB_SPI_BITS_ORDER,
        SCB_SPI_TRANSFER_SEPARATION,
        0u,
        NULL,
        0u,
        NULL,
        (uint32) SCB_SCB_IRQ_INTERNAL,
        SCB_SPI_INTR_RX_MASK,
        SCB_SPI_RX_TRIGGER_LEVEL,
        SCB_SPI_INTR_TX_MASK,
        SCB_SPI_TX_TRIGGER_LEVEL,
        (uint8) SCB_SPI_BYTE_MODE_ENABLE,
        (uint8) SCB_SPI_FREE_RUN_SCLK_ENABLE,
        (uint8) SCB_SPI_SS_POLARITY
    };


    /*******************************************************************************
    * Function Name: SCB_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for SPI operation.
    *
    *  This function is intended specifically to be used when the SCB 
    *  configuration is set to “Unconfigured SCB” in the customizer. 
    *  After initializing the SCB in SPI mode using this function, 
    *  the component can be enabled using the SCB_Start() or 
    * SCB_Enable() function.
    *  This function uses a pointer to a structure that provides the configuration 
    *  settings. This structure contains the same information that would otherwise 
    *  be provided by the customizer settings.
    *
    *  \param config: pointer to a structure that contains the following list of 
    *   fields. These fields match the selections available in the customizer. 
    *   Refer to the customizer for further description of the settings.
    *
    *******************************************************************************/
    void SCB_SpiInit(const SCB_SPI_INIT_STRUCT *config)
    {
        if(NULL == config)
        {
            CYASSERT(0u != 0u); /* Halt execution due to bad function parameter */
        }
        else
        {
            /* Configure pins */
            SCB_SetPins(SCB_SCB_MODE_SPI, config->mode, SCB_DUMMY_PARAM);

            /* Store internal configuration */
            SCB_scbMode       = (uint8) SCB_SCB_MODE_SPI;
            SCB_scbEnableWake = (uint8) config->enableWake;
            SCB_scbEnableIntr = (uint8) config->enableInterrupt;

            /* Set RX direction internal variables */
            SCB_rxBuffer      =         config->rxBuffer;
            SCB_rxDataBits    = (uint8) config->rxDataBits;
            SCB_rxBufferSize  =         config->rxBufferSize;

            /* Set TX direction internal variables */
            SCB_txBuffer      =         config->txBuffer;
            SCB_txDataBits    = (uint8) config->txDataBits;
            SCB_txBufferSize  =         config->txBufferSize;

            /* Configure SPI interface */
            SCB_CTRL_REG     = SCB_GET_CTRL_OVS(config->oversample)           |
                                            SCB_GET_CTRL_BYTE_MODE(config->enableByteMode) |
                                            SCB_GET_CTRL_EC_AM_MODE(config->enableWake)    |
                                            SCB_CTRL_SPI;

            SCB_SPI_CTRL_REG = SCB_GET_SPI_CTRL_CONTINUOUS    (config->transferSeperation)  |
                                            SCB_GET_SPI_CTRL_SELECT_PRECEDE(config->submode &
                                                                          SCB_SPI_MODE_TI_PRECEDES_MASK) |
                                            SCB_GET_SPI_CTRL_SCLK_MODE     (config->sclkMode)            |
                                            SCB_GET_SPI_CTRL_LATE_MISO_SAMPLE(config->enableLateSampling)|
                                            SCB_GET_SPI_CTRL_SCLK_CONTINUOUS(config->enableFreeRunSclk)  |
                                            SCB_GET_SPI_CTRL_SSEL_POLARITY (config->polaritySs)          |
                                            SCB_GET_SPI_CTRL_SUB_MODE      (config->submode)             |
                                            SCB_GET_SPI_CTRL_MASTER_MODE   (config->mode);

            /* Configure RX direction */
            SCB_RX_CTRL_REG     =  SCB_GET_RX_CTRL_DATA_WIDTH(config->rxDataBits)         |
                                                SCB_GET_RX_CTRL_BIT_ORDER (config->bitOrder)           |
                                                SCB_GET_RX_CTRL_MEDIAN    (config->enableMedianFilter) |
                                                SCB_SPI_RX_CTRL;

            SCB_RX_FIFO_CTRL_REG = SCB_GET_RX_FIFO_CTRL_TRIGGER_LEVEL(config->rxTriggerLevel);

            /* Configure TX direction */
            SCB_TX_CTRL_REG      = SCB_GET_TX_CTRL_DATA_WIDTH(config->txDataBits) |
                                                SCB_GET_TX_CTRL_BIT_ORDER (config->bitOrder)   |
                                                SCB_SPI_TX_CTRL;

            SCB_TX_FIFO_CTRL_REG = SCB_GET_TX_FIFO_CTRL_TRIGGER_LEVEL(config->txTriggerLevel);

            /* Configure interrupt with SPI handler but do not enable it */
            CyIntDisable    (SCB_ISR_NUMBER);
            CyIntSetPriority(SCB_ISR_NUMBER, SCB_ISR_PRIORITY);
            (void) CyIntSetVector(SCB_ISR_NUMBER, &SCB_SPI_UART_ISR);

            /* Configure interrupt sources */
            SCB_INTR_I2C_EC_MASK_REG = SCB_NO_INTR_SOURCES;
            SCB_INTR_SPI_EC_MASK_REG = SCB_NO_INTR_SOURCES;
            SCB_INTR_SLAVE_MASK_REG  = SCB_GET_SPI_INTR_SLAVE_MASK(config->rxInterruptMask);
            SCB_INTR_MASTER_MASK_REG = SCB_GET_SPI_INTR_MASTER_MASK(config->txInterruptMask);
            SCB_INTR_RX_MASK_REG     = SCB_GET_SPI_INTR_RX_MASK(config->rxInterruptMask);
            SCB_INTR_TX_MASK_REG     = SCB_GET_SPI_INTR_TX_MASK(config->txInterruptMask);
            
            /* Configure TX interrupt sources to restore. */
            SCB_IntrTxMask = LO16(SCB_INTR_TX_MASK_REG);

            /* Set active SS0 */
            SCB_SpiSetActiveSlaveSelect(SCB_SPI_SLAVE_SELECT0);

            /* Clear RX buffer indexes */
            SCB_rxBufferHead     = 0u;
            SCB_rxBufferTail     = 0u;
            SCB_rxBufferOverflow = 0u;

            /* Clear TX buffer indexes */
            SCB_txBufferHead = 0u;
            SCB_txBufferTail = 0u;
        }
    }

#else

    /*******************************************************************************
    * Function Name: SCB_SpiInit
    ****************************************************************************//**
    *
    *  Configures the SCB for the SPI operation.
    *
    *******************************************************************************/
    void SCB_SpiInit(void)
    {
        /* Configure SPI interface */
        SCB_CTRL_REG     = SCB_SPI_DEFAULT_CTRL;
        SCB_SPI_CTRL_REG = SCB_SPI_DEFAULT_SPI_CTRL;

        /* Configure TX and RX direction */
        SCB_RX_CTRL_REG      = SCB_SPI_DEFAULT_RX_CTRL;
        SCB_RX_FIFO_CTRL_REG = SCB_SPI_DEFAULT_RX_FIFO_CTRL;

        /* Configure TX and RX direction */
        SCB_TX_CTRL_REG      = SCB_SPI_DEFAULT_TX_CTRL;
        SCB_TX_FIFO_CTRL_REG = SCB_SPI_DEFAULT_TX_FIFO_CTRL;

        /* Configure interrupt with SPI handler but do not enable it */
    #if(SCB_SCB_IRQ_INTERNAL)
            CyIntDisable    (SCB_ISR_NUMBER);
            CyIntSetPriority(SCB_ISR_NUMBER, SCB_ISR_PRIORITY);
            (void) CyIntSetVector(SCB_ISR_NUMBER, &SCB_SPI_UART_ISR);
    #endif /* (SCB_SCB_IRQ_INTERNAL) */

        /* Configure interrupt sources */
        SCB_INTR_I2C_EC_MASK_REG = SCB_SPI_DEFAULT_INTR_I2C_EC_MASK;
        SCB_INTR_SPI_EC_MASK_REG = SCB_SPI_DEFAULT_INTR_SPI_EC_MASK;
        SCB_INTR_SLAVE_MASK_REG  = SCB_SPI_DEFAULT_INTR_SLAVE_MASK;
        SCB_INTR_MASTER_MASK_REG = SCB_SPI_DEFAULT_INTR_MASTER_MASK;
        SCB_INTR_RX_MASK_REG     = SCB_SPI_DEFAULT_INTR_RX_MASK;
        SCB_INTR_TX_MASK_REG     = SCB_SPI_DEFAULT_INTR_TX_MASK;

        /* Configure TX interrupt sources to restore. */
        SCB_IntrTxMask = LO16(SCB_INTR_TX_MASK_REG);
            
        /* Set active SS0 for master */
    #if (SCB_SPI_MASTER_CONST)
        SCB_SpiSetActiveSlaveSelect(SCB_SPI_SLAVE_SELECT0);
    #endif /* (SCB_SPI_MASTER_CONST) */

    #if(SCB_INTERNAL_RX_SW_BUFFER_CONST)
        SCB_rxBufferHead     = 0u;
        SCB_rxBufferTail     = 0u;
        SCB_rxBufferOverflow = 0u;
    #endif /* (SCB_INTERNAL_RX_SW_BUFFER_CONST) */

    #if(SCB_INTERNAL_TX_SW_BUFFER_CONST)
        SCB_txBufferHead = 0u;
        SCB_txBufferTail = 0u;
    #endif /* (SCB_INTERNAL_TX_SW_BUFFER_CONST) */
    }
#endif /* (SCB_SCB_MODE_UNCONFIG_CONST_CFG) */


/*******************************************************************************
* Function Name: SCB_SpiPostEnable
****************************************************************************//**
*
*  Restores HSIOM settings for the SPI master output pins (SCLK and/or SS0-SS3) 
*  to be controlled by the SCB SPI.
*
*******************************************************************************/
void SCB_SpiPostEnable(void)
{
#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SCB_CHECK_SPI_MASTER)
    {
    #if (SCB_CTS_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_CTS_SCLK_HSIOM_REG, SCB_CTS_SCLK_HSIOM_MASK,
                                       SCB_CTS_SCLK_HSIOM_POS, SCB_CTS_SCLK_HSIOM_SEL_SPI);
    #endif /* (SCB_CTS_SCLK_PIN) */

    #if (SCB_RTS_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_RTS_SS0_HSIOM_REG, SCB_RTS_SS0_HSIOM_MASK,
                                       SCB_RTS_SS0_HSIOM_POS, SCB_RTS_SS0_HSIOM_SEL_SPI);
    #endif /* (SCB_RTS_SS0_PIN) */

    #if (SCB_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS1_HSIOM_REG, SCB_SS1_HSIOM_MASK,
                                       SCB_SS1_HSIOM_POS, SCB_SS1_HSIOM_SEL_SPI);
    #endif /* (SCB_SS1_PIN) */

    #if (SCB_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS2_HSIOM_REG, SCB_SS2_HSIOM_MASK,
                                       SCB_SS2_HSIOM_POS, SCB_SS2_HSIOM_SEL_SPI);
    #endif /* (SCB_SS2_PIN) */

    #if (SCB_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS3_HSIOM_REG, SCB_SS3_HSIOM_MASK,
                                       SCB_SS3_HSIOM_POS, SCB_SS3_HSIOM_SEL_SPI);
    #endif /* (SCB_SS3_PIN) */
    }

#else

    #if (SCB_SPI_MASTER_SCLK_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SCLK_M_HSIOM_REG, SCB_SCLK_M_HSIOM_MASK,
                                       SCB_SCLK_M_HSIOM_POS, SCB_SCLK_M_HSIOM_SEL_SPI);
    #endif /* (SCB_MISO_SDA_TX_PIN_PIN) */

    #if (SCB_SPI_MASTER_SS0_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS0_M_HSIOM_REG, SCB_SS0_M_HSIOM_MASK,
                                       SCB_SS0_M_HSIOM_POS, SCB_SS0_M_HSIOM_SEL_SPI);
    #endif /* (SCB_SPI_MASTER_SS0_PIN) */

    #if (SCB_SPI_MASTER_SS1_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS1_M_HSIOM_REG, SCB_SS1_M_HSIOM_MASK,
                                       SCB_SS1_M_HSIOM_POS, SCB_SS1_M_HSIOM_SEL_SPI);
    #endif /* (SCB_SPI_MASTER_SS1_PIN) */

    #if (SCB_SPI_MASTER_SS2_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS2_M_HSIOM_REG, SCB_SS2_M_HSIOM_MASK,
                                       SCB_SS2_M_HSIOM_POS, SCB_SS2_M_HSIOM_SEL_SPI);
    #endif /* (SCB_SPI_MASTER_SS2_PIN) */

    #if (SCB_SPI_MASTER_SS3_PIN)
        /* Set SCB SPI to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS3_M_HSIOM_REG, SCB_SS3_M_HSIOM_MASK,
                                       SCB_SS3_M_HSIOM_POS, SCB_SS3_M_HSIOM_SEL_SPI);
    #endif /* (SCB_SPI_MASTER_SS3_PIN) */

#endif /* (SCB_SCB_MODE_UNCONFIG_CONST_CFG) */

    /* Restore TX interrupt sources. */
    SCB_SetTxInterruptMode(SCB_IntrTxMask);
}


/*******************************************************************************
* Function Name: SCB_SpiStop
****************************************************************************//**
*
*  Changes the HSIOM settings for the SPI master output pins 
*  (SCLK and/or SS0-SS3) to keep them inactive after the block is disabled. 
*  The output pins are controlled by the GPIO data register.
*
*******************************************************************************/
void SCB_SpiStop(void)
{
#if(SCB_SCB_MODE_UNCONFIG_CONST_CFG)

    if (SCB_CHECK_SPI_MASTER)
    {
    #if (SCB_CTS_SCLK_PIN)
        /* Set output pin state after block is disabled */
        SCB_uart_cts_spi_sclk_Write(SCB_GET_SPI_SCLK_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_CTS_SCLK_HSIOM_REG, SCB_CTS_SCLK_HSIOM_MASK,
                                       SCB_CTS_SCLK_HSIOM_POS, SCB_CTS_SCLK_HSIOM_SEL_GPIO);
    #endif /* (SCB_uart_cts_spi_sclk_PIN) */

    #if (SCB_RTS_SS0_PIN)
        /* Set output pin state after block is disabled */
        SCB_uart_rts_spi_ss0_Write(SCB_GET_SPI_SS0_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_RTS_SS0_HSIOM_REG, SCB_RTS_SS0_HSIOM_MASK,
                                       SCB_RTS_SS0_HSIOM_POS, SCB_RTS_SS0_HSIOM_SEL_GPIO);
    #endif /* (SCB_uart_rts_spi_ss0_PIN) */

    #if (SCB_SS1_PIN)
        /* Set output pin state after block is disabled */
        SCB_spi_ss1_Write(SCB_GET_SPI_SS1_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS1_HSIOM_REG, SCB_SS1_HSIOM_MASK,
                                       SCB_SS1_HSIOM_POS, SCB_SS1_HSIOM_SEL_GPIO);
    #endif /* (SCB_SS1_PIN) */

    #if (SCB_SS2_PIN)
        /* Set output pin state after block is disabled */
        SCB_spi_ss2_Write(SCB_GET_SPI_SS2_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS2_HSIOM_REG, SCB_SS2_HSIOM_MASK,
                                       SCB_SS2_HSIOM_POS, SCB_SS2_HSIOM_SEL_GPIO);
    #endif /* (SCB_SS2_PIN) */

    #if (SCB_SS3_PIN)
        /* Set output pin state after block is disabled */
        SCB_spi_ss3_Write(SCB_GET_SPI_SS3_INACTIVE);

        /* Set GPIO to drive output pin */
        SCB_SET_HSIOM_SEL(SCB_SS3_HSIOM_REG, SCB_SS3_HSIOM_MASK,
                                       SCB_SS3_HSIOM_POS, SCB_SS3_HSIOM_SEL_GPIO);
    #endif /* (SCB_SS3_PIN) */
    
        /* Store TX interrupt sources (exclude level triggered) for master. */
        SCB_IntrTxMask = LO16(SCB_GetTxInterruptMode() & SCB_INTR_SPIM_TX_RESTORE);
    }
    else
    {
        /* Store TX interrupt sources (exclude level triggered) for slave. */
        SCB_IntrTxMask = LO16(SCB_GetTxInterruptMode() & SCB_INTR_SPIS_TX_RESTORE);
    }

#else

#if (SCB_SPI_MASTER_SCLK_PIN)
    /* Set output pin state after block is disabled */
    SCB_sclk_m_Write(SCB_GET_SPI_SCLK_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB_SET_HSIOM_SEL(SCB_SCLK_M_HSIOM_REG, SCB_SCLK_M_HSIOM_MASK,
                                   SCB_SCLK_M_HSIOM_POS, SCB_SCLK_M_HSIOM_SEL_GPIO);
#endif /* (SCB_MISO_SDA_TX_PIN_PIN) */

#if (SCB_SPI_MASTER_SS0_PIN)
    /* Set output pin state after block is disabled */
    SCB_ss0_m_Write(SCB_GET_SPI_SS0_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB_SET_HSIOM_SEL(SCB_SS0_M_HSIOM_REG, SCB_SS0_M_HSIOM_MASK,
                                   SCB_SS0_M_HSIOM_POS, SCB_SS0_M_HSIOM_SEL_GPIO);
#endif /* (SCB_SPI_MASTER_SS0_PIN) */

#if (SCB_SPI_MASTER_SS1_PIN)
    /* Set output pin state after block is disabled */
    SCB_ss1_m_Write(SCB_GET_SPI_SS1_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB_SET_HSIOM_SEL(SCB_SS1_M_HSIOM_REG, SCB_SS1_M_HSIOM_MASK,
                                   SCB_SS1_M_HSIOM_POS, SCB_SS1_M_HSIOM_SEL_GPIO);
#endif /* (SCB_SPI_MASTER_SS1_PIN) */

#if (SCB_SPI_MASTER_SS2_PIN)
    /* Set output pin state after block is disabled */
    SCB_ss2_m_Write(SCB_GET_SPI_SS2_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB_SET_HSIOM_SEL(SCB_SS2_M_HSIOM_REG, SCB_SS2_M_HSIOM_MASK,
                                   SCB_SS2_M_HSIOM_POS, SCB_SS2_M_HSIOM_SEL_GPIO);
#endif /* (SCB_SPI_MASTER_SS2_PIN) */

#if (SCB_SPI_MASTER_SS3_PIN)
    /* Set output pin state after block is disabled */
    SCB_ss3_m_Write(SCB_GET_SPI_SS3_INACTIVE);

    /* Set GPIO to drive output pin */
    SCB_SET_HSIOM_SEL(SCB_SS3_M_HSIOM_REG, SCB_SS3_M_HSIOM_MASK,
                                   SCB_SS3_M_HSIOM_POS, SCB_SS3_M_HSIOM_SEL_GPIO);
#endif /* (SCB_SPI_MASTER_SS3_PIN) */

    #if (SCB_SPI_MASTER_CONST)
        /* Store TX interrupt sources (exclude level triggered). */
        SCB_IntrTxMask = LO16(SCB_GetTxInterruptMode() & SCB_INTR_SPIM_TX_RESTORE);
    #else
        /* Store TX interrupt sources (exclude level triggered). */
        SCB_IntrTxMask = LO16(SCB_GetTxInterruptMode() & SCB_INTR_SPIS_TX_RESTORE);
    #endif /* (SCB_SPI_MASTER_CONST) */

#endif /* (SCB_SCB_MODE_UNCONFIG_CONST_CFG) */
}


#if (SCB_SPI_MASTER_CONST)
    /*******************************************************************************
    * Function Name: SCB_SetActiveSlaveSelect
    ****************************************************************************//**
    *
    *  Selects one of the four slave select lines to be active during the transfer.
    *  After initialization the active slave select line is 0.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer (TX FIFO is empty and the
    *     SCB_INTR_MASTER_SPI_DONE status is set).
    *
    *  This function does not check that these conditions are met.
    *  This function is only applicable to SPI Master mode of operation.
    *
    *  \param slaveSelect: slave select line which will be active while the following
    *   transfer.
    *   - SCB_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - SCB_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - SCB_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - SCB_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *******************************************************************************/
    void SCB_SpiSetActiveSlaveSelect(uint32 slaveSelect)
    {
        uint32 spiCtrl;

        spiCtrl = SCB_SPI_CTRL_REG;

        spiCtrl &= (uint32) ~SCB_SPI_CTRL_SLAVE_SELECT_MASK;
        spiCtrl |= (uint32)  SCB_GET_SPI_CTRL_SS(slaveSelect);

        SCB_SPI_CTRL_REG = spiCtrl;
    }
#endif /* (SCB_SPI_MASTER_CONST) */


#if !(SCB_CY_SCBIP_V0 || SCB_CY_SCBIP_V1)
    /*******************************************************************************
    * Function Name: SCB_SpiSetSlaveSelectPolarity
    ****************************************************************************//**
    *
    *  Sets active polarity for slave select line.
    *  The component should be in one of the following states to change the active
    *  slave select signal source correctly:
    *   - The component is disabled.
    *   - The component has completed transfer.
    *  
    *  This function does not check that these conditions are met.
    *
    *  \param slaveSelect: slave select line to change active polarity.
    *   - SCB_SPI_SLAVE_SELECT0 - Slave select 0.
    *   - SCB_SPI_SLAVE_SELECT1 - Slave select 1.
    *   - SCB_SPI_SLAVE_SELECT2 - Slave select 2.
    *   - SCB_SPI_SLAVE_SELECT3 - Slave select 3.
    *
    *  \param polarity: active polarity of slave select line.
    *   - SCB_SPI_SS_ACTIVE_LOW  - Slave select is active low.
    *   - SCB_SPI_SS_ACTIVE_HIGH - Slave select is active high.
    *
    *******************************************************************************/
    void SCB_SpiSetSlaveSelectPolarity(uint32 slaveSelect, uint32 polarity)
    {
        uint32 ssPolarity;

        /* Get position of the polarity bit associated with slave select line */
        ssPolarity = SCB_GET_SPI_CTRL_SSEL_POLARITY((uint32) 1u << slaveSelect);

        if (0u != polarity)
        {
            SCB_SPI_CTRL_REG |= (uint32)  ssPolarity;
        }
        else
        {
            SCB_SPI_CTRL_REG &= (uint32) ~ssPolarity;
        }
    }
#endif /* !(SCB_CY_SCBIP_V0 || SCB_CY_SCBIP_V1) */


#if(SCB_SPI_WAKE_ENABLE_CONST)
    /*******************************************************************************
    * Function Name: SCB_SpiSaveConfig
    ****************************************************************************//**
    *
    *  Clears INTR_SPI_EC.WAKE_UP and enables it. This interrupt
    *  source triggers when the master assigns the SS line and wakes up the device.
    *
    *******************************************************************************/
    void SCB_SpiSaveConfig(void)
    {
        /* Clear and enable SPI wakeup interrupt source */
        SCB_ClearSpiExtClkInterruptSource(SCB_INTR_SPI_EC_WAKE_UP);
        SCB_SetSpiExtClkInterruptMode(SCB_INTR_SPI_EC_WAKE_UP);
    }


    /*******************************************************************************
    * Function Name: SCB_SpiRestoreConfig
    ****************************************************************************//**
    *
    *  Disables the INTR_SPI_EC.WAKE_UP interrupt source. After wakeup
    *  slave does not drive the MISO line and the master receives 0xFF.
    *
    *******************************************************************************/
    void SCB_SpiRestoreConfig(void)
    {
        /* Disable SPI wakeup interrupt source */
        SCB_SetSpiExtClkInterruptMode(SCB_NO_INTR_SOURCES);
    }
#endif /* (SCB_SPI_WAKE_ENABLE_CONST) */


/* [] END OF FILE */
