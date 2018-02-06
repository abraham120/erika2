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
	@file flex_dmb.c
	@brief www.scicos.org, www.scicoslab.org
	@author Roberto Bucher, SUPSI- Lugano
	@author Simone Mannori, ScicosLab developer
	@date 2006-2010
*/ 
 
 
#include <machine.h>
#include <scicos_block4.h>

#include <ee.h>
#include "pic30/flex_daughter.h"

#ifdef __USE_BUZZER__
void flex_daughter_buzzer_update(float new_freq_f)
{
    static const EE_UINT32 frequency_span = EE_BUZZER_MAX_FREQ - EE_BUZZER_MIN_FREQ;
    if(new_freq_f > 0.0F)
    {
        /* Saturate IN to 1.0 */
        if(new_freq_f > 1.0F)
            new_freq_f = 1.0F;
        /* Frequency in Hz */
        EE_UINT32 new_span = new_freq_f * frequency_span;
        EE_UINT32 new_freq = new_span + EE_BUZZER_MIN_FREQ;
        EE_buzzer_start(new_freq);
    }
    else
        EE_buzzer_stop();
}
#endif

#ifdef __USE_LCD__

#include "stdio.h"
#include "string.h"

// defined in the dspic_main template
extern int scicos_lcd_used;
extern char ee_lcd_line1[17];
extern char ee_lcd_line2[17];

void flex_daughter_lcd_init(void)
{
	scicos_lcd_used = 1;
}

void flex_daughter_lcd_end(void)
{
}

void EESCI_flexdmb_lcd_float_inout_line (int line_id, float scicos_lcd_value) {
	if (line_id == 1) {
		EE_pic30_disableIRQ();
		//snprintf(ee_lcd_line1, 16, "%+.6E", (double)scicos_lcd_value);
		snprintf(ee_lcd_line1, 16, "%f", (double)scicos_lcd_value);
		_fill_LCD_string(ee_lcd_line1, strlen(ee_lcd_line1));
		EE_pic30_enableIRQ();
	} else if (line_id == 2) {
		EE_pic30_disableIRQ();
		snprintf(ee_lcd_line2, 16, "%f", (double)scicos_lcd_value);
		_fill_LCD_string(ee_lcd_line2, strlen(ee_lcd_line2));
		EE_pic30_enableIRQ();
	} else
		return;
}

void EESCI_flexdmb_lcd_uint8_inout_line (int line_id, unsigned char* line, int size) {
	int i;
	if(size > 16)
		size = 16;
	if (line_id == 1) {
		EE_pic30_disableIRQ();
		for (i=0; i<size; i++)
			ee_lcd_line1[i] = line[i];
		ee_lcd_line1[size] = '\0';
		_fill_LCD_string(ee_lcd_line1, strlen(ee_lcd_line1));
		EE_pic30_enableIRQ();
	} else if (line_id == 2) {
		EE_pic30_disableIRQ();
		for (i=0; i<size; i++)
			ee_lcd_line2[i] = line[i];
		ee_lcd_line2[size] = '\0';
		_fill_LCD_string(ee_lcd_line2, strlen(ee_lcd_line2));
		EE_pic30_enableIRQ();
	} else
		return;
}

void EESCI_flexdmb_lcd_float_inout(float scicos_lcd_value1, float scicos_lcd_value2) {
	EE_pic30_disableIRQ();
	snprintf(ee_lcd_line1, 16, "%f", (double)scicos_lcd_value1);
	snprintf(ee_lcd_line2, 16, "%f", (double)scicos_lcd_value2);
	_fill_LCD_string(ee_lcd_line1, strlen(ee_lcd_line1));
	_fill_LCD_string(ee_lcd_line2, strlen(ee_lcd_line2));
	EE_pic30_enableIRQ();
}

void EESCI_flexdmb_lcd_uint8_inout(unsigned char* line1, unsigned char* line2, int size) {
	int i;
	if(size > 16)
		size = 16;
	EE_pic30_disableIRQ();
	for(i=0; i<size; i++) {
		ee_lcd_line1[i] = line1[i];
		ee_lcd_line2[i] = line2[i];
	}
	ee_lcd_line1[size] = '\0';
	ee_lcd_line2[size] = '\0';
	_fill_LCD_string(ee_lcd_line1, strlen(ee_lcd_line1));
	_fill_LCD_string(ee_lcd_line2, strlen(ee_lcd_line2));
	EE_pic30_enableIRQ();
}

void flex_daughter_lcd_inout (int type, void* y_1, void* y_2, int size)
{
	if (type == LCD_PRINT_FLOAT) {
		float* y1 = (float *)y_1;
		float* y2 = (float *)y_2;
		EESCI_flexdmb_lcd_float_inout(y1[0], y2[0]);
	}
	else {
		unsigned char* y1 = (unsigned char *)y_1;
		unsigned char* y2 = (unsigned char *)y_2;
		EESCI_flexdmb_lcd_uint8_inout(y1, y2, size);
	}
}

void flex_daughter_lcd_inout_line (int line_id, int type, void* u, int size)
{
	if (type == LCD_PRINT_FLOAT) {
		float* u1 = (float *)u;
		EESCI_flexdmb_lcd_float_inout_line (line_id, u1[0]);
	}
	else {
		unsigned char* u1 = (unsigned char *)u;
		EESCI_flexdmb_lcd_uint8_inout_line (line_id, u1, size);
	}
}

