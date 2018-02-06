#ifndef __INCLUDE_MICROCHIP_PIC32_I2C_H__
#define __INCLUDE_MICROCHIP_PIC32_I2C_H__

#include "ee.h"

/*
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif
*/
/******************************************************************************/
/*			I2C available speed values			      */
/******************************************************************************/

#define EE_I2C_100KHZ		100000
#define EE_I2C_400KHZ		400000


/******************************************************************************/
/*			I2C configuration paramaters			      */
/******************************************************************************/

#define EE_I2C_DEFAULT_FLAGS 	0x0
#define CONNECTION_TIMEOUT	2000 

/******************************************************************************/
/*			Returned Messages				      */
/******************************************************************************/

#define EE_I2C_SUCCESS		1 	//Used as positive
#define EE_I2C_FAILURE	 	1
#define EE_I2C_ERR_BAD_PORT 	2
#define EE_I2C_WRONG_SPEED 	2


/******************************************************************************/
/*			Port Definition			      		      */
/******************************************************************************/


#ifdef __32MX795F512L__

enum {
	EE_I2C_PORT_1  = 0,
	EE_I2C_PORT_1A,
	EE_I2C_PORT_2,
	EE_I2C_PORT_2A,
	EE_I2C_PORT_3A,
	EE_I2C_PORT_N,
};

#else //not defined __32MX795F512L__


enum {
	EE_I2C_PORT_1  = 0,
	EE_I2C_PORT_2,
	EE_I2C_PORT_N,
};

#endif


/******************************************************************************/
/*			Interrupt Flags and Enable Registers   		      */
/******************************************************************************/



#ifdef __32MX795F512L__

/* NOTE: The following registers have different names from the ones 
	 * written in the device manual, but they are taken from the 
	 * p32mx795f512l.h header file. If some problems in the next versions
	 * of the compiler will rise, substitute these registers with the
	 *right ones. */

#if defined (_IEC0_I2C1AEIE_POSITION)
    #define __I2C1AEIE__  I2C1AEIE
    #define __I2C1ARXIE__ I2C1ARXIE
    #define __I2C1ATXIE__ I2C1ATXIE
#elif defined (_IEC0_I2C3BIE_POSITION)
    #define __I2C1AEIE__  I2C3BIE
    #define __I2C1ARXIE__ I2C3SIE
    #define __I2C1ATXIE__ I2C3MIE
#elif defined (_IEC0_I2C1ABIE_POSITION)
    #define __I2C1AEIE__  I2C1ABIE
    #define __I2C1ARXIE__ I2C1ASIE
    #define __I2C1ATXIE__ I2C1AMIE
#endif

#if defined (_IEC1_I2C2AEIE_POSITION)
    #define __I2C2AEIE__  I2C2AEIE
    #define __I2C2ARXIE__ I2C2ARXIE
    #define __I2C2ATXIE__ I2C2ATXIE
#elif defined (_IEC1_I2C4BIE_POSITION)
    #define __I2C2AEIE__  I2C4BIE
    #define __I2C2ARXIE__ I2C4SIE
    #define __I2C2ATXIE__ I2C4MIE
#elif defined (_IEC1_I2C2ABIE_POSITION)
    #define __I2C2AEIE__  I2C2ABIE
    #define __I2C2ARXIE__ I2C2ASIE
    #define __I2C2ATXIE__ I2C2AMIE
#endif

#if defined (_IEC1_I2C3AEIE_POSITION)
    #define __I2C3AEIE__  I2C3AEIE
    #define __I2C3ARXIE__ I2C3ARXIE
    #define __I2C3ATXIE__ I2C3ATXIE
#elif defined (_IEC1_I2C5BIE_POSITION)
    #define __I2C3AEIE__  I2C5BIE
    #define __I2C3ARXIE__ I2C5SIE
    #define __I2C3ATXIE__ I2C5MIE
#elif defined (_IEC1_I2C3ABIE_POSITION)
    #define __I2C3AEIE__  I2C3ABIE
    #define __I2C3ARXIE__ I2C3ASIE
    #define __I2C3ATXIE__ I2C3AMIE
#endif

#if defined (_IFS0_I2C1AEIF_POSITION)
    #define __I2C1AEIF__  I2C1AEIF
    #define __I2C1ARXIF__ I2C1ARXIF
    #define __I2C1ATXIF__ I2C1ATXIF
#elif defined (_IFS0_I2C3BIF_POSITION)
    #define __I2C1AEIF__  I2C3BIF
    #define __I2C1ARXIF__ I2C3SIF
    #define __I2C1ATXIF__ I2C3MIF
