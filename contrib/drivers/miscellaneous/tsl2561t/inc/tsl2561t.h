/** 
* @file tsl2561t.h
* @brief TSL2561T Light Sensor Driver
* @author Matteo Petracca
* @author Marco Ghibaudi 
* @date 2010-04-22
*
* This file is the definition of the hardware abstraction layer used by the 
* tsl2561t light sensor 
*
* \todo Write something about the supported compilers.
*/

#ifndef __TSL2561T_H__
#define __TSL2561T_H__

#include "tsl2561t_compiler.h"
#include "tsl2561t_hal.h"


/******************************************************************************/
/*				Registers Definition 			      */
/******************************************************************************/

/*	Slave device addresses		*/
#define DEVICE_ADDRESS_GND 0x52 
#define DEVICE_ADDRESS_FLOAT 0x72 
#define DEVICE_ADDRESS_VDD 0x92 


/*	Addressing-mode			*/
#define SELECT_ADDRESS_GND 0
#define SELECT_ADDRESS_VDD 1
#define SELECT_ADDRESS_FLOAT 2

/* Driver Macros */
#define TLS2561_READ_WORD       (2)
#define TLS2561_WRITE_WORD      (2)
#define TLS2561_COMMAND_BIT     (0x80)
#define TLS2561_WORD_PROT       (0x20)
#define TLS2561_WORD_COMMAND(x) (TLS2561_COMMAND_BIT | TLS2561_WORD_PROT | (x))

/*	Register adresses		*/
#define CONTROL_REGISTER 0X00
#define TIMING_REGISTER 0X01
#define THRES_LOW_LOW_REGISTER 0X02
#define THRES_LOW_HIGH_REGISTER 0X03
#define THRES_HIGH_LOW_REGISTER 0X04
#define THRES_HIGH_HIGH_REGISTER 0X05
#define INTERRUPT_REGISTER 0X06
#define ID_REGISTER 0X0A
#define DATA_0_LOW_REGISTER 0X0C
#define DATA_0_HIGH_REGISTER 0X0D
#define DATA_1_LOW_REGISTER 0X0E
#define DATA_1_HIGH_REGISTER 0X0F

/*	Register options		*/

/*	CONTROL REGISTER		*/
#define POWER_ON  0x03
#define POWER_OFF  0x00

/*	TIMING REGISTER	*/
#define LOW_GAIN_INT_13MS  0x00
#define LOW_GAIN_INT_101MS 0x01 
#define LOW_GAIN_INT_402MS 0x02
#define HIGH_GAIN_INT_13MS  0x10
#define HIGH_GAIN_INT_101MS 0x11 
#define HIGH_GAIN_INT_402MS 0x12

/*	INTERRUPT CONTROL REGISTER	*/
#define DISABLE_INTERRUPT 0x00
#define INTERRUPT_EVERYADCCYCLE      0x10
#define INTERRUPT_ANYVALUEOUTOFRANGE 0x11 
#define INTERRUPT_2OUTOFRANGE        0x12
#define INTERRUPT_3OUTOFRANGE        0x13
#define INTERRUPT_4OUTOFRANGE        0x14
#define INTERRUPT_5OUTOFRANGE        0x15
#define INTERRUPT_6OUTOFRANGE        0x16
#define INTERRUPT_7OUTOFRANGE        0x17
#define INTERRUPT_8OUTOFRANGE        0x18
#define INTERRUPT_9OUTOFRANGE        0x19
#define INTERRUPT_10OUTOFRANGE       0x1A
#define INTERRUPT_11OUTOFRANGE       0x1B
#define INTERRUPT_12OUTOFRANGE       0x1C
#define INTERRUPT_13OUTOFRANGE       0x1D
#define INTERRUPT_14OUTOFRANGE       0x1E
#define INTERRUPT_15OUTOFRANGE       0x1F

/*	Commands			*/
#define COMMAND_CONTROL_REGISTER        0x80
#define COMMAND_TIMING_REGISTER         0x81
#define COMMAND_THRESHLOWLOW_REGISTER   0x82
#define COMMAND_THRESHLOWHIGH_REGISTER  0x83
#define COMMAND_THRESHHIGHLOW_REGISTER  0x84
#define COMMAND_THRESHHIGHHIGH_REGISTER 0x85
#define COMMAND_INTERRUPT_REGISTER      0x86
#define COMMAND_ID_REGISTER      	0x8A
#define COMMAND_DATA0LOW_REGISTER      	0x8C
#define COMMAND_DATA0HIGH_REGISTER      0x8D
#define COMMAND_DATA1LOW_REGISTER      	0x8E
#define COMMAND_DATA1HIGH_REGISTER     	0x8F


/*	Operation Status		*/
#define TSL2516T_NO_ERROR		1	//returned as positive
#define TSL2516T_I2C_INIT_ERROR		1
#define TSL2516T_POWER_ON_ERROR		2
#define TSL2516T_CONFIG_ERROR		3

/*	Configurable Properties		*/
#define TSL2561T_TIMING			0
#define TSL2561T_INTERRUPT_MODE		1



/******************************************************************************/
/* 			LUX conversion constants			      */
/******************************************************************************/

#define LUX_SCALE    14     // scale by 2^14
#define RATIO_SCALE 9       // scale ratio by 2^9
//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
// Integration time scaling factors
//−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−−
#define CH_SCALE            10     // scale channel values by 2^10
#define CHSCALE_TINT0       0x7517 // 322/11 * 2^CH_SCALE
#define CHSCALE_TINT1       0x0fe7 // 322/81 * 2^CH_SCALE


