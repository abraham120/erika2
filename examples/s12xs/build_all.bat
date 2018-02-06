@echo off

rem ***************************************************************
rem * Are you here because the script can not find the bash shell?
rem * Please change the following line!
rem ***************************************************************
set EE_BASH_PATH=C:\cygwin\bin\bash.exe

if not exist %EE_BASH_PATH% goto error

rem ***************************************************************
rem * Are you here because the script can not run?
rem * Please insert the folder path changing the following line!
rem ***************************************************************
set EXAMPLES_PATH=C:\examples\s12xs

:ok
set OLDDIR=%CD%
cd %EXAMPLES_PATH%
set SHELLOPTS=igncr
%EE_BASH_PATH% -c "/bin/bash --login -c \"cd `/bin/cygpath/ -ms \"$PWD\"`; ./build.sh %1 \""
cd /d %OLDDIR% 
goto end

:error
echo *** ERROR:
echo ***  The compile.bat script can not find the Cygwin BASH shell.
echo ***  Please change the EE_BASH_PATH environment variable inside compile.bat
pause

:end