#elif defined (_IFS0_I2C1ABIF_POSITION)
    #define __I2C1AEIF__  I2C1ABIF
    #define __I2C1ARXIF__ I2C1ASIF
    #define __I2C1ATXIF__ I2C1AMIF
#endif

#if defined (_IFS1_I2C2AEIF_POSITION)
    #define __I2C2AEIF__  I2C2AEIF
    #define __I2C2ARXIF__ I2C2ARXIF
    #define __I2C2ATXIF__ I2C2ATXIF
#elif defined (_IFS1_I2C4BIF_POSITION)
    #define __I2C2AEIF__  I2C4BIF
    #define __I2C2ARXIF__ I2C4SIF
    #define __I2C2ATXIF__ I2C4MIF
#elif defined (_IFS1_I2C2ABIF_POSITION)
    #define __I2C2AEIF__  I2C2ABIF
    #define __I2C2ARXIF__ I2C2ASIF
    #define __I2C2ATXIF__ I2C2AMIF
#endif

#if defined (_IFS1_I2C3AEIF_POSITION)
    #define __I2C3AEIF__  I2C3AEIF
    #define __I2C3ARXIF__ I2C3ARXIF
    #define __I2C3ATXIF__ I2C3ATXIF
#elif defined (_IFS1_I2C5BIF_POSITION)
    #define __I2C3AEIF__  I2C5BIF
    #define __I2C3ARXIF__ I2C5SIF
    #define __I2C3ATXIF__ I2C5MIF
#elif defined (_IFS1_I2C3ABIF_POSITION)
    #define __I2C3AEIF__  I2C3ABIF
    #define __I2C3ARXIF__ I2C3ASIF
    #define __I2C3ATXIF__ I2C3AMIF
#endif    
     
/* 	Interrupt Enable registers	*/

#define	EE_I2C_PORT1_MASTER_INT_ENABLE 		IEC0bits.I2C1MIE
#define	EE_I2C_PORT1_SLAVE_INT_ENABLE 		IEC0bits.I2C1SIE
#define	EE_I2C_PORT1_BUS_INT_ENABLE 		IEC0bits.I2C1BIE

#define	EE_I2C_PORT1A_MASTER_INT_ENABLE 	IEC0bits.__I2C1ATXIE__
#define	EE_I2C_PORT1A_SLAVE_INT_ENABLE 		IEC0bits.__I2C1ARXIE__
#define	EE_I2C_PORT1A_BUS_INT_ENABLE 		IEC0bits.__I2C1AEIE__

#define	EE_I2C_PORT2_MASTER_INT_ENABLE 		IEC1bits.I2C2MIE
#define	EE_I2C_PORT2_SLAVE_INT_ENABLE 		IEC1bits.I2C2SIE
#define	EE_I2C_PORT2_BUS_INT_ENABLE 		IEC1bits.I2C2BIE

#define	EE_I2C_PORT2A_MASTER_INT_ENABLE 	IEC1bits.__I2C2ATXIE__
#define	EE_I2C_PORT2A_SLAVE_INT_ENABLE 		IEC1bits.__I2C2ARXIE__
#define	EE_I2C_PORT2A_BUS_INT_ENABLE 		IEC1bits.__I2C2AEIE__

#define	EE_I2C_PORT3A_MASTER_INT_ENABLE 	IEC1bits.__I2C3ATXIE__
#define	EE_I2C_PORT3A_SLAVE_INT_ENABLE 		IEC1bits.__I2C3ARXIE__
#define	EE_I2C_PORT3A_BUS_INT_ENABLE 		IEC1bits.__I2C3AEIE__



/* 	Interrupt Flag bits	*/

#define	EE_I2C_PORT1_MASTER_INT_FLAG 		IFS0bits.I2C1MIF
#define	EE_I2C_PORT1_SLAVE_INT_FLAG 		IFS0bits.I2C1SIF
#define	EE_I2C_PORT1_BUS_INT_FLAG 		IFS0bits.I2C1BIF

#define	EE_I2C_PORT1A_MASTER_INT_FLAG 		IFS0bits.__I2C1ATXIF__
#define	EE_I2C_PORT1A_SLAVE_INT_FLAG 		IFS0bits.__I2C1ARXIF__
#define	EE_I2C_PORT1A_BUS_INT_FLAG 		IFS0bits.__I2C1AEIF__

