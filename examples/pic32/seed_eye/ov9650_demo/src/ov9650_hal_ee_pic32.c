/*
Copyright (C) 2009 -  Salvatore Marrapese, Claudio Salvadori 
and Christian Nastasi
This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.
*/

/*
 * ov9650_hal.c
 *
 * Created on: 9-feb-2009
 * Modified on: 23-jun-2012
 * Author: Salvatore Marrapese, Claudio Salvadori
 */

#include "inc/ov9650.h"
#include "inc/ov9650_hal_ee_pic32.h"

#include "mcu/microchip_pic32/inc/ee_i2c.h"
#include "mcu/microchip_pic32/inc/ee_oc.h"
#include "mcu/microchip_pic32/inc/ee_dma.h"

#include "console_serial.h"

#include "cpu/pic32/inc/ee_utils.h"
#include "sw_sccb.h"

/* We can use the sw i2c or hw i2c protocol */
#define SW_I2C

/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
/* These variables are declared volatile, maybe this declaration isn't 
 * need for them.
 * Actually, most of them shouldn't modified concurrently, or the driver
 * will fail anyway. */
static void (* volatile capture_complete_func) (ov9650_status_t) = NULL;
static uint8_t * volatile frame_buffer = NULL;
static volatile uint16_t row_id;
static volatile uint16_t height, width;
static volatile uint32_t frame_idx, image_size;

/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/
/* ----------------------------------------------------------------------------
|  Start OCx Interface:                                                        |
|                                                                              |
|  OCx: Generate MasterClock for OmniVision Camera (use TimerY)                |
 ---------------------------------------------------------------------------- */
void ov9650_oc_hal_init(uint32_t frequency)
{
	EE_oc_generate_clock_init(OV9650_OC_PORT, frequency);
}

void ov9650_oc_hal_start(void)
{
	EE_oc_generate_clock_start(OV9650_OC_PORT);
	
}

void ov9650_oc_hal_stop(void)
{
	EE_oc_generate_clock_stop(OV9650_OC_PORT);
}

ov9650_status_t ov9650_hal_init(uint8_t dma_channel)
{

	if (ov9650_i2c_hal_init() != OV9650_SUCCESS)
		return -OV9650_ERR_I2C_INIT;
	#ifdef __USE_DMA__
	if (ov9650_dma_hal_init() != OV9650_SUCCESS)
		return -OV9650_ERR_DMA_INIT; 
	#endif
	return OV9650_SUCCESS;
}

#ifdef __USE_DMA__
ov9650_status_t ov9650_dma_hal_init(void){

	/* Initialize the DMA channel 	*/
	EE_dma_init(OV9650_DMA_CH);

	/* Set the channel priority and some flags	*/
	EE_dma_advanced_setup(OV9650_DMA_CH, OV9650_DMA_PRIORITY, 
			OV9650_DMA_DEFAULT_FLAG);

	/* Set the source, destination, cell sizes, the interrupt associated
		and the priority  */
	EE_dma_init_transfer(OV9650_DMA_CH, OV9650_DMA_SOURCE_SIZE,
			width, OV9650_DMA_CELL_SIZE,
	OV9650_DMA_INT_SOURCE, OV9650_DMA_INT_PRIOR, 
			OV9650_DMA_INT_SUB_PRIOR);
	
	return OV9650_SUCCESS;
	
}
#endif // __USE_DMA__

/* ----------------------------------------------------------------------------
|  EOF Interrupt                                                               |
|                                                                              |
|  Interrupt that inform about the termination of the acquisition              |
 ---------------------------------------------------------------------------- */

OV9650_EOF_INTERRUPT()
{
	if (capture_complete_func)
		capture_complete_func(OV9650_SUCCESS);
	OV9650_EOF_RESET_IF();	/* Clear interrupt flag */
}

/* ----------------------------------------------------------------------------
|  ISR1 CN:                                                                    |
|                                                                              |
|  New row.                                                                    |
|  Change notify interrupt to understand the start of a new row; that means    |
|  the pixel value after this interrupt are valid value. So what this interrupt|
|  does is the pixel interrupt activation (start of row) and pixel interrupt   |
|  deactivation (end of row).                                                  |
|  In this interrupt is is implemented a procedure to resync the image buffer  |
|  if some pixels are lost in the previous row.                                |
|  This interrupt manages also the end-of-frame notification, switching on     |
|  an interrupt (INT0) that call a callback function                           |
 ---------------------------------------------------------------------------- */

