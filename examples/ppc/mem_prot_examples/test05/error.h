#ifndef ERROR_H
#define ERROR_H

/* Error codes */
enum err_code {
	/* GetISRID() returned a valid ID while outside an ISR */
	err_notinvalid_isr,
	/* GetApplicationID() returned INVALID_OSAPPLICATION in a task */
	err_invalid_task_app,
	/* GetApplicationID() returned INVALID_OSAPPLICATION in an ISR  */
	err_invalid_isr_app,
	/* GetApplicationID() returned the wrong result for a task */
	err_wrong_task_app,
	/* GetApplicationID() returned the wrong result for an ISR  */
	err_wrong_isr_app,
	/* Local variable is not readable */
	err_perm_loc_noread,
	/* Local variable is not writeable */
	err_perm_loc_nowrite,
	/* Local variable is not inside the stack */
	err_perm_loc_nostack,
	/* Constant variable is not readable */
	err_perm_const_noread,
	/* Constant variable is writeable */
	err_perm_const_write,
	/* Constant variable is inside the stack */
	err_perm_const_stack,
	/* Global variable is not readable */
	err_perm_glob_noread,
	/* Global variable is not writeable */
	err_perm_glob_nowrite,
	/* Global variable is inside the stack */
	err_perm_glob_stack,
	/* Variable in an other OS-application is writeable */
	err_perm_othapp_write,
	/* Code is not executable */
	err_perm_code_noexec,
	/* Code is inside the stack */
	err_perm_code_stack
};

/* Error function */
void error(enum err_code code);

#endif /* ERROR_H */
