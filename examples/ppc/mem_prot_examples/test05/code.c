#include <ee.h>
#include <ee_irq.h>
#include "error.h"
#include "app.h"


void error(enum err_code code)
{
	/* Do nothing; you should add a breakpoint on this function to catch
	 * errors */
}

void init_trusted_timer(void)
{
	void TrustedIsr(void);
	EE_e200z7_register_ISR(10, TrustedIsr, 0);
	EE_e200z7_setup_decrementer_oneshot(200000);
}

void init_app1_timer(void)
{
	void App1Isr(void);
	EE_e200z7_register_ISR(10, App1Isr, 0);
	EE_e200z7_setup_decrementer_oneshot(80000);
}

void init_app2_timer(void)
{
	void App2Isr(void);
	EE_e200z7_register_ISR(11, App2Isr, 1);
	EE_e200zx_setup_fixed_intv(64-19);
}

void main(void)
{
	StartOS(OSDEFAULTAPPMODE);
	EE_hal_enableIRQ();
	while (1) {
		/* Background loop */
	}
}