OV9650_HSYNC_INTERRUPT()
{
	if (OV9650_HSYNC_VALUE() == OV9650_HSYNC_RISING) {
		/* Enables the DMA Channel  */
		OV9650_DMA_CH_ENABLE();
	} else {
		/* Disables the DMA Channel  */
		OV9650_DMA_CH_DISABLE();
		frame_idx += width;

		/* Check if last row is ready -> frame ready? */
		if((frame_idx >= image_size) || (++row_id >= height)) {
			/* Stop row and frame syncs, notify capture complete */
			OV9650_PIN_HSYNC_STOP();
			OV9650_PIN_VSYNC_STOP();
			OV9650_EOF_ACTIVATE_IF();  //Activate interrupt
		} else {
			/* Set the DMA source pointer for reading the Y0-Y7 camera pins */	
			OV9650_DMA_SOURCE_ADD_REG = 
			EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)OV9650_PIN_Y_ADDRESS);

			/* Set the DMA destionation to the correct line of the stored frame */
			OV9650_DMA_DEST_ADD_REG = 
				EE_ADDR_VIRTUAL_TO_PHYSICAL(frame_buffer + frame_idx);
		}
		OV9650_HSYNC_RESET_IF();	/* Reset CN interrupt flag */
	}
}

/* ----------------------------------------------------------------------------
|  ISR1 INT3:                                                                  |
|                                                                              |
|  New Frame.                                                                  |
|                                                                              |
|  Zeroing of row and pixel counters, set image dimension variables, start     |
|  reception of row interrupts.                                                |
|  If "Debug" configuration is possible to manage the function that measure    |
|  the frame duration, and toggle a value of output pin to show that duration  |
 ---------------------------------------------------------------------------- */
OV9650_VSYNC_INTERRUPT()
{
	OV9650_PIN_HSYNC_START();
	OV9650_VSYNC_RESET_IF();    /* Reset INT3 interrupt flag */
}

ov9650_status_t ov9650_i2c_hal_init(void)
{
	#ifdef SW_I2C
	sw_sccb_init();
	return OV9650_SUCCESS;
	#else
	if (EE_i2c_init(OV9650_I2C_PORT, OV9650_I2C_CLOCK, EE_I2C_DEFAULT_FLAGS) != EE_I2C_SUCCESS)
		return -OV9650_ERR_I2C_INIT;
	return OV9650_SUCCESS;
	#endif
}

ov9650_status_t ov9650_i2c_hal_reg_write(ov9650_reg_t reg, uint8_t val)
{
	#ifdef SW_I2C
	sw_sccb_write(OV9650_DEVICE_ID, (uint8_t) reg, val);
	return OV9650_SUCCESS;
	#else
	if (EE_i2c_write_byte(OV9650_I2C_PORT, OV9650_DEVICE_ID, reg, val) !=  EE_I2C_SUCCESS)
		return -OV9650_ERR_I2C_WRITE;
	return OV9650_SUCCESS;
	#endif
}

ov9650_status_t ov9650_i2c_hal_reg_read(ov9650_reg_t reg, uint8_t *val)
{
	#ifdef SW_I2C
	sw_sccb_read(OV9650_DEVICE_ID, (uint8_t) reg, val);
	return OV9650_SUCCESS; 
	#else
	
	if (EE_i2c_read_byte(OV9650_I2C_PORT, OV9650_DEVICE_ID, reg, val) !=  EE_I2C_SUCCESS)
		return -OV9650_ERR_I2C_READ;
	return OV9650_SUCCESS; 
	#endif
}

/* ----------------------------------------------------------------------------
|  Start Capture from OV9650 Camera :                                          |
|                                                                              |
|  - TODO:                                                                     |
 ---------------------------------------------------------------------------- */
ov9650_status_t ov9650_hal_capture(uint8_t *image, ov9650_cback_t *func)
{
	frame_idx 	= 0;
	row_id = 0;

	//Read the size of the picture (colour is alway present)
	width 	= 2 * ov9650_get_width();
	height 	= ov9650_get_height();
	image_size = ov9650_get_size();
	
	#ifdef __USE_DMA__
	if (ov9650_dma_hal_init() != OV9650_SUCCESS)
		return -OV9650_ERR_DMA_INIT;
	#endif

	frame_buffer = image;
	capture_complete_func = func;

	/* Set the DMA source pointer to the PIN_Y 8 bit BUS */
	OV9650_DMA_SOURCE_ADD_REG = 
		EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)OV9650_PIN_Y_ADDRESS);

	/* Set the DMA destionation pointer to the first line of the	*/
	/* stored frame							*/
	OV9650_DMA_DEST_ADD_REG = 
		EE_ADDR_VIRTUAL_TO_PHYSICAL(frame_buffer);

	OV9650_VSYNC_RESET_IF();

	//Enables the interrupt associated with the VSYN
	OV9650_PIN_VSYNC_START();	/* Initializes the Frame Sync */

	return OV9650_SUCCESS;
}

