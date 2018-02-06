#include "mcu/microchip_pic32/inc/ee_dma.h"
#include "cpu/pic32/inc/ee_utils.h"

#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif


/******************************************************************************/
/*				Local Functions				      */
/******************************************************************************/

EE_INT8	dma_init_ch0(void) {


	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA0IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA0IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 

	return EE_DMA_NO_ERR;
}

EE_INT8	dma_init_ch1(void) {


	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA1IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA1IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 

	return EE_DMA_NO_ERR;
}


EE_INT8	dma_init_ch2(void) {


	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA2IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA2IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 

	return EE_DMA_NO_ERR;
}

EE_INT8	dma_init_ch3(void) {


	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA3IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA3IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 

	return EE_DMA_NO_ERR;
}


#ifdef __32MX795F512L__
EE_INT8	dma_init_ch4(void) {
	
	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA4IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA4IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 	
	return EE_DMA_NO_ERR;

}

EE_INT8	dma_init_ch5(void) {
	
	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA5IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA5IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 	
	return EE_DMA_NO_ERR;

}

EE_INT8	dma_init_ch6(void) {
	
	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA6IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA6IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 	
	return EE_DMA_NO_ERR;

}

EE_INT8	dma_init_ch7(void) {
	
	/* Disabled the DMA interrupts */	
	IEC1CLR = _IEC1_DMA7IE_MASK;  		
	/* Cleaned the DMA interrupt flags */
	IFS1CLR = _IFS1_DMA7IF_MASK; 		
	
	/* Turn on the DMA peripheral */		
	DMACONSET = _DMACON_ON_MASK; 	
	return EE_DMA_NO_ERR;

}

#endif //__32MX795F512L__



