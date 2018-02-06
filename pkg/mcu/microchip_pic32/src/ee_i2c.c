#include "mcu/microchip_pic32/inc/ee_i2c.h"
#include "ee_internal.h"
#include "cpu/pic32/inc/ee_irqstub.h"
#include "cpu/pic32/inc/ee_utils.h"


/******************************************************************************/
/*			 Local variables 				      */
/******************************************************************************/


#ifdef __32MX795F512L__


static EE_UINT8 i2c_HS_port1;

static EE_UINT8 i2c_HS_port1a;

static EE_UINT8 i2c_HS_port2;

static EE_UINT8 i2c_HS_port2a;

static EE_UINT8 i2c_HS_port3a;
 
#else //not defined __32MX795F512L__ 

static EE_UINT8 i2c_HS_port1;
static EE_UINT8 i2c_HS_port2;

#endif

/******************************************************************************/
/* 			Inline functions 				      */
/******************************************************************************/

#ifdef __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/


__INLINE__ void init_i2c_port_1(EE_UINT16 spibrg, EE_UINT16 flags) {
	/* Stop I2C port */
	I2C1CONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT1_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT1_MASTER_INT_FLAG = 0;
	EE_I2C_PORT1_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT1_BUS_INT_FLAG = 0;
	

	/* Errata Silica Suggestion, the SDA port must be manually 
	set-up before configuring the module	*/
	TRISAbits.TRISA15 = 0;
	LATAbits.LATA15 = 0;
	
	/* Clear address and mask */
	I2C1ADD=0;
	I2C1MSK=0;

	/* Set baudrate */
	I2C1BRG = spibrg;	

	/* Configure I2C port */
	I2C1CON = 0;
	if (i2c_HS_port1)
		I2C1CONbits.DISSLW = 0; // Enable HS mode
	else
		I2C1CONbits.DISSLW = 1; // Disable HS mode
	

	I2C1CONbits.ACKDT = 1;	
			
	/* Start I2C port */
	I2C1CONbits.ON = 1;
}

__INLINE__ void init_i2c_port_1A(EE_UINT16 spibrg, EE_UINT16 flags) {
	/* Stop I2C port */
	I2C1ACONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT1A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1A_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT1A_MASTER_INT_FLAG = 0;
	EE_I2C_PORT1A_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT1A_BUS_INT_FLAG = 0;
	
	
	/* Errata Silica Suggestion, the SDA port must be manually 
	set-up before configuring the module	*/
	TRISFbits.TRISF2 = 0;
	LATFbits.LATF2 = 0;	
	
	/* Clear address and mask */
	I2C1AADD = 0;
	I2C1AMSK = 0;

	/* Set baudrate */
	I2C1ABRG = spibrg;	

	/* Configure I2C port */
	I2C1ACON = 0;
	if (i2c_HS_port1a)
		I2C1ACONbits.DISSLW = 0; // Enable HS mode
	else
		I2C1ACONbits.DISSLW = 1; // Disable HS mode
	

	I2C1ACONbits.ACKDT = 1;	
			
	/* Start I2C port */
	I2C1ACONbits.ON = 1;
}

__INLINE__ void init_i2c_port_2(EE_UINT16 spibrg, EE_UINT16 flags) {
	/*TODO: use the flags. */	
	
	/* Stop I2C port */
	I2C2CONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT2_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT2_MASTER_INT_FLAG = 0;
	EE_I2C_PORT2_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT2_BUS_INT_FLAG = 0;

	/* Errata Silica Suggestion, the SDA port must be manually 
	set-up before configuring the module	*/
	TRISAbits.TRISA3 = 0;
	LATAbits.LATA3 = 0;
	
	/* Clear address and mask */
	I2C2ADD = 0;
	I2C2MSK = 0;

	/* Set baudrate */
	I2C2BRG = spibrg;

	/* Configure I2C port */
	I2C2CON = 0;
	I2C2CONbits.ACKDT = 1;
	if (i2c_HS_port2)
		I2C2CONbits.DISSLW = 0; // Enable HS mode
	else
		I2C2CONbits.DISSLW = 1; // Disable HS mode
	/* Start I2C port */
	I2C2CONbits.ON = 1;
}

