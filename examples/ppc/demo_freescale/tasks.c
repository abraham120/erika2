#include <ee.h>
#include <support.h>

DeclareTask(disturbing_task);
DeclareTask(CheckOK_task);

/* Disturbing Task */
TASK(disturbing_task)
{
	int check_res;
	delay(MEDIUM_DELAY);

	/* Read var2 */
	lock_var();
	delay(LARGE_DELAY);
	check_res = check_shared_value(2,shared_data);
	unlock_var();

	delay(MEDIUM_DELAY);

	/* If check is ok activate CheckOK_task */
	if (check_res)
		ActivateTask(CheckOK_task);

	TerminateTask();
}

TASK(CheckOK_task)
{
	delay(MEDIUM_DELAY);
	TerminateTask();
}

