@echo off

rem mplab_generatelib.bat "c:\Documents and Settings\Pj\workspace\prova\conf.oil" "c:\Documents and Settings\Pj\workspace\prova\mplab"

rem ***************************************************************
rem * Are you here because the script can not find the bash shell?
rem * Please change the following line!
rem ***************************************************************
set EE_BASH_PATH=C:\cygwin\bin\bash.exe

if not exist %EE_BASH_PATH% goto error

:ok
set SHELLOPTS=igncr

rem Create the directory if it does not exist
setlocal enableextensions
mkdir %2 > NUL 2>&1
mkdir %2\Debug > NUL 2>&1
mkdir %2\Files > NUL 2>&1

set EE_MPLAB_GENERATELIB_PARAM1=%1
set EE_MPLAB_GENERATELIB_PARAM2=%2
%EE_BASH_PATH% -c "/bin/bash --login -c \"cd `/bin/cygpath/ -ms \"$PWD\"`; ./mplab_generatelib.sh\""
set EE_MPLAB_GENERATELIB_PARAM1=
set EE_MPLAB_GENERATELIB_PARAM2=

goto end

:error
echo *** ERROR:
echo ***  The mplab_generatelib.bat script can not find the Cygwin BASH shell.
echo ***  Please change the EE_BASH_PATH environment variable inside
echo ***  mplab_generatelib.bat
pause

:end