__INLINE__ void init_i2c_port_2A(EE_UINT16 spibrg, EE_UINT16 flags) {
	/*TODO: use the flags. */	
	
	/* Stop I2C port */
	I2C2ACONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT2A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2A_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT2A_MASTER_INT_FLAG = 0;
	EE_I2C_PORT2A_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT2A_BUS_INT_FLAG = 0;
	

	/* Errata Silica Suggestion, the SDA port must be manually 
	set-up before configuring the module	*/
	TRISGbits.TRISG7 = 0;
	LATGbits.LATG7 = 0;
	
	/* Clear address and mask */
	I2C2AADD = 0;
	I2C2AMSK = 0;

	/* Set baudrate */
	I2C2ABRG = spibrg;

	/* Configure I2C port */
	I2C2ACON = 0;
	I2C2ACONbits.ACKDT = 1;
	if (i2c_HS_port2a)
		I2C2ACONbits.DISSLW = 0; // Enable HS mode
	else
		I2C2ACONbits.DISSLW = 1; // Disable HS mode
	/* Start I2C port */
	I2C2ACONbits.ON = 1;
}


__INLINE__ void init_i2c_port_3A(EE_UINT16 spibrg, EE_UINT16 flags) {
	/*TODO: use the flags. */	
	
	/* Stop I2C port */
	I2C3ACONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT3A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT3A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT3A_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT3A_MASTER_INT_FLAG = 0;
	EE_I2C_PORT3A_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT3A_BUS_INT_FLAG = 0;

	/* Errata Silica Suggestion, the SDA port must be manually 
	set-up before configuring the module	*/
	TRISFbits.TRISF4 = 0;
	LATFbits.LATF4 = 0;
	
	/* Clear address and mask */
	I2C3AADD = 0;
	I2C3AMSK = 0;

	/* Set baudrate */
	I2C3ABRG = spibrg;

	/* Configure I2C port */
	I2C3ACON = 0;
	I2C3ACONbits.ACKDT = 1;
	if (i2c_HS_port3a)
		I2C3ACONbits.DISSLW = 0; // Enable HS mode
	else
		I2C3ACONbits.DISSLW = 1; // Disable HS mode
	/* Start I2C port */
	I2C3ACONbits.ON = 1;
}



#else //not defined __32MX795F512L__


/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx360f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/

__INLINE__ void init_i2c_port_1(EE_UINT32 i2cbrg, EE_UINT16 flags) {
	/* Stop I2C port */
	I2C1CONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT1_MASTER_INT_ENABLE = 0;	
	EE_I2C_PORT1_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT1_MASTER_INT_FLAG = 0;
	EE_I2C_PORT1_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT1_BUS_INT_FLAG = 0;

	/* Clear address and mask */
	I2C1ADD=0;
	I2C1MSK=0;

	/* Set baudrate */
	I2C1BRG = i2cbrg;	

	/* Configure I2C port */
	I2C1CON = 0;
	if (i2c_HS_port1)
		I2C1CONbits.DISSLW = 0; // Enable HS mode
	else
		I2C1CONbits.DISSLW = 1; // Disable HS mode
	

	I2C1CONbits.ACKDT = 1;	
			
	/* Start I2C port */
	I2C1CONbits.ON = 1;
}


__INLINE__ void init_i2c_port_2(EE_UINT16 i2cbrg, EE_UINT16 flags) {
	/*TODO: use the flags. */	
	
	/* Stop I2C port */
	I2C2CONbits.ON = 0;

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT2_MASTER_INT_ENABLE = 0;	
	EE_I2C_PORT2_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2_BUS_INT_ENABLE = 0;

	/* Clear Interrupt flag bits */
	EE_I2C_PORT2_MASTER_INT_FLAG = 0;
	EE_I2C_PORT2_SLAVE_INT_FLAG = 0;
	EE_I2C_PORT2_BUS_INT_FLAG = 0;

	/* Clear address and mask */
	I2C2ADD = 0;
	I2C2MSK = 0;

	/* Set baudrate */
	I2C2BRG = i2cbrg;

	/* Configure I2C port */
	I2C2CON = 0;
	I2C2CONbits.ACKDT = 1;
	if (i2c_HS_port2)
		I2C2CONbits.DISSLW = 0; // Enable HS mode
	else
		I2C2CONbits.DISSLW = 1; // Disable HS mode
	/* Start I2C port */
	I2C2CONbits.ON = 1;
}

#endif



/******************************************************************************/
/* 			Local functions 				      */
/******************************************************************************/

/****************************************************************/
/* 			BRG calculation	 			*/
/****************************************************************/

