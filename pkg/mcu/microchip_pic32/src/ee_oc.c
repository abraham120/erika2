#include "mcu/microchip_pic32/inc/ee_oc.h"
#include "mcu/microchip_pic32/inc/ee_timer.h"
#include "cpu/pic32/inc/ee_utils.h"
/* Include a file with the registers from Microchip C32 distribution */
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif



static EE_UINT32 oc_get_peripheral_clock(void) {
	return EE_get_peripheral_clock();
}	


#ifdef __USE_EE_OC_1__
__INLINE__ void __ALWAYS_INLINE__ oc1_init(void)
{
	TRISDbits.TRISD0 = 0;
	IEC0bits.OC1IE = 0;
	IFS0bits.OC1IF = 0;						
	OC1CON = 0x00;			
}


__INLINE__ EE_INT8 __ALWAYS_INLINE__ oc1_setup(EE_UINT16 configuration, 
				    	    EE_UINT16 period, EE_UINT8 prescale)
{
	OC1CON = (EE_UREG)configuration;
	T2CONbits.T32 = 0;

	if(configuration && EE_OC_TIMER_3){
		
		if(configuration & EE_OC_TIMER_32_BITS)
			return -EE_OC_ERR_BAD_TIMER_CONF;
		
		if(EE_timer_hard_init(EE_TIMER_3, period, prescale) != 
		   				EE_TIMER_NO_ERRORS)		
			return -EE_OC_ERR_TIMER_INIT;
					
		return EE_TIMER_NO_ERRORS;
	}else{
		if(configuration && EE_OC_TIMER_32_BITS)
			return -EE_OC_ERR_UNIMPLEMENTED; 
		return -EE_OC_ERR_UNIMPLEMENTED;
	}			
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ oc1_advanced_setup(EE_UINT32 dreg, 
						EE_UINT32 sdreg, EE_UINT8 mode)
{
	//TODO: gestire il parametro mode.
	OC1R  = (EE_UREG)dreg;	
	OC1RS = (EE_UREG)sdreg;
	
	return EE_OC_NO_ERRORS;		
}

__INLINE__ void __ALWAYS_INLINE__ oc1_start(void)
{
	EE_timer_start(EE_TIMER_3);	
	OC1CONbits.ON = 1;	
}

__INLINE__ void __ALWAYS_INLINE__ oc1_stop(void)
{
	OC1CONbits.ON = 0;
	EE_timer_stop(EE_TIMER_3);	
		
}
#endif 



#ifdef __USE_EE_OC_4__
__INLINE__ void __ALWAYS_INLINE__ oc4_init(void)
{
	
	TRISDbits.TRISD3 = 0;
	IEC0bits.OC4IE = 0;
	IFS0bits.OC4IF = 0;						
	OC4CON = 0x00;			
}


__INLINE__ EE_INT8 __ALWAYS_INLINE__ oc4_setup(EE_UINT16 configuration, 
				    	    EE_UINT16 period, EE_UINT8 prescale)
{
	OC4CON = (EE_UREG)configuration;
	T2CONbits.T32 = 0;

	if(configuration && EE_OC_TIMER_3){
		
		if(configuration & EE_OC_TIMER_32_BITS)
			return -EE_OC_ERR_BAD_TIMER_CONF;
		
		if(EE_timer_hard_init(EE_TIMER_3, period, prescale) != 
		   				EE_TIMER_NO_ERRORS)		
			return -EE_OC_ERR_TIMER_INIT;
					
		return EE_TIMER_NO_ERRORS;
	}else{
		if(configuration && EE_OC_TIMER_32_BITS)
			return -EE_OC_ERR_UNIMPLEMENTED; 
		return -EE_OC_ERR_UNIMPLEMENTED;
	}			
}

__INLINE__ EE_INT8 __ALWAYS_INLINE__ oc4_advanced_setup(EE_UINT32 dreg, 
						EE_UINT32 sdreg, EE_UINT8 mode)
{
	//TODO: gestire il parametro mode.
	OC4R  = (EE_UREG)dreg;	
	OC4RS = (EE_UREG)sdreg;
	
	return EE_OC_NO_ERRORS;		
}

__INLINE__ void __ALWAYS_INLINE__ oc4_start(void)
{
	EE_timer_start(EE_TIMER_3);	
	OC4CONbits.ON = 1;	
}

__INLINE__ void __ALWAYS_INLINE__ oc4_stop(void)
{
	OC4CONbits.ON = 0;
	EE_timer_stop(EE_TIMER_3);	
		
}
#endif 



EE_INT8 EE_oc_init(EE_UINT8 id)
{
	
	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		oc1_init();
		break;
	#endif // __USE_EE_OC_1__
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		
		oc4_init();	
		break;
	#endif // __USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}	
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_oc_setup(EE_UINT8 id, EE_UINT16 configuration, EE_UINT16 period, 
							      EE_UINT8 prescale)
{


	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		return oc1_setup(configuration, period, prescale);
		break;
	#endif //__USE_EE_OC_1__
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		return oc4_setup(configuration, period, prescale);	
		break;
	#endif //__USE_EE_OC_4__
	
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
}

EE_INT8 EE_oc_set_callback(EE_UINT8 id, void (*f)(void))
{
	return -EE_OC_ERR_UNIMPLEMENTED;
}

EE_INT8 EE_oc_advanced_setup(EE_UINT8 id, EE_UINT32 dreg, EE_UINT32 sdreg, 
								EE_UINT8 mode)
{

	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		return oc1_advanced_setup(dreg, sdreg, mode);
		break;
	#endif //__USE_EE_OC_1__	
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		return oc4_advanced_setup(dreg, sdreg, mode);	
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
}

EE_INT8 EE_oc_start(EE_UINT8 id)
{	


	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		oc1_start();
		break;
	#endif
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		oc4_start();	
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_oc_stop(EE_UINT8 id)
{

	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		oc1_stop();
		break;
	#endif //__USE_EE_OC_1__
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		oc4_stop();	
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
	return EE_TIMER_NO_ERRORS;
}

#ifdef __32MX795F512L__

EE_INT8 EE_oc_generate_clock_init(EE_UINT8 id, EE_UINT32 frequency)
{
	
	EE_UINT32 period = (oc_get_peripheral_clock() / frequency) - 1; 
	EE_UINT32 duty_cycle = period >> 1;
	
	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1:
		oc1_init();
		oc1_setup(EE_OC_PWM_NO_FAULT | EE_OC_TIMER_3, period, 
							EE_TIMERx_PRESCALE_1);
		oc1_advanced_setup(duty_cycle, duty_cycle, EE_OC_NO_ADVANCED_SET);
	 
		break;
	#endif //__USE_EE_OC_1__
	case EE_OC_2:
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	
	case EE_OC_3:
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4:
		oc4_init();
		oc4_setup(EE_OC_PWM_NO_FAULT | EE_OC_TIMER_3, period, 
							EE_TIMERx_PRESCALE_1);
		oc4_advanced_setup( duty_cycle, duty_cycle, EE_OC_NO_ADVANCED_SET);
					
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5:
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
	return EE_TIMER_NO_ERRORS;
}

#endif




#ifdef __32MX360F512L__

EE_INT8 EE_oc_generate_clock_init(EE_UINT8 id, EE_UINT32 frequency)
{
	
	EE_UINT32 period = (oc_get_peripheral_clock() / (2 * frequency)) - 1; 
	
	if (period == 0)
		return - EE_OC_ERR_TIMER_INIT;

	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		oc1_init();
		oc1_setup(EE_OC_CONFIGURE_TOGGLE | EE_OC_TIMER_3, period, 
							EE_TIMERx_PRESCALE_1);
		oc1_advanced_setup(0, 0, EE_OC_NO_ADVANCED_SET);
		break;
	#endif //__USE_EE_OC_1__
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		oc4_init();
		oc4_setup(EE_OC_CONFIGURE_TOGGLE | EE_OC_TIMER_3, period, 
							EE_TIMERx_PRESCALE_1);
		oc4_advanced_setup( 0, 0, EE_OC_NO_ADVANCED_SET); 	
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
	return EE_TIMER_NO_ERRORS;
}

#endif 



EE_INT8 EE_oc_generate_clock_start(EE_UINT8 id)
{

	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		oc1_start();
		break;
	#endif //__USE_EE_OC_1__
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		oc4_start(); 
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
	return EE_TIMER_NO_ERRORS;
}


EE_INT8 EE_oc_generate_clock_stop(EE_UINT8 id)
{

	switch (id) {
	#ifdef __USE_EE_OC_1__
	case EE_OC_1 :
		oc1_stop();
		break;
	#endif //__USE_EE_OC_1__
	case EE_OC_2 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	
	case EE_OC_3 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;
	#ifdef __USE_EE_OC_4__
	case EE_OC_4 :
		oc4_stop(); 	
		break;
	#endif //__USE_EE_OC_4__
	case EE_OC_5 :
		return -EE_OC_ERR_UNIMPLEMENTED;	
		break;

	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
		break;
	}
	return EE_TIMER_NO_ERRORS;
}


