LOG CMDLINE = ON, CMDFILE = OFF, RESPONSES = ON, ERRORS = ON, NOTICES = ON

// script used to load t32_jobs.cmm.
// DO NOT MODIFY this script. Modify common/e7t_manual/t32_quit.cmm instead

WAIT 1

cd tmp
lf logfile.txt
printf("MODISTARC regression tests in progress...")
cf s12_jobs.cmd        
printf("...Done!!!")
nolf
cd ..\common\s12