static EE_UINT16 i2c_calculate_brg(EE_UINT32 speed){
	
	EE_UINT32 pbc = EE_get_peripheral_clock();
	return (EE_UINT16)((pbc/(2*speed)) - 2);
}



/****************************************************************/
/* 			Write functions 			*/
/****************************************************************/

#ifdef __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/



static EE_INT8 i2c_write_port_1(EE_UINT8 device, EE_UINT8 address,
							EE_UINT8 data){
	
	unsigned int cto;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));
	

	/* Transmit a Start condition, initiate Start on SDA and SCL pins */
	I2C1CONbits.SEN = 1;		

	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.SEN);

	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C1TRN = device;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;
	
	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);
	
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT) ;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	I2C1TRN = data;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF) ;

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT) ;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins 

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	EE_I2C_PORT1_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1_BUS_INT_ENABLE = 0;	

	return EE_I2C_SUCCESS;
}

static EE_INT8 i2c_write_port_1A(EE_UINT8 device, EE_UINT8 address,
							EE_UINT8 data){
	
	unsigned int cto;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1A));
	

	/* Transmit a Start condition, initiate Start on SDA and SCL pins */
	I2C1ACONbits.SEN = 1;		

	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C1ACONbits.SEN);

	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C1ATRN = device;
	if(I2C1ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;
	
	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1ASTATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));

	/* Write word address */
	I2C1ATRN = address;
	if(I2C1ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1ASTATbits.TBF);
	
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT) ;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));
	
	I2C1ATRN = data;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1ASTATbits.TBF) ;

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1ASTATbits.ACKSTAT) ;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));

	/* send STOP condition */
	I2C1ACONbits.PEN = 1;		// initiate Stop on SDA and SCL pins 

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C1ACONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	EE_I2C_PORT1A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1A_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;
}

static EE_INT8 i2c_write_port_2(EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 data){

	unsigned int cto = 0;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Transmit a Start condition */
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins
			
	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C2CONbits.SEN);
	
	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C2TRN = device;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Write word address */
	I2C2TRN = address;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));	
	
	/* Write data byte to serial */
	I2C2TRN = data;
	if(I2C2STATbits.IWCOL)        // If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins
	
	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C2CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	EE_I2C_PORT2_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2_BUS_INT_ENABLE = 0;
	
	return EE_I2C_SUCCESS;
}


static EE_INT8 i2c_write_port_2A(EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 data){

	unsigned int cto = 0;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* Transmit a Start condition */
	I2C2ACONbits.SEN = 1;		// initiate Start on SDA and SCL pins
			
	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C2ACONbits.SEN);
	
	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C2ATRN = device;

	if(I2C2ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* Write word address */
	I2C2ATRN = address;

	if(I2C2ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));	
	
	/* Write data byte to serial */
	I2C2ATRN = data;
	if(I2C2ASTATbits.IWCOL)        // If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2ASTATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* send STOP condition */
	I2C2ACONbits.PEN = 1;		// initiate Stop on SDA and SCL pins
	
	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C2ACONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));


	EE_I2C_PORT2A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2A_BUS_INT_ENABLE = 0;	
	
	return EE_I2C_SUCCESS;
}


static EE_INT8 i2c_write_port_3A(EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 data){

	unsigned int cto = 0;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* Transmit a Start condition */
	I2C3ACONbits.SEN = 1;		// initiate Start on SDA and SCL pins
			
	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C3ACONbits.SEN);
	
	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C3ATRN = device;

	if(I2C3ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C3ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C3ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* Write word address */
	I2C3ATRN = address;

	if(I2C3ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C3ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C3ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));	
	
	/* Write data byte to serial */
	I2C3ATRN = data;
	if(I2C3ASTATbits.IWCOL)        // If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C3ASTATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C3ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* send STOP condition */
	I2C3ACONbits.PEN = 1;		// initiate Stop on SDA and SCL pins
	
	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C3ACONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	EE_I2C_PORT3A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT3A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT3A_BUS_INT_ENABLE = 0;
	
	return EE_I2C_SUCCESS;
}


#else //not defined __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx360f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/


