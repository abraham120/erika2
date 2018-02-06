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
 * Author: 2004 Antonio Fiaschi
 * CVS: $Id: code.c,v 1.3 2006/01/05 14:39:07 pj Exp $
 */

#include "code.h"


/*
 * Display a number during a short pause 
 */
//#define LOOP_LENGHT 100000
#define LOOP_LENGHT 10000
//#define LOOP_LENGHT 1000
//#define LOOP_LENGHT 100
//#define LOOP_LENGHT 10
//#define LOOP_LENGHT 1
void pause_and_display(int disp)
{
    int i=0;
    int j=0;
    
    for (i=0; i<LOOP_LENGHT; i++) {
        ERIKA_LCD_display(disp);
        for(j=0; j<10; j++) {
            /* do nothing */
        }
    }
}



void main(void)
{
    /* peripherals initialization */
    init_drivers();
    
    /* periodic tick timer installation and starting */
    tick_start();

    /* if there are no thread to execute, the main thread will go
     * into an infinite loop */
    for (;;) {
	/* LCD idle indication */
	ERIKA_LCD_display(0xd);
    }
}
