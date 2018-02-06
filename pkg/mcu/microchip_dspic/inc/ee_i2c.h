/**
 *  \file EE_i2c.h
 *
 *  \date Created on: 17-mag-2010
 *  \author Author: Francesco Prosperi
 *  \brief I2C communication files
 *
 */

#ifndef __INCLUDE_MICROCHIP_DSPIC_I2C_H__
#define __INCLUDE_MICROCHIP_DSPIC_I2C_H__

#include "ee.h"

/* Include a file with the registers from Microchip C30 distribution */
#ifdef __PIC30_INCLUDE_REGS__
#include "ee_pic30regs.h"
#endif

#define EE_I2C_SUCCESS 	0
#define EE_I2C_BAD_PORT 1
#define EE_I2C_FAILURE 	2
#define EE_I2C_COLLISION 3


#define CONNECTION_TIMEOUT 2000

#define EE_I2C_100KHZ		 100000
#define EE_I2C_400KHZ		 400000
#define EE_I2C_1MHZ			1000000

#ifndef EE_I2C_INSTRUCTION_CLOCK
	#ifdef __PIC24FJ32GA004__
		/* we are considering Fcy = 16 MHz */
		#define EE_UART_INSTRUCTION_CLOCK	16000000ul
	#else
		#define EE_UART_INSTRUCTION_CLOCK	2500000ul
	#endif
#endif


enum {
	EE_I2C_PORT_1 = 0,
	EE_I2C_PORT_2,
	EE_I2C_PORT_N,
};

/******************************************************************************/
/*                            INLINE Functions                                */
/******************************************************************************/
__INLINE__ EE_INT8 i2c_idle_port_1(void){
	return (I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN ||
		   I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT);
}

__INLINE__ EE_INT8 i2c_idle_port_2(void){
	return (I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN ||
		   I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT);
}

__INLINE__ void i2c_init_port_1 (EE_UINT32 baudrate, EE_UINT16 flagsvoid) 
{
	I2C1CONbits.I2CEN = 0;	/* Configure I2C port */
	
	IEC1bits.SI2C1IE = 0;	/* Disable Interrupts */
	IEC1bits.MI2C1IE = 0;
	
	IFS1bits.SI2C1IF = 0;	/* Clear Interrupt flag bits */
	IFS1bits.MI2C1IF = 0;
	
	I2C1RCV = 0;			/* Clear I/O registers */
	I2C1TRN = 0;
	
#ifdef __PIC24FJ32GA004__
	ODCBbits.ODB8 = 1;		/* Configure SCL/SDA pin as open-drain */
	ODCBbits.ODB9 = 1;
	I2C1BRG = 157;			/* Set baudrate: SCL=100KHz @ Fcy=80MHz*/
#else
	ODCGbits.ODCG2 = 1;		/* Configure SCL/SDA pin as open-drain */
	ODCGbits.ODCG3 = 1;
	I2C1BRG = 362;			/* Set baudrate: SCL=100KHz @ Fcy=40MHz*/
#endif

	I2C1ADD=0;				/* Clear Address */
	I2C1MSK=0;				/* Clear mask */
	
	I2C1CONbits.DISSLW = 1;
	I2C1CONbits.ACKDT  = 1;
	I2C1CONbits.I2CEN  = 1;	/* Start I2C port */
}

__INLINE__ void i2c_init_port_2 (EE_UINT32 baudrate, EE_UINT16 flagsvoid) 
{
	I2C2CONbits.I2CEN = 0;	/* Stop I2C port */
	
	IEC3bits.SI2C2IE = 0;	/* Disable Interrupts */
	IEC3bits.MI2C2IE = 0;
	
	IFS3bits.SI2C2IF = 0;	/* Clear Interrupt flag bits */
	IFS3bits.MI2C2IF = 0;
	
	I2C1RCV = 0;			/* Clear I/O registers */
	I2C1TRN = 0;

#ifdef __PIC24FJ32GA004__	
	ODCBbits.ODB2 = 1;		/* Configure SCL/SDA pin as open-drain */
	ODCBbits.ODB3 = 1;
	I2C1BRG = 157;			/* Set baudrate: SCL=100KHz @ Fcy=80MHz*/
#else
	ODCAbits.ODCA2 = 1;		/* Configure SCL/SDA pin as open-drain */
	ODCAbits.ODCA3 = 1;
	I2C1BRG = 362;			/* Set baudrate: SCL=100KHz @ Fcy=40MHz*/
#endif

	I2C2ADD=0;				/* Clear Address */
	I2C2MSK=0;				/* Clear mask */

	I2C2CONbits.ACKDT = 1;
	I2C2CONbits.I2CEN = 1;	/* Start I2C port */
}

/******************************************************************************/
/*                         Function Declarations                              */
/******************************************************************************/
/**
* @brief Initialize the I2C Driver
*
*
* @return 	Return \ref I2C_SUCCESS if no error occurs,
* 		otherwise a specific error code.
*/

EE_INT8 EE_i2c_init(
		EE_UINT8 port,
		EE_UINT32 baudrate,
		EE_UINT16 flags );

EE_INT8 EE_i2c_idle( EE_UINT8 port );

EE_INT8 EE_i2c_write_byte(
		EE_UINT8 port,
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 data );

EE_INT8 EE_i2c_read_byte(
		EE_UINT8 port,
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8* data );

EE_INT8 EE_i2c_read_bytes(
		EE_UINT8 port,
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 nbytes,
		EE_UINT8* data );

#endif // __EE_I2C_H__