static EE_INT8 i2c_write_port_1(EE_UINT8 device, EE_UINT8 address,
							EE_UINT8 data){
	
	unsigned int cto;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON(EE_i2c_idle(EE_I2C_PORT_1));
	

	/* Transmit a Start condition, initiate Start on SDA and SCL pins */
	I2C1CONbits.SEN = 1;		

	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.SEN);


	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C1TRN = device;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;
	
	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);


	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);
	

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));



	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);
	
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT) ;

	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	


	I2C1TRN = data;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF) ;


	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT) ;
	

	/* Ensure I2C module is idle */

	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));


	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins 

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.PEN);


	/* Ensure I2C module is idle */

	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	EE_I2C_PORT1_MASTER_INT_ENABLE 	= 0;
	EE_I2C_PORT1_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;
}


static EE_INT8 i2c_write_port_2(EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 data){

	unsigned int cto = 0;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Transmit a Start condition */
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins
			
	/* Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C2CONbits.SEN);
	

	/* Write Slave address and set master for transmission 
	(R/W bit should be 0) */
	I2C2TRN = device;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Write word address */
	I2C2TRN = address;

	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);


	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);


	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));	
	
	/* Write data byte to serial */
	I2C2TRN = data;
	if(I2C2STATbits.IWCOL)        // If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins
	
	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C2CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));


	EE_I2C_PORT2_MASTER_INT_ENABLE 	= 0;
	EE_I2C_PORT2_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2_BUS_INT_ENABLE = 0;	
	
	return EE_I2C_SUCCESS;
}

#endif


/****************************************************************/
/* 			Read functions	 			*/
/****************************************************************/

#ifdef __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/


static EE_INT8 i2c_read_port_1(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data){
	
	unsigned int cto = 0;
	
	/*  Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	// Transmit a Start condition on i2c1
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	/*  Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)*/            
	I2C1TRN = device;

	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* Generate the I2C bus restart condition */
	I2C1CONbits.RSEN = 1;	// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	ACTIVE_WAIT_ON (I2C1CONbits.RSEN);

	/* Write Slave address and set master for reception
	(R/W bit should be 1) */
	I2C1TRN = device+1;
	if(I2C1STATbits.IWCOL)	// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	/* Read the data byte */
	I2C1CONbits.RCEN = 1;
	while(I2C1CONbits.RCEN);
	I2C1STATbits.I2COV = 0;
	*data = I2C1RCV & 0xFF;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C1CONbits.ACKDT = 1;
	I2C1CONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C1CONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));


	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT1_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1_BUS_INT_ENABLE = 0;

	

	return EE_I2C_SUCCESS;			// return with data
}

static EE_INT8 i2c_read_port_1A(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data){
	
	unsigned int cto = 0;
	
	/*  Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));

	// Transmit a Start condition on i2c1
	I2C1ACONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	/*  Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C1ACONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)*/            
	I2C1ATRN = device;

	if(I2C1ASTATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));
	
	/* Write word address */
	I2C1ATRN = address;
	if(I2C1ASTATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1ASTATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1ASTATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));

	/* Generate the I2C bus restart condition */
	I2C1ACONbits.RSEN = 1;	// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	ACTIVE_WAIT_ON (I2C1ACONbits.RSEN);

	/* Write Slave address and set master for reception
	(R/W bit should be 1) */
	I2C1ATRN = device + 1;
	if(I2C1ASTATbits.IWCOL)	// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));
	
	/* Read the data byte */
	I2C1ACONbits.RCEN = 1;
	while(I2C1ACONbits.RCEN);
	I2C1ASTATbits.I2COV = 0;
	*data = I2C1ARCV & 0xFF;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));

	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C1ACONbits.ACKDT = 1;
	I2C1ACONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C1ACONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));

	/* send STOP condition */
	I2C1ACONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C1ACONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1A));


	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT1A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1A_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;			// return with data
}




static EE_INT8 i2c_read_port_2(EE_UINT8 device, EE_UINT8 address , EE_UINT8 *data){
	
	unsigned int cto = 0;

	/* Ensure I2C module is idle  */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Transmit a Start condition on i2c2  */
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins
	
	/* Wait till Start sequence is completed  */
	ACTIVE_WAIT_ON (I2C2CONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)  */
        I2C2TRN = device;

	if(I2C2STATbits.IWCOL)	// If write collision occurs,return -1 
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Write word address */
	I2C2TRN = address;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);
		
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));
		
	/* Generate the I2C bus restart condition */
	I2C2CONbits.RSEN = 1;		// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	while (I2C2CONbits.RSEN);

	/* Write Slave address and set master for reception 
						(R/W bit should be 1) */
	I2C2TRN = device+1;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Read the data byte */
	I2C2CONbits.RCEN = 1;
	while(I2C2CONbits.RCEN) ;
	I2C2STATbits.I2COV = 0;
	*data = I2C2RCV & 0xFF;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));
	
	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C2CONbits.ACKDT = 1;
	I2C2CONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C2CONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	while(I2C2CONbits.PEN) ;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT2_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;			// return with data
}

