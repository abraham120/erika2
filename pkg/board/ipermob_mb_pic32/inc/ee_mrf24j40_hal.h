/** 
* @file mrf24j40_hal_ee_pic32.h
* @brief MRF24J40 Hw Abstraction Layer for the ipermob_mother board
* @author Marco Ghibaudi
* @date 2010-12-17
*
* This file is the definition of the hardware abstraction layer 
* used by  MRF24J40 library. 
*
*/
#ifndef EE_MRF24J40_HAL_BOARD_H
#define EE_MRF24J40_HAL_BOARD_H

/* ------------------------------ Pin Mapping ------------------------------- */
#ifndef MRF24J40_RESETn
#define MRF24J40_RESETn		PORTFbits.RF1
#endif

#ifndef MRF24J40_INT
#define MRF24J40_INT		PORTAbits.RA14
#endif

#ifndef MRF24J40_CSn
#define MRF24J40_CSn		PORTAbits.RA15
#endif

#ifndef MRF24J40_VREG_EN
#define MRF24J40_VREG_EN   	PORTGbits.RG15
#endif

/* ---------------------------- Pin Tri-States ------------------------------ */
#ifndef MRF24J40_TRIS_RESETn
#define MRF24J40_TRIS_RESETn	TRISFbits.TRISF1
#endif

#ifndef MRF24J40_TRIS_INT
#define MRF24J40_TRIS_INT	TRISAbits.TRISA14
#endif

#ifndef MRF24J40_TRIS_CSn
#define MRF24J40_TRIS_CSn	TRISAbits.TRISA15
#endif

#ifndef MRF24J40_TRIS_VREG_EN
#define MRF24J40_TRIS_VREG_EN   TRISGbits.TRISG15
#endif


/* --------------------------- IRQ Type Selection --------------------------- */

#ifdef MRF24J40_IRQ_EE_CN	/* IRQ type is Change Notification (EE_CN) */

#define MRF24J40_HAL_ISR() 		 EE_CN_HANDLER(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_FLAG_CLR()		
#define MRF24J40_INTERRUPT_ENABLE_SET()	 EE_cn_enable(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_ENABLE_CLR()	 EE_cn_disable(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_ENABLE_STAT() EE_cn_status(mrf24j40_cn_isr)
#define MRF24J40_INTERRUPT_INIT(p, s)	 EE_cn_init(p, s)

#else				/* IRQ type is External Interrupt */

#ifndef MRF24J40_INTERRUPT_NAME	
#define MRF24J40_INTERRUPT_NAME			_EXTERNAL_3_VECTOR
#endif
#ifndef MRF24J40_INTERRUPT_FLAG	
#define MRF24J40_INTERRUPT_FLAG			IFS0bits.INT3IF
#endif
#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE 		IEC0bits.INT3IE
#endif
#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY	 	IPC3bits.INT3IP
#endif
#ifndef MRF24J40_INTERRUPT_SUBPRIORITY
#define MRF24J40_INTERRUPT_SUBPRIORITY 		IPC3bits.INT3IS
#endif
#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY	
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCONbits.INT3EP
#endif

#define MRF24J40_HAL_ISR() 		 ISR2(MRF24J40_INTERRUPT_NAME)
#define MRF24J40_INTERRUPT_FLAG_CLR()	 MRF24J40_INTERRUPT_FLAG = 0
#define MRF24J40_INTERRUPT_ENABLE_SET()	 MRF24J40_INTERRUPT_ENABLE = 1
#define MRF24J40_INTERRUPT_ENABLE_CLR()	 MRF24J40_INTERRUPT_ENABLE = 0
#define MRF24J40_INTERRUPT_ENABLE_STAT() MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_INIT(p, s)		\
do {						\
	MRF24J40_INTERRUPT_PRIORITY = p;	\
	MRF24J40_INTERRUPT_SUBPRIORITY = s;	\
	MRF24J40_INTERRUPT_EDGE_POLARITY = 0;	\
} while (0)					

#endif /* IRQ Type Selection */

#endif // EE_MRF24J40_HAL_BOARD_H 
