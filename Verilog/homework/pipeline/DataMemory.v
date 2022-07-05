
module DataMemory(reset, clk, Address, Write_data, Read_data, MemRead, MemWrite);
	input reset, clk;
	input [31:0] Address, Write_data;
	input MemRead, MemWrite;
	output [31:0] Read_data;
	
	parameter RAM_SIZE = 256;
	parameter RAM_SIZE_BIT = 8;
	
	reg [31:0] RAM_data[RAM_SIZE - 1: 0];
	// assign Read_data = MemRead? RAM_data[Address[RAM_SIZE_BIT + 1:2]]: 32'h00000000;
	assign Read_data = MemRead? RAM_data[Address[RAM_SIZE_BIT - 1:0]]: 32'h00000000;
	
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
		RAM_data[0]  = 8'h6C;
		RAM_data[1]  = 8'h69;
		RAM_data[2]  = 8'h6E;
		RAM_data[3]  = 8'h75;
		RAM_data[4]  = 8'h78;
		RAM_data[5]  = 8'h20;
		RAM_data[6]  = 8'h69;
		RAM_data[7]  = 8'h73;
		RAM_data[8]  = 8'h20;
		RAM_data[9]  = 8'h6E;
		RAM_data[10] = 8'h6F;
		RAM_data[11] = 8'h74;
		RAM_data[12] = 8'h20;
		RAM_data[13] = 8'h75;
		RAM_data[14] = 8'h6E;
		RAM_data[15] = 8'h69;
		RAM_data[16] = 8'h78;
		RAM_data[17] = 8'h20;
		RAM_data[18] = 8'h69;
		RAM_data[19] = 8'h73;
		RAM_data[20] = 8'h20;
		RAM_data[21] = 8'h6E;
		RAM_data[22] = 8'h6F;
		RAM_data[23] = 8'h74;
		RAM_data[24] = 8'h20;
		RAM_data[25] = 8'h75;
		RAM_data[26] = 8'h6E;
		RAM_data[27] = 8'h69;
		RAM_data[28] = 8'h78;
		RAM_data[29] = 8'h20;
		RAM_data[30] = 8'h69;
		RAM_data[31] = 8'h73;
		RAM_data[32] = 8'h20;
		RAM_data[33] = 8'h6E;
		RAM_data[34] = 8'h6F;
		RAM_data[35] = 8'h74;
		RAM_data[36] = 8'h20;
		RAM_data[37] = 8'h75;
		RAM_data[38] = 8'h6E;
		RAM_data[39] = 8'h69;
		RAM_data[40] = 8'h78;

		RAM_data[100] = 8'h75;
		RAM_data[101] = 8'h6E;
		RAM_data[102] = 8'h69;
		RAM_data[103] = 8'h78;
	end


endmodule
