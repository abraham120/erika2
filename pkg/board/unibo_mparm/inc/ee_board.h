/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2008  Evidence Srl
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
 * Author: 2001-2002 Alessandro Colantonio, 2002- Paolo Gai
 * CVS: $Id: ee_board.h,v 1.4 2006/04/08 21:07:19 pj Exp $
 */

#ifndef __INCLUDE_UNIBO_MPARM_BOARD_H__
#define __INCLUDE_UNIBO_MPARM_BOARD_H__

#include "mcu/unibo_mparm/inc/ee_mcu.h"


/*************************************************************************
**************************************************************************
 Memory-mapped support functions
*************************************************************************
*************************************************************************/

/*************************************************************************
External variables declaration
 *************************************************************************/

extern volatile char *ee_time_low_ptr;
extern volatile char *ee_time_high_ptr;
extern volatile char *ee_time_stop_ptr;
extern volatile char *ee_time_rel_ptr;

extern volatile char *ee_cycle_low_ptr;
extern volatile char *ee_cycle_high_ptr;
extern volatile char *ee_cycle_stop_ptr;
extern volatile char *ee_cycle_rel_ptr;

/*************************************************************************
Constants
 *************************************************************************/

// Start statistics collection
#define START_METRIC_ADDRESS     0x00000000
// Stop statistics collection
#define STOP_METRIC_ADDRESS      0x00000004
// Mark the end of the boot stage
#define ENDBOOT_ADDRESS          0x00000008
// Shutdown this processor
#define SHUTDOWN_ADDRESS         0x0000000c
// Dump system statistics
#define DUMP_ADDRESS             0x00000010
// Dump system statistics (light version)
#define DUMP_LIGHT_ADDRESS       0x00000014
// Clear system statistics
#define CLEAR_ADDRESS            0x00000018

// Get the ID of this CPU
#define GET_CPU_ID_ADDRESS       0x00000020
// Get the total amopunt of CPUs in this system
#define GET_CPU_CNT_ADDRESS      0x00000024

// 
#define SET_REQ_IO_ADDRESS       0x00000030

// Get the current simulation time (32 LSBs)
#define GET_TIME_ADDRESS_LO      0x00000040
// Get the current simulation time (32 MSBs)
#define GET_TIME_ADDRESS_HI      0x00000044
// Get the current simulation cycle (32 LSBs)
#define GET_CYCLE_ADDRESS_LO     0x00000048
// Get the current simulation cycle (32 MSBs)
#define GET_CYCLE_ADDRESS_HI     0x0000004c
// Freeze the current simulation time for retrieval
#define STOP_TIME_ADDRESS        0x00000050
// Unfreeze the simulation time counter
#define RELEASE_TIME_ADDRESS     0x00000054
// Freeze the current simulation cycle for retrieval
#define STOP_CYCLE_ADDRESS       0x00000058
// Unfreeze the simulation cycle counter
#define RELEASE_CYCLE_ADDRESS    0x0000005c

// Print a debug message to console: set output string
#define DEBUG_MSG_STRING_ADDRESS 0x00000060
// Print a debug message to console: set output value
#define DEBUG_MSG_VALUE_ADDRESS  0x00000064
// Print a debug message to console: set output mode (newline, etc.) and print
#define DEBUG_MSG_MODE_ADDRESS   0x00000068
// Print a debug message to console: ID of the involved processor
#define DEBUG_MSG_ID_ADDRESS     0x0000006c

// Profile print functions
#define DUMP_TIME_START          0x00000070
#define DUMP_TIME_STOP           0x00000074

// Location where to find the command line argc
#define GET_ARGC_ADDRESS         0x00010000
// Location where to find a pointer to the command line argv
#define GET_ARGV_ADDRESS         0x00010004
// Location where to find a pointer to the environment
#define GET_ENVP_ADDRESS         0x00010008
// Location where to find the command line argv (64 kB area)
#define ARGV_ADDRESS             0x00020000
// Location where to find the environment (64 kB area)
#define ENVP_ADDRESS             0x00030000

/* Print mode flags
 ----------------------------------------------
    bit     mnemonic         output
 ----------------------------------------------
 0x00000001 PR_CPU_ID   "Processor PROCID - "
 0x00000002 PR_STRING   "STRING "
 0x00000004 PR_HEX      "0xHEXVAL "
 0x00000008 PR_DEC      "DECVAL "
 0x00000010 PR_CHAR     "CHARVAL "
 0x00000020 PR_TSTAMP   "@ TIMESTAMP "
 0x00000040 PR_NEWL     "\n"
 
 e.g.: 0x00000067 PR_CPU_ID | PR_STRING | PR_HEX | PR_TSTAMP | PR_NEWL  "Processor PROCID - STRING 0xHEXVAL @ TIMESTAMP \n"
 e.g.: 0x00000049 PR_CPU_ID | PR_DEC | PR_NEWL                          "Processor PROCID - DECVAL \n"
*/ 
#define PR_CPU_ID 0x00000001
#define PR_STRING 0x00000002
#define PR_HEX    0x00000004
#define PR_DEC    0x00000008
#define PR_CHAR   0x00000010
#define PR_TSTAMP 0x00000020
#define PR_NEWL   0x00000040