static EE_INT8 i2c_read_port_2A(EE_UINT8 device, EE_UINT8 address , EE_UINT8 *data){
	
	unsigned int cto = 0;

	/* Ensure I2C module is idle  */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* Transmit a Start condition on i2c2  */
	I2C2ACONbits.SEN = 1;		// initiate Start on SDA and SCL pins
	
	/* Wait till Start sequence is completed  */
	ACTIVE_WAIT_ON (I2C2ACONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)  */
        I2C2ATRN = device;

	if(I2C2ASTATbits.IWCOL)	// If write collision occurs,return -1 
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2ASTATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* Write word address */
	I2C2ATRN = address;
	if(I2C2ASTATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2ASTATbits.ACKSTAT);
		
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));
		
	/* Generate the I2C bus restart condition */
	I2C2ACONbits.RSEN = 1;		// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	while (I2C2ACONbits.RSEN);

	/* Write Slave address and set master for reception 
						(R/W bit should be 1) */
	I2C2ATRN = device+1;
	if(I2C2ASTATbits.IWCOL)		// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2ASTATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* Read the data byte */
	I2C2ACONbits.RCEN = 1;
	while(I2C2ACONbits.RCEN) ;
	I2C2ASTATbits.I2COV = 0;
	*data = I2C2ARCV & 0xFF;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));
	
	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C2ACONbits.ACKDT = 1;
	I2C2ACONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C2ACONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* send STOP condition */
	I2C2ACONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	while(I2C2ACONbits.PEN) ;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2A));

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT2A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2A_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;			// return with data
}






static EE_INT8 i2c_read_port_3A(EE_UINT8 device, EE_UINT8 address , EE_UINT8 *data){
	
	unsigned int cto = 0;

	/* Ensure I2C module is idle  */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* Transmit a Start condition on i2c2  */
	I2C3ACONbits.SEN = 1;		// initiate Start on SDA and SCL pins
	
	/* Wait till Start sequence is completed  */
	ACTIVE_WAIT_ON (I2C3ACONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)  */
        I2C3ATRN = device;

	if(I2C3ASTATbits.IWCOL)	// If write collision occurs,return -1 
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C3ASTATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C3ASTATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* Write word address */
	I2C3ATRN = address;
	if(I2C3ASTATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C3ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C3ASTATbits.ACKSTAT);
		
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));
		
	/* Generate the I2C bus restart condition */
	I2C3ACONbits.RSEN = 1;		// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	while (I2C3ACONbits.RSEN);

	/* Write Slave address and set master for reception 
						(R/W bit should be 1) */
	I2C3ATRN = device+1;
	if(I2C3ASTATbits.IWCOL)		// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C3ASTATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C3ASTATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* Read the data byte */
	I2C3ACONbits.RCEN = 1;
	while(I2C3ACONbits.RCEN) ;
	I2C3ASTATbits.I2COV = 0;
	*data = I2C3ARCV & 0xFF;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));
	
	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C3ACONbits.ACKDT = 1;
	I2C3ACONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C3ACONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* send STOP condition */
	I2C3ACONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	while(I2C3ACONbits.PEN) ;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_3A));

	/* Disable Interrupts, due to master, slave and channel*/
	EE_I2C_PORT3A_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT3A_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT3A_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;			// return with data
}




#else //not defined __32MX795F512L__

/******************************************************************************/
/* 	*********************************************************	      */	
/* 	* Specific set of functions for the pic32mx795f512l mcu *	      */
/*   	*********************************************************	      */
/******************************************************************************/



