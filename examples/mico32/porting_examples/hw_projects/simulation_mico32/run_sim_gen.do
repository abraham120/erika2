set platform_dir $1
set platform_name $2
set testbench_name $3

if not [exist sim_space.aws]
	workspace create sim_space
endif
if not [exist sim_design/sim_design.adf]
	design create sim_design .
endif
design open sim_design
cd ../..
set sim_working_folder .
# add additional vlog commands for each PMI module in the
# design. The list shown is not intended to be complete for all
# possible LM32 designs.
vlog +define+SIMULATION $platform_dir/soc/$platform_name.v
#acom $platform_dir/soc/.vhd
vlog +incdir+$platform_dir/Components/lm32_top/rtl/verilog+$platform_dir/soc ${platform_name}_tb.v

# the VSIM command uses the Aldec for Lattice pre-compiled FPGA
# libraries. If the Aldec for Lattice simulator is not being
# used, it will be necessary to compile the behavioral code for
# the FPGA. For the ECP2, the behavioral code is located at:
# <isptools>/cae_library/simulation/verilog/ecp2
vsim $testbench_name -L ovi_xp2 -PL pmi_work

clear -wave
add wave -noreg {/reset_n}
add wave -noreg {/clk_i}
#add wave -noreg {/UUT/LM32/cpu/pc_f}
#add wave -noreg {/UUT/LM32/cpu/pc_x}
#add wave -noreg {/UUT/LM32/cpu/pc_w}
add wave -noreg {/UUT/LM32/cpu/interrupt/ie}
add wave -noreg {/UUT/LM32/cpu/interrupt/ip}
add wave -noreg {/UUT/LM32/cpu/interrupt/im}
add wave -vbus pc_w -noreg {/full_pc_w}
add wave -vbus pc_x -noreg {/full_pc_x}
add wave -vbus pc_f -noreg {/full_pc_f}
add wave -vbus r1 -noreg {/UUT/LM32/cpu/registers(1)} 
add wave -vbus r2 -noreg {/UUT/LM32/cpu/registers(2)}
add wave -vbus r3 -noreg {/UUT/LM32/cpu/registers(3)}
add wave -vbus r4 -noreg {/UUT/LM32/cpu/registers(4)}
add wave -vbus r5 -noreg {/UUT/LM32/cpu/registers(5)}
add wave -vbus r6 -noreg {/UUT/LM32/cpu/registers(6)}
add wave -vbus r7 -noreg {/UUT/LM32/cpu/registers(7)}
add wave -vbus r8 -noreg {/UUT/LM32/cpu/registers(8)}
add wave -vbus r9 -noreg {/UUT/LM32/cpu/registers(9)}
add wave -vbus r10 -noreg {/UUT/LM32/cpu/registers(10)}
add wave -vbus r11 -noreg {/UUT/LM32/cpu/registers(11)}
add wave -vbus r12 -noreg {/UUT/LM32/cpu/registers(12)}
add wave -vbus r13 -noreg {/UUT/LM32/cpu/registers(13)}
add wave -vbus r14 -noreg {/UUT/LM32/cpu/registers(14)}
add wave -vbus r15 -noreg {/UUT/LM32/cpu/registers(15)}
add wave -vbus r16 -noreg {/UUT/LM32/cpu/registers(16)}
add wave -vbus r17 -noreg {/UUT/LM32/cpu/registers(17)}
add wave -vbus r18 -noreg {/UUT/LM32/cpu/registers(18)}
add wave -vbus r19 -noreg {/UUT/LM32/cpu/registers(19)}
add wave -vbus r20 -noreg {/UUT/LM32/cpu/registers(20)}
add wave -vbus r21 -noreg {/UUT/LM32/cpu/registers(21)}
add wave -vbus r22 -noreg {/UUT/LM32/cpu/registers(22)}
add wave -vbus r23 -noreg {/UUT/LM32/cpu/registers(23)}
add wave -vbus r24 -noreg {/UUT/LM32/cpu/registers(24)}
add wave -vbus r25 -noreg {/UUT/LM32/cpu/registers(25)}
add wave -vbus r26 -noreg {/UUT/LM32/cpu/registers(26)}
add wave -vbus fp -noreg {/UUT/LM32/cpu/registers(27)}
add wave -vbus sp -noreg {/UUT/LM32/cpu/registers(28)}
add wave -vbus ra -noreg {/UUT/LM32/cpu/registers(29)}
add wave -vbus ea -noreg {/UUT/LM32/cpu/registers(30)}

@if [exist "global.do"]
	source "global.do"
@else
	@echo {WARNING: Missing "global.do"; not displaying global variables.}
	@pause 3
@endif

# Leave the vsim command visible
@echo vsim $testbench_name -L ovi_xp2 -PL pmi_work

run 25us
