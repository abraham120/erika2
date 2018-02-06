/** 
* @file tsl2561t.h
* @brief TSL2561T Light Sensor Driver
* @author Marco Ghibaudi 
* @date 2010-04-26
*
*/

#include "tsl2561t.h"
#include "tsl2561t_hal_ee_pic32.h"

void tsl2561t_write_register(EE_UINT8 device_address, EE_UINT8 reg , 
		EE_UINT8 value) {

	EE_i2c_write_byte(TSL2561T_I2C_PORT, device_address, 
			 reg, value);	
}

void tsl2561t_read_register(EE_UINT8 device_address, EE_UINT8 reg , 
		EE_UINT8 * value) {

	EE_i2c_read_byte(TSL2561T_I2C_PORT, device_address, 
			 reg, value);	
}


EE_UINT8 tsl2561t_hal_i2c_init(void) {

	if (EE_i2c_init(TSL2561T_I2C_PORT, TSL2561T_I2C_CLK,
				 TSL2561T_I2C_FLAGS) > 0 ) 

		return TSL2516T_NO_ERROR;
	
	return -TSL2516T_I2C_INIT_ERROR;
}
