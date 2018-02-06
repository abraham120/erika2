#include "mcu/microchip_pic32/inc/ee_uart.h"
#include "ee_internal.h"
#include "cpu/pic32/inc/ee_irqstub.h"
#include "cpu/pic32/inc/ee_utils.h"
#include "ee.h"

#ifdef __32MX795F512L__

#ifdef EE_UART_PORT_1A_ISR_ENABLE
static void (*Rx1aIsrFunction)(EE_UINT8 data) = NULL;
#endif
#ifdef EE_UART_PORT_1B_ISR_ENABLE
static void (*Rx1bIsrFunction)(EE_UINT8 data) = NULL;
#endif
#ifdef EE_UART_PORT_2A_ISR_ENABLE
static void (*Rx2aIsrFunction)(EE_UINT8 data) = NULL;
#endif
#ifdef EE_UART_PORT_2B_ISR_ENABLE
static void (*Rx2bIsrFunction)(EE_UINT8 data) = NULL;
#endif
#ifdef EE_UART_PORT_3A_ISR_ENABLE
static void (*Rx3aIsrFunction)(EE_UINT8 data) = NULL;
#endif
#ifdef EE_UART_PORT_3B_ISR_ENABLE
static void (*Rx3bIsrFunction)(EE_UINT8 data) = NULL;
#endif

#else

#ifdef EE_UART_PORT_1_ISR_ENABLE
static void (*Rx1IsrFunction)(EE_UINT8 data) = NULL;
#endif
#ifdef EE_UART_PORT_2_ISR_ENABLE
static void (*Rx2IsrFunction)(EE_UINT8 data) = NULL;
#endif

#endif //__32MX795F512L__



__INLINE__ EE_UINT32 __ALWAYS_INLINE__ uart_get_peripheral_clock(void){
	return EE_get_peripheral_clock();
}






#ifdef __32MX795F512L__

/******************************************************************************/
/*			PIC32MX795F512L - Specific Functions		      */
/******************************************************************************/

/******************************************************************************/
/* All the functions in this part of the file are specific for the 	      */
/* pic32mx795f512l that is characterized by registers' name that differ from  */
/* the 3xx and 4xx families of the pic32mx.			              */
/******************************************************************************/


/****************************************/
/*		 Uart port 1A 		*/
/****************************************/

#ifdef __USE_UART_PORT1A__
static EE_INT8 uart_init_port1A (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

	// Stop UART port
	U1AMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT1A_RX_INT_ENABLE = 0;
	EE_UART_PORT1A_TX_INT_ENABLE = 0;
	EE_UART_PORT1A_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT1A_RX_INT_FLAG = 0;
 	EE_UART_PORT1A_TX_INT_FLAG = 0;
	EE_UART_PORT1A_ERR_INT_FLAG = 0;

	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U1ABRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U1ABRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U1AMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U1AMODEbits.BRGH = 0;
	else
		U1AMODEbits.BRGH = 1;

	// Setup and port start
	U1AMODEbits.UARTEN = 1;

	if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
		U1AMODEbits.RTSMD = 1;
		U1AMODEbits.UEN = 0b10;
	} else {
		U1AMODEbits.RTSMD = 0;
		U1AMODEbits.UEN = 0;
	}

	U1AMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U1ASTA = 0;			// TX & RX interrupt modes
	U1ASTAbits.UTXEN = 1; //Enable Transmission
	U1ASTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}
#endif //#ifdef __USE_UART_PORT1A__




/****************************************/
/*		 Uart port 1B		*/
/****************************************/

#ifdef __USE_UART_PORT1B__
static EE_INT8 uart_init_port1B (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

	// Stop UART port
	U1BMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT1B_RX_INT_ENABLE = 0;
	EE_UART_PORT1B_TX_INT_ENABLE = 0;
	EE_UART_PORT1B_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT1B_RX_INT_FLAG = 0;
 	EE_UART_PORT1B_TX_INT_FLAG = 0;
	EE_UART_PORT1B_ERR_INT_FLAG = 0;


	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U1BBRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U1BBRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U1BMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U1BMODEbits.BRGH = 0;
	else
		U1BMODEbits.BRGH = 1;

	// Setup and port start
	U1BMODEbits.UARTEN = 1;

	U1BMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U1BSTA = 0;			// TX & RX interrupt modes
	U1BSTAbits.UTXEN = 1; //Enable Transmission
	U1BSTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}
