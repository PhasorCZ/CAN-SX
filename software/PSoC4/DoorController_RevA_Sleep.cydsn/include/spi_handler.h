/*******************************************************************************
* \file         spi_handler.h
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

#if !defined(SPI_HANDLER_H)
#define SPI_HANDLER_H
    
// -----------------------------------------------------------------------------
    
#include "project.h"

// -----------------------------------------------------------------------------

//void send_spi_data(uint8 tx[3], uint8 rx[3]); // better
void send_spi_data( uint8 *BTM9021EP_1_data,
                    uint8 *BTM9021EP_2_data,
                    uint8 *BTM9021EP_3_data,
                    uint8 *BTM9021EP_1_responce,
                    uint8 *BTM9021EP_2_responce,
                    uint8 *BTM9021EP_3_responce);

// -----------------------------------------------------------------------------

#endif /* SPI_HANDLER_H */

/* [] END OF FILE */
