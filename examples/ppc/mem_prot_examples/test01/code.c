#include "common.h"

#ifdef EE_ISR_DYNAMIC_TABLE
static void init_app1_timer(void)
{
	void App1Isr(void);
	EE_e200z7_register_ISR(10, App1Isr, 0);
	EE_e200z7_setup_decrementer(50000);
}

static void init_trusted_irq(void)
{
	void TrustedIsr(void);
	EE_e200z7_register_ISR(11, TrustedIsr, 1);
	EE_e200zx_setup_fixed_intv(64-15);
}
#else
static void init_app1_timer(void)
{
	EE_e200z7_setup_decrementer(50000);
}

static void init_trusted_irq(void)
{
	EE_e200zx_setup_fixed_intv(64-15);
}
#endif

void main(void)
{
	init_app1_timer();
	init_trusted_irq();
	StartOS(OSDEFAULTAPPMODE);
	EE_hal_enableIRQ();
	while (1) {
		/* Background loop */
	}
}
