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
 * hv7131gp_hal_ee_pic32.c
 *
 */

#ifndef HV7131GP_HAL_EE_PIC32_H_
#define HV7131GP_HAL_EE_PIC32_H_

#include "hv7131gp_types.h"
#include "hv7131gp_reg.h"
#include "mcu/microchip_pic32/inc/ee_cn.h"



/******************************************************************************/
/*			Board Selection					      */
/******************************************************************************/

#if defined __USE_SINGLE_PIC_128K__

#include "hv7131gp_hal_ee_board_single_128k.h"

#elif defined __USE_IPERMOB_BOARD_V2__

#include "board/ipermob_board_v2/inc/ee_hv7131gp_camera_board.h"

#else	//Standard ELCO_BOARD

#include "board/ipermob_db_pic32/inc/ee_hv7131gp_camera_board.h"

#endif


/******************************************************************************/
/*                         Functions Prototypes                               */
/******************************************************************************/




hv7131gp_status_t hv7131gp_hal_init(uint8_t DMA_CH);

void hv7131gp_oc_hal_init(uint32_t frequency);
void hv7131gp_oc_hal_start(void);
void hv7131gp_oc_hal_stop(void);

COMPILER_INLINE void hv7131gp_hal_delay_us(uint32_t delay_count)
{
	EE_delay_us(delay_count);
}

hv7131gp_status_t hv7131gp_i2c_hal_init(void);
hv7131gp_status_t hv7131gp_i2c_hal_reg_write(hv7131gp_reg_t reg, uint8_t  val);
hv7131gp_status_t hv7131gp_i2c_hal_reg_read(hv7131gp_reg_t reg, uint8_t *val);
hv7131gp_status_t hv7131gp_dma_hal_init();
hv7131gp_status_t hv7131gp_hal_capture(uint8_t *image, hv7131gp_cback_t *func);



/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/

#define HV7131GP_HAL_DRIVING_PINS           1

#define	HV7131GP_MORE_THAN_1_MS			1500
#define	HV7131GP_MORE_THAN_4_MCLK_CYCLES	1 	
#define	HV7131GP_MORE_THAN_2086000_MCLK_CYCLES	300000

//Main clock speed

//#define SYSTEM_INSTRUCTION_CLOCK 80000000ul
//#define	HV7131GP_MCLK_PERIOD	0x02

#ifndef HV7131GP_MCLK_FREQ
#define HV7131GP_MCLK_FREQ	HV7131GP_OC_FREQ 
#endif


#ifdef __32MX360F512L__
#define HV7131GP_MAX_SIZE	19200	/**< For PIC32MX */
#endif

#ifdef __32MX795F512L__
#ifndef HV7131GP_MAX_SIZE
#define HV7131GP_MAX_SIZE	19200	/**< For PIC32MX */
#endif //HV7131GP_MAX_SIZE
#endif


/******************************************************************************/
/* 				OC specific definition			      */
/******************************************************************************/

//TODO: Must be implemented a logic of selection between the available boards

#ifndef HV7131GP_OC_FREQ
#define HV7131GP_OC_FREQ 	20000000ul
#endif

/******************************************************************************/
/* 				I2C specific definition			      */
/******************************************************************************/



#ifndef HV7131GP_I2C_CLOCK
#define HV7131GP_I2C_CLOCK 	EE_I2C_400KHZ
#endif

/******************************************************************************/
/* 				DMA specific definition			      */
/******************************************************************************/


/* Registers exploited */
#ifndef HV7131GP_DMA_CH
#define HV7131GP_DMA_CH				EE_DMA_CH0
#endif


#if (HV7131GP_DMA_CH == 0)

#define HV7131GP_DMA_DEST_ADD_REG		DCH0DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH0SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH0CONSET = _DCH0CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH0CONCLR = _DCH0CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH0ECONSET = _DCH0ECON_CFORCE_MASK				 

#elif	(HV7131GP_DMA_CH == 1)				 

#define HV7131GP_DMA_DEST_ADD_REG		DCH1DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH1SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH1CONSET = _DCH1CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH1CONCLR = _DCH1CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH1ECONSET = _DCH1ECON_CFORCE_MASK

#elif	(HV7131GP_DMA_CH == 2)

#define HV7131GP_DMA_DEST_ADD_REG		DCH2DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH2SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH2ONSET = _DCH2CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH2CONCLR = _DCH2CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH2ECONSET = _DCH2ECON_CFORCE_MASK


#elif	(HV7131GP_DMA_CH == 3)

#define HV7131GP_DMA_DEST_ADD_REG		DCH3DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH3SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH3CONSET = _DCH3CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH3CONCLR = _DCH3CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH3ECONSET = _DCH3ECON_CFORCE_MASK

#elif	(HV7131GP_DMA_CH == 4)

#define HV7131GP_DMA_DEST_ADD_REG		DCH4DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH4SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH4CONSET = _DCH4CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH4CONCLR = _DCH4CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH4ECONSET = _DCH4ECON_CFORCE_MASK

#elif	(HV7131GP_DMA_CH == 5)

#define HV7131GP_DMA_DEST_ADD_REG		DCH5DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH5SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH5CONSET = _DCH5CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH5CONCLR = _DCH5CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH5ECONSET = _DCH5ECON_CFORCE_MASK

#elif	(HV7131GP_DMA_CH == 6)

#define HV7131GP_DMA_DEST_ADD_REG		DCH6DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH6SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH6CONSET = _DCH6CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH6CONCLR = _DCH6CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH6ECONSET = _DCH6ECON_CFORCE_MASK


#elif	(HV7131GP_DMA_CH == 7)

#define HV7131GP_DMA_DEST_ADD_REG		DCH7DSA				 
#define HV7131GP_DMA_SOURCE_ADD_REG		DCH7SSA	
#define HV7131GP_DMA_CH_ENABLE()		DCH7CONSET = _DCH7CON_CHEN_MASK
#define HV7131GP_DMA_CH_DISABLE()		DCH7CONCLR = _DCH7CON_CHEN_MASK
#define HV7131GP_DMA_FORCE_START()		DCH7ECONSET = _DCH7ECON_CFORCE_MASK


#endif


/* Macro definitions used */

#ifndef HV7131GP_DMA_PRIORITY
#define HV7131GP_DMA_PRIORITY			3
#endif

#define HV7131GP_DMA_DEFAULT_FLAG		0
	

#define HV7131GP_DMA_SOURCE_SIZE		1


#define HV7131GP_DMA_CELL_SIZE			1

#ifndef	HV7131GP_DMA_INT_PRIOR
#define HV7131GP_DMA_INT_PRIOR			5
#endif

#ifndef HV7131GP_DMA_INT_SUB_PRIOR
#define HV7131GP_DMA_INT_SUB_PRIOR		2
#endif 

#define HV7131GP_DMA_INT_SOURCE			HV7131GP_VCLK_INT_TABLE_POSITION




/********************************************************/
/* 		Interrupt Management Functions		*/
/********************************************************/

#define HV7131GP_HAL_DISABLE_INTERRUPTS() asm volatile("di")
#define HV7131GP_HAL_ENABLE_INTERRUPTS() asm volatile("ei")


/* For compatibilty with other HALs */
#define hv7131gp_hal_init_ack() HV7131GP_SUCCESS

#endif /* HV7131GP_HAL_EE_PIC32_H_ */
