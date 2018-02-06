#include "mcu/microchip_dspic/inc/ee_i2c.h"
#include "ee_internal.h"
#include "cpu/pic30/inc/ee_irqstub.h"

/******************************************************************************/
/*                            Local Macros                                    */
/******************************************************************************/
void tx_dump(EE_UINT8 data)
{
		while (U1STAbits.UTXBF) ;
		U1TXREG = data;
		while (!U1STAbits.TRMT) ;
}

#define ACTIVE_WAIT_ON(__FLAG__) cto = 0; \
								while (__FLAG__)	\
								{	\
									if(++cto > CONNECTION_TIMEOUT)	\
									return -EE_I2C_FAILURE; \
								}
/******************************************************************************/
/*                         Global Variables                                   */
/******************************************************************************/
// Time out counter for i2c
unsigned int cto;
/******************************************************************************/
/*                          Function Definitions                              */
/******************************************************************************/
/******************************************************************************/
//                                                                             |
//  Initialization I2C Port                                                    |
//                                                                             |
//---------------------------------------------------------------------------- */

EE_INT8 EE_i2c_init(
		EE_UINT8 port,
		EE_UINT32 baudrate,
		EE_UINT16 flags)
{

	if( port == EE_I2C_PORT_1 ) {
		i2c_init_port_1(baudrate, flags);
	} else if( port == EE_I2C_PORT_2 ) {
		i2c_init_port_2(baudrate, flags);
	} else return -EE_I2C_BAD_PORT;

	return EE_I2C_SUCCESS;
}

// ---------------------------- end init section -------------------------//

EE_INT8 EE_i2c_idle( EE_UINT8 port ){
	if( port == EE_I2C_PORT_1 )
		return i2c_idle_port_1();
	else if( port == EE_I2C_PORT_2 )
		return i2c_idle_port_2();
	else return -EE_I2C_BAD_PORT;
	
	return EE_I2C_SUCCESS;
}

// ------------------------------------------------------------------------//

/**
* @brief Write a byte
*
* @param device		The device ID (device address).
* @param address 	The device register (register address).
* @param data 		The byte to write.
*
* @return 	Return \ref I2C_SUCCESS if no error occurs,
*		otherwise a specific error code.
*/
static EE_INT8 i2c_write_port_1(
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 data)
{

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	/* Transmit a Start condition, initiate Start on SDA and SCL pins */
	I2C1CONbits.SEN = 1;

	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON(I2C1CONbits.SEN);

	/* Write Slave address and set master for transmission
	(R/W bit should be 0) */
	I2C1TRN = device;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	I2C1TRN = data;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON(I2C1CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	IEC1bits.MI2C1IE = 0;
	IEC1bits.SI2C1IE = 0;
	
	return EE_I2C_SUCCESS;
}

static EE_INT8 i2c_write_port_2(
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 data)
{

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	/* Transmit a Start condition, initiate Start on SDA and SCL pins */
	I2C2CONbits.SEN = 1;

	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON(I2C2CONbits.SEN);

	/* Write Slave address and set master for transmission
	(R/W bit should be 0) */
	I2C2TRN = device;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	/* Write word address */
	I2C2TRN = address;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	I2C1TRN = data;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON(I2C2CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	IEC3bits.MI2C2IE = 0;
	IEC3bits.SI2C2IE = 0;
	

	return EE_I2C_SUCCESS;
}

static EE_INT8 i2c_read_port_1(
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 nbytes,
		EE_UINT8* data)
{
	EE_UINT8	nb;

	/*  Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	// Transmit a Start condition on i2c1
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	/*  Wait till Start sequence is completed */
	ACTIVE_WAIT_ON(I2C1CONbits.SEN);

	/* Write Slave address and set master for transmission
	(R/W bit should be 0)*/
	I2C1TRN = device;
	
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	/* Generate the I2C bus restart condition */
	I2C1CONbits.RSEN = 1;	// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	ACTIVE_WAIT_ON(I2C1CONbits.RSEN);

	/* Write Slave address and set master for reception
	(R/W bit should be 1) */
	I2C1TRN = device+1;
	if(I2C1STATbits.IWCOL)	// If write collision occurs,return -1
		return -EE_I2C_COLLISION;
		
	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C1STATbits.ACKSTAT);
	
	for (nb = 0; nb<nbytes; nb++) 
	{
		/* Ensure I2C module is idle */
		ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

		/* Read the data byte */
		I2C1CONbits.RCEN = 1;

		ACTIVE_WAIT_ON(I2C1CONbits.RCEN);

		I2C1STATbits.I2COV = 0;
		*(data+nb) = I2C1RCV & 0xFF;

		/* Ensure I2C module is idle */
		ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

		/* send (N)ACK condition back to the I2C slave indicating master received
		the data byte */
		if (nb == nbytes-1)
			I2C1CONbits.ACKDT = 1;
		else
			I2C1CONbits.ACKDT = 0;
		I2C1CONbits.ACKEN = 1;

		/* wait until (N)ACK sequence is over */
		ACTIVE_WAIT_ON(I2C1CONbits.ACKEN);
	}

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON(I2C1CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));

	IEC1bits.MI2C1IE = 0;
	IEC1bits.SI2C1IE = 0;

	return EE_I2C_SUCCESS;			// return with data
}