#endif

#ifdef __USE_BUTTONS__

void flex_daughter_button_init()
{
	// Enable buttons without interrupt support
	EE_buttons_init(NULL, NULL);
}

void flex_daughter_button_end(void)
{
}

void flex_daughter_button_float_output(int val, void *ptr_y, int ptr_type)
{
	if(ptr_type == SCITYPE_FLOAT) {
		float *y = (float *)ptr_y;
		y[0] = val;
	}
	else if(ptr_type == SCITYPE_INT8) {
		char *y = (char *)ptr_y;
		y[0] = val;
	}
}

void flex_daughter_button_inout(int pin, void *ptr_y, int ptr_type)
{
	#if defined(__USE_DEMOBOARD__)
	if ((pin < 1) || (pin > 4))
	#elif defined(__USE_MOTIONBOARD__)
	if ((pin < 1) || (pin > 2))
	#endif
		return; //** return if outside the allowed range

	switch(pin) {
		case 1:
			if (EE_button_get_S1())
				flex_daughter_button_float_output(1, ptr_y, ptr_type);
			else
				flex_daughter_button_float_output(0, ptr_y, ptr_type);
			break;
		case 2:
			if (EE_button_get_S2())
				flex_daughter_button_float_output(1, ptr_y, ptr_type);
			else
				flex_daughter_button_float_output(0, ptr_y, ptr_type);
			break;
#if defined(__USE_DEMOBOARD__)
		case 3:
			if (EE_button_get_S3())
				flex_daughter_button_float_output(1, ptr_y, ptr_type);
			else
				flex_daughter_button_float_output(0, ptr_y, ptr_type);
			break;
		case 4:
			if (EE_button_get_S4())
				flex_daughter_button_float_output(1, ptr_y, ptr_type);
			else
				flex_daughter_button_float_output(0, ptr_y, ptr_type);
			break;
#endif // USE_DEMOBOARD__
	}
}

#endif


#ifdef __USE_LEDS__

void flex_daughter_led_switch_on (int i)
{
	switch (i) { //** set the bit to one 
		case 1:
			EE_led_0_on(); break;
		case 2:
			EE_led_1_on(); break;
		#if defined(__USE_DEMOBOARD__)
		case 3:
			EE_led_2_on(); break;
		case 4:
			EE_led_3_on(); break;
		case 5:
			EE_led_4_on(); break;
		case 6:
			EE_led_5_on(); break;
		case 7:
			EE_led_6_on(); break;
		case 8:
			EE_led_7_on(); break;
		#endif
	}
}

void flex_daughter_led_switch_off (int i)
{
	switch (i) { //** set the bit to zero 
		case 1:
			EE_led_0_off(); break;
		case 2:
			EE_led_1_off(); break;
		#if defined(__USE_DEMOBOARD__)
		case 3:
			EE_led_2_off(); break;
		case 4:
			EE_led_3_off(); break;
		case 5:
			EE_led_4_off(); break;
		case 6:
			EE_led_5_off(); break;
		case 7:
			EE_led_6_off(); break;
		case 8:
			EE_led_7_off(); break;
		#endif
	}
}

void flex_daughter_leds_barrier_init(void)
{
	EE_daughter_leds_init();
}

void flex_daughter_leds_barrier_inout(float threshold, float *leds_values)
{
	int i;
	
	if( threshold < 0.01 || threshold > 0.99 )
		threshold = 0.5;
		
	for(i=FLEX_DAUGHTER_NUM_LEDS-1; i>=0; i--) {
		if(leds_values[i] > threshold)
			flex_daughter_led_switch_on(i+1);
		else
			flex_daughter_led_switch_off(i+1);
	}
}

void flex_daughter_leds_barrier_inout_uint8(unsigned char leds_values)
{
	int i;

	for (i=FLEX_DAUGHTER_NUM_LEDS-1; i>=0; i--) {
		if (leds_values & (0x01<<i))
			flex_daughter_led_switch_on(i+1);
		else
			flex_daughter_led_switch_off(i+1);
	}
}

void flex_daughter_leds_barrier_end(void)
{
	EE_leds_off(); 
}

void flex_daughter_leds_init(void)
{
	flex_daughter_leds_barrier_init();
}

void flex_daughter_leds_inout(float threshold, float *leds_values)
{
	flex_daughter_leds_barrier_inout(threshold, leds_values);
}

void flex_daughter_leds_inout_uint8(unsigned char leds_values)
{
	flex_daughter_leds_barrier_inout_uint8(leds_values);
}

void flex_daughter_leds_end(void)
{
	flex_daughter_leds_barrier_end();
}

void flex_daughter_led_init(void)
{
	EE_daughter_leds_init();
}

void flex_daughter_led_inout(int pin, float threshold, float led_value)
{
	if (threshold < 0.01 || threshold > 0.99)
		threshold = 0.5;
		
	if (led_value > threshold)
		flex_daughter_led_switch_on(pin);
	else
		flex_daughter_led_switch_off(pin);
}

void flex_daughter_led_end(void)
{
	EE_leds_off(); 
}
#endif





