
module DataMemory(reset, clk, Address, Write_data, Read_data, MemRead, MemWrite, LbuOp, LEDs, ENs, ClkNumber, UART_TXD, UART_RXD, UART_CON);
	input reset, clk;
	input [31:0] Address, Write_data;
	input MemRead, MemWrite, LbuOp;
	output [31:0] Read_data;
	output reg [7:0] LEDs;
	output reg [11:0] ENs;
	output reg [7:0] ClkNumber;
	output reg [7:0] UART_TXD;
	output reg [7:0] UART_RXD;
	output reg [3:0] UART_CON;
	
	parameter RAM_SIZE = 256;
	parameter RAM_SIZE_BIT = 8;
	
	reg [31:0] RAM_data[RAM_SIZE - 1: 0];
	wire [31:0] Read_data_word;
	assign Read_data_word = ~MemRead? 32'h00000000 : 
							(Address[31:10] == 22'b0) ? RAM_data[Address[RAM_SIZE_BIT + 1:2]] : 
							(Address == 32'h4000000C) ? {24'b0, LEDs} : 
							(Address == 32'h40000010) ? {20'b0, ENs}  : 
							(Address == 32'h40000014) ? {24'b0, ClkNumber} : 
							(Address == 32'h40000018) ? {24'b0, UART_TXD} : 
							(Address == 32'h4000001C) ? {24'b0, UART_RXD} : 
							(Address == 32'h40000020) ? {28'b0, UART_CON} : 
							32'h00000000;
							
	assign Read_data = ~LbuOp ? Read_data_word : 
					   (Address[1:0] == 2'b11) ? {24'h000000, Read_data_word[31:24]} : 
					   (Address[1:0] == 2'b10) ? {24'h000000, Read_data_word[23:16]} : 
					   (Address[1:0] == 2'b01) ? {24'h000000, Read_data_word[15: 8]} : 
					   {24'h000000, Read_data_word[7 : 0]};
	
	integer i = 0;
	always @(posedge reset or posedge clk)
		if (reset)
		begin
			RAM_data[0]  <= 32'h756E696C;
			RAM_data[1]  <= 32'h73692078;
			RAM_data[2]  <= 32'h746F6E20;
			RAM_data[3]  <= 32'h696E7520;
			RAM_data[4]  <= 32'h73692078;
			RAM_data[5]  <= 32'h746F6E20;
			RAM_data[6]  <= 32'h696E7520;
			RAM_data[7]  <= 32'h73692078;
			RAM_data[8]  <= 32'h746F6E20;
			RAM_data[9]  <= 32'h696E7520;
			RAM_data[10] <= 32'h00000078;

			RAM_data[25] <= 32'h78696E75;
			// for (i = 0; i < RAM_SIZE; i = i + 1)
				// RAM_data[i] <= 32'h00000000;
			LEDs <= 8'b0;
			ENs <= 12'b0;
			ClkNumber <= 8'b0;
			UART_TXD <= 8'b0;
			UART_RXD <= 8'b0;
			UART_CON <= 4'b0;
		end
		else if (MemWrite)
		begin
			if (Address[31:10] == 22'b0)
				RAM_data[Address[RAM_SIZE_BIT + 1:2]] <= Write_data;
			else 
			begin
				case (Address)
					32'h4000000C: LEDs <= {24'b0, Write_data[7:0]};
					32'h40000010: ENs <= {20'b0, Write_data[11:0]};
					32'h40000014: ClkNumber <= {24'b0, Write_data[7:0]};
					32'h40000018: UART_TXD <= {24'b0, Write_data[7:0]};
					32'h4000001C: UART_RXD <= {24'b0, Write_data[7:0]};
					32'h40000020: UART_CON <= {28'b0, Write_data[3:0]};
				endcase
			end
		end
			

	initial
	begin
		#101;
		// RAM_data[0]  = 32'h756E696C;
		// RAM_data[1]  = 32'h73692078;
		// RAM_data[2]  = 32'h746F6E20;
		// RAM_data[3]  = 32'h696E7520;
		// RAM_data[4]  = 32'h73692078;
		// RAM_data[5]  = 32'h746F6E20;
		// RAM_data[6]  = 32'h696E7520;
		// RAM_data[7]  = 32'h73692078;
		// RAM_data[8]  = 32'h746F6E20;
		// RAM_data[9]  = 32'h696E7520;
		// RAM_data[10] = 32'h00000078;

		// RAM_data[25] = 32'h78696E75;
	end


endmodule
