`timescale 1ns / 1ps
//////////////////////////////////////////////////////////////////////////////////
// Class: Fundamentals of Digital Logic and Processor
// Designer: Shulin Zeng
// 
// Create Date: 2021/04/30
// Design Name: MultiCycleCPU
// Module Name: MultiCycleCPU
// Project Name: Multi-cycle-cpu
// Target Devices: 
// Tool Versions: 
// Description: 
// 
// Dependencies: 
// 
// Revision:
// Revision 0.01 - File Created
// Additional Comments:
// 
//////////////////////////////////////////////////////////////////////////////////


module test_cpu();
	
	reg sysclk;
	reg reset;
	reg clk;
	reg [1:0] RegShow;
	
	wire [3:0] ENs;
	wire [7:0] LEDs;
	wire [6:0] BCDs;
	MultiCycleCPU MultiCycleCPU_1(sysclk, reset, clk, RegShow, ENs, LEDs, BCDs);
	
	initial begin
		sysclk = 1'b1;
		reset = 1'b1;
		clk = 1'b1;
		RegShow = 2'b11;
		#100 reset = 1'b0;

		#40000 $finish;
        // #5000 $finish;
	end
	
	always #50 clk = ~clk;
	always #5 sysclk = ~sysclk;
		
endmodule
