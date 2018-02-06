@echo off

REM


set RTD_STD_BASE=%~dp0
set LIB_BASE=%RTD_STD_BASE%\jars

set E_BASE=%EVIDENCE_BASE%
set RTD_CMD_LINE_ARGS=

if "XX%E_BASE%XX"=="XXXX" goto set_E_BASE
goto E_BASE_ready
:set_E_BASE
set E_BASE=%RTD_STD_BASE%\..\\
REM set E_BASE=C:\Programmi\Evidence
:E_BASE_ready



:setupArgs
if ""%1""==""--list"" goto listArg
if ""%1""==""--help"" goto helpArg

:loopArgs
if ""%1""=="""" goto doneArgs
if ""%1""==""--output"" goto outputArg
if ""%1""==""--template"" goto templateArg
goto doneArgs

:templateArg
shift
set RTD_CMD_LINE_ARGS=%RTD_CMD_LINE_ARGS% --template %1
shift
goto loopArgs

:outputArg
shift
set RTD_CMD_LINE_ARGS=%RTD_CMD_LINE_ARGS% --output %1
shift
goto loopArgs

:listArg
set RTD_CMD_LINE_ARGS=%RTD_CMD_LINE_ARGS% %1
shift
goto doneArgs

:helpArg
set RTD_CMD_LINE_ARGS=%RTD_CMD_LINE_ARGS% %1
shift
goto doneArgs

:doneArgs

set L_CLASSPATH=%CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\emf.common_2.2.1.v200702131851.jar;%L_CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\emf.ecore.xmi_2.2.2.v200702131851.jar;%L_CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\emf.ecore_2.2.2.v200702131851.jar;%L_CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\emf.edit_2.2.2.v200702131851.jar;%L_CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\rtd_core.jar;%L_CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\rtd_oil_core.jar;%L_CLASSPATH%
set L_CLASSPATH=%LIB_BASE%\rtd_stdalone_helper.jar;%L_CLASSPATH%

java -classpath "%L_CLASSPATH%" -DEVIDENCEBASE="%E_BASE%" com.eu.evidence.rtdruid.TemplateWriter  %RTD_CMD_LINE_ARGS%
