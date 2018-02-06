/** 
* @file ee_dma.h
* @brief DMA interface for PIC32MX
* @author Ghibaudi Marco
* @version 0.1
* @date 2010-14-07
*/
#ifndef __INCLUDE_MICROCHIP_PIC32_DMA_H__
#define __INCLUDE_MICROCHIP_PIC32_DMA_H__

#include "ee.h"


/******************************************************************************/
/*				Channels Definition			      */
/******************************************************************************/

#ifdef __32MX795F512L__

#define	EE_DMA_CH0  	0
#define	EE_DMA_CH1  	1
#define	EE_DMA_CH2  	2
#define	EE_DMA_CH3  	3
#define	EE_DMA_CH4  	4
#define	EE_DMA_CH5 	5
#define	EE_DMA_CH6  	6
#define	EE_DMA_CH7  	7

#else 

#define	EE_DMA_CH0 	0
#define	EE_DMA_CH1 	1
#define	EE_DMA_CH2 	2
#define	EE_DMA_CH3 	3

#endif


/******************************************************************************/
/*				Returned Messages 			      */
/******************************************************************************/


#define EE_DMA_NO_ERR				1 //returned positive

#define EE_DMA_CHANNEL_NOT_AVAILABLE		1

/******************************************************************************/
/*			Event Control Register Flags			      */
/******************************************************************************/



#define EE_DMA_CH0_START_TRANS_IRQ		_DCH0ECON_SIRQEN_MASK
#define EE_DMA_CH0_START_TRANS_MANUALLY		_DCH0ECON_CFORCE_MASK	
#define EE_DMA_CH0_ABORT_TRANS			_DCH0ECON_CABORT_MASK

#define EE_DMA_CH1_START_TRANS_IRQ		_DCH1ECON_SIRQEN_MASK
#define EE_DMA_CH1_START_TRANS_MANUALLY		_DCH1ECON_CFORCE_MASK	
#define EE_DMA_CH1_ABORT_TRANS			_DCH1ECON_CABORT_MASK

#define EE_DMA_CH2_START_TRANS_IRQ		_DCH2ECON_SIRQEN_MASK
#define EE_DMA_CH2_START_TRANS_MANUALLY		_DCH2ECON_CFORCE_MASK	
#define EE_DMA_CH2_ABORT_TRANS			_DCH2ECON_CABORT_MASK

#define EE_DMA_CH3_START_TRANS_IRQ		_DCH3ECON_SIRQEN_MASK
#define EE_DMA_CH3_START_TRANS_MANUALLY		_DCH3ECON_CFORCE_MASK	
#define EE_DMA_CH3_ABORT_TRANS			_DCH3ECON_CABORT_MASK

/* Additional DMA Channel definitions specific for the 32MX795F512L devices  */

#ifdef __32MX795F512L__

#define EE_DMA_CH4_START_TRANS_IRQ		_DCH4ECON_SIRQEN_MASK
#define EE_DMA_CH4_START_TRANS_MANUALLY		_DCH4ECON_CFORCE_MASK	
#define EE_DMA_CH4_ABORT_TRANS			_DCH4ECON_CABORT_MASK

#define EE_DMA_CH5_START_TRANS_IRQ		_DCH5ECON_SIRQEN_MASK
#define EE_DMA_CH5_START_TRANS_MANUALLY		_DCH5ECON_CFORCE_MASK	
#define EE_DMA_CH5_ABORT_TRANS			_DCH5ECON_CABORT_MASK

#define EE_DMA_CH6_START_TRANS_IRQ		_DCH6ECON_SIRQEN_MASK
#define EE_DMA_CH6_START_TRANS_MANUALLY		_DCH6ECON_CFORCE_MASK	
#define EE_DMA_CH6_ABORT_TRANS			_DCH6ECON_CABORT_MASK

#define EE_DMA_CH7_START_TRANS_IRQ		_DCH7ECON_SIRQEN_MASK
#define EE_DMA_CH7_START_TRANS_MANUALLY		_DCH7ECON_CFORCE_MASK	
#define EE_DMA_CH7_ABORT_TRANS			_DCH7ECON_CABORT_MASK

#endif


/******************************************************************************/
/*				Prototypes				      */
/******************************************************************************/


EE_INT8 EE_dma_init(EE_UINT8 channel);



EE_INT8 EE_dma_advanced_setup(EE_UINT8 channel, EE_UINT8 subpriority, 
				EE_UREG event_control_flags );



EE_INT8 EE_dma_init_transfer(EE_UINT8 channel, EE_UINT16 source_size, 
		EE_UINT16 destination_size, EE_UINT16 cell_size, 
		EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior); 


#endif	//__INCLUDE_MICROCHIP_PIC32_DMA_H__