static EE_INT8 i2c_read_port_1(EE_UINT8 device, EE_UINT8 address, EE_UINT8 *data){
	
	unsigned int cto = 0;
	
	/*  Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	// Transmit a Start condition on i2c1
	I2C1CONbits.SEN = 1;		// initiate Start on SDA and SCL pins

	/*  Wait till Start sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)*/            
	I2C1TRN = device;

	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	/* Write word address */
	I2C1TRN = address;
	if(I2C1STATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* Generate the I2C bus restart condition */
	I2C1CONbits.RSEN = 1;	// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	ACTIVE_WAIT_ON (I2C1CONbits.RSEN);

	/* Write Slave address and set master for reception
	(R/W bit should be 1) */
	I2C1TRN = device+1;
	if(I2C1STATbits.IWCOL)	// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C1STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C1STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));
	
	/* Read the data byte */
	I2C1CONbits.RCEN = 1;
	while(I2C1CONbits.RCEN);
	I2C1STATbits.I2COV = 0;
	*data = I2C1RCV & 0xFF;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C1CONbits.ACKDT = 1;
	I2C1CONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C1CONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	/* send STOP condition */
	I2C1CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	ACTIVE_WAIT_ON (I2C1CONbits.PEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_1));

	EE_I2C_PORT1_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT1_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT1_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;			// return with data
}




static EE_INT8 i2c_read_port_2(EE_UINT8 device, EE_UINT8 address , EE_UINT8 *data){
	
	unsigned int cto = 0;

	/* Ensure I2C module is idle  */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Transmit a Start condition on i2c2  */
	I2C2CONbits.SEN = 1;		// initiate Start on SDA and SCL pins
	
	/* Wait till Start sequence is completed  */
	ACTIVE_WAIT_ON (I2C2CONbits.SEN);

	/* Write Slave address and set master for transmission  
	(R/W bit should be 0)  */
        I2C2TRN = device;

	if(I2C2STATbits.IWCOL)	// If write collision occurs,return -1 
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);
	
	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Write word address */
	I2C2TRN = address;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1                     
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));
		
	/* Generate the I2C bus restart condition */
	I2C2CONbits.RSEN = 1;		// initiate restart on SDA and SCL pins

	/* Wait until re-start condition is over */
	while (I2C2CONbits.RSEN);

	/* Write Slave address and set master for reception 
						(R/W bit should be 1) */
	I2C2TRN = device+1;
	if(I2C2STATbits.IWCOL)		// If write collision occurs,return -1                      
		return -EE_I2C_FAILURE;

	/* Wait till address is transmitted */
	ACTIVE_WAIT_ON (I2C2STATbits.TBF);

	/* Test for ACK condition received */
	ACTIVE_WAIT_ON (I2C2STATbits.ACKSTAT);
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* Read the data byte */
	I2C2CONbits.RCEN = 1;
	while(I2C2CONbits.RCEN) ;
	I2C2STATbits.I2COV = 0;
	*data = I2C2RCV & 0xFF;
	
	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));
	
	/* send NACK condition back to the I2C slave indicating master received 
	the data byte */
	I2C2CONbits.ACKDT = 1;
	I2C2CONbits.ACKEN = 1;

	/* wait until NACK sequence is over */
	ACTIVE_WAIT_ON (I2C2CONbits.ACKEN);

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	/* send STOP condition */
	I2C2CONbits.PEN = 1;		// initiate Stop on SDA and SCL pins

	/* Wait till Stop sequence is completed */
	while(I2C2CONbits.PEN) ;

	/* Ensure I2C module is idle */
	ACTIVE_WAIT_ON (EE_i2c_idle(EE_I2C_PORT_2));

	EE_I2C_PORT2_MASTER_INT_ENABLE = 0;
	EE_I2C_PORT2_SLAVE_INT_ENABLE = 0;
	EE_I2C_PORT2_BUS_INT_ENABLE = 0;

	return EE_I2C_SUCCESS;			// return with data
}



#endif


/******************************************************************************/
/*			Global Functions 				      */
/******************************************************************************/


/* 
 * EE_i2c_init initializes the channel.
 */



