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

/*
 * Author: 2012  Gianluca Franchino gianluca@evidence.eu.com
 */


#ifndef EE_LCD_H
#define EE_LCD_H

#define EE_LCD_LINE1 0
#define EE_LCD_LINE2 16
#define EE_DATA_WR 1
#define EE_CTRL_WR 0
	

/* LCD minimal commands. For other commands see the datasheet*/
#define EE_LCD_CLEAR        0x01
#define EE_LCD_HOME_L1      0x80    
#define EE_LCD_HOME_L2      0xC0
#define EE_LCD_DISPLAY_ON	0x04
#define EE_LCD_TWO_LINE		0x08
#define EE_LCD_CURSOR_OFF	0x0C
#define EE_LCD_CURSOR_ON	0x0E
#define EE_LCD_CLEAR		0x01
#define EE_LCD_HOME_L1		0x80
#define EE_LCD_HOME_L2		0xC0


void EE_LCD_init(void);
void EE_LCD_disp(EE_UINT8, const EE_UINT8 *);
void EE_LCD_wr(EE_UINT8, EE_UINT8);
void EE_LCD_clear(void);

#endif /*EE_LCD_H */