#endif //#ifdef __USE_UART_PORT1B__


/****************************************/
/*		 Uart port 2A 		*/
/****************************************/


#ifdef __USE_UART_PORT2A__
static EE_INT8 uart_init_port2A (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

	// Stop UART port
	U2AMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT2A_RX_INT_ENABLE = 0;
	EE_UART_PORT2A_TX_INT_ENABLE = 0;
	EE_UART_PORT2A_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT2A_RX_INT_FLAG = 0;
 	EE_UART_PORT2A_TX_INT_FLAG = 0;
	EE_UART_PORT2A_ERR_INT_FLAG = 0;


	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U2ABRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U2ABRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U2AMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U2AMODEbits.BRGH = 0;
	else
		U2AMODEbits.BRGH = 1;

	// Setup and port start
	U2AMODEbits.UARTEN = 1;

	if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
		U2AMODEbits.RTSMD = 1;
		U2AMODEbits.UEN = 0b10;
	} else {
		U2AMODEbits.RTSMD = 0;
		U2AMODEbits.UEN = 0;
	}

	U2AMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U2ASTA = 0;			// TX & RX interrupt modes
	U2ASTAbits.UTXEN = 1; //Enable Transmission
	U2ASTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}
#endif //#ifdef __USE_UART_PORT2A__



/****************************************/
/*		 Uart port 2B 		*/
/****************************************/


#ifdef __USE_UART_PORT2B__
static EE_INT8 uart_init_port2B (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

	// Stop UART port
	U2BMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT2B_RX_INT_ENABLE = 0;
	EE_UART_PORT2B_TX_INT_ENABLE = 0;
	EE_UART_PORT2B_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT2B_RX_INT_FLAG = 0;
 	EE_UART_PORT2B_TX_INT_FLAG = 0;
	EE_UART_PORT2B_ERR_INT_FLAG = 0;


	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U2BBRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U2BBRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U2BMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U2BMODEbits.BRGH = 0;
	else
		U2BMODEbits.BRGH = 1;

	// Setup and port start
	U2BMODEbits.UARTEN = 1;

	U2BMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U2BSTA = 0;			// TX & RX interrupt modes
	U2BSTAbits.UTXEN = 1; //Enable Transmission
	U2BSTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}
#endif //#ifdef __USE_UART_PORT2B__

/****************************************/
/*		 Uart port 3A 		*/
/****************************************/


#ifdef __USE_UART_PORT3A__
static EE_INT8 uart_init_port3A (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {


	// Stop UART port
	U3AMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT3A_RX_INT_ENABLE = 0;
	EE_UART_PORT3A_TX_INT_ENABLE = 0;
	EE_UART_PORT3A_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT3A_RX_INT_FLAG = 0;
 	EE_UART_PORT3A_TX_INT_FLAG = 0;
	EE_UART_PORT3A_ERR_INT_FLAG = 0;


	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U3ABRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U3ABRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U3AMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U3AMODEbits.BRGH = 0;
	else
		U3AMODEbits.BRGH = 1;

	// Setup and port start
	U3AMODEbits.UARTEN = 1;

	if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
		U3AMODEbits.RTSMD = 1;
		U3AMODEbits.UEN = 0b10;
	} else {
		U3AMODEbits.RTSMD = 0;
		U3AMODEbits.UEN = 0;
	}

	U3AMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U3ASTA = 0;			// TX & RX interrupt modes
	U3ASTAbits.UTXEN = 1; //Enable Transmission
	U3ASTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}
#endif //#ifdef __USE_UART_PORT3A__


/****************************************/
/*		 Uart port 3B 		*/
/****************************************/


#ifdef __USE_UART_PORT3B__
static EE_INT8 uart_init_port3B (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

	// Stop UART port
	U3BMODEbits.UARTEN = 0;

	// Disable Interrupts
	EE_UART_PORT3B_RX_INT_ENABLE = 0;
	EE_UART_PORT3B_TX_INT_ENABLE = 0;
	EE_UART_PORT3B_ERR_INT_ENABLE = 0;

	// Reset Interrupt Flags
	EE_UART_PORT3B_RX_INT_FLAG = 0;
 	EE_UART_PORT3B_TX_INT_FLAG = 0;
	EE_UART_PORT3B_ERR_INT_FLAG = 0;


	// Choice between the two available divisors
	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
		U3BBRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
	}
	else {
		U3BBRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
	}

	// Mode Register Reset
	U3BMODE = 0;

	if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
		U3BMODEbits.BRGH = 0;
	else
		U3BMODEbits.BRGH = 1;

	// Setup and port start
	U3BMODEbits.UARTEN = 1;

	U3BMODE |= byte_format & 0x07;	// Number of bit, Parity and Stop bits

	// Status bits
	U3BSTA = 0;			// TX & RX interrupt modes
	U3BSTAbits.UTXEN = 1; //Enable Transmission
	U3BSTAbits.URXEN = 1; //Enable Receiver
	return EE_UART_NO_ERROR;
}
#endif //#ifdef __USE_UART_PORT3B__


