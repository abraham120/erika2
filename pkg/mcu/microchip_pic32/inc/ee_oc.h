#ifndef __INCLUDE_MICROCHIP_PIC32_OUTPUT_COMPARE_H__
#define __INCLUDE_MICROCHIP_PIC32_OUTPUT_COMPARE_H__

#include "ee.h"

/******************************************************************************/
/* 				Returned Messages			      */
/******************************************************************************/

#define EE_OC_NO_ERRORS			1	//Used positive
#define EE_OC_ERR_BAD_TIMER_CONF	1
#define EE_OC_ERR_TIMER_INIT		2
#define EE_OC_ERR_UNIMPLEMENTED		10


/******************************************************************************/
/* 				Configuration Labels			      */
/******************************************************************************/

#define EE_OC_CONFIGURE_PULSE	0x5
#define EE_OC_CONFIGURE_TOGGLE	0x3
#define EE_OC_PWM_NO_FAULT	0x6

#define EE_OC_TIMER_2		0x0
#define EE_OC_TIMER_3		0x8

#define EE_OC_NO_ADVANCED_SET	0x0

#define EE_OC_TIMER_32_BITS	0x20
#define EE_OC_TIMER_16_BITS	0x00
#define EE_OC_INTERRUPT_MODE	0x1


/******************************************************************************/
/* 				Ports Definition			      */
/******************************************************************************/

enum {
	EE_OC_1	= 1,
	EE_OC_2,
	EE_OC_3,
	EE_OC_4,
	EE_OC_5,
};


/******************************************************************************/
/* 				Prototypes Definition			      */
/******************************************************************************/


/**
* @brief Initialize the Output Compare peripheral.
*
* This function initializes the Output Compare peripheral defined by 
* the input parameter \p port.

* @param[in] port 	
* @return 	\todo
*
* @pre		None
*/

EE_INT8 EE_oc_init(EE_UINT8 id);


/**
* @brief Setup the Output Compare peripheral.
*
* This function sets up the Output Compare peripheral defined by 
* the input parameter \p port. 

* @param[in] port		the OC port to be used
* @param[in] configuration	the configuration parameters
* @param[in] period 		the period of the timer exploited
* @param[in] prescale  		the prescale of the timer exploited
* @return 	\todo
*
* @pre		None
*/

EE_INT8 EE_oc_setup(EE_UINT8 id, EE_UINT16 configuration, EE_UINT16 period, 
							EE_UINT8 prescale);



/**
* @brief Set the callback for the OC peripheral
*
* This function sets up a callback function for Output Compare peripheral 
 
* @param[in] port		the OC port to be used
* @param[in] *f(void)		the callback's pointer
* @return 	\todo
*
* @pre		None
*/

EE_INT8 EE_oc_set_callback(EE_UINT8 id, void (*f)(void)); 



/**
* @brief Sets the advanced feature of the OC peripheral
*
* This function sets the advanced feature of the Output Compare peripheral 
 
* @param[in] port		the OC port to be used
* @param[in] dreg		the compare register
* @param[in] sdreg		the secondary compare register
* @param[in] mode		particular modality of function
* @return 	\todo
*
* @pre		None
*/

EE_INT8 EE_oc_advanced_setup(EE_UINT8 id, EE_UINT32 dreg, EE_UINT32 sdreg, 
							EE_UINT8 mode);



/**
* @brief Starts the OC peripheral
*
* This function starts the Output Compare peripheral 
 
* @param[in] port		the OC port to be used
* @return 	\todo
*
* @pre		None
*/

EE_INT8 EE_oc_start(EE_UINT8 id);




/**
* @brief Stops the OC peripheral
*
* This function stops the Output Compare peripheral 
 
* @param[in] port		the OC port to be used
* @return 	\todo
*
* @pre		None
*/

EE_INT8 EE_oc_stop(EE_UINT8 id);


/******************************************************************************/
/* 			Clock generator functions			      */
/******************************************************************************/

/**
* @brief Initialize the Output Compare peripheral as a clock generator.
*
* This function initializes the Output Compare peripheral defined by 
* the input parameter \p port as a clock generator with a specific frequency.

* @param[in] port		the OC port to be used
* @param[in] frequency   	the frequency expected
* @return 	\todo
*
* @pre		frequency must be lower than the peripheral clock.
*/

EE_INT8 EE_oc_generate_clock_init(EE_UINT8 id, EE_UINT32 frequency);



/**
* @brief Starts the Output Compare peripheral as a clock generator.
*
* This function starts the Output Compare peripheral defined by 
* the input parameter \p port as a clock generator with a specific frequency.

* @param[in] port		the OC port to be used

* @return 	\todo
*
* @pre		
*/

EE_INT8 EE_oc_generate_clock_start(EE_UINT8 id);



/**
* @brief Stops the Output Compare peripheral as a clock generator.
*
* This function stops the Output Compare peripheral defined by 
* the input parameter \p port as a clock generator with a specific frequency.

* @param[in] port		the OC port to be used

* @return 	\todo
*
* @pre		
*/

EE_INT8 EE_oc_generate_clock_stop(EE_UINT8 id);


#endif /* __INCLUDE_MICROCHIP_PIC32_OUTPUT_COMPARE_H__*/
