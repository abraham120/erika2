@ECHO OFF
pushd "%~dp0"
C:\ti\uniflashv3\ccs_base\scripting\examples\uniflash\cmdLine\uniflash -ccxml ./tms570.ccxml -loadSettings ./tms570.uniflashsession -program ../_tms570.out -targetOp run
popd