#else //not __32MX795F512L__

/******************************************************************************/
/* All the functions in this part of the file are specific for the 	      */
/* pic32mx360f512l that is characterized by registers' name that differ from  */
/* the 5xx, 6xx and 7xx families of the pic32mx.			      */
/******************************************************************************/


static EE_INT8 uart_init_port1 (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

		// Stop UART port
		U1MODEbits.UARTEN = 0;

		// Disable Interrupts
		EE_UART_PORT1_RX_INT_ENABLE = 0;
		EE_UART_PORT1_TX_INT_ENABLE = 0;
		EE_UART_PORT1_ERR_INT_ENABLE = 0;

		// Clean Interrupt flags
		EE_UART_PORT1_RX_INT_FLAG = 0;
		EE_UART_PORT1_TX_INT_FLAG = 0;
		EE_UART_PORT1_ERR_INT_FLAG = 0;

		// Set-up for the control flow pins
		if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
			TRISDbits.TRISD14 = 1;	// Set In CTS Pin
			TRISDbits.TRISD15 = 0;	// Set Out RTS Pin
		}

		// Choice between the two available divisors
		if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE){
			U1BRG  = ((uart_get_peripheral_clock() / (16 * baud))) - 1;
		}
		else {
			U1BRG  = ((uart_get_peripheral_clock() / (4 * baud))) - 1;
		}

		U1MODE = 0;

		if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
			U1MODEbits.BRGH = 0;
		else
			U1MODEbits.BRGH = 1;

		// Setup and port start
		U1MODEbits.UARTEN = 1;

		if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
			U1MODEbits.RTSMD = 1;
			U1MODEbits.UEN = 0b10;
		} else {
			U1MODEbits.RTSMD = 0;
			U1MODEbits.UEN = 0;
		}

		// Number of bit, Parity and Stop bits
		U1MODE |= byte_format & 0x07;

		// Status bits
		U1STA = 0;			// TX & RX interrupt modes
		U1STAbits.UTXEN = 1; 		//Enable Transmission
		U1STAbits.URXEN = 1; 		//Enable Receiver

		return EE_UART_NO_ERROR;
}


static EE_INT8 uart_init_port2 (EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode) {

		// Stop UART port
		U2MODEbits.UARTEN = 0;

		// Disable Interrupts
		EE_UART_PORT2_RX_INT_ENABLE = 0;
		EE_UART_PORT2_TX_INT_ENABLE = 0;
		EE_UART_PORT2_ERR_INT_ENABLE = 0;

		// Clear Interrupts' Flag
		EE_UART_PORT2_RX_INT_FLAG  = 0;
		EE_UART_PORT2_TX_INT_FLAG = 0;
		EE_UART_PORT2_ERR_INT_FLAG = 0;

		// Set-up for the control flow pins
		if ((mode & EE_UART_CTRL_MASK) == EE_UART_CTRL_FLOW) {
			TRISFbits.TRISF12 = 1;	// Set In CTS Pin
			TRISFbits.TRISF13 = 0;	// Set Out RTS Pin
		}

		// Choice between the two available divisors
		if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
			U2BRG = (uart_get_peripheral_clock() / (16 * baud)) - 1;
		else
			U2BRG = (uart_get_peripheral_clock() / (4 * baud)) - 1;

		U2MODE = 0;

		//Set-up of the BRG value;
		if ((mode & EE_UART_BRGH_MASK) == EE_UART_BRGH_NONE)
			U2MODEbits.BRGH = 0;
		else
			U2MODEbits.BRGH = 1;

		// Setup and port start
		U2MODEbits.UARTEN = 1;

		if ((mode & EE_UART_CTRL_MASK)  == EE_UART_CTRL_FLOW) {
			U2MODEbits.RTSMD = 1;
			U2MODEbits.UEN = 0b10;
		} else {
			U2MODEbits.RTSMD = 0;
			U2MODEbits.UEN = 0;
		}

		// Number of bit, Parity and Stop bits
		U2MODE |= byte_format & 0x07;

		// Status bits
		U2STA = 0;			// TX & RX interrupt modes
		U2STAbits.UTXEN = 1;
		U2STAbits.URXEN = 1; 		//Enable Receiver

		return EE_UART_NO_ERROR;
}