EE_INT8 dma_event_setup_ch0(EE_UINT8 subpriority, EE_UREG event_control_flags) {


	/* Setup of the priority of the channel */
	DCH0CONSET = (subpriority) & _DCH0CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH0CONCLR = _DCH0CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH0ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

EE_INT8 dma_event_setup_ch1(EE_UINT8 subpriority, EE_UREG event_control_flags) {


	/* Setup of the priority of the channel */
	DCH1CONSET = (subpriority) & _DCH1CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH1CONCLR = _DCH1CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH1ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

EE_INT8 dma_event_setup_ch2(EE_UINT8 subpriority, EE_UREG event_control_flags) {


	/* Setup of the priority of the channel */
	DCH2CONSET = (subpriority) & _DCH2CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH2CONCLR = _DCH2CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH2ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

EE_INT8 dma_event_setup_ch3(EE_UINT8 subpriority, EE_UREG event_control_flags) {


	/* Setup of the priority of the channel */
	DCH3CONSET = (subpriority) & _DCH3CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH3CONCLR = _DCH3CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH3ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

#ifdef __32MX795F512L__
EE_INT8	dma_event_setup_ch4(EE_UINT8 subpriority, EE_UREG event_control_flags) {
	
	/* Setup of the priority of the channel */
	DCH4CONSET = (subpriority) & _DCH4CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH4CONCLR = _DCH4CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH4ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

EE_INT8	dma_event_setup_ch5(EE_UINT8 subpriority, EE_UREG event_control_flags) {
	
	/* Setup of the priority of the channel */
	DCH5CONSET = (subpriority) & _DCH5CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH5CONCLR = _DCH5CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH5ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

EE_INT8	dma_event_setup_ch6(EE_UINT8 subpriority, EE_UREG event_control_flags) {
	
	/* Setup of the priority of the channel */
	DCH6CONSET = (subpriority) & _DCH6CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH6CONCLR = _DCH6CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH6ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}

EE_INT8	dma_event_setup_ch7(EE_UINT8 subpriority, EE_UREG event_control_flags) {
	
	/* Setup of the priority of the channel */
	DCH7CONSET = (subpriority) & _DCH7CON_CHPRI_MASK;
	
	/* Channel disabled */ 
	DCH7CONCLR = _DCH7CON_CHEN_MASK;
	
	/* Set of the  */ 
	DCH7ECONSET = event_control_flags;

	return EE_DMA_NO_ERR;

}
#endif //__32MX795F512L__


EE_INT8 dma_init_transfer_ch0(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {


	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH0SSIZ = (EE_UINT16) source_size;
	DCH0DSIZ = (EE_UINT16) destination_size; 
	DCH0CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH0INTCLR = 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH0ECON = _DCH0ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH0ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC9CLR = _IPC9_DMA0IP_MASK | _IPC9_DMA0IS_MASK;
		IPC9SET = ((int_prior <<_IPC9_DMA0IP_POSITION ) & _IPC9_DMA0IP_MASK)  |
			  ((int_subprior << _IPC9_DMA0IS_POSITION) & _IPC9_DMA0IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}

EE_INT8 dma_init_transfer_ch1(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH1SSIZ = (EE_UINT16) source_size;
	DCH1DSIZ = (EE_UINT16) destination_size; 
	DCH1CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH1INTCLR = 0;	
	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH1ECON = _DCH1ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH1ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC9CLR = _IPC9_DMA1IP_MASK | _IPC9_DMA1IS_MASK;
		IPC9SET = ((int_prior <<_IPC9_DMA1IP_POSITION ) & _IPC9_DMA1IP_MASK)  | 
		((int_subprior << _IPC9_DMA1IS_POSITION) & _IPC9_DMA1IS_MASK);	
			
	}
	
	return EE_DMA_NO_ERR;
}


EE_INT8 dma_init_transfer_ch2(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH2SSIZ = (EE_UINT16) source_size;
	DCH2DSIZ = (EE_UINT16) destination_size; 
	DCH2CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH2INTCLR = 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH2ECON = _DCH2ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH2ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC9CLR = _IPC9_DMA2IP_MASK | _IPC9_DMA2IS_MASK;
		IPC9SET = ((int_prior <<_IPC9_DMA2IP_POSITION ) & _IPC9_DMA2IP_MASK)  |
			  ((int_subprior << _IPC9_DMA2IS_POSITION) & _IPC9_DMA2IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}


EE_INT8 dma_init_transfer_ch3(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH3SSIZ = (EE_UINT16) source_size;
	DCH3DSIZ = (EE_UINT16) destination_size; 
	DCH3CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH3INTCLR = 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH3ECON = _DCH3ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH3ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC9CLR = _IPC9_DMA3IP_MASK | _IPC9_DMA3IS_MASK;
		IPC9SET = ((int_prior <<_IPC9_DMA3IP_POSITION ) & _IPC9_DMA3IP_MASK)  |
			  ((int_subprior << _IPC9_DMA3IS_POSITION) & _IPC9_DMA3IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}




#ifdef __32MX795F512L__
EE_INT8 dma_init_transfer_ch4(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH4SSIZ = (EE_UINT16) source_size;
	DCH4DSIZ = (EE_UINT16) destination_size; 
	DCH4CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH4INTCLR= 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH4ECON = _DCH4ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH4ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC10CLR = _IPC10_DMA4IP_MASK | _IPC10_DMA4IS_MASK;
		IPC10SET = ((int_prior <<_IPC10_DMA4IP_POSITION ) & _IPC10_DMA4IP_MASK)  |
			  ((int_subprior << _IPC10_DMA4IS_POSITION) & _IPC10_DMA4IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}

EE_INT8 dma_init_transfer_ch5(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH5SSIZ = (EE_UINT16) source_size;
	DCH5DSIZ = (EE_UINT16) destination_size; 
	DCH5CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH5INTCLR= 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH5ECON = _DCH5ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH5ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC10CLR = _IPC10_DMA5IP_MASK | _IPC10_DMA5IS_MASK;
		IPC10SET = ((int_prior <<_IPC10_DMA5IP_POSITION ) & _IPC10_DMA5IP_MASK)  |
			  ((int_subprior << _IPC10_DMA5IS_POSITION) & _IPC10_DMA5IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}

EE_INT8 dma_init_transfer_ch6(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH6SSIZ = (EE_UINT16) source_size;
	DCH6DSIZ = (EE_UINT16) destination_size; 
	DCH6CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH6INTCLR= 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH6ECON = _DCH6ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH6ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC10CLR = _IPC10_DMA6IP_MASK | _IPC10_DMA6IS_MASK;
		IPC10SET = ((int_prior <<_IPC10_DMA6IP_POSITION ) & _IPC10_DMA6IP_MASK)  |
			  ((int_subprior << _IPC10_DMA6IS_POSITION) & _IPC10_DMA6IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}

EE_INT8 dma_init_transfer_ch7(EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {

	/* Setup of the source, destination and cell size. See refman for more
	specific information about the use	*/
	DCH7SSIZ = (EE_UINT16) source_size;
	DCH7DSIZ = (EE_UINT16) destination_size; 
	DCH7CSIZ = (EE_UINT16) cell_size;

	/* Interrupt register clean */	
	DCH7INTCLR= 0;	

	
	/* Set the interrupt source that starts the acquisition */	
	if ( interrupt_request_source >= 0 ) {
		DCH7ECON = _DCH7ECON_SIRQEN_MASK | 
			       (interrupt_request_source  << _DCH7ECON_CHSIRQ_POSITION);
	
		/* Set the interrupt priority */
		IPC10CLR = _IPC10_DMA7IP_MASK | _IPC10_DMA7IS_MASK;
		IPC10SET = ((int_prior <<_IPC10_DMA7IP_POSITION ) & _IPC10_DMA7IP_MASK)  |
			  ((int_subprior << _IPC10_DMA7IS_POSITION) & _IPC10_DMA7IS_MASK);	
	}
	
	return EE_DMA_NO_ERR;
}
#endif //__32MX795F512L__




/******************************************************************************/
/*				Global Functions			      */
/******************************************************************************/



EE_INT8 EE_dma_init(EE_UINT8 channel) {
	switch (channel) {
		case EE_DMA_CH0:
			return dma_init_ch0();
		break;
		case EE_DMA_CH1:
			return dma_init_ch1();
		break;

		case EE_DMA_CH2:
			return dma_init_ch2();	
		break;

		case EE_DMA_CH3:
			return dma_init_ch3();
		break;
		
	#ifdef __32MX795F512L__
		case EE_DMA_CH4:
			return dma_init_ch4();		
		break;
		
		case EE_DMA_CH5:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
		
		case EE_DMA_CH6:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;

		case EE_DMA_CH7:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
		break;
	#endif
		
		default:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
	}	


}


EE_INT8 EE_dma_advanced_setup(EE_UINT8 channel, EE_UINT8 subpriority, 
				EE_UREG event_control_flags ) {
	switch (channel) {
		case EE_DMA_CH0:
			return dma_event_setup_ch0(subpriority,
						event_control_flags);
		break;

		case EE_DMA_CH1:
			return dma_event_setup_ch1(subpriority,
						event_control_flags);
		break;

		case EE_DMA_CH2:
			return dma_event_setup_ch2(subpriority,
						event_control_flags);		
		break;

		case EE_DMA_CH3:
			return dma_event_setup_ch3(subpriority,
						event_control_flags);
		break;
		
	#ifdef __32MX795F512L__
		case EE_DMA_CH4:
			return dma_event_setup_ch4(subpriority,
						event_control_flags);		
		break;
		
		case EE_DMA_CH5:
			return dma_event_setup_ch5(subpriority,
						event_control_flags);	
		break;
		
		case EE_DMA_CH6:
			return dma_event_setup_ch6(subpriority,
						event_control_flags);	
		break;

		case EE_DMA_CH7:
			return dma_event_setup_ch7(subpriority,
						event_control_flags);	
		break;
	#endif
		
		default:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
	}	
}





EE_INT8 EE_dma_init_transfer(EE_UINT8 channel, EE_UINT16 source_size, EE_UINT16 destination_size,
		EE_UINT16 cell_size, EE_INT16 interrupt_request_source, EE_UINT8 int_prior, 
		EE_UINT8 int_subprior) {
	switch (channel) {
	
		case EE_DMA_CH0:
			return dma_init_transfer_ch0(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;
		case EE_DMA_CH1:

			return dma_init_transfer_ch1(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;
		case EE_DMA_CH2:
			return dma_init_transfer_ch2(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);		
		break;
		case EE_DMA_CH3:
			return dma_init_transfer_ch3(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;
		
	#ifdef __32MX795F512L__
		case EE_DMA_CH4:
			return dma_init_transfer_ch4(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);		
		break;
		
		case EE_DMA_CH5:
			return dma_init_transfer_ch5(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;
		
		case EE_DMA_CH6:
			return dma_init_transfer_ch6(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;

		case EE_DMA_CH7:
			return dma_init_transfer_ch7(source_size, destination_size,
					cell_size, interrupt_request_source, 
					int_prior, int_subprior);
		break;
	#endif
		
		default:
			return -EE_DMA_CHANNEL_NOT_AVAILABLE;
	}	
}

