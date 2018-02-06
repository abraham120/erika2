/** 
* @file tsl2561t.c
* @brief TSL2561T Light Sensor Driver
* @author Marco Ghibaudi 
* @date 2010-04-26
*/

#include "tsl2561t.h"
#include "tsl2561t_hal.h"


static uint8_t integration_time = 0;

EE_UINT8 tsl2561t_power_on(EE_UINT8 address_in_use) {
	EE_UINT8 Status;

	//TODO: address_in_use non è ancora definito a dovere
	
	tsl2561t_write_register(address_in_use, COMMAND_CONTROL_REGISTER, 
					POWER_ON);

	tsl2561t_read_register(address_in_use, COMMAND_CONTROL_REGISTER, 
					&Status);
	
	/* Check the correct starting of the device */

	if ((Status & 0x3) == POWER_ON)
		return TSL2516T_NO_ERROR; 

	return -TSL2516T_POWER_ON_ERROR; 	
}


void ptsl2561t_power_off(uint8_t address_in_use)
{
	tsl2561t_write_register(address_in_use, 
			  COMMAND_CONTROL_REGISTER, POWER_OFF);
}



uint8_t tsl2561t_init(uint8_t selection) {

	if(tsl2561t_hal_i2c_init() != TSL2516T_NO_ERROR)
		return -TSL2516T_I2C_INIT_ERROR;

	tsl2561t_hal_set_INT_pin();

	switch (selection){
		case SELECT_ADDRESS_GND:
			tsl2561t_hal_set_ADDRESS_gnd();	
			return DEVICE_ADDRESS_GND;
		break;
		case SELECT_ADDRESS_VDD:
			tsl2561t_hal_set_ADDRESS_vdd();
			return DEVICE_ADDRESS_VDD;
			
		break;
		default:
			tsl2561t_hal_set_ADDRESS_float();
			return DEVICE_ADDRESS_FLOAT;
	}	
}

uint8_t tsl2561t_set_configuration(uint8_t address, uint8_t parameter, uint8_t value){

	switch (parameter) {

	case TSL2561T_TIMING:
	/* Define the Integration Timing used by the sensor */
		tsl2561t_write_register(address, COMMAND_TIMING_REGISTER, value);

		if ((value & 0x3) == 0)  
			integration_time = 0;

		else if ((value & 0x3) == 1) 
	
			integration_time = 1;
		else 
			integration_time = 2;

		return TSL2516T_NO_ERROR;
	break;
	
	case TSL2561T_INTERRUPT_MODE:
	//TODO: Implement the interrupt register set-up
		return -TSL2516T_CONFIG_ERROR;
	break;

	default:
	return -TSL2516T_CONFIG_ERROR;
	
	}
}




uint8_t tsl2561t_get_configuration(uint8_t address, uint8_t parameter, uint8_t *value){

	switch (parameter) {

	case TSL2561T_TIMING:
	/* Define the Integration Timing used by the sensor */
		*value = integration_time;
		return TSL2516T_NO_ERROR;
	break;
	
	case TSL2561T_INTERRUPT_MODE:
	//TODO: Implement the interrupt register set-up
		return -TSL2516T_CONFIG_ERROR;
	break;

	default:
	return -TSL2516T_CONFIG_ERROR;
	
	}
}


void tsl2561t_read_lux(uint8_t address_in_use, uint32_t *lux){

	uint32_t channel1;
	uint32_t channel0;
	uint16_t ch0;
	uint16_t ch1;
	uint32_t chScale;

	tsl2561t_read_buffer(address_in_use, TLS2561_WORD_COMMAND(DATA_0_LOW_REGISTER), (EE_UINT8 *)&ch0 , TLS2561_READ_WORD);	
	channel0 = tsl2561t_swap_16(ch0);
	tsl2561t_read_buffer(address_in_use, TLS2561_WORD_COMMAND(DATA_1_LOW_REGISTER) , (EE_UINT8 *)&ch1 , TLS2561_READ_WORD);
	channel1 = tsl2561t_swap_16(ch1);
	
	/* Calculation of the lux value */
	
	uint8_t integration_time;

	tsl2561t_get_configuration(address_in_use, TSL2561T_TIMING, 
				&integration_time);	
	
	switch (integration_time)
	{
		case 0:    // 13.7 msec
			chScale = CHSCALE_TINT0;	
			break;
		case 1:    // 101 msec
			chScale = CHSCALE_TINT1;	
			break;
		default:   // assume no scaling
			chScale = (1 << CH_SCALE);
			break;
	}
	
	channel0 = (channel0* chScale) >> CH_SCALE;
	channel1 = (channel1* chScale) >> CH_SCALE;

	EE_UINT32 ratio1 = 0;
	if (channel0 != 0) 
		ratio1 = (channel1 << (RATIO_SCALE+1)) / channel0;
	EE_UINT32 ratio = (ratio1 + 1) >> 1;
	
	// is ratio <= eachBreak ?
	EE_UINT32 b, m;
	if ((ratio >= 0) && (ratio <= K1T)){
		b=B1T; 
		m=M1T;
	}
	else if (ratio <= K2T){
		b=B2T; 
		m=M2T;
	}
        else if (ratio <= K3T){
		b=B3T; 
		m=M3T;
	}
	else if (ratio <= K4T){
		b=B4T; 
		m=M4T;
	}
	else if (ratio <= K5T){
		b=B5T; 
		m=M5T;
	}
	else if (ratio <= K6T){
		b=B6T; 
		m=M6T;
	}
	else if (ratio <= K7T){
		b=B7T; 
		m=M7T;
	}
	else if (ratio > K8T){
		b=B8T; 
		m=M8T;
	}

   
	EE_UINT32 temp;
	temp = ((channel0 * b) - (channel1 * m));
	
	// do not allow negative lux value
	if (temp < 0) 
		temp = 0;
	/* round lsb (2^(LUX_SCALE−1)) */

	temp += (1 << (LUX_SCALE - 1));

	// strip off fractional portion
	*lux =  temp >> LUX_SCALE;
	
}