#define K1T 	0x0040          // 0.125 * 2^RATIO_SCALE
#define B1T 	0x01f2          // 0.0304 * 2^LUX_SCALE
#define M1T 	0x01be          // 0.0272 * 2^LUX_SCALE
#define K2T  	0x0080        // 0.250 * 2^RATIO_SCALE


#define B2T   	0x0214        // 0.0325 * 2^LUX_SCALE
#define M2T   	0x02d1        // 0.0440 * 2^LUX_SCALE
#define K3T   	0x00c0        // 0.375 * 2^RATIO_SCALE
#define B3T   	0x023f        // 0.0351 * 2^LUX_SCALE
#define M3T   	0x037b        // 0.0544 * 2^LUX_SCALE
#define K4T   	0x0100        // 0.50 * 2^RATIO_SCALE
#define B4T  	0x0270        // 0.0381 * 2^LUX_SCALE
#define M4T  	0x03fe        // 0.0624 * 2^LUX_SCALE
#define K5T   	0x0138        // 0.61 * 2^RATIO_SCALE
#define B5T   	0x016f        // 0.0224 * 2^LUX_SCALE
#define M5T   	0x01fc        // 0.0310 * 2^LUX_SCALE
#define K6T  	0x019a        // 0.80 * 2^RATIO_SCALE
#define B6T   	0x00d2        // 0.0128 * 2^LUX_SCALE
#define M6T   	0x00fb        // 0.0153 * 2^LUX_SCALE
#define K7T  	0x029a        // 1.3 * 2^RATIO_SCALE
#define B7T   	0x0018        // 0.00146 * 2^LUX_SCALE
#define M7T   	0x0012        // 0.00112 * 2^LUX_SCALE
#define K8T   	0x029a        // 1.3 * 2^RATIO_SCALE
#define B8T   	0x0000        // 0.000 * 2^LUX_SCALE
#define M8T   	0x0000        // 0.000 * 2^LUX_SCALE




/******************************************************************************/
/*				 Inline Functions 			      */
/******************************************************************************/





/******************************************************************************/
/*				 Prototipes	 			      */
/******************************************************************************/

/** 
* @brief Initialize the module 
* 	
* This function initializes the tsl2561t light sensor.
* 
* @ param[in] selection one of the three available address the device can have	 
* @ return  \ref returns the assigned Address, 
*	otherwise TSL2516T_I2C_INIT_ERROR as a negative number
*/



uint8_t tsl2561t_init(uint8_t selection);
__INLINE__ uint8_t __ALWAYS_INLINE__  EE_lightsensor_init(void)
{
    return tsl2561t_init(SELECT_ADDRESS_VDD);
}

/** 
* @brief  Turn on the module 
* 	
* This function activates the tsl2561t light sensor.
* 
* @ param[in] address_in_use the address of the device 	 
* @ return  \ref returns TSL2516T_NO_ERROR if the initializzation succeed, 
*	otherwise TSL2516T_POWER_ON_ERROR
*/


uint8_t tsl2561t_power_on(uint8_t address_in_use);
__INLINE__ uint8_t __ALWAYS_INLINE__  EE_lightsensor_power_on(void)
{
    return tsl2561t_power_on(DEVICE_ADDRESS_VDD);
}

/** 
* @brief  Turn off the module 
* 	
* This function deactivates the tsl2561t light sensor.
*
* @ param[in] address_in_use the address of the device   	 
*/

void tsl2561t_power_off(uint8_t address_in_use);
__INLINE__ void __ALWAYS_INLINE__  EE_lightsensor_power_off(void)
{
    tsl2561t_power_off(DEVICE_ADDRESS_VDD);
}

/** 
* @brief  Read the lux value 
* 	
* This function reads the lux value calculated by the tsl2561t light sensor.
* 
* @ param[in] address_in_use the address of the device 
* @ param[in/out] value the lux value 
*/

void tsl2561t_read_lux(uint8_t address_in_use, uint32_t *value_low);
__INLINE__ void __ALWAYS_INLINE__  EE_lightsensor_read_lux(uint32_t *value_low)
{
    tsl2561t_read_lux(DEVICE_ADDRESS_VDD, value_low);
}

/** 
* @brief  Configure the parameters of the device 
* 	
* This function configure the tsl2561t light sensor parameters.
* 
* @ param[in] address_in_use the address of the device 
* @ param[in] parameter the parameter to be set 
* @ param[in] value the value to be set 
* @ return  \ref returns TSL2516T_NO_ERROR if the setting succeed, 
*	otherwise TSL2516T_CONFIG_ERROR

*/

uint8_t tsl2561t_set_configuration(uint8_t address, uint8_t parameter, 
						uint8_t value);
__INLINE__ uint8_t __ALWAYS_INLINE__  EE_lightsensor_set_configuration(uint8_t parameter, 
																		uint8_t value)
{
    return tsl2561t_set_configuration(DEVICE_ADDRESS_VDD, parameter, value);
}


/** 
* @brief  Get the configuration parameters of the device 
* 	
* This function gets the tsl2561t light sensor configuration parameters.
* 
* @ param[in] address_in_use the address of the device 
* @ param[in] parameter the parameter to be set 
* @ param[in] value the value got
* @ return  \ref returns TSL2516T_NO_ERROR if the setting succeed, 
*	otherwise TSL2516T_CONFIG_ERROR

*/

uint8_t tsl2561t_get_configuration(uint8_t address, uint8_t parameter, 
						uint8_t *value);
__INLINE__ uint8_t __ALWAYS_INLINE__  EE_lightsensor_get_configuration(uint8_t parameter, 
																		uint8_t *value)
{
    return tsl2561t_get_configuration(DEVICE_ADDRESS_VDD, parameter, value);
}



#endif // __TSL2561T_H___
