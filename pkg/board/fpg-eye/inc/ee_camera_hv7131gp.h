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
 
/** 
	@file ee_camera_hv7131gp.h
	@brief HV7131GP camera header file (board dependent file: XP2 CAMERA BOARD). 
	@author Dario Di Stefano
	@date 2010
*/


#ifndef __EE_CAMERA_HV7131GP__
#define __EE_CAMERA_HV7131GP__

/* Board dependent macros */
// void

#if(0)

/*---------------------------------------------------------------------------*/
/* Macros, types and functions added for compatibility */
typedef int hv7131gp_reg_t;
typedef int hv7131gp_status_t;
typedef int hv7131gp_R_Value_t;
typedef int hv7131gp_T_D_Value_t;
typedef int hv7131gp_Q_Value_t;

#define hv7131gp_configure_resolution(res)  	EE_hv7131gp_set_resolution(res)
#define hv7131gp_configure_time_divisor(div)	EE_hv7131gp_set_time_divisor(div)
#define hv7131gp_set_sleep_status()				EE_hv7131gp_set_sleep_status()
#define hv7131gp_set_active_status()			EE_hv7131gp_set_active_status()
#define hv7131gp_hblank_set(hb)					EE_hv7131gp_set_hblank(hb)
#define hv7131gp_vblank_set(vb)					EE_hv7131gp_set_vblank(vb)
#define hv7131gp_window_set(w,h,x,y)			EE_hv7131gp_set_window(w, h, x, y)
#define hv7131gp_reg_write(reg,val)				EE_hv7131gp_write_byte(reg, val)		
#define hv7131gp_get_Y_average()				EE_hv7131gp_get_Y_average()
#define hv7131gp_get_width()					EE_hv7131gp_get_width()
#define hv7131gp_get_height()					EE_hv7131gp_get_height()
#define hv7131gp_get_size()						EE_hv7131gp_get_size()
#define hv7131gp_capture(add, cbk)				EE_hv7131gp_capture(add, cbk)
#define hv7131gp_configure(div)					EE_hv7131gp_set_configuration(div, EE_HV7131GP_DEFAULT_FORMAT,\
												EE_HV7131GP_DEFAULT_RESOLUTION, EE_HV7131GP_DEFAULT_WIDTH,\
												EE_HV7131GP_DEFAULT_HEIGTH, EE_HV7131GP_DEFAULT_COLUMN,\
												EE_HV7131GP_DEFAULT_ROW, EE_HV7131GP_DEFAULT_HBLANK, EE_HV7131GP_DEFAULT_VBLANK)

__INLINE__ int __ALWAYS_INLINE__ hv7131gp_init(void)
{
	EE_hv7131gp_init(EE_HV7131GP_ISR_MODE);
	return EE_hv7131gp_set_default_configuration();
}

//__INLINE__ int __ALWAYS_INLINE__ hv7131gp_get_fdh(void)
//{
//	return 0;
//}
//
//__INLINE__ int __ALWAYS_INLINE__ hv7131gp_get_fdl(void)
//{
//	return 0;
//}
//
//__INLINE__ int __ALWAYS_INLINE__ hv7131gp_get_fl(void)
//{
//	return 0;
//}

#endif // #if(0)

#endif //#ifndef __EE_CAMERA_HV7131GP__


