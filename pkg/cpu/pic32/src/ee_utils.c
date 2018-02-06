#include "ee_internal.h"

/* External Clock Source, redefine in the application if differs from this
*  value */
#ifndef CLOCK_SOURCE
#define CLOCK_SOURCE 8000000ul
#endif 


#ifndef DEVCFG2
#define DEVCFG2  0xBFC02FF4 //virtual address of the register
#endif //DEVCFG2

#ifndef PLLIDIV_MASK
#define PLLIDIV_MASK 0x7
#endif 


/* Function used to calculate the initialize the system */
void EE_system_init(void)
{
	register EE_UREG r;

	/* Disable JTAG Port */
	DDPCONbits.JTAGEN = 0; 
	#ifndef EE_PIC32_DISABLE_PCACHE
	/* Enable cacheability on memory segment KSEG0 */
	asm volatile ("mfc0 %0,$16,0" :  "=r"(r));
        r = (r & ~7) | 3;
        asm volatile ("mtc0 %0,$16,0\n\tehb\n\t" : "+r"(r));
	/* Configure Cache: TODO find the best for this (better having an API)*/
	CHECON = (2 << _CHECON_PFMWS_POSITION) | (1 << _CHECON_PREFEN_POSITION);
	#endif /* EE_PIC32_DISABLE_PCACHE */
	/* Enable interrupts: set CP0 cause IV bit, enable multi-vector IRQ */
        asm volatile("mfc0   %0,$13" : "=r"(r));
        r |= 0x00800000; 	
        asm volatile("mtc0   %0,$13\n\tehb\n\t" : "+r"(r));
        INTCONSET = _INTCON_MVEC_MASK;
	ASM_EN_INT; 
}

static const unsigned int FPPLIDIV_VAL [8] = {1,2,3,4,5,6,10,12};
static const unsigned int PLLODIV_VAL [8] = {1,2,4,8,16,32,64,256};
static const unsigned int PLLMULT_VAL [8] = {15,16,17,18,19,20,21,24};
static const unsigned int PBDIV_VAL [4] = {1,2,4,8};

/* Function used to calculate the system clock */
EE_UINT32 EE_get_system_clock(void)
{
	register EE_UREG pllodiv;
	register EE_UREG pllmult;
	register EE_UREG fpllidiv;

	/* Extraction of pplodiv */
	pllodiv = PLLODIV_VAL[(unsigned int)OSCCONbits.PLLODIV];	
	/* Extraction of pplmult */
	pllmult = PLLMULT_VAL[(unsigned int)OSCCONbits.PLLMULT];
	/* Extraction of pplidiv */
	fpllidiv =  FPPLIDIV_VAL[(*((EE_UREG *)DEVCFG2)) & PLLIDIV_MASK];
	  
	return  (CLOCK_SOURCE * pllmult / (fpllidiv * pllodiv));
}

/* Function used to calculate the peripherals clock */
EE_UINT32 EE_get_peripheral_clock(void)
{
	register EE_UREG pbdiv;

	pbdiv = PBDIV_VAL[OSCCONbits.PBDIV];
	return  (EE_get_system_clock() / pbdiv);
}

void EE_nop_delay_us_80mips(EE_UINT32 delay)
{
	/* FOR delay DO 80 x nops (1 nops = 12,5ns -> 80 nops = 1us) */
	asm volatile (	".set noreorder \n\t"
			"2:\n\t"
			"       li $v0, 36\n\t"
			"1:\n\t"
			"       bne $v0, $zero, 1b\n\t"
			"       addi $v0, -1\n\t"
			"	nop\n\t"
			"	nop\n\t"
			"	nop\n\t"
			"       bne $a0, $zero, 2b\n\t"
			"       addi $a0, -1\n\t");
}

void EE_delay_ticks(EE_UINT32 ticks)
{
	register EE_UREG r;

	/* TODO: use this if the core-timer is OFF (at reset is ON)
        asm volatile("mfc0   %0,$13" : "=r"(r));
	r |= 0x08000000;
        asm volatile("mtc0   %0,$13\n\tehb" : "+r"(r));
	*/
        asm volatile("mfc0 %0, $9" : "=r"(r));
	ticks = (ticks >> 1) + r;
	if (ticks < r) /* If final tick overlap the 32-bit representation */
		while (r < 0xFFFFFFFF) 
        		asm volatile("mfc0 %0, $9" : "=r"(r));
	while (r < ticks) 
       		asm volatile("mfc0 %0, $9" : "=r"(r));
}

void EE_delay_us(EE_UINT32 delay)
{
	
	/* NOTE: this function works only for CPU_CLOCK multiple of 1 MHz */
	register EE_UREG r;
	register EE_UREG prev;
	EE_UREG delay_tick;

	prev = EE_pic32_get_core_timer_value();
	r = EE_get_system_clock(); /* Get system frequency [Hz] */
	r = r / 1000000U; /* Transform frequency [MHz] */
	/* Core timer frequency is half the CPU frequency */	   
	delay_tick = r * delay / 2; /* count = delay[us] * frequency[MHz] / 2 */
		
	/* TODO: use this if the core-timer is OFF (at reset is ON)
	register EE_UREG r;
        asm volatile("mfc0   %0,$13" : "=r"(r));
	r |= 0x08000000;
        asm volatile("mtc0   %0,$13\n\tehb" : "+r"(r));
	*/
	/* We could miss the exit condition only if we are preempted for more
	 * than (2^32 - delay_tick) ticks, which is always larger than 2
	 * billion ticks due to the divison by 2 above.  The subtraction handles
	 * correctly any wrap-around. */
	do {
		r = EE_pic32_get_core_timer_value();
	} while (r - prev < delay_tick);
}

#ifdef __USE_EE_CORETIMER_ALARM__

void (* volatile coretimer_callback)(void);

void EE_coretimer_hard_alarm(EE_UINT32 pr, void (*f)(void))
{
	if (f == NULL)
		return;
	coretimer_callback = f;
	IPC0CLR = _IPC0_CTIP_MASK;
	IPC0SET = (2 << _IPC0_CTIP_POSITION); //TODO:change hardcoding Irq Prio?
	IPC1CLR = _IPC0_CTIS_MASK; //TODO:change hardcoding Irq Sub-Prio?
	asm volatile (	"mfc0 $v0, $9\n\t" 
			"addu $v0, $v0, $a0\n\t" 
			"mtc0 $v0, $11\n\t"
			"ehb\n\t");
	/* TODO: use this if the core-timer is OFF (at reset is ON)
	register EE_UREG r;
        asm volatile("mfc0   %0,$13" : "=r"(r));
	r |= 0x08000000;
        asm volatile("mtc0   %0,$13" : "+r"(r));
	*/
	IFS0CLR = _IFS0_CTIF_MASK;	
	IEC0SET = _IEC0_CTIE_MASK;	
}

void EE_coretimer_soft_alarm(EE_UINT32 period_us, void (*f)(void))
{
	/* NOTE: the following functions works only for CPU_CLOCK = N x MHz */
	EE_UINT32 base_freq = EE_get_system_clock();
	EE_UINT32 ticks;
	ticks = period_us * (base_freq / 1000000U);
	ticks >>= 1;
	EE_coretimer_hard_alarm(ticks, f);
}

ISR2(_CORE_TIMER_VECTOR)
{
	IFS0CLR = _IFS0_CTIF_MASK;	
	IEC0CLR = _IEC0_CTIE_MASK;	
	coretimer_callback();
}

#endif /* __USE_EE_CORETIMER_ALARM__ */