#endif






/******************************************************************************/
/*				General Functions			      */
/******************************************************************************/





EE_INT8 EE_uart_init(EE_UINT8 port, EE_UINT32 baud, EE_UINT16 byte_format,
		     EE_UINT16 mode)
{
#ifdef __32MX795F512L__

	switch (port){
#ifdef __USE_UART_PORT1A__
	case EE_UART_PORT_1A:
		return uart_init_port1A(baud, byte_format, mode);
	break;
#endif //__USE_UART_PORT1A__
#ifdef __USE_UART_PORT1B__
	case EE_UART_PORT_1B:
		return uart_init_port1B(baud, byte_format, mode);
	break;
#endif //__USE_UART_PORT1B__
#ifdef __USE_UART_PORT2A__
	case EE_UART_PORT_2A:
		return uart_init_port2A(baud, byte_format, mode);
	break;
#endif //__USE_UART_PORT2A__
#ifdef __USE_UART_PORT2B__
	case EE_UART_PORT_2B:
		return uart_init_port2B(baud, byte_format, mode);
	break;
#endif //__USE_UART_PORT2B__
#ifdef __USE_UART_PORT3A__
	case EE_UART_PORT_3A:
		return uart_init_port3A(baud, byte_format, mode);
	break;
#endif //__USE_UART_PORT3A__
#ifdef __USE_UART_PORT3B__
	case EE_UART_PORT_3B:
		return uart_init_port3B(baud, byte_format, mode);
	break;
#endif //__USE_UART_PORT3B__
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__

	switch (port){

	case EE_UART_PORT_1:
		return uart_init_port1(baud, byte_format, mode);
	break;

	case EE_UART_PORT_2:
		return uart_init_port2(baud, byte_format, mode);
	break;
	default:
		return -EE_UART_ERR_BAD_PORT;
	}
#endif
}





EE_INT8 EE_uart_close(EE_UINT8 port)
{

//TODO: implement real close function for all the ports

#ifdef __32MX795F512L__


	switch (port){
#ifdef __USE_UART_PORT1A__
	case EE_UART_PORT_1A:
		/* Bibo: TODO: Release something */
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
#endif //__USE_UART_PORT1A__
#ifdef __USE_UART_PORT1B__
	case EE_UART_PORT_1B:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
#endif //__USE_UART_PORT1B__
#ifdef __USE_UART_PORT2A__
	case EE_UART_PORT_2A:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
#endif //__USE_UART_PORT2A__
#ifdef __USE_UART_PORT2B__
	case EE_UART_PORT_2B:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
#endif //__USE_UART_PORT2B__
#ifdef __USE_UART_PORT3A__
	case EE_UART_PORT_3A:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
#endif //__USE_UART_PORT3A__
#ifdef __USE_UART_PORT3B__
	case EE_UART_PORT_3B:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
#endif //__USE_UART_PORT3B__
	default:
		return -EE_UART_ERR_BAD_PORT;
	}


#else //not defined __32MX795F512L__
	switch (port){

	case EE_UART_PORT_1:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;

	case EE_UART_PORT_2:
		return -EE_UART_FUNCTION_NOT_IMPLEMENTED;
	break;
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#endif
}


EE_INT8 EE_uart_set_rx_callback(EE_UINT8 port, void (*RxFunc)(EE_UINT8 data),
				EE_UINT8 rxmode)
{

#ifdef __32MX795F512L__
	switch (port){
	case EE_UART_PORT_1A:
		#ifdef EE_UART_PORT_1A_ISR_ENABLE
		Rx1aIsrFunction = RxFunc;
		if (RxFunc) {
			// TODO: interrupt served
			/*U1STA &= 0x5FFF;
			U1STA |= rxmode & 0xA000;
			IEC0bits.U1RXIE = 1;
			IFS0bits.U1RXIF = 0;*/
		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	case EE_UART_PORT_1B:
		#ifdef EE_UART_PORT_1B_ISR_ENABLE
		Rx1bIsrFunction = RxFunc;
		if (RxFunc) {

		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	case EE_UART_PORT_2A:
		#ifdef EE_UART_PORT_2A_ISR_ENABLE
		Rx2aIsrFunction = RxFunc;
		if (RxFunc) {
			// TODO: interrupt served
		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	case EE_UART_PORT_2B:
		#ifdef EE_UART_PORT_2B_ISR_ENABLE
		Rx2bIsrFunction = RxFunc;
		if (RxFunc) {
			// TODO: interrupt served
		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	case EE_UART_PORT_3A:
		#ifdef EE_UART_PORT_3A_ISR_ENABLE
		Rx3aIsrFunction = RxFunc;
		if (RxFunc) {
			// TODO: interrupt served

		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	case EE_UART_PORT_3B:
		#ifdef EE_UART_PORT_3B_ISR_ENABLE
		Rx3bIsrFunction = RxFunc;
		if (RxFunc) {
			U3BSTA &= 0xFFFFFF3F; 
			U3BSTA |= rxmode;
			EE_UART_PORT3B_RX_INT_ENABLE = 1;
			EE_UART_PORT3B_RX_INT_FLAG = 0;
			IPC12 = 0x10000000; //Set priority 7, and sub-priority 3
		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__

	switch (port){

	case EE_UART_PORT_1:
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		Rx1IsrFunction = RxFunc;
		if (RxFunc) {
			// TODO: interrupt served
			U1STA &= 0x5FFF;
			U1STA |= rxmode & 0xA000;
			IEC0bits.U1RXIE = 1;
			IFS0bits.U1RXIF = 0;
		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;

	case EE_UART_PORT_2:
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		Rx2IsrFunction = RxFunc;
		if (RxFunc) {
			// TODO: interrupt served
			U2STA &= 0x5FFF;
			U2STA |= rxmode & 0xA000;
			IEC1bits.U2RXIE = 1;
			IFS1bits.U2RXIF = 0;
		}
		return EE_UART_NO_ERROR;
		#else
		return -EE_UART_ERR_INT_DISABLED;
		#endif
	break;
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#endif
}




EE_INT8 EE_uart_write_byte(EE_UINT8 port, EE_UINT8 data)
{

#ifdef __32MX795F512L__

	switch (port){
	#ifdef __USE_UART_PORT1A__
	case EE_UART_PORT_1A:
		while (U1ASTAbits.UTXBF) ;
		U1ATXREG = data;
		while (!U1ASTAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	#endif //__USE_UART_PORT1A__
	#ifdef __USE_UART_PORT1B__
	case EE_UART_PORT_1B:
		while (U1BSTAbits.UTXBF) ;
		U1BTXREG = data;
		while (!U1BSTAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	#endif //__USE_UART_PORT1B__
	#ifdef __USE_UART_PORT2A__
	case EE_UART_PORT_2A:
		while (U2ASTAbits.UTXBF) ;
		U2ATXREG = data;
		while (!U2ASTAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	#endif //__USE_UART_PORT2A__
	#ifdef __USE_UART_PORT2B__
	case EE_UART_PORT_2B:
		while (U2BSTAbits.UTXBF) ;
		U2BTXREG = data;
		while (!U2BSTAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	#endif //__USE_UART_PORT2B__
	#ifdef __USE_UART_PORT3A__
	case EE_UART_PORT_3A:
		while (U3ASTAbits.UTXBF) ;
		U3ATXREG = data;
		while (!U3ASTAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	#endif //__USE_UART_PORT3A__
	#ifdef __USE_UART_PORT3B__
	case EE_UART_PORT_3B:
		while (U3BSTAbits.UTXBF) ;
		U3BTXREG = data;
		while (!U3BSTAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	#endif //__USE_UART_PORT3B__
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__

	switch (port){

	case EE_UART_PORT_1:
		while (U1STAbits.UTXBF) ;
		U1TXREG = data;
		while (!U1STAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;

	case EE_UART_PORT_2:
		while (U2STAbits.UTXBF) ;
		U2TXREG = data;
		while (!U2STAbits.TRMT) ;
		return EE_UART_NO_ERROR;
	break;
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#endif
}





EE_INT8 EE_uart_read_byte(EE_UINT8 port, EE_UINT8 *data)
{

#ifdef __32MX795F512L__

	switch (port){
	#ifdef __USE_UART_PORT1A__
	case EE_UART_PORT_1A:
	#ifdef EE_UART_PORT_1A_ISR_ENABLE
	if (Rx1aIsrFunction == NULL) {
	#endif //EE_UART_PORT_1A_ISR_ENABLE
		/* Polling mode */
		if (U1ASTAbits.OERR) {
			U1ASTAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U1ASTAbits.URXDA) {
			*data = U1ARXREG & 0x00FF;
			return EE_UART_NO_ERROR;
		}
		return -EE_UART_ERR_NO_DATA;
	#ifdef EE_UART_PORT_1A_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
	#endif //EE_UART_PORT_1A_ISR_ENABLE
	break;
	#endif //__USE_UART_PORT1A__

	#ifdef __USE_UART_PORT1B__
	case EE_UART_PORT_1B:
	#ifdef EE_UART_PORT_1B_ISR_ENABLE
	if (Rx1bIsrFunction == NULL) {
	#endif //EE_UART_PORT_1B_ISR_ENABLE
		/* Polling mode */
		if (U1BSTAbits.OERR) {
			U1BSTAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U1BSTAbits.URXDA) {
			*data = U1BRXREG & 0x00FF;
			return EE_UART_NO_ERROR;
		}
		return -EE_UART_ERR_NO_DATA;
	#ifdef EE_UART_PORT_1B_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
	#endif //EE_UART_PORT_1B_ISR_ENABLE
	break;
	#endif //__USE_UART_PORT1B__

	#ifdef __USE_UART_PORT2A__
	case EE_UART_PORT_2A:
	#ifdef EE_UART_PORT_2A_ISR_ENABLE
	if (Rx2aIsrFunction == NULL) {
	#endif //EE_UART_PORT_2A_ISR_ENABLE
		/* Polling mode */
		if (U2ASTAbits.OERR) {
			U2ASTAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U2ASTAbits.URXDA) {
			*data = U2ARXREG & 0x00FF;
			return EE_UART_NO_ERROR;
		}
		return -EE_UART_ERR_NO_DATA;
	#ifdef EE_UART_PORT_2A_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
	#endif //EE_UART_PORT_2A_ISR_ENABLE
	break;
	#endif //__USE_UART_PORT2A__

	#ifdef __USE_UART_PORT2B__
	case EE_UART_PORT_2B:
	#ifdef EE_UART_PORT_2A_ISR_ENABLE
	if (Rx2bIsrFunction == NULL) {
	#endif //EE_UART_PORT_2B_ISR_ENABLE
		/* Polling mode */
		if (U2BSTAbits.OERR) {
			U2BSTAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U2BSTAbits.URXDA) {
			*data = U2BRXREG & 0x00FF;
			return EE_UART_NO_ERROR;
		}
		return -EE_UART_ERR_NO_DATA;
	#ifdef EE_UART_PORT_2B_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
	#endif	//EE_UART_PORT_2B_ISR_ENABLE
	break;
	#endif //__USE_UART_PORT2B__

	#ifdef __USE_UART_PORT3A__
	case EE_UART_PORT_3A:
	#ifdef EE_UART_PORT_3A_ISR_ENABLE
	if (Rx3aIsrFunction == NULL) {
	#endif //EE_UART_PORT_3A_ISR_ENABLE
		/* Polling mode */
		if (U3ASTAbits.OERR) {
			U3ASTAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U3ASTAbits.URXDA) {
			*data = U3ARXREG & 0x00FF;
			return EE_UART_NO_ERROR;
		}
		return -EE_UART_ERR_NO_DATA;
	#ifdef EE_UART_PORT_3A_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
	#endif	//EE_UART_PORT_3A_ISR_ENABLE
	break;
	#endif //__USE_UART_PORT3A__

	#ifdef __USE_UART_PORT3B__
	case EE_UART_PORT_3B:
	#ifdef EE_UART_PORT_3B_ISR_ENABLE
	if (Rx3bIsrFunction == NULL) {
	#endif //EE_UART_PORT_3B_ISR_ENABLE
		/* Polling mode */
		if (U3BSTAbits.OERR) {
			U3BSTAbits.OERR = 0;
			return -EE_UART_ERR_OVERFLOW;
		}
		if (U3BSTAbits.URXDA) {
			*data = U3BRXREG & 0x00FF;
			return EE_UART_NO_ERROR;
		}
		return -EE_UART_ERR_NO_DATA;
	#ifdef EE_UART_PORT_3B_ISR_ENABLE
	}
	return -EE_UART_ERR_INT_MODE;
	#endif	//EE_UART_PORT_3B_ISR_ENABLE
	break;
	#endif //__USE_UART_PORT3B__

	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__

	switch (port){

	case EE_UART_PORT_1:
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		if (Rx1IsrFunction == NULL) {
		#endif
			/* Polling mode */
			if (U1STAbits.OERR) {
				U1STAbits.OERR = 0;
				return -EE_UART_ERR_OVERFLOW;
			}
			if (U1STAbits.URXDA) {
				*data = U1RXREG & 0x00FF;
				return EE_UART_NO_ERROR;
			}
			return -EE_UART_ERR_NO_DATA;
		#ifdef EE_UART_PORT_1_ISR_ENABLE
		}
		return -EE_UART_ERR_INT_MODE;
		#endif
	break;

	case EE_UART_PORT_2:
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		if (Rx2IsrFunction == NULL) {
		#endif
			/* Polling mode */
			if (U2STAbits.OERR) {
				U2STAbits.OERR = 0;
				return -EE_UART_ERR_OVERFLOW;
			}
			if (U2STAbits.URXDA) {
				*data = U2RXREG & 0x00FF;
				return EE_UART_NO_ERROR;
			}
			return -EE_UART_ERR_NO_DATA;
		#ifdef EE_UART_PORT_2_ISR_ENABLE
		}
		return -EE_UART_ERR_INT_MODE;
		#endif
	break;
	default:
		return -EE_UART_ERR_BAD_PORT;
	}

#endif

}





/******************************************************************************/
/* All the ISR Handlers in this part of the file are specific for the 	      */
/* pic32mx795f512l that is characterized by registers' name that differ from  */
/* the 3xx and 4xx families of the pic32mx.			              */
/******************************************************************************/

#ifdef EE_UART_PORT_1A_ISR_ENABLE
// TODO: ISR management!!!
ISR2( /*TODO: use right interrupt name */)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	//IFS0bits.U1RXIF = 0;
}
#endif


#ifdef EE_UART_PORT_1B_ISR_ENABLE
// TODO: ISR management!!!
ISR2( /*TODO: use right interrupt name */)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	//IFS0bits.U1RXIF = 0;
}
#endif




#ifdef EE_UART_PORT_2A_ISR_ENABLE
// TODO: ISR management!!!
ISR2( /*TODO: use right interrupt name */)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	//IFS0bits.U1RXIF = 0;
}
#endif

#ifdef EE_UART_PORT_2B_ISR_ENABLE
// TODO: ISR management!!!
ISR2( /*TODO: use right interrupt name */)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	//IFS0bits.U1RXIF = 0;
}
#endif

#ifdef EE_UART_PORT_3A_ISR_ENABLE
// TODO: ISR management!!!
ISR2( /*TODO: use right interrupt name */)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	//IFS0bits.U1RXIF = 0;
}
#endif

#ifdef EE_UART_PORT_3B_ISR_ENABLE
// TODO: ISR management!!!
ISR2(_UART_3B_VECTOR)
{
	EE_UART_PORT3B_RX_INT_FLAG = 0;

	if (Rx3bIsrFunction != NULL) {
		/* Execute callback function */
		Rx3bIsrFunction(U3BRXREG);
	}

}
#endif



/******************************************************************************/
/* All the ISR Handlers in this part of the file are specific for the 	      */
/* pic32mx360f512l that is characterized by registers' name that differ from  */
/* the 5xx, 6xx and 7xx families of the pic32mx.			      */
/******************************************************************************/


#ifdef EE_UART_PORT_1_ISR_ENABLE
// TODO: ISR management!!!
ISR2(_U1RXInterrupt)
{
	if (Rx1IsrFunction != NULL) {
		/* Execute callback function */
		//Rx1IsrFunction(U1RXREG & 0x00FF);
	}
	//IFS0bits.U1RXIF = 0;
}
#endif

#ifdef EE_UART_PORT_2_ISR_ENABLE
// TODO: ISR management!!!
ISR2(_U2RXInterrupt)
{
	if (Rx2IsrFunction != NULL) {
		/* Execute callback function */
		//Rx2IsrFunction(U2RXREG & 0x00FF);
	}
	//IFS1bits.U2RXIF = 0;
}
#endif

