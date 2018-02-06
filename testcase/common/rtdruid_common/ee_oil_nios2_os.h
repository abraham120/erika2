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

#ifdef nios2
		CFLAGS = "-DALT_DEBUG -O0 -g";
		CFLAGS = "-Wall";
		LDFLAGS = "-Wl,-Map -Wl,project.map";
		ASFLAGS = "-g";
		LDDEPS = "\\";
		LIBS = "-lm";
		NIOS2_SYS_CONFIG = "Debug";
		NIOS2_APP_CONFIG = "Debug";
		NIOS2_DO_MAKE_OBJDUMP = TRUE;
//		MASTER_CPU = "cpu0";			
//		IPIC_GLOBAL_NAME = "IPIC_OUTPUT";

//NIOS2_JAM_FILE = "C:/altera/kits/nios2_60/examples/verilog/niosII_stratix_1s40/full_featured/fpga.jam";
//NIOS2_JAM_FILE = "c:/altera/kits/nios2_60/examples/verilog/niosII_stratix_1s40/standard/standard.jam";
//NIOS2_JAM_FILE = "c:/altera/80/nios2eds/examples/verilog/niosII_stratixII_2s60/standard/standard.jam";
		NIOS2_JAM_FILE = "C:/altera/81/nios2eds/examples/verilog/niosII_stratixII_2s60_RoHS/frsh_multi4/fpga.jam";
		NIOS2_PTF_FILE = "C:/altera/81/nios2eds/examples/verilog/niosII_stratixII_2s60_RoHS/frsh_multi4/NiosII_stratixII_2s60_RoHS_small_sopc.ptf";

		CPU_DATA = NIOSII {
//			ID = "cpu0";
			APP_SRC = "code.c";
			STACK_TOP = "__alt_stack_pointer";
			SYS_SIZE = 0x1000;

			//SYSTEM_LIBRARY_NAME = "full_featured_syslib";
			//SYSTEM_LIBRARY_PATH = EE_NIOS2_SYSTEM_LIBRARY_PATH_FULLFEATURED;

			//SYSTEM_LIBRARY_NAME = "standard_syslib";
			//SYSTEM_LIBRARY_PATH = EE_NIOS2_SYSTEM_LIBRARY_PATH;

			SYSTEM_LIBRARY_NAME = "frsh_multi4_syslib_0";
			SYSTEM_LIBRARY_PATH = "/cygdrive/c/Users/pj/workspaceFRSH81/frsh_multi4_syslib_0";
#endif
