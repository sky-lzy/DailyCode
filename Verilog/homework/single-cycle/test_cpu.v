
module test_cpu();
	
	reg sysclk;
	reg reset;
	reg clk;
	reg [1:0] RegShow;
	
	wire [3:0] ENs;
	wire [7:0] LEDs;
	wire [6:0] BCDs;
	CPU cpu1(sysclk, reset, clk, RegShow, ENs, LEDs, BCDs);
	
	initial begin
		sysclk = 1'b1;
		reset = 1'b1;
		clk = 1'b1;
		RegShow = 2'b11;
		#100 reset = 1'b0;

		#10000 $finish;
		// #2000 $finish;
	end
	
	always #50 clk = ~clk;
	always #5 sysclk = ~sysclk;
		
endmodule
