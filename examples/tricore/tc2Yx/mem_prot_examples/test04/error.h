#ifndef ERROR_H
#define ERROR_H

#include "ee.h"

/* Error codes */
enum err_code {
  err_wrong_irq_tos, /* An IRQ TOS is different while outside any ISR */
  err_disable_irq_fail, /* DisableAllInterrupts() didn't disable */
  err_enable_irq_fail, /* EnableAllInterrupts() didn't enable */
  err_suspend_irq_fail, /* SuspendAllInterrupts() didn't suspend */
  err_resume_irq_early_fail, /* ResumeAllInterrupts() resumed too early */
  err_resume_irq_fail, /* ResumeAllInterrupts() didn't resume */
  err_suspend_os_irq_fail, /* SuspendOSInterrupts() didn't suspend */
  err_resume_os_irq_early_fail, /* ResumeOSInterrupts() resumed too
                                   early */
  err_resume_os_irq_fail /* ResumeOSInterrupts() didn't resume */
};

/* Error and delay functions */
void error(enum err_code code);

#endif /* ERROR_H */
