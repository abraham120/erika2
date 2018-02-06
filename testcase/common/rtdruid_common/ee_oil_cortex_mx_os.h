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

#ifdef cortex_mx

#ifdef cortex_m0

#ifdef lpc12xx
		EE_OPT = "__ADD_LIBS__";
		LIB = ENABLE {
			NAME = "CMSIS";
		};
		EE_OPT = "__USE_LPC12XX_CMSIS_V2__";

		MCU_DATA = LPCXPRESSO {
			MODEL = LPC12xx;
		};
#endif	/* lpc12xx */

#else	/* cortex_m0 */

#ifdef cortex_m4

#ifdef lm4f232xxxx
		MCU_DATA = STELLARIS {
			MODEL = LM4F232xxxx;
		};
#else	/* lm4f232xxxx */

#ifdef stm32f4xx
		EE_OPT = "__ADD_LIBS__";
		LIB = ENABLE { NAME = "ST_CMSIS"; };

		MCU_DATA = STM32 {
			MODEL = STM32F4xx;
		};
#endif	/* stm32f4xx */

#endif	/* !lm4f232xxxx */

#endif	/* !cortex_m4 */

#endif	/* !cortex_m0 */

		CPU_DATA = CORTEX_MX {

#ifdef cortex_m0
			MODEL = M0;
#else	/* cortex_m0 */

#ifdef cortex_m4
			MODEL = M4;
#endif	/* cortex_m4 */

#endif	/* !cortex_m0 */

			APP_SRC = "code.c";

#if ( defined(cortex_m4) && defined(USEIRQ) )
			APP_SRC = "../../common/cortex_mx/test_irq.c";
#endif

#ifdef iar
			JLINK = TRUE;
			COMPILER_TYPE = IAR;
#else	/* iar */

#ifdef ccs
			COMPILER_TYPE = CCS;
#else	/* ccs */

#ifdef keil
			COMPILER_TYPE = KEIL;
#else	/* keil */

#ifdef gnu
			COMPILER_TYPE = GNU;
#endif	/* gnu */
			
#endif	/* !keil */

#endif	/* !ccs */

#endif	/* !iar */

#endif	/* cortex_mx */
