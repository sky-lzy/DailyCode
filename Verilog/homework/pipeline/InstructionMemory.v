
module InstructionMemory(Address, Instruction);
	input [31:0] Address;
	output reg [31:0] Instruction;
	
	always @(*)
		case (Address[9:2])
			// lui $s0, 16384
			8'd0:   Instruction <= {6'h0f, 5'd0 , 5'd16, 16'h4000};
			// addi $s0, $s0, 16
			8'd1:   Instruction <= {6'h08, 5'd16, 5'd16, 16'h0010};
			// addi $t0, $0, 0x14f
			8'd2:   Instruction <= {6'h08, 5'd0 , 5'd8 , 16'h014f};
			// sw $t0, 0($s0)
			8'd3:   Instruction <= {6'h2b, 5'd16, 5'd8 , 16'h0};
			
			default: Instruction <= 32'h00000000;
		endcase
		
endmodule
