@REM This batch file has been generated by the IAR Embedded Workbench
@REM C-SPY Debugger, as an aid to preparing a command line for running
@REM the cspybat command line utility using the appropriate settings.
@REM
@REM You can launch cspybat by typing the name of this batch file followed
@REM by the name of the debug file (usually an ELF/DWARF or UBROF file).
@REM Note that this file is generated every time a new debug session
@REM is initialized, so you may want to move or rename the file before
@REM making changes.
@REM 


"C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\common\bin\cspybat" "C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm\bin\armproc.dll" "C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm\bin\armjlink.dll"  %1 --plugin "C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm\bin\armbat.dll" --macro "C:\Users\Deus Ex Machina\Documenti\cortex_ex\lpc1227_test1\Project_Template\IAR_EWARM\config\Flash.mac" --flash_loader "C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm\config\flashloader\NXP\FlashNXPLPC128K_CortexLL.board" --backend -B "--endian=little" "--cpu=Cortex-M0" "--fpu=None" "-p" "C:\Programmi\IAR Systems\Embedded Workbench 6.0 Kickstart\arm\config\debugger\NXP\iolpc1224.ddf" "--drv_verify_download" "--semihosting" "--device=LPC1227" "--drv_communication=USB0" "--jlink_speed=2000" "--jlink_reset_strategy=0,0" "--jlink_interface=SWD" "--drv_catch_exceptions=0x000" "--drv_swo_clock_setup=12000000,0,20000000" 


