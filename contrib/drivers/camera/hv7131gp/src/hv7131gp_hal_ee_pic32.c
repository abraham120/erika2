/*
Copyright (C) 2009 -  Claudio Salvadori and Christian Nastasi
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
 * hv7131gp_hal.c
 *
 * Created on: 9-feb-2009
 * Author: Claudio Salvadori
 */

#include "hv7131gp_hal.h"
#include "hv7131gp.h"

#include "mcu/microchip_pic32/inc/ee_i2c.h"
#include "mcu/microchip_pic32/inc/ee_oc.h"
#include "mcu/microchip_pic32/inc/ee_dma.h"

#include "cpu/pic32/inc/ee_utils.h"

/******************************************************************************/
/*                          Local Variables                                   */
/******************************************************************************/
/* These variables are declared volatile, but probably there is no need for
 * it.  Actually, most of them shouldn't modified concurrently, or the driver
 * will fail anyway. */
static void (* volatile capture_complete_func) (hv7131gp_status_t) = NULL;
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
|  OCx: Generate MasterClock for Sparkfun Camera (use TimerY)                  |                       
 ---------------------------------------------------------------------------- */
void hv7131gp_oc_hal_init(uint32_t frequency)
{
	EE_oc_generate_clock_init(HV7131GP_OC_PORT, frequency);
	
}

void hv7131gp_oc_hal_start(void)
{
	EE_oc_generate_clock_start(HV7131GP_OC_PORT);
	
}

void hv7131gp_oc_hal_stop(void)
{
	EE_oc_generate_clock_stop(HV7131GP_OC_PORT);
}

/* ----------------------------------------------------------------------------
|  EOF Interrupt                                                               |
|                                                                              |
|  Interrupt that inform about the termination of the acquisition              |
 ---------------------------------------------------------------------------- */

HV7131GP_EOF_INTERRUPT()
{
	if (capture_complete_func)
		capture_complete_func(HV7131GP_SUCCESS);
	HV7131GP_EOF_RESET_IF();	/* Clear interrupt flag */
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

#ifdef HV7131GP_HSYNC_INT_MODE
HV7131GP_HSYNC_INTERRUPT()                
{
#ifdef __USE_DMA__


#ifdef __INT_DMA__
if (HV7131GP_HSYNC_VALUE() == HV7131GP_HSYNC_RISING) {
#endif	//__INT_DMA__

		
	#ifndef __INT_DMA__
	/* Disable Interrupts */
	HV7131GP_HAL_DISABLE_INTERRUPTS();
	#endif// __INT_DMA__
	
		
	/* Enables the DMA Channel  */
	HV7131GP_DMA_CH_ENABLE();


	#ifndef __INT_DMA__	
	while(HV7131GP_HSYNC_VALUE())
	{		
		while( HV7131GP_VCLK_PIN_VALUE() ) ;	//Pixel clock			
			HV7131GP_DMA_FORCE_START(); 	// Force Tx Start 
	}	
	#endif
		
	#ifdef __INT_DMA__
} else {
	#endif //__INT_DMA__

	#ifdef __INT_DMA__
	/* Enables the DMA Channel  */
	HV7131GP_DMA_CH_DISABLE();
	#endif
	
	frame_idx += width;

	#ifndef __INT_DMA__
	HV7131GP_HAL_ENABLE_INTERRUPTS();
	#endif// __INT_DMA__
	/* Check if last row is ready -> frame ready? */

	
	if((frame_idx >= image_size) || (++row_id >= height)){
		/* Stop row and frame syncs, notify capture complete */
		HV7131GP_PIN_HSYNC_STOP();
		HV7131GP_PIN_VSYNC_STOP();
		HV7131GP_EOF_ACTIVATE_IF(); //Activate interrupt
	} else {
		/* Set the DMA source pointer for reading the Y0-Y7 camera pins */	
		HV7131GP_DMA_SOURCE_ADD_REG = 
		EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)HV7131GP_PIN_Y_ADDRESS);

	/* Set the DMA destionation to the correct line of the stored frame */
	
		HV7131GP_DMA_DEST_ADD_REG = 
			EE_ADDR_VIRTUAL_TO_PHYSICAL(frame_buffer + frame_idx);

	}
	HV7131GP_HSYNC_RESET_IF();			/* Reset CN interrupt flag */
		
	#ifdef __INT_DMA__
	}
	#endif	//__INT_DMA__