/*************************************************************************
Print
 *************************************************************************/
/* pr - Allows printing debug info even without support from an OS */
__INLINE__ void __ALWAYS_INLINE__ EE_print(char *msg, unsigned long int value, unsigned long int mode)
{
	/* Initialize message, value */
	*((volatile unsigned long int *)(SIMSUPPORT_BASE + DEBUG_MSG_STRING_ADDRESS)) = (unsigned int)msg;
	*((volatile unsigned long int *)(SIMSUPPORT_BASE + DEBUG_MSG_VALUE_ADDRESS)) = value;
	/* Set mode and print */
	*((volatile unsigned long int *)(SIMSUPPORT_BASE + DEBUG_MSG_MODE_ADDRESS)) = mode;
}


/*************************************************************************
Info
 *************************************************************************/
 
/* get_proc_id - Allows getting the processor's ID (from 1 onwards) */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_proc_id()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + GET_CPU_ID_ADDRESS);
	return (*(unsigned long int *)ptr);
}

/* get_proc_num - Allows getting the number of processors in the platform */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_proc_num()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + GET_CPU_CNT_ADDRESS);
	return (*(unsigned long int *)ptr);
}


/*************************************************************************
Simulation Support
 *************************************************************************/

/* end_boot - Marks the end of the bootstrap stage */
__INLINE__ void __ALWAYS_INLINE__ EE_end_boot()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + ENDBOOT_ADDRESS);
	*ptr = 1;
}

/* stop_simulation - Exits the simulation (when all processors will be done) */
__INLINE__ void __ALWAYS_INLINE__ EE_stop_simulation()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + SHUTDOWN_ADDRESS);
	*ptr = 1;
}


/*************************************************************************
Statistics
 *************************************************************************/

/* dump_metric - Does an instant dump of simulation statistics */
__INLINE__ void __ALWAYS_INLINE__ EE_dump_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + DUMP_ADDRESS);
	*ptr = 1;
}

/* dump_light_metric - Does an instant light dump of simulation statistics */
__INLINE__ void __ALWAYS_INLINE__ EE_dump_light_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + DUMP_LIGHT_ADDRESS);
	*ptr = 1;
}

/* clear_metric - Resets simulation statistics */
__INLINE__ void __ALWAYS_INLINE__ EE_clear_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + CLEAR_ADDRESS);
	*ptr = 1;
}

/* start_metric - Starts statistic collection for this processor */
__INLINE__ void __ALWAYS_INLINE__ EE_start_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + START_METRIC_ADDRESS);
	*ptr = 1;
}

/* stop_metric - Stop statistic collection for this processor */
__INLINE__ void __ALWAYS_INLINE__ EE_stop_metric()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + STOP_METRIC_ADDRESS);
	*ptr = 1;
}

#define time_start(r) (*(volatile int *)(SIMSUPPORT_BASE+DUMP_TIME_START)) = r

#define time_stop(r) (*(volatile int *)(SIMSUPPORT_BASE+DUMP_TIME_STOP)) = r

/*************************************************************************
Environment
 *************************************************************************/

/* get_argc - Allows getting the argc command line parameter */
__INLINE__ unsigned int __ALWAYS_INLINE__ EE_get_argc()
{
	char *ptr = (char *)(SIMSUPPORT_BASE + GET_ARGC_ADDRESS);
	return (*(unsigned long int *)ptr);
}

/* get_argv - Allows getting the argv command line parameter */
__INLINE__ char __ALWAYS_INLINE__ **EE_get_argv()
{
	char **ptr = (char **)(SIMSUPPORT_BASE + GET_ARGV_ADDRESS);
	return (ptr);
}

/* get_envp - Allows getting the environment */
__INLINE__ char __ALWAYS_INLINE__ **EE_get_envp()
{
	char **ptr = (char **)(SIMSUPPORT_BASE + GET_ENVP_ADDRESS);
	return (ptr);
}

/*************************************************************************
Time Info
 *************************************************************************/

/* get_time - Allows getting the current simulation time */
__INLINE__ unsigned long long int __ALWAYS_INLINE__ EE_get_time()
{
	unsigned long long int time;
  
	*ee_time_stop_ptr = 1;
	time = (((unsigned long long int)(*(unsigned long int *)ee_time_high_ptr)) << 32) + *(unsigned long int *)ee_time_low_ptr;
	*ee_time_rel_ptr = 1;
  
	return (time);
}

/* get_cycle - Allows getting the current simulation cycle */
__INLINE__ unsigned long long int __ALWAYS_INLINE__ EE_get_cycle()
{
	unsigned long long int cycle;
  
	*ee_cycle_stop_ptr = 1;
	cycle = (((unsigned long long int)(*(unsigned long int *)ee_cycle_high_ptr)) << 32) + *(unsigned long int *)ee_cycle_low_ptr;
	*ee_cycle_rel_ptr = 1;
  
	return (cycle);
}

#endif
