Simple testcase to test the folliwings AUTOSAR extensions to OSEK/VDX kernel:

Tasks ends without calling a TerminateTask() or ChainTask()

- [OS052]	If a task returns from its entry function without making a
		TerminateTask() or ChainTask() call, the Operating System module
		shall terminate the task (and call the PostTaskHook() if
		configured). (BSW11009)

- [OS069]	If a task returns from its entry function without making a
		TerminateTask() or ChainTask() call AND the error hook is
		configured, the Operating System module shall call the
		ErrorHook() (this is done regardless of whether the task causes
		other errors, e.g. E_OS_RESOURCE) with status E_OS_MISSINGEND
		before the task leaves the RUNNING state. (BSW11009)

- [OS070]	If a task returns from the entry function without making a
		TerminateTask() or ChainTask() call and still holds OSEK
		Resources, the Operating System module shall release them.
		(BSW11009, BSW11013)

- [OS239]	If a task returns from the entry function without making a
		TerminateTask() or ChainTask() call and interrupts are still
		disabled, the Operating System module shall enable them.
 