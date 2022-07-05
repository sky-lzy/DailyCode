
module DataMemory(reset, clk, Address, Write_data, Read_data, MemRead, MemWrite, LbuOp);
	input reset, clk;
	input [31:0] Address, Write_data;
	input MemRead, MemWrite, LbuOp;
	output [31:0] Read_data;
	
	parameter RAM_SIZE = 256;
	parameter RAM_SIZE_BIT = 8;
	
	reg [31:0] RAM_data[RAM_SIZE - 1: 0];
	wire [31:0] Read_data_word;
	assign Read_data_word = MemRead? RAM_data[Address[RAM_SIZE_BIT + 1:2]]: 32'h00000000;
	assign Read_data = ~LbuOp ? Read_data_word : 
					   (Address[1:0] == 2'b11) ? {24'h000000, Read_data_word[31:24]} : 
					   (Address[1:0] == 2'b10) ? {24'h000000, Read_data_word[23:16]} : 
					   (Address[1:0] == 2'b01) ? {24'h000000, Read_data_word[15: 8]} : 
					   {24'h000000, Read_data_word[7 : 0]};
	
	integer i = 0;
	always @(posedge reset or posedge clk)
		if (reset)
			for (i = 0; i < RAM_SIZE; i = i + 1)
				RAM_data[i] <= 32'h00000000;
		else if (MemWrite)
			RAM_data[Address[RAM_SIZE_BIT + 1:2]] <= Write_data;
			

	initial
	begin
		#101;
		RAM_data[0]  = 32'h756E696C;
		RAM_data[1]  = 32'h73692078;
		RAM_data[2]  = 32'h746F6E20;
		RAM_data[3]  = 32'h696E7520;
		RAM_data[4]  = 32'h73692078;
		RAM_data[5]  = 32'h746F6E20;
		RAM_data[6]  = 32'h696E7520;
		RAM_data[7]  = 32'h73692078;
		RAM_data[8]  = 32'h746F6E20;
		RAM_data[9]  = 32'h696E7520;
		RAM_data[10] = 32'h00000078;

		RAM_data[25] = 32'h78696E75;
	end


endmodule
