/* ###*B*###
 * ERIKA Enterprise - a tiny RTOS for small microcontrollers
 *
 * Copyright (C) 2010, Pebble Bay Consulting Ltd.
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

/* Author: Steve Langstaff, Pebble Bay Consulting Ltd, 2010
 *
 */

#include "ee_internal.h"
#include "cpu/esi_risc/inc/ee_irq.h"

#ifdef __USE_LEDS__

/* Which GPIOs are connected to the LEDs */
#define LED_GPIOS		0x0f

/* The GPIO device driving the LEDs. */
static esi_gpio_t *led_gpio = 0;

/* keep track of what LEDs we are currently displaying */
static volatile unsigned char ledval = 0;

void EE_leds_init(void)
{
	/* Information about the GPIO device, such as which interrupt it is using. */
	esi_device_info_t *gpio_device;

	/* Get a GPIO device */
	gpio_device = esi_device_get(ESI_VID_ENSILICA, ESI_DID_ENSILICA_APB_GPIO, 0, 0);
	if(!gpio_device)
	{
		/* TODO: log error code or return indication */
		return;
	}
	led_gpio = (esi_gpio_t *)gpio_device->base_address;

	/* Set GPIOs connected to LEDs to be outputs. */
	esi_gpio_set_outputs(led_gpio, LED_GPIOS);

	/* turn off LEDs (active low) */
	esi_gpio_set_data(led_gpio, LED_GPIOS, LED_GPIOS);
	ledval = 0;
}

/* can be called with interrupts enabled */
void EE_leds_on(unsigned char theled)
{
	int reg=esi_interrupt_disable();
	ledval |= theled;
	if (led_gpio != 0)
	{
		/* LEDs are active low on the GPIOs */
		esi_gpio_set_data(led_gpio, LED_GPIOS, ~ledval);
	}
	esi_interrupt_restore(reg);
}

/* can be called with interrupts enabled */
void EE_leds_off(unsigned char theled)
{
	int reg=esi_interrupt_disable();
	ledval &= ~theled;
	if (led_gpio != 0)
	{
		/* LEDs are active low on the GPIOs */
		esi_gpio_set_data(led_gpio, LED_GPIOS, ~ledval);
	}
	esi_interrupt_restore(reg);
}

#endif


#ifdef	__USE_TIMERS__
void timer_init(void ** timer_handle, int index, EE_UINT32 rate,
		void (*handler)(void))
{
	esi_device_info_t * timer_device;
	esi_timer_t *timer;

	*timer_handle = 0;

	/* Get the timer device */
	timer_device = esi_device_get(ESI_VID_ENSILICA, ESI_DID_ENSILICA_APB_TIMER,
			0, index);
	if(!timer_device)
	{
		return;
	}
	if (timer_device->irq < 0)
	{
		return;
	}

	timer = (esi_timer_t *)timer_device->base_address;

	/* set timer to wrap depending on rate demanded */
	timer->wrap_comparator = rate-1;
	esi_timer_set_counter (timer, 0);
	timer->control = ESI_TIMER_ENABLE | ESI_TIMER_MODE_TIMER | ESI_TIMER_WRAP_INT_ENABLE;

	/* Install interrupt handler. */
	install_irq_handler(timer_device->irq, handler);

	/* Unmask the timer interrupt. */
	esi_interrupt_set_mask(esi_interrupt_get_mask() |
			(1 << timer_device->irq));

	*timer_handle = timer_device;
}

void timer_stop(void * timer_handle)
{
	esi_device_info_t * timer_device = (esi_device_info_t *)timer_handle;
	esi_timer_t * timer = (esi_timer_t *)timer_device->base_address;
	timer->control = ESI_TIMER_DISABLE;
}

void timer_irq_ack(void * timer_handle)
{
	/* Clear the interrupt request. */
	esi_device_info_t * timer_device = (esi_device_info_t *)timer_handle;
	esi_timer_t * timer = (esi_timer_t *)timer_device->base_address;
    esi_timer_wrap_interrupt_acknowledge(timer);
	esi_interrupt_acknowledge(timer_device->irq);
}
#endif