static EE_INT8 i2c_read_port_2(
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 nbytes,
		EE_UINT8* data)
{
	EE_UINT8	nb;
	
	/*  Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2) != NULL);

	// Transmit a Start condition on i2c1
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	/*  Wait till Start sequence is completed */
	ACTIVE_WAIT_ON(I2C2CONbits.SEN);

	/* Write Slave address and set master for transmission
	(R/W bit should be 0)*/
	I2C2TRN = device;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	/* Write word address */
	I2C2TRN = address;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	/* Generate the I2C bus restart condition */
	I2C2CONbits.RSEN = 1;	// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	ACTIVE_WAIT_ON(I2C2CONbits.RSEN);

	/* Write Slave address and set master for reception
	(R/W bit should be 1) */
	I2C2TRN = device+1;
	if(I2C2STATbits.IWCOL)	// If write collision occurs,return -1
		return -EE_I2C_COLLISION;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON(I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON(I2C2STATbits.ACKSTAT);

	for (nb = 0; nb<nbytes; nb++)
	{
		/* Ensure I2C module is idle */
		ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

		/* Read the data byte */
		I2C2CONbits.RCEN = 1;

		ACTIVE_WAIT_ON(I2C2CONbits.RCEN);

		I2C2STATbits.I2COV = 0;
		*(data+nb) = I2C2RCV & 0xFF;

		/* Ensure I2C module is idle */
		ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

		/* send (N)ACK condition back to the I2C slave indicating master received
			the data byte */
		if (nb == nbytes-1)
			I2C2CONbits.ACKDT = 1;
		else
			I2C2CONbits.ACKDT = 0;
		I2C2CONbits.ACKEN = 1;

		/* wait until (N)ACK sequence is over */
		ACTIVE_WAIT_ON(I2C2CONbits.ACKEN);
	}
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON(I2C2CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_2));

	IEC3bits.MI2C2IE = 0;
	IEC3bits.SI2C2IE = 0;

	return EE_I2C_SUCCESS;			// return with data
}

EE_INT8 EE_i2c_write_byte(
		EE_UINT8 port,
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 data)
{
	if( port == EE_I2C_PORT_1 )
		i2c_write_port_1( device, address, data );
	else if( port == EE_I2C_PORT_2 )
		i2c_write_port_2( device, address, data );
	else return -EE_I2C_BAD_PORT;
	
	return EE_I2C_SUCCESS;
}

EE_INT8 EE_i2c_read_byte(
		EE_UINT8 port,
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8* data)
{
	if( port == EE_I2C_PORT_1 )
		i2c_read_port_1( device, address, 1, data );
	else if( port == EE_I2C_PORT_2 )
		i2c_read_port_2( device, address, 1, data );
	else return -EE_I2C_BAD_PORT;
	
	return EE_I2C_SUCCESS;
}

EE_INT8 EE_i2c_read_bytes(
		EE_UINT8 port,
		EE_UINT8 device,
		EE_UINT8 address,
		EE_UINT8 nbytes,
		EE_UINT8* data)
{
	if( port == EE_I2C_PORT_1 )
		i2c_read_port_1( device, address, nbytes, data );
	else if( port == EE_I2C_PORT_2 )
		i2c_read_port_2( device, address, nbytes, data );
	else return -EE_I2C_BAD_PORT;
	
	return EE_I2C_SUCCESS;
}
