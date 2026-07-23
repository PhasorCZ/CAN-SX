/*******************************************************************************
* File Name: ProgramTimer_PM.c
* Version 2.10
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "ProgramTimer.h"

static ProgramTimer_BACKUP_STRUCT ProgramTimer_backup;


/*******************************************************************************
* Function Name: ProgramTimer_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ProgramTimer_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: ProgramTimer_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ProgramTimer_Sleep(void)
{
    if(0u != (ProgramTimer_BLOCK_CONTROL_REG & ProgramTimer_MASK))
    {
        ProgramTimer_backup.enableState = 1u;
    }
    else
    {
        ProgramTimer_backup.enableState = 0u;
    }

    ProgramTimer_Stop();
    ProgramTimer_SaveConfig();
}


/*******************************************************************************
* Function Name: ProgramTimer_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ProgramTimer_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: ProgramTimer_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void ProgramTimer_Wakeup(void)
{
    ProgramTimer_RestoreConfig();

    if(0u != ProgramTimer_backup.enableState)
    {
        ProgramTimer_Enable();
    }
}


/* [] END OF FILE */
