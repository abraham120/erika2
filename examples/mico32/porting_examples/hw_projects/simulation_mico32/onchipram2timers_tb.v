

`timescale 1 ns / 1 ns
`include "lm32_include.v"

// Define Module for Test Fixture
module platform_top();

	event done;
	wire[`LM32_WORD_RNG] full_pc_w;
	wire[`LM32_WORD_RNG] full_pc_x;
	wire[`LM32_WORD_RNG] full_pc_f;

// Inputs
    reg clk_i;
    reg reset_n;


// Outputs


// Bidirs


// Instantiate the UUT
// Please check and add your parameters manually
    onchipram2timers UUT (
        .clk_i(clk_i), 
        .reset_n(reset_n)
        );


/*----------------------------------------------------------------------
Clock & Reset
----------------------------------------------------------------------*/
initial begin
reset_n = 0;
#100; // delay 100 ns
reset_n = 1;
end
initial begin
clk_i = 0;
#5; // delay 5 ns
forever #(5) clk_i = ~clk_i; // toggle the clk_i signal every 5ns
end

/*
Complete copy of the Pc
*/
assign full_pc_w = UUT.LM32.cpu.valid_w == 1'b1 ? {UUT.LM32.cpu.pc_w, 2'b00} :
                   32'bx;
assign full_pc_x = UUT.LM32.cpu.valid_x == 1'b1 ? {UUT.LM32.cpu.pc_x, 2'b00} :
                   32'bx;
assign full_pc_f = UUT.LM32.cpu.valid_f == 1'b1 ? {UUT.LM32.cpu.pc_f, 2'b00} :
                   32'bx;

/*----------------------------------------------------------------------
Trap "Exit" System Call to terminate simulation
----------------------------------------------------------------------*/
reg scall_m, scall_w;
always @(negedge clk_i)
begin
	if (UUT.LM32.cpu.instruction_unit.i_err_i == `TRUE || UUT.LM32.cpu.load_store_unit.d_err_i == `TRUE)
    begin
		// Instruction/data bus error
		if (UUT.LM32.cpu.instruction_unit.i_err_i == `TRUE)
			$display("Instruction bus error");
		else
			$display("Data bus error");
    	-> done;
	end
	if (UUT.LM32.cpu.stall_m == 1'b0)
	begin
		scall_m <= UUT.LM32.cpu.scall_x &
		UUT.LM32.cpu.valid_x;
		scall_w <= scall_m & UUT.LM32.cpu.valid_m;
	end
	// System Call number is passed in r8, Exit System Call is call number 1
	if (scall_w && (UUT.LM32.cpu.registers[8] == 1))
	begin
		$display("Program exited with code %0d.\n",
		UUT.LM32.cpu.registers[1]);
		-> done;
	end
end

/*----------------------------------------------------------------------
Tasks to perform when simulation terminates
----------------------------------------------------------------------*/
always @(done)
$finish;

endmodule // platform_top
