/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2002-2012  Evidence Srl
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

/** @file	WdgIf_Types.h
 *  @brief	AUTOSAR Watchdog Interface Types Header File.
 *
 *  <b>WDGIF010</b>:	The Watchdog Interface's implementer shall place the
 *  			type definitions of the Watchdog Interface in the file
 *  			WdgIf_Types.h.
 *
 *  @note	The implementer of the Watchdog Interface shall not change or
 *  		extend the type definitions of the Watchdog Interface for a
 *  		specific watchdog device or platform.
 *
 *  <b>WDGIF049</b>:	The Watchdog Interface shall comprise a header file
 *  			WdgIf_Types.h providing type declarations for the
 *  			watchdog interface and common type declarations to be
 *  			imported by watchdog drivers.
 *
 *  @author	Giuseppe Serano
 *  @date	2012
 */

#ifndef	WDG_IF_H
#define	WDG_IF_H

/*
 * WdgIf_Types.h shall include Std_Types.h.
 */
#include "Std_Types.h"

/** @brief	Watchdog Driver Mode Type.
 *
 *  <b>WDGIF016</b>	The <tt>WdgIf_ModeType</tt> values shall be passed as
 *  			parameters to the watchdog drivers mode switching
 *  			function (<tt>Wdg_SetMode()</tt>). (<tt>BSW12018</tt>)
 *
 *  @note	The hardware specific settings behind these modes are given in
 *  		the watchdog drivers configuration set.
 *
 *  Watchdog Operational Modes:
 *  - <tt>Off-Mode</tt>:	The watchdog hardware is disabled / shut down.
 *  				This might be necessary in order to shut down
 *  				the complete ECU and not get cyclic resets from
 *  				a still running external watchdog.
 *  				This mode might not be allowed for safety
 *  				critical systems. In this case, the Wdg module
 *  				has to be configured to prevent switching to
 *  				this mode.
 *  - <tt>Slow-Mode</tt>:	Triggering the watchdog hardware can be done
 *  				with a long timeout period.
 *  				This mode can e.g. be used during system startup
 *  				/ initialization phase. E.g. the watchdog
 *  				hardware is configured for toggle mode (no
 *  				constraints on the point in time at which the
 *  				triggering is done) and a timeout period of 20
 *  				milliseconds.
 *  - <tt>Fast-Mode</tt>:	Triggering the watchdog hardware has to be done
 *  				with a short timeout period.
 *  				This mode can e.g. be used during normal
 *  				operations of the ECU. E.g. the watchdog
 *  				hardware is configured for window mode
 *  				(triggering the watchdog has to occur within
 *  				certain minimum / maximum boundaries within the
 *  				timeout period) and a timeout period of 5
 *  				milliseconds.
 */
typedef enum {
  WDGIF_OFF_MODE = 0,	/**< In this mode, the watchdog driver is disabled
  			 *   (switched off).				      */
  WDGIF_SLOW_MODE,	/**< In this mode, the watchdog driver is set up for a
			 *   long timeout period (slow triggering).	      */
  WDGIF_FAST_MODE	/**< In this mode, the watchdog driver is set up for a
			 *   short timeout period (fast triggering).	      */
}	WdgIf_ModeType;

#endif	/* WDG_IF_H */
