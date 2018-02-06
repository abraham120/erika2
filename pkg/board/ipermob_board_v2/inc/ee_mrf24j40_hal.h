/** 
* @file mrf24j40_hal_ee_pic32.h
* @brief MRF24J40 Hw Abstraction Layer for the ipermob_v2 board
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
#define MRF24J40_RESETn		PORTGbits.RG15
#endif

#ifndef MRF24J40_INT
#define MRF24J40_INT		PORTAbits.RA15
#endif

#ifndef MRF24J40_CSn
#define MRF24J40_CSn		PORTFbits.RF12
#endif

/* ---------------------------- Pin Tri-States ------------------------------ */
#ifndef MRF24J40_TRIS_RESETn
#define MRF24J40_TRIS_RESETn	TRISGbits.TRISG1
#endif

#ifndef MRF24J40_TRIS_INT
#define MRF24J40_TRIS_INT	TRISAbits.TRISA15
#endif

#ifndef MRF24J40_TRIS_CSn
#define MRF24J40_TRIS_CSn	TRISFbits.TRISF12
#endif

/* ---------------------------- IRQ Definition ------------------------------ */
#ifndef MRF24J40_INTERRUPT_NAME	
#define MRF24J40_INTERRUPT_NAME			_EXTERNAL_4_VECTOR
#endif
#ifndef MRF24J40_INTERRUPT_FLAG	
#define MRF24J40_INTERRUPT_FLAG			IFS0bits.INT4IF
#endif
#ifndef MRF24J40_INTERRUPT_ENABLE
#define MRF24J40_INTERRUPT_ENABLE 		IEC0bits.INT4IE
#endif
#ifndef MRF24J40_INTERRUPT_PRIORITY
#define MRF24J40_INTERRUPT_PRIORITY	 	IPC4bits.INT4IP
#endif
#ifndef MRF24J40_INTERRUPT_SUBPRIORITY
#define MRF24J40_INTERRUPT_SUBPRIORITY 		IPC4bits.INT4IS
#endif
#ifndef MRF24J40_INTERRUPT_EDGE_POLARITY	
#define MRF24J40_INTERRUPT_EDGE_POLARITY	 INTCONbits.INT4EP
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

#define MRF24J40MB_NOT_INVERTED_RESET	

#endif // EE_MRF24J40_HAL_BOARD_H 
