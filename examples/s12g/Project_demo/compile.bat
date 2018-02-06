@echo off

rem ***************************************************************
rem * Are you here because the script can not find the bash shell?
rem * Please change the following line!
rem ***************************************************************
set EE_BASH_PATH=C:\cygwin\bin\bash.exe
if not exist %EE_BASH_PATH% goto error

if [%1]==[help] goto help

:ok
echo.
set SHELLOPTS=igncr
%EE_BASH_PATH% -c "/bin/bash --login -c \"cd `/bin/cygpath/ -ms \"$PWD\"`; ./compile.sh %1 \""
echo.
goto end

:error
echo.
echo *** ERROR:
echo ***  The compile.bat script can not find the Cygwin BASH shell.
echo ***  Please change the EE_BASH_PATH environment variable inside compile.bat
echo.
goto end

:help
echo.
echo *******************************************************
echo *** HELP:                                           ***
echo ***  Make/Clean project utility.                    ***
echo ***                                                 ***
echo ***  Default usage:                                 ***
echo ***      double click on 'compile.bat' icon         ***
echo ***      to build the project.                      ***
echo ***                                                 ***
echo ***  Command line usage:                            ***
echo ***      compile.bat help    (to print this help)   ***
echo ***      compile.bat make    (to build the project) ***
echo ***      compile.bat clean   (to clean the project) ***
echo *******************************************************
echo.
goto finish

:end
pause

:finish

