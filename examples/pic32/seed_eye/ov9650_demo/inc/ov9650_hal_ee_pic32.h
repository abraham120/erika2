/*
Copyright (C) 2012 - Salvatore Marrapese, Claudio Salvadori and 
Christian Nastasi.
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
 * ov9650_hal_ee_pic32.c
 *
 */

#ifndef OV9650_HAL_EE_PIC32_H_
#define OV9650_HAL_EE_PIC32_H_

#include "ee_cn_config.h"
#include "ov9650_types.h"
#include "ov9650_reg.h"
#include "mcu/microchip_pic32/inc/ee_cn.h"

/******************************************************************************/
/*			Board Selection					                                  */
/******************************************************************************/

#include "ov9650_hal_ee_board_single_128k.h"

/******************************************************************************/
/*                         Functions Prototypes                               */
/******************************************************************************/

ov9650_status_t ov9650_hal_init(uint8_t DMA_CH);

void ov9650_oc_hal_init(uint32_t frequency);
void ov9650_oc_hal_start(void);
void ov9650_oc_hal_stop(void);

COMPILER_INLINE void ov9650_hal_delay_us(uint32_t delay_count)
{
	EE_delay_us(delay_count);
}

ov9650_status_t ov9650_i2c_hal_init(void);
ov9650_status_t ov9650_i2c_hal_reg_write(ov9650_reg_t reg, uint8_t  val);
ov9650_status_t ov9650_i2c_hal_reg_read(ov9650_reg_t reg, uint8_t *val);
ov9650_status_t ov9650_dma_hal_init();
ov9650_status_t ov9650_hal_capture(uint8_t *image, ov9650_cback_t *func);

/******************************************************************************/
/*                           Hardware Abstraction Layer                       */
/******************************************************************************/

#define OV9650_HAL_DRIVING_PINS           1

#define	OV9650_MORE_THAN_1_MS			1500
#define	OV9650_MORE_THAN_4_MCLK_CYCLES	1 	
#define	OV9650_MORE_THAN_2086000_MCLK_CYCLES	300000

#ifndef OV9650_MCLK_FREQ
#define OV9650_MCLK_FREQ	OV9650_OC_FREQ 
#endif

#ifdef __32MX360F512L__
#define OV9650_MAX_SIZE	19200	/**< For PIC32MX */
#endif

#ifdef __32MX795F512L__
#ifndef OV9650_MAX_SIZE
#define OV9650_MAX_SIZE	19200	/**< For PIC32MX */
#endif //OV9650_MAX_SIZE
#endif

/******************************************************************************/
/* 				OC specific definition			      */
/******************************************************************************/

#ifndef OV9650_OC_FREQ
#define OV9650_OC_FREQ 	5000000ul
#endif

/******************************************************************************/
/* 				DMA specific definition			      */
/******************************************************************************/

/* Registers exploited */
#ifndef OV9650_DMA_CH
#define OV9650_DMA_CH				EE_DMA_CH0
#endif

#if (OV9650_DMA_CH == 0)
#define OV9650_DMA_DEST_ADD_REG		DCH0DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH0SSA
#define OV9650_DMA_CH_ENABLE()		DCH0CONSET = _DCH0CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH0CONCLR = _DCH0CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH0ECONSET = _DCH0ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 1)
#define OV9650_DMA_DEST_ADD_REG		DCH1DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH1SSA
#define OV9650_DMA_CH_ENABLE()		DCH1CONSET = _DCH1CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH1CONCLR = _DCH1CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH1ECONSET = _DCH1ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 2)
#define OV9650_DMA_DEST_ADD_REG		DCH2DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH2SSA
#define OV9650_DMA_CH_ENABLE()		DCH2ONSET = _DCH2CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH2CONCLR = _DCH2CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH2ECONSET = _DCH2ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 3)
#define OV9650_DMA_DEST_ADD_REG		DCH3DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH3SSA
#define OV9650_DMA_CH_ENABLE()		DCH3CONSET = _DCH3CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH3CONCLR = _DCH3CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH3ECONSET = _DCH3ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 4)
#define OV9650_DMA_DEST_ADD_REG		DCH4DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH4SSA
#define OV9650_DMA_CH_ENABLE()		DCH4CONSET = _DCH4CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH4CONCLR = _DCH4CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH4ECONSET = _DCH4ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 5)
#define OV9650_DMA_DEST_ADD_REG		DCH5DSA				 
#define OV9650_DMA_SOURCE_ADD_REG	DCH5SSA	
#define OV9650_DMA_CH_ENABLE()		DCH5CONSET = _DCH5CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH5CONCLR = _DCH5CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH5ECONSET = _DCH5ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 6)
#define OV9650_DMA_DEST_ADD_REG		DCH6DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH6SSA
#define OV9650_DMA_CH_ENABLE()		DCH6CONSET = _DCH6CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH6CONCLR = _DCH6CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH6ECONSET = _DCH6ECON_CFORCE_MASK

#elif	(OV9650_DMA_CH == 7)
#define OV9650_DMA_DEST_ADD_REG		DCH7DSA
#define OV9650_DMA_SOURCE_ADD_REG	DCH7SSA
#define OV9650_DMA_CH_ENABLE()		DCH7CONSET = _DCH7CON_CHEN_MASK
#define OV9650_DMA_CH_DISABLE()		DCH7CONCLR = _DCH7CON_CHEN_MASK
#define OV9650_DMA_FORCE_START()	DCH7ECONSET = _DCH7ECON_CFORCE_MASK

#endif

/* Macro definitions used */

#ifndef OV9650_DMA_PRIORITY
#define OV9650_DMA_PRIORITY			3
#endif

#define OV9650_DMA_DEFAULT_FLAG		0

#define OV9650_DMA_SOURCE_SIZE		1

#define OV9650_DMA_CELL_SIZE		1

#ifndef	OV9650_DMA_INT_PRIOR
#define OV9650_DMA_INT_PRIOR		5
#endif

#ifndef OV9650_DMA_INT_SUB_PRIOR
#define OV9650_DMA_INT_SUB_PRIOR	2
#endif 

#define OV9650_DMA_INT_SOURCE		OV9650_PCLK_INT_TABLE_POSITION

/********************************************************/
/* 		Interrupt Management Functions		*/
/********************************************************/

#define OV9650_HAL_DISABLE_INTERRUPTS() asm volatile("di")
#define OV9650_HAL_ENABLE_INTERRUPTS() asm volatile("ei")

/* For compatibilty with other HALs */
#define ov9650_hal_init_ack() OV9650_SUCCESS

#endif /* OV9650_HAL_EE_PIC32_H_ */
