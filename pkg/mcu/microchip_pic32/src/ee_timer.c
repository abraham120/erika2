#include "mcu/microchip_pic32/inc/ee_timer.h"
#ifdef __PIC32_INCLUDE_REGS__
#include "ee_pic32regs.h"
#endif

/******************************************************************************/
/*                             Utility Macros                                 */
/******************************************************************************/

/******************************************************************************/
/*                       Private Local Variables                              */
/******************************************************************************/
#ifdef __USE_EE_TIMER_1__
static void (* volatile timer1_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_2__
static void (* volatile timer2_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_3__
static void (* volatile timer3_callback)(void) = NULL;
#endif
#if defined(__USE_EE_TIMER_4__) || defined(__USE_EE_TIMER_45__)
static void (* volatile timer4_callback)(void) = NULL;
#endif
#ifdef __USE_EE_TIMER_5__
static void (* volatile timer5_callback)(void) = NULL;
#endif

/******************************************************************************/
/*                       Private Local Functions                              */
/******************************************************************************/
#ifdef __USE_EE_TIMER_1__
__INLINE__ void __ALWAYS_INLINE__ timer1_enable_IRQ(void)
{
	IFS0CLR = _IFS0_T1IF_MASK;	// Clean Timer IRQ Flag
	IEC0SET = _IEC0_T1IE_MASK;	// Enable Timer IRQ
}
	
__INLINE__ void __ALWAYS_INLINE__ timer1_disable_IRQ(void)
{
	IEC0CLR = _IEC0_T1IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T1IF_MASK;	// Clean Timer IRQ Flag
}

__INLINE__ void __ALWAYS_INLINE__ timer1_init(EE_UINT32 pr, EE_UINT8 tckps)
{
	timer1_disable_IRQ();
	IPC1CLR = _IPC1_T1IP_MASK;	// Clean IRQ Priority
	IPC1SET = (2 << _IPC1_T1IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC1CLR = _IPC1_T1IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	PR1 = pr;
	TMR1 = 0;
	T1CON = ((tckps) << _T1CON_TCKPS_POSITION);
}

__INLINE__ void __ALWAYS_INLINE__ timer1_start(void) 
{
#ifdef __COUNTER_TICK_ON_TIMER_1__
	timer1_enable_IRQ();
#endif
	T1CONSET = _T1CON_ON_MASK;	// Start Timer
}

__INLINE__ void __ALWAYS_INLINE__ timer1_stop(void) 
{
	T1CONCLR = _T1CON_ON_MASK;	// Stop Timer
	timer1_disable_IRQ();
}
#endif /* __USE_EE_TIMER_1__ */

#ifdef __USE_EE_TIMER_2__
__INLINE__ void __ALWAYS_INLINE__ timer2_enable_IRQ(void)
{
	IFS0CLR = _IFS0_T2IF_MASK;	// Clean Timer IRQ Flag
	IEC0SET = _IEC0_T2IE_MASK;	// Enable Timer IRQ
}
	
__INLINE__ void __ALWAYS_INLINE__ timer2_disable_IRQ(void)
{
	IEC0CLR = _IEC0_T2IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T2IF_MASK;	// Clean Timer IRQ Flag
}

__INLINE__ void __ALWAYS_INLINE__ timer2_init(EE_UINT32 pr, EE_UINT8 tckps)
{
	timer2_disable_IRQ();
	IPC2CLR = _IPC2_T2IP_MASK;	// Clean IRQ Priority
	IPC2SET = (2 << _IPC2_T2IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC2CLR = _IPC2_T2IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	PR2 = pr;
	TMR2 = 0;
	T2CON = ((tckps) << _T2CON_TCKPS_POSITION);
}

__INLINE__ void __ALWAYS_INLINE__ timer2_start(void) 
{
	T2CONSET = _T2CON_ON_MASK;	// Start Timer
}

__INLINE__ void __ALWAYS_INLINE__ timer2_stop(void) 
{
	T2CONCLR = _T2CON_ON_MASK;	// Stop Timer
	timer2_disable_IRQ();
}
#endif /* __USE_EE_TIMER_2__ */


#ifdef __USE_EE_TIMER_3__
__INLINE__ void __ALWAYS_INLINE__ timer3_enable_IRQ(void)
{
	IFS0CLR = _IFS0_T3IF_MASK;	// Clean Timer IRQ Flag
	IEC0SET = _IEC0_T3IE_MASK;	// Enable Timer IRQ
}
	
__INLINE__ void __ALWAYS_INLINE__ timer3_disable_IRQ(void)
{
	IEC0CLR = _IEC0_T3IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T3IF_MASK;	// Clean Timer IRQ Flag
}

__INLINE__ void __ALWAYS_INLINE__ timer3_init(EE_UINT32 pr, EE_UINT8 tckps)
{
	IPC3CLR = _IPC3_T3IP_MASK;	// Clean IRQ Priority
	IPC3SET = (2 << _IPC3_T3IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC3CLR = _IPC3_T3IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	PR3 = pr;
	TMR3 = 0;
	T3CON = ((tckps) << _T3CON_TCKPS_POSITION);
}

__INLINE__ void __ALWAYS_INLINE__ timer3_start(void) 
{
	T3CONSET = _T3CON_ON_MASK;	// Start Timer
}

__INLINE__ void __ALWAYS_INLINE__ timer3_stop(void) 
{
	T3CONCLR = _T3CON_ON_MASK;	// Stop Timer
	timer3_disable_IRQ();
}
#endif /* __USE_EE_TIMER_3__ */


/* FIXME Probably this check should be done in makefile instead */
#if defined(__USE_EE_TIMER_45__) && \
(defined(__USE_EE_TIMER_4__) || defined(__USE_EE_TIMER_5__))
#error TIMER 45 cannot be used together with TIMER 4 or TIMER 5
#endif



#if defined(__USE_EE_TIMER_4__) || defined(__USE_EE_TIMER_45__)
__INLINE__ void __ALWAYS_INLINE__ timer4_enable_IRQ(void)
{
	IFS0CLR = _IFS0_T4IF_MASK;	// Clean Timer IRQ Flag
	IEC0SET = _IEC0_T4IE_MASK;	// Enable Timer IRQ
}
	
__INLINE__ void __ALWAYS_INLINE__ timer4_disable_IRQ(void)
{
	IEC0CLR = _IEC0_T4IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T4IF_MASK;	// Clean Timer IRQ Flag
}

__INLINE__ void __ALWAYS_INLINE__ timer4_init(EE_UINT32 pr, EE_UINT8 tckps)
{
	IPC4CLR = _IPC4_T4IP_MASK;	// Clean IRQ Priority
	IPC4SET = (2 << _IPC4_T4IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC4CLR = _IPC4_T4IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	PR4 = pr;
	TMR4 = 0;
	T4CON = ((tckps) << _T4CON_TCKPS_POSITION);
}

__INLINE__ void __ALWAYS_INLINE__ timer4_start(void) 
{
	T4CONSET = _T4CON_ON_MASK;	// Start Timer
}

__INLINE__ void __ALWAYS_INLINE__ timer4_stop(void) 
{
	T4CONCLR = _T4CON_ON_MASK;	// Stop Timer
	timer4_disable_IRQ();
}
#endif /* __USE_EE_TIMER_4__ || __USE_EE_TIMER_45__ */


#if defined(__USE_EE_TIMER_45__)
__INLINE__ void __ALWAYS_INLINE__ timer45_init(EE_UINT32 pr, EE_UINT8 tckps)
{
	T4CON = 0;
	T5CON = 0;
	T4CONSET = _T2CON_T32_MASK | ((tckps & 0x03) << _T4CON_TCKPS_POSITION);
	IPC4CLR = _IPC4_T4IP_MASK;	// Clean IRQ Priority
	IPC4SET = (2 << _IPC4_T4IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC4CLR = _IPC4_T4IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	TMR4 = 0;
	PR4 = pr;
}
#endif /* __USE_EE_TIMER_45__ */


#ifdef __USE_EE_TIMER_5__
__INLINE__ void __ALWAYS_INLINE__ timer5_enable_IRQ(void)
{
	IFS0CLR = _IFS0_T5IF_MASK;	// Clean Timer IRQ Flag
	IEC0SET = _IEC0_T5IE_MASK;	// Enable Timer IRQ
}
	
__INLINE__ void __ALWAYS_INLINE__ timer5_disable_IRQ(void)
{
	IEC0CLR = _IEC0_T5IE_MASK;	// Disable Timer IRQ
	IFS0CLR = _IFS0_T5IF_MASK;	// Clean Timer IRQ Flag
}

__INLINE__ void __ALWAYS_INLINE__ timer5_init(EE_UINT32 pr, EE_UINT8 tckps)
{
	IPC5CLR = _IPC5_T5IP_MASK;	// Clean IRQ Priority
	IPC5SET = (2 << _IPC5_T5IP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC5CLR = _IPC5_T5IS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	PR5 = pr;
	TMR5 = 0;
	T5CON = ((tckps) << _T5CON_TCKPS_POSITION);
}

__INLINE__ void __ALWAYS_INLINE__ timer5_start(void) 
{
	T5CONSET = _T5CON_ON_MASK;	// Start Timer
}

__INLINE__ void __ALWAYS_INLINE__ timer5_stop(void) 
{
	T5CONCLR = _T5CON_ON_MASK;	// Stop Timer
	timer5_disable_IRQ();
}
#endif /* __USE_EE_TIMER_5__ */


/******************************************************************************/
/*                              TIMER ISRs                                    */
/******************************************************************************/
#ifdef __USE_EE_TIMER_1__
ISR2(_TIMER_1_VECTOR)
{
	IFS0CLR = _IFS0_T1IF_MASK;
	#ifdef __COUNTER_TICK_ON_TIMER_1__
	CounterTick(__COUNTER_TICK_ON_TIMER_1__);
	#endif
	if (timer1_callback)
		timer1_callback();
}
#endif /* __USE_EE_TIMER_1__ */

#ifdef __USE_EE_TIMER_2__
ISR2(_TIMER_2_VECTOR)
{
	IFS0CLR = _IFS0_T2IF_MASK;
	if (timer2_callback)
		timer2_callback();
}
#endif /* __USE_EE_TIMER_2__ */

#ifdef __USE_EE_TIMER_3__
ISR2(_TIMER_3_VECTOR)
{
	IFS0CLR = _IFS0_T3IF_MASK;
	if (timer3_callback)
		timer3_callback();
}
#endif /* __USE_EE_TIMER_3__ */

#ifdef __USE_EE_TIMER_4__
ISR2(_TIMER_4_VECTOR)
{
	IFS0CLR = _IFS0_T4IF_MASK;
	if (timer4_callback)
		timer4_callback();
}
#endif /* __USE_EE_TIMER_4__ */

#ifdef __USE_EE_TIMER_5__
ISR2(_TIMER_5_VECTOR)
{
	IFS0CLR = _IFS0_T5IF_MASK;
	if (timer5_callback)
		timer5_callback();
}
#endif /* __USE_EE_TIMER_5__ */

/******************************************************************************/
/*                       Public Global Functions                              */
/******************************************************************************/
EE_INT8 EE_timer_hard_init(EE_UINT8 id, EE_UINT32 period, EE_UINT8 prescale)
{
	
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_init(period, prescale);
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		timer2_init(period, prescale);
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :	
		timer3_init(period, prescale);
		break; 
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		timer4_init(period, prescale);
		break;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		timer5_init(period, prescale);
		break;
	#endif 
	#ifdef __USE_EE_TIMER_45__
	case EE_TIMER_45 :
		timer45_init(period, prescale);
		break;
	#endif
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
} 


EE_INT8 EE_timer_soft_init(EE_UINT8 id, EE_UINT32 period_us)
{
	EE_UINT32 base_freq = EE_get_peripheral_clock();
	/* This works if base_freq is a multiple of 1 million, which should be
	 * normally the case */
	EE_UINT32 ticks = period_us * (base_freq / 1000000U);
	EE_UINT16 prd; /* Period */
	EE_UINT8 psc; /* Prescale */
	const EE_UINT32 max_period = 0xffffU;
	switch (id) {
	#ifdef __USE_EE_TIMER_45__
	case EE_TIMER_45:
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif
	#ifdef __USE_EE_TIMER_23__
	case EE_TIMER_23:
		return -EE_TIMER_ERR_UNIMPLEMENTED;
	#endif
	default:
		; /* Proceed */
	}
	if (ticks < max_period) {
		prd = ticks;
		psc = (id==EE_TIMER_1) ? EE_TIMER1_PRESCALE_1 : EE_TIMERx_PRESCALE_1;
	} else if (ticks / 8 < max_period) {
		prd = ticks / 8;
		psc = (id==EE_TIMER_1) ? EE_TIMER1_PRESCALE_8 : EE_TIMERx_PRESCALE_8;
	} else if (ticks / 64 < max_period) {
		prd = ticks / 64;
		psc = (id==EE_TIMER_1) ? EE_TIMER1_PRESCALE_64 : EE_TIMERx_PRESCALE_64;
	} else if (ticks / 256 < max_period) {
		prd = ticks / 256;
		psc = (id==EE_TIMER_1) ? EE_TIMER1_PRESCALE_256 : EE_TIMERx_PRESCALE_256;
	} else {
		return -EE_TIMER_ERR_BAD_ARGS;
	}
	return EE_timer_hard_init(id, prd, psc);
}


EE_INT8 EE_timer_set_callback(EE_UINT8 id, void (*f)(void))
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_callback = f;
		if (f != NULL)
			timer1_enable_IRQ();
		else
			timer1_disable_IRQ();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		timer2_callback = f;
		if (f != NULL)
			timer2_enable_IRQ();
		else
			timer2_disable_IRQ();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		timer3_callback = f;
		if (f != NULL)
			timer3_enable_IRQ();
		else
			timer3_disable_IRQ();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		timer4_callback = f;
		if (f != NULL)
			timer4_enable_IRQ();
		else
			timer4_disable_IRQ();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		timer5_callback = f;
		if (f != NULL)
			timer5_enable_IRQ();
		else
			timer5_disable_IRQ();
		break;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
} 

EE_INT8 EE_timer_start(EE_UINT8 id)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_start();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		timer2_start();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		timer3_start();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		timer4_start();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		timer5_start();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_45__
	case EE_TIMER_45 :
		/* Timer 45 is controlled by timer 4 */
		timer4_start();
		break;
	#endif
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_timer_stop(EE_UINT8 id)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		timer1_stop();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		timer2_stop();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		timer3_stop();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		timer4_stop();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		timer5_stop();
		break;
	#endif 
	#ifdef __USE_EE_TIMER_45__
	case EE_TIMER_45 :
		/* Timer 45 is controlled by timer 4 */
		timer4_stop();
		break;
	#endif
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}

EE_INT8 EE_timer_get_val(EE_UINT8 id, EE_UINT16 *v)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		*v = TMR1;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		*v = TMR2;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		*v = TMR3;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		*v = TMR4;
		break;	
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		*v = TMR5;
		break;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}


EE_INT8 EE_timer_get_val32(EE_UINT8 id, EE_UINT32 *v)
{
	switch (id) {
	#ifdef __USE_EE_TIMER_1__
	case EE_TIMER_1 :
		*v = TMR1;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_2__
	case EE_TIMER_2 :
		*v = TMR2;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_3__
	case EE_TIMER_3 :
		*v = TMR3;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_4__
	case EE_TIMER_4 :
		*v = TMR4;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_5__
	case EE_TIMER_5 :
		*v = TMR5;
		break;
	#endif 
	#ifdef __USE_EE_TIMER_45__
	case EE_TIMER_45 :
		/* Timer 45 is controlled by timer 4 */
		*v = TMR4;
		break;
	#endif 
	default:
		return -EE_TIMER_ERR_BAD_TIMER_ID;
	}
	return EE_TIMER_NO_ERRORS;
}

/*
  Local Variables:
  tab-width: 4
  indent-tabs-mode: t
  End:
*/