#define	EE_I2C_PORT2_MASTER_INT_FLAG 		IFS1bits.I2C2MIF
#define	EE_I2C_PORT2_SLAVE_INT_FLAG 		IFS1bits.I2C2SIF
#define	EE_I2C_PORT2_BUS_INT_FLAG 		IFS1bits.I2C2BIF 

#define	EE_I2C_PORT2A_MASTER_INT_FLAG 		IFS1bits.__I2C2ATXIF__
#define	EE_I2C_PORT2A_SLAVE_INT_FLAG 		IFS1bits.__I2C2ARXIF__
#define	EE_I2C_PORT2A_BUS_INT_FLAG 		IFS1bits.__I2C2AEIF__

#define	EE_I2C_PORT3A_MASTER_INT_FLAG 		IFS1bits.__I2C3ATXIF__
#define	EE_I2C_PORT3A_SLAVE_INT_FLAG 		IFS1bits.__I2C3ARXIF__
#define	EE_I2C_PORT3A_BUS_INT_FLAG 		IFS1bits.__I2C3AEIF__


#else //not defined __32MX795F512L__


/* 	Interrupt Enable registers	*/

#define	EE_I2C_PORT1_MASTER_INT_ENABLE 		IEC0bits.I2C1MIE
#define	EE_I2C_PORT1_SLAVE_INT_ENABLE 		IEC0bits.I2C1SIE
#define	EE_I2C_PORT1_BUS_INT_ENABLE 		IEC0bits.I2C1BIE

#define	EE_I2C_PORT2_MASTER_INT_ENABLE 		IEC1bits.I2C2MIE
#define	EE_I2C_PORT2_SLAVE_INT_ENABLE 		IEC1bits.I2C2SIE
#define	EE_I2C_PORT2_BUS_INT_ENABLE 		IEC1bits.I2C2BIE



/* 	Interrupt Flag bits	*/

#define	EE_I2C_PORT1_MASTER_INT_FLAG 		IFS0bits.I2C1MIF
#define	EE_I2C_PORT1_SLAVE_INT_FLAG 		IFS0bits.I2C1SIF
#define	EE_I2C_PORT1_BUS_INT_FLAG 		IFS0bits.I2C1BIF

#define	EE_I2C_PORT2_MASTER_INT_FLAG 		IFS1bits.I2C2MIF
#define	EE_I2C_PORT2_SLAVE_INT_FLAG 		IFS1bits.I2C2SIF
#define	EE_I2C_PORT2_BUS_INT_FLAG 		IFS1bits.I2C2BIF 


#endif


#define ACTIVE_WAIT_ON(eval) 	\
			do {	\
				cto = 0;	\
				while(eval){		\
					if(++cto == CONNECTION_TIMEOUT)	\
					return -EE_I2C_FAILURE; \
					}	\
			} while(0)	


#ifdef __32MX795F512L__
__INLINE__ EE_INT8 i2c_port1_idle(void){
	return I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
				I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port1A_idle(void){
	return I2C1ACONbits.SEN || I2C1ACONbits.PEN || I2C1ACONbits.RCEN || 
				I2C1ACONbits.ACKEN || I2C1ASTATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2_idle(void){
	return I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
				I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2A_idle(void){
	return I2C2ACONbits.SEN || I2C2ACONbits.PEN || I2C2ACONbits.RCEN || 
				I2C2ACONbits.ACKEN || I2C2ASTATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port3A_idle(void){
	return I2C3ACONbits.SEN || I2C3ACONbits.PEN || I2C3ACONbits.RCEN || 
				I2C3ACONbits.ACKEN || I2C3ASTATbits.TRSTAT;
}

#else //not defined __32MX795F512L__

__INLINE__ EE_INT8 i2c_port1_idle(void){
	return I2C1CONbits.SEN || I2C1CONbits.PEN || I2C1CONbits.RCEN || 
				I2C1CONbits.ACKEN || I2C1STATbits.TRSTAT;
}

__INLINE__ EE_INT8 i2c_port2_idle(void){
	return I2C2CONbits.SEN || I2C2CONbits.PEN || I2C2CONbits.RCEN || 
				I2C2CONbits.ACKEN || I2C2STATbits.TRSTAT;
}

#endif



EE_INT8 EE_i2c_init(EE_UINT8 port, EE_UINT32 baudrate, EE_UINT16 flags);

EE_INT8 EE_i2c_idle(EE_UINT8 port);

EE_INT8 EE_i2c_read_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
							EE_UINT8 *data);

EE_INT8 EE_i2c_write_byte(EE_UINT8 port, EE_UINT8 device, EE_UINT8 address, 
			EE_UINT8 data);

#endif //__EE_I2C_H__
