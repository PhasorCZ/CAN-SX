/*******************************************************************************
* \file         spi_handler.c
* \version      1.00
*
* \brief
*   Provides definitions of Bootloader API functions for custom interface
*   with CAN used as a transport layer. Compatible with PSoC3, PSoC4 and PSoC5.
*
*   CAN_RX_FRAME_ID -   command message received FROM external programmer
*
********************************************************************************
* \author       Tomas Kozak <pasorcz@gmail.com>
* \copyright    GNU Public License V3
*******************************************************************************/

#include "project.h"
#include "spi_handler.h"

// -----------------------------------------------------------------------------

void send_spi_data( uint8 *BTM9021EP_1_data,
                    uint8 *BTM9021EP_2_data,
                    uint8 *BTM9021EP_3_data,
                    uint8 *BTM9021EP_1_responce,
                    uint8 *BTM9021EP_2_responce,
                    uint8 *BTM9021EP_3_responce)
{
    /* Wake up slaves */
    //SPI_CS_Write(1);
    //CyDelayUs(50);
    
    /* Clean-up */
    SCB_SpiUartClearTxBuffer();
    SCB_SpiUartClearRxBuffer();
    
    /* Protect transmission start*/
    //uint32 intrMask = CyEnterCriticalSection();
    
    /* Send commands to slaves */
    SCB_SpiUartPutArray(BTM9021EP_3_data, 1);
    SCB_SpiUartPutArray(BTM9021EP_2_data, 1);
    SCB_SpiUartPutArray(BTM9021EP_1_data, 1);
    
    /* Wait for all responce bits to arrive */
    while (SCB_SpiUartGetRxBufferSize() < 3)
    {
        CyDelayUs(10);
    }
    
    /* Read responces */
    *BTM9021EP_3_responce = SCB_SpiUartReadRxData();
    *BTM9021EP_2_responce = SCB_SpiUartReadRxData();
    *BTM9021EP_1_responce = SCB_SpiUartReadRxData();
    
    /* Protect transmission end*/
    //CyExitCriticalSection(intrMask);
    
    /* Close communication */
    //CyDelayUs(50);
    //SPI_CS_Write(0);
}

// -----------------------------------------------------------------------------

/* [] END OF FILE */
