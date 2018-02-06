/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2010  Evidence Srl
 *
 * This file is part of ERIKA Enterprise.
 *
 * ERIKA Enterprise is free software; you can redistribute it
 * and/or modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation, 
 * (with a special exception described below).
 *
 * Linking this code statically or dynamically with other modules is
 * making a combined work based on this code.  Thus, the terms and
 * conditions of the GNU General Public License cover the whole
 * combination.
 *
 * As a special exception, the copyright holders of this library give you
 * permission to link this code with independent modules to produce an
 * executable, regardless of the license terms of these independent
 * modules, and to copy and distribute the resulting executable under
 * terms of your choice, provided that you also meet, for each linked
 * independent module, the terms and conditions of the license of that
 * module.  An independent module is a module which is not derived from
 * or based on this library.  If you modify this code, you may extend
 * this exception to your version of the code, but you are not
 * obligated to do so.  If you do not wish to do so, delete this
 * exception statement from your version.
 *
 * ERIKA Enterprise is distributed in the hope that it will be
 * useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License version 2 for more details.
 *
 * You should have received a copy of the GNU General Public License
 * version 2 along with ERIKA Enterprise; if not, write to the
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 * Boston, MA 02110-1301 USA.
 * ###*E*### */

/*
 * Author: 2014,  Francesco Esposito
 * Company: Evidence SRL
 */

// Autosar reference: AUTOSAR_SWS_ECUStateManagerFixed.pdf

#include <ee.h>
#include "BswCommon.h"
#include "CanDrv.h"
#include "State.h"
#include "initHW.h"
#include "Error.h"

#define MODULE_ID   (19)

#define DUMMY_ERROR_CODE    (0U)

#define SaveCanSnapshotToFlah()     (STD_OK)

static uint32 clock0 = 0;   ///< Time since power on (unit: 50 usec) (max value 59 hours). Saturated (i.e. no restart after reaching MAX_UINT32). Note: saturated timer are useful for timestamps.
static uint32 clock1 = 0;   ///< Time since power on (unit: 50 usec) (max value 59 hours). Rolling (i.e. the counter restarts after reaching MAX_UINT32). Note: rolling timer are useful for timeout detection.
static uint32 clock2 = 0;   ///< Time since power on (unit: 1 msec) (max value 49 days). Rolling (i.e. the counter restarts after reaching MAX_UINT32). Note: rolling timer are useful for timeout detection.
static uint16 clock3 = 0;   ///< Time since power on (unit: 12.8 msec) (max value 839 sec). Saturated (i.e. no restart after reaching MAX_UINT32). Note: saturated timer are useful for timestamps.

/// Main state of the BSW.
typedef enum
{
    MAIN_STATE_STARTUP,             ///< Startup transition.
    MAIN_STATE_RUN,                 ///< Standard running mode.
    MAIN_STATE_DIAG,                ///< Diagnostic mode.
    MAIN_STATE_LIMP_HOME,           ///< Degraded mode.
    MAIN_STATE_SAFE,                ///< Safe never-exit state.
        // Todo: analisi condizioni di MAIN_STATE_SAFE
        //  - errore di tipo 'fatal' (see SetFatalError())
        //  - intervento del watchdog
        //  - eccezione non gestita
    MAIN_STATE_RESET_ON_FAILURE,    ///< Restart in case of errors.
    MAIN_STATE_SHUTDOWN,            ///< Shutdown requested by a key off.
} MainStateType;

// Internal state of the component
static boolean initializationState = FALSE;
static MainStateType componentState;

DeclareTask(Task_Idle);

/// Calling period 50 usec.
/// This function updates the following variables: clock0, clock1, clock2, clock3.
void UpdateClock(void)
{
    clock1++;
    if (clock0 < MAX_UINT32)
    {
        clock0++;
    }
    if ( (clock1 % 20) == 0 )    // 20 is the ratio between clock1 and clock2
    {
        // Note: this 'if' is entered every 1 msec
        clock2++;
        if ( (clock0 & 0xFF000000) > 0 )    // If clock3 will result in an overflow ...
        {
            clock3 = MAX_UINT16;
        }
        else
        {
            clock3 = (uint16)(clock0>>8);
        }
    }
}

/// Calling period 20 msec.
/// This function updates the following variables: clock1, clock0, clock2, clock3.
void UpdateClock20msec()
{
    clock1 += 400;   // 400 because unit of clock0 is 50 usec
    if (clock0 < (MAX_UINT32-400))
    {
        clock0 += 400;   // 400 because unit of clock0 is 50 usec
    }
    clock2 += 20;          // Because this function is called every 20 msec.
    if ( (clock0 & 0xFF000000) > 0 )    // If clock3 will result in an overflow ...
    {
        clock3 = MAX_UINT16;
    }
    else
    {
        clock3 = (uint16)(clock0>>8);
    }
}

uint32 GetClock0(void)
{
    return(clock0);
}

uint32 GetClock2(void)
{
    return(clock2);
}
    
uint32 GetClock3(void)
{
    return(clock3);
}

