/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2006-2010  Simone Mannori, Roberto Bucher
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
	@file flex_dmb.h
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>

#ifdef __USE_BUZZER__
void flex_daughter_buzzer_update(float new_freq_f);
#define flex_daughter_buzzer_start(f) EE_buzzer_start(f)
#define flex_daughter_buzzer_stop() EE_buzzer_stop()
#define flex_daughter_buzzer_init() EE_buzzer_init()
#else
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_buzzer_update(float new_freq_f){}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_buzzer_start(EE_UINT32 freq){}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_buzzer_stop(void){}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_buzzer_init(void){}
#endif

#ifdef __USE_LCD__
#define LCD_PRINT_FLOAT SCITYPE_FLOAT
#define LCD_PRINT_CHARS SCITYPE_INT8
void flex_daughter_lcd_init (void);
void flex_daughter_lcd_end (void);
void EESCI_flexdmb_lcd_float_inout (float scicos_lcd_value1, float scicos_lcd_value2);
void EESCI_flexdmb_lcd_uint8_inout (unsigned char* line1, unsigned char* line2, int size);
void EESCI_flexdmb_lcd_float_inout_line (int line_id, float scicos_lcd_value);
void EESCI_flexdmb_lcd_uint8_inout_line (int line_id, unsigned char* line, int size);
void flex_daughter_lcd_inout (int type, void* y_1, void* y_2, int size);
void flex_daughter_lcd_inout_line (int line_id, int type, void* u, int size);

__INLINE__ void __ALWAYS_INLINE__ _fill_LCD_string(char* str, int len)
{
	int i;
	for(i=len; i<16; i++)
		str[i] = ' ';
	str[16] = '\0';
}

#else
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_lcd_init (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_lcd_end (void)
{}
__INLINE__ void __ALWAYS_INLINE__ EESCI_flexdmb_lcd_float_inout (float scicos_lcd_value1, float scicos_lcd_value2)
{}
__INLINE__ void __ALWAYS_INLINE__ EESCI_flexdmb_lcd_uint8_inout (unsigned char* line1, unsigned char* line2, int size)
{}
__INLINE__ void __ALWAYS_INLINE__ EESCI_flexdmb_lcd_float_inout_line (int line_id, float scicos_lcd_value)
{}
__INLINE__ void __ALWAYS_INLINE__ EESCI_flexdmb_lcd_uint8_inout_line (int line_id, unsigned char* line, int size)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_lcd_inout (int type, void* y_1, void* y_2, int size)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_lcd_inout_line (int line_id, int type, void* u, int size)
{}
#endif

#ifdef __USE_BUTTONS__
void flex_daughter_button_init ();
void flex_daughter_button_end (void);
void flex_daughter_button_float_output (int val, void *ptr_y, int ptr_type);
void flex_daughter_button_inout (int pin, void *ptr_y, int ptr_type);
#else
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_button_init ()
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_button_end (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_button_float_output (int val, void *ptr_y, int ptr_type)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_button_inout (int pin, void *ptr_y, int ptr_type)
{}
#endif

#if defined(__USE_DEMOBOARD__)
#define FLEX_DAUGHTER_NUM_LEDS 8
#elif defined(__USE_MOTIONBOARD__)
#define FLEX_DAUGHTER_NUM_LEDS 2
#endif

#ifdef __USE_LEDS__
void flex_daughter_leds_barrier_init (void);
void flex_daughter_leds_barrier_inout (float threshold, float *leds_values);
void flex_daughter_leds_barrier_end (void);
void flex_daughter_leds_init (void);
void flex_daughter_leds_inout (float threshold, float *leds_values);
void flex_daughter_leds_inout_uint8(unsigned char leds_values);
void flex_daughter_leds_end (void);
void flex_daughter_led_init (void);
void flex_daughter_led_inout (int pin, float threshold, float led_value);
void flex_daughter_led_end (void);
#else
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_barrier_init (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_barrier_inout (float threshold, float *leds_values)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_barrier_end (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_init (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_inout (float threshold, float *leds_values)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_inout_uint8(unsigned char leds_values)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_leds_end (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_led_init (void)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_led_inout (int pin, float threshold, float led_value)
{}
__INLINE__ void __ALWAYS_INLINE__ flex_daughter_led_end (void)
{}
#endif
