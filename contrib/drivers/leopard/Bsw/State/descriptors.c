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

#include "descriptors.h"

#define MODULE_ID   (21)

#if !defined __E200ZX_EXECUTE_FROM_RAM__
/* If application runs from Flash */

#pragma push // save current pragma context
#pragma section R "calib_flash_descriptor_section" "calib_flash_descriptor_section"
CALIBRATIONS_SECTION("calib_flash_descriptor_section")
const FlashSegmentDescriptorType descriptor_calib_flash;
#pragma pop

#pragma push // save current pragma context
#pragma section RW "calib_ram_descriptor_section" "calib_ram_descriptor_section"
CALIBRATIONS_SECTION("calib_ram_descriptor_section")
FlashSegmentDescriptorType descriptor_calib_ram;
#pragma pop

#pragma push // save current pragma context
#pragma section R "APPL_descriptor_section" "APPL_descriptor_section"
CALIBRATIONS_SECTION("APPL_descriptor_section")
const FlashSegmentDescriptorType descriptor_appl;
#pragma pop

#else

/* Dummy values if application runs from SRAM */
const FlashSegmentDescriptorType descriptor_calib_flash;
FlashSegmentDescriptorType descriptor_calib_ram;
const FlashSegmentDescriptorType descriptor_appl;
#endif