/// Returns the clock (unit:msec) using a rolling counter.
/// Can be used in combination with the function After().
uint32 GetClockMsec(void)
{
    return(clock2);
}

/// Returns TRUE if a given period of time has elapsed.
/// \param uint32 time0 : unit:1 msec. Starting time.
/// \param uint32 period : unit:1 msec. Time period to check if it's elapsed or not.
/// Note: overflow is possible: the result is not valid if delta-time > MAX_UINT32 (= 49 days).
/// When overflow occurs, After() becomes FALSE for a period of 'period' msec.
boolean After(uint32 time0, uint32 period)
{
    return((clock2 - time0) > period);
}

void EcuFunctionReset(void)
{
    /* functional software reset */
    ME.MCTL.R = 0x00005AF0;
    ME.MCTL.R = 0x0000A50F;
}

void EcuDestructiveReset(void)
{
    /* destructive software reset, valid only for cut2/3 */
    ME.MCTL.R = 0xF0005AF0;
    ME.MCTL.R = 0xF000A50F;
}

/// Causes the shutdown and restart of the ECU
// Può essere chiamata da Watchdog.c, da DiagService.c, da Error.c
// Autosar references: BRF00262 EcuReset service.
void EcuReset()
{
    /*
     * Currently SW reset is a Destructive reset
     * Main features:
     * - the content of SRAM is not guaranteed after reset
     * - when system restart, MBIST and LBIST will be executed
     * Note: use this reset if system fails and it needs to be
     * checked and reinitialized from scratch
     */
    EcuDestructiveReset();

    /*
     * In alternative there is a functional reset
     * Main features:
     * - the content of SRAM is guaranteed after reset
     * - when system restart, MBIST and LBIST are skipped
     * Note: use this reset if system does not fails and it does not
     * need to be checked and reinitialized from scratch
     */
    //EcuFunctionReset();
}

/// This function check if a SW functional reset has been occurred or not.
/// Returns STD_OK if the start of the ECU has been caused by a software reset.
/// To clear this information, the application must call EcuClearSwFuncReset().
// It returns STD_OK if a SW reset has been occurred
// It returns STD_NOT_OK if a SW reset has not been occurred
StdReturnType EcuCheckFuncReset(void)
{
    /* Check whether a SW reset has been occurred or not */
    if (RGM.FES.B.F_SOFT_FUNC == 0x1U) {
        return(STD_OK);
    }
    else {
        return(STD_NOT_OK);
    }
}

/// This function clears the SW functional reset flag
/// Usually called after EcuCheckFuncReset(). 
void EcuClearFuncReset(void)
{
    /* Clear SW reset flag */
    RGM.FES.B.F_SOFT_FUNC = 0x1U;
}

/// This function clears the SW Destructive reset flag
/// Usually called after EcuCheckFuncDestrReset().
/// works only for cut2, cut3
void EcuClearDestrReset(void)
{
    /* Clear SW reset flag */
    RGM.DES.B.F_SOFT_DEST = 0x1U;
}

/// This function check if a SW Destructive reset has been occurred or not.
/// Returns STD_OK if the start of the ECU has been caused by a software reset.
/// To clear this information, the application must call EcuClearSwFuncReset().
// It returns STD_OK if a SW reset has been occurred
// It returns STD_NOT_OK if a SW reset has not been occurred
/// works only for cut2, cut3
StdReturnType EcuCheckDestrReset(void)
{
    /* Check whether a SW reset has been occurred or not */
    if (RGM.DES.B.F_SOFT_DEST == 0x1U) {
        return(STD_OK);
    }
    else {
        return(STD_NOT_OK);
    }
}

/// Implements one of the main state of the component State.c: MAIN_STATE_SAFE.
/// Set the ECU to a safe state: output disabled, only diagnostic communication enabled.
/// This function never exits.
void MainStateSafe()
{
#ifdef __OO_HAS_SHUTDOWNHOOK__
    /*
     * - Disable ISRs (intrinsically performed by EE_oo_call_ShutdownHook infrastructure by calling EE_hal_begin_nested_primitive)
     * - Call ShutdownHook (since it is enabled at .oil level)
     */
	ShutdownOS(DUMMY_ERROR_CODE);
#endif /* __OO_HAS_SHUTDOWNHOOK__ */

#ifdef UNIT_TEST       // If UNIT_TEST is defined the function shall exit in order to complete the test.
        return;
#endif

    // Note that the endless loop is not necessary when __OO_HAS_SHUTDOWNHOOK__ is defined, because the hook routine never exits (see ShutdownHook()).
    while(1);
}

#ifdef __OO_HAS_SHUTDOWNHOOK__

void ShutdownHook(StatusType Error)
{ 
    while (TRUE)
    {
        /* Endless loop */
    }
}

#endif /* __OO_HAS_SHUTDOWNHOOK__ */

/// Manage the main state of the BSW.
/// Task period: 20 msec.
void StateTask(void) 
{
    switch (componentState) 
    {
        default:
            break;
    }
}

