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
 * Author: 2002 Davide Cantini
 * CVS: $Id: code.h,v 1.1.1.1 2004/11/05 16:03:03 pj Exp $
 */

#include "eecfg.h"
#include "ee.h"		
#include "erikahal.h"


void thread0(void);
void thread1(void);
void thread2(void);
void thread3(void);


void RUNBUTTON_handler(void);
void ONOFFBUTTON_handler(void);

extern EE_UINT8 mot_pow;

#ifdef __PLAY_BUFFER_SUPPORT__

    #define _pause _DO0 
    #define _1th	255
    #define _2th	_1th >> 1
    #define _4th	_1th >> 2
    #define _8th	_1th >> 3
    #define _16th	_1th >> 4


    static struct EE_note_type n_buf[] =
	{   {_SOL0,_4th,_4th},
	    {_SOL0,_4th,_4th},
	    {_SOL0,_4th,_4th},
	    {_SOL0,_4th,_4th},
	    {_LA0, _2th,_2th},
	    {_LA0, _4th,_4th},
	    {_LA0, _4th,_4th},
	    {_SOL0,_2th,_2th},
    	    {_MI0, _2th,_2th},	
	    {_SOL0,_2th,_2th},
	    {_MI0, _2th,_2th},
	    {_MI0, _4th,_4th},
	    {_MI0, _4th,_4th},    
	    {_MI0, _4th,_4th},
	    {_MI0, _4th,_4th},
	    {_FA0, _2th,_2th},
    	    {_FA0, _4th,_4th},	
	    {_FA0, _4th,_4th},
	    {_MI0, _2th,_2th},
	    {_DO0, _2th,_2th},
	    {_MI0, _2th,_2th},    
	    {_DO0, _2th,_2th},
	    {_DO1, _1th,_4th},
	    {_LA0, _4th,_4th},
    	    {_SI0, _4th,_4th},
	    {_DO1, _4th,_4th},
	    {_LA0, _4th,_4th},
	    {_SOL0,_1th,_1th},			
	    {_LA0, _2th,_2th},	
	    {_SOL0,_2th,_2th},	
	    {_FA0, _2th,_2th},	
	    {_MI0, _2th,_2th},	
	    {_DO0, _2th,_2th},	
	    {_DO0, _2th,_2th},	
	    {_DO0, _2th,_2th},		
	    {_DO0, _2th,_2th},	
	    {_DO0, _1th, 0},
	    {_DO0, _2th, 255},
	    {_pause,  0, 255},
	    {_pause,  0, 255}		
	};


    #define kuka_buffer (n_buf)
    #define kuka_buffer_len 40  
    /* The words are: "Kukaburra sta tutto il santo giorno su una vecchia 
     *                 pianta felice canta. Qua, Kukaburra qua, Kukaburra
     *		       canta insieme a me."
     */

#endif