EE_INT8 EE_i2c_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags)
{	


#ifdef __32MX795F512L__
	
	switch(port){

	case EE_I2C_PORT_1:
	
		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port1 = 0;
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port1 = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
		init_i2c_port_1(i2c_calculate_brg(baudrate), flags);
		
		return EE_I2C_SUCCESS;
	break;

	case EE_I2C_PORT_1A:
		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port1a = 0;
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port1a = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
		init_i2c_port_1A(i2c_calculate_brg(baudrate), flags);
		return EE_I2C_SUCCESS;
	break;

	case EE_I2C_PORT_2:
		
		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port2 = 0;
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port2 = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
			
		init_i2c_port_2(i2c_calculate_brg(baudrate), flags);
		
		return EE_I2C_SUCCESS;
	break;
	
	case EE_I2C_PORT_2A:
		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port2a = 0;
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port2a = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
		init_i2c_port_2A(i2c_calculate_brg(baudrate), flags);
		return EE_I2C_SUCCESS;
	break;

	case EE_I2C_PORT_3A:
		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port3a = 0;
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port3a = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
		init_i2c_port_3A(i2c_calculate_brg(baudrate), flags);
		return EE_I2C_SUCCESS;
	break;

	default:
		return -EE_I2C_ERR_BAD_PORT;
	}		
	
#else //not defined __32MX795F512L__
	
	if (port == EE_I2C_PORT_1) {
		
		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port1 = 0;
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port1 = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
		init_i2c_port_1(i2c_calculate_brg(baudrate), flags);
		return EE_I2C_SUCCESS;

	} else if (port == EE_I2C_PORT_2) {

		switch (baudrate){
		case EE_I2C_100KHZ:
			i2c_HS_port1 = 0;
			
		break;
		case EE_I2C_400KHZ:
			i2c_HS_port1 = 1;
		break;
		default:
			return -EE_I2C_WRONG_SPEED;
		}
		init_i2c_port_2(i2c_calculate_brg(baudrate), flags);
		return EE_I2C_SUCCESS;
		
	}
	return -EE_I2C_ERR_BAD_PORT;

#endif
}

/* 
 * EE_i2c_idle verifies the state of the channel.
 */

EE_INT8 EE_i2c_idle(EE_UINT8 port){

#ifdef __32MX795F512L__

	switch(port){

	case EE_I2C_PORT_1:
		return i2c_port1_idle();
	break;

	case EE_I2C_PORT_1A:
		return i2c_port1A_idle();
	break;

	case EE_I2C_PORT_2:
		return i2c_port2_idle();
	break;

	case EE_I2C_PORT_2A:
		return i2c_port2A_idle();
	break;

	case EE_I2C_PORT_3A:
		return i2c_port3A_idle();
	break;

	default:
		return -EE_I2C_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__

	if (port == EE_I2C_PORT_1) {
		return i2c_port1_idle();
	} else if (port == EE_I2C_PORT_2) {
		return i2c_port2_idle();
	}
	return -EE_I2C_ERR_BAD_PORT;

#endif
	
}


/* 
 * EE_i2c_read_byte calls the specific read function associated with each port
 * of the I2C to speed_up the communication task 
 */

EE_INT8 EE_i2c_read_byte (EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 * data ){

#ifdef __32MX795F512L__	
	switch(port){

	case EE_I2C_PORT_1:
		return i2c_read_port_1(device, address, data);
	break;

	case EE_I2C_PORT_1A:
		return i2c_read_port_1A(device, address, data);
	break;

	case EE_I2C_PORT_2:
		return i2c_read_port_2(device, address, data);
	break;
	
	case EE_I2C_PORT_2A:
		return i2c_read_port_2A(device, address, data);
	break;

	case EE_I2C_PORT_3A:
		return i2c_read_port_3A(device, address, data);
	break;

	default:
		return -EE_I2C_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__	
	
	if (port == EE_I2C_PORT_1 )
		return i2c_read_port_1(device, address, data);
	else if (port == EE_I2C_PORT_2 )
		return i2c_read_port_2(device, address, data); 
	else
		return -EE_I2C_ERR_BAD_PORT;
#endif
}


/* EE_i2c_write_byte calls the specific write function associated with each 
 * port of the I2C to speed_up the communication task 
 */
EE_INT8 EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
			EE_UINT8 data) {

#ifdef __32MX795F512L__

	switch(port){

	case EE_I2C_PORT_1:
		return i2c_write_port_1(device, address, data);
	break;

	case EE_I2C_PORT_1A:
		return i2c_write_port_1A(device, address, data);
	break;

	case EE_I2C_PORT_2:
		return i2c_write_port_2(device, address, data);
	break;
	
	case EE_I2C_PORT_2A:
		return i2c_write_port_2A(device, address, data);
	break;

	case EE_I2C_PORT_3A:
		return i2c_write_port_3A(device, address, data);
	break;

	default:
		return -EE_I2C_ERR_BAD_PORT;
	}

#else //not defined __32MX795F512L__
	
	if (port == EE_I2C_PORT_1 )
		return i2c_write_port_1(device, address, data);
	else if (port == EE_I2C_PORT_2 )
		return i2c_write_port_2(device, address, data);
	else
		return -EE_I2C_ERR_BAD_PORT;



#endif		

}

