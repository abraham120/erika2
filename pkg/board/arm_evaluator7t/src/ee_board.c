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
 * Author: 2001-2002 Alessandro Colantonio
 * CVS: $Id: ee_board.c,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "ee_internal.h"


#ifdef __LCD_USED__

/* number <-> segments mapping */
EE_UREG EE_LCD_numeric_display[16] = 
{
    EE_LCD_DISP_0, EE_LCD_DISP_1, EE_LCD_DISP_2, EE_LCD_DISP_3,
    EE_LCD_DISP_4, EE_LCD_DISP_5, EE_LCD_DISP_6, EE_LCD_DISP_7,
    EE_LCD_DISP_8, EE_LCD_DISP_9, EE_LCD_DISP_A, EE_LCD_DISP_B,
    EE_LCD_DISP_C, EE_LCD_DISP_D, EE_LCD_DISP_E, EE_LCD_DISP_F
};	

#endif /* __LCD_USED__ */

