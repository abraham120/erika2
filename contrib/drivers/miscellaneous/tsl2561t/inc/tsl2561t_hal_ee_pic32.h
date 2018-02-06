#ifndef __TSL2561T_HAL_EE_PIC32_H__
#define __TSL2561T_HAL_EE_PIC32_H__


#ifndef __USE_I2C__
#error "TSL2561T HAL EE : The I2C module from MCU is required!"
#endif

#include <mcu/microchip_pic32/inc/ee_i2c.h>


#define TSL2561T_I2C_PORT_1	EE_I2C_PORT_1
#define TSL2561T_I2C_PORT_2	EE_I2C_PORT_2

#ifdef __IPERMOB_DB_PIC32__ 
/* Specific pin-out used by IPERMOB_DB_PIC32 */

#ifndef TSL2561T_INT_PIN
#define TSL2561T_INT_PIN	PORTEbits.RE9	
#endif

#ifndef TSL2561T_TRIS_INT_PIN
#define TSL2561T_TRIS_INT_PIN	TRISEbits.TRISE9
#endif

#ifndef TSL2561T_ADD_PIN
#define TSL2561T_ADD_PIN	PORTFbits.RF1	
#endif

#ifndef TSL2561T_TRIS_ADD_PIN
#define TSL2561T_TRIS_ADD_PIN	TRISFbits.TRISF1
#endif

#ifndef TSL2561T_I2C_PORT
#define TSL2561T_I2C_PORT	TSL2561T_I2C_PORT_2
#endif

#ifndef TSL2561T_I2C_CLK
#define TSL2561T_I2C_CLK	400		//KHz
#endif

#ifndef TSL2561T_I2C_FLAGS
#define TSL2561T_I2C_FLAGS	0x0		//No special settings.
#endif


#else //__IPERMOB_DB_PIC32__

#error "BOARD NOT SUPPORTED"

#endif // __IPERMOB_DB_PIC32__


/******************************************************************************/
/*				Inlinde Functions 			      */
/******************************************************************************/

COMPILER_INLINE EE_UINT32 tsl2561t_swap_32(EE_UINT32 le_val){
	return le_val;
}

COMPILER_INLINE EE_UINT16 tsl2561t_swap_16(EE_UINT16 le_val){
	return le_val;
}

COMPILER_INLINE void tsl2561t_hal_set_ADDRESS_gnd(void){
	TSL2561T_TRIS_ADD_PIN = 0;	// pin connected to ADD as output.
	TSL2561T_ADD_PIN = 0;	// pin connected to ADD set to Ground 
}

COMPILER_INLINE void tsl2561t_hal_set_ADDRESS_vdd(void){
	TSL2561T_TRIS_ADD_PIN = 0;	// pin connected to ADD as output.
	TSL2561T_ADD_PIN = 1;	// pin connected to ADD set to VDD 
}

COMPILER_INLINE void tsl2561t_hal_set_ADDRESS_float(void){
	TSL2561T_TRIS_ADD_PIN = 1;	// pin connected to ADD as input. 
}

__INLINE__ void tsl2561t_hal_set_INT_pin(void){
	TSL2561T_TRIS_INT_PIN = 1;	// pin connected to INT as input.
}


/******************************************************************************/
/*				Function Prototipes			      */
/******************************************************************************/


EE_UINT8 tsl2561t_hal_i2c_init(void);


void tsl2561t_write_register(uint8_t device_address, uint8_t reg , 
		uint8_t value);


void tsl2561t_read_register(uint8_t device_address, uint8_t reg , 
		uint8_t * value); 
		
COMPILER_INLINE void tsl2561t_read_buffer(uint8_t device_address, uint8_t reg , 
		uint8_t *data, int len) {
	
	int i;

	for(i=0; i<len; i++)
	{
		tsl2561t_read_register(device_address, reg+i, data+i);
	}
}

COMPILER_INLINE void tsl2561t_write_buffer(EE_UINT8 device_address, EE_UINT8 reg , 
		EE_UINT8 *data, int len) {
		
	int i;

	for(i=0; i<len; i++)
	{
		tsl2561t_write_register(device_address, reg+i, *(data+i));
	}
}		

#endif //__TSL2561T_HAL_EE_PIC32_H__