#endif // __USE_DMA__
}
#endif


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

HV7131GP_VSYNC_INTERRUPT()
{	
	HV7131GP_PIN_HSYNC_START();
	HV7131GP_VSYNC_RESET_IF();    /* Reset INT3 interrupt flag */
}


#ifdef __USE_DMA__
hv7131gp_status_t hv7131gp_dma_hal_init(void){

	/* Initialize the DMA channel 	*/
	EE_dma_init(HV7131GP_DMA_CH);

	/* Set the channel priority and some flags	*/
	EE_dma_advanced_setup(HV7131GP_DMA_CH, HV7131GP_DMA_PRIORITY, 
			HV7131GP_DMA_DEFAULT_FLAG);

	/* Set the source, destination, cell sizes, the interrupt associated
		and the priority  */
	EE_dma_init_transfer(HV7131GP_DMA_CH, HV7131GP_DMA_SOURCE_SIZE,
			width, HV7131GP_DMA_CELL_SIZE,
	HV7131GP_DMA_INT_SOURCE, HV7131GP_DMA_INT_PRIOR, 
			HV7131GP_DMA_INT_SUB_PRIOR);
	
	return HV7131GP_SUCCESS;
	
}
#endif // __USE_DMA__


hv7131gp_status_t hv7131gp_i2c_hal_init(void)
{
	if (EE_i2c_init(HV7131GP_I2C_PORT, HV7131GP_I2C_CLOCK, EE_I2C_DEFAULT_FLAGS) != EE_I2C_SUCCESS)
		return -HV7131GP_ERR_I2C_INIT;
	return HV7131GP_SUCCESS;
}

hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t val)
{
	if (EE_i2c_write_byte(HV7131GP_I2C_PORT, HV7131GP_DEVICE_ID, reg, val) !=  EE_I2C_SUCCESS)
		return -HV7131GP_ERR_I2C_WRITE;
	return HV7131GP_SUCCESS;
}

hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val)
{
	
	if (EE_i2c_read_byte(HV7131GP_I2C_PORT, HV7131GP_DEVICE_ID, reg, val) !=  EE_I2C_SUCCESS)
		return -HV7131GP_ERR_I2C_READ;
	return HV7131GP_SUCCESS; 
}


hv7131gp_status_t hv7131gp_hal_init(uint8_t dma_channel){
	
	
	if (hv7131gp_i2c_hal_init() != HV7131GP_SUCCESS)
		return -HV7131GP_ERR_I2C_INIT;
	#ifdef __USE_DMA__
		
	if (hv7131gp_dma_hal_init() != HV7131GP_SUCCESS)
		return -HV7131GP_ERR_DMA_INIT; 
	#endif
	return HV7131GP_SUCCESS;
}


/* ----------------------------------------------------------------------------
|  Start Capture from HV7131GP Camera :                                        |
|                                                                              |
|  - TODO:                                                                     |
 ---------------------------------------------------------------------------- */
hv7131gp_status_t hv7131gp_hal_capture(uint8_t *image, hv7131gp_cback_t *func)
{
	frame_idx 	= 0;
	row_id = 0;
	
	//Read the size of the picture
	width 	= hv7131gp_get_width();
	height 	= hv7131gp_get_height();
	image_size = hv7131gp_get_size();
	
	#ifdef __USE_DMA__
	if (hv7131gp_dma_hal_init() != HV7131GP_SUCCESS)
		return -HV7131GP_ERR_DMA_INIT;
	#endif

	frame_buffer = image;
	capture_complete_func = func;

	/* Set the DMA source pointer to the PIN_Y 8 bit BUS */
	HV7131GP_DMA_SOURCE_ADD_REG = 
	EE_ADDR_VIRTUAL_TO_PHYSICAL((void *)HV7131GP_PIN_Y_ADDRESS);

	/* Set the DMA destionation pointer to the first line of the	*/
	/* stored frame							*/
	HV7131GP_DMA_DEST_ADD_REG = 
			EE_ADDR_VIRTUAL_TO_PHYSICAL(frame_buffer);

	HV7131GP_VSYNC_RESET_IF();

	//Enables the interrupt associated with the VSYN
	HV7131GP_PIN_VSYNC_START();	/* Initializes the Frame Sync */

	return HV7131GP_SUCCESS;
}

