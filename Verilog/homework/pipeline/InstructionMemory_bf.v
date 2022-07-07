
module InstructionMemory_bf(Address, Instruction);
	input [31:0] Address;
	output reg [31:0] Instruction;
	
	always @(*)
		case (Address[9:2])
			// add $v0, $0, $0
			8'd0:    Instruction <= {6'h00, 5'd0 , 5'd0 , 5'd2 , 5'd0 , 6'h20};
			// addi	$s0, $0, 41	
			8'd1:    Instruction <= {6'h08, 5'd0 , 5'd16, 16'd41};
			// addi	$s1, $0, 4
			8'd2:    Instruction <= {6'h08, 5'd0 , 5'd17, 16'd4};
            // addi	$s2, $0, 0
			8'd3:    Instruction <= {6'h08, 5'd0 , 5'd18, 16'd0};
            // addi	$s3, $0, 100
			8'd4:    Instruction <= {6'h08, 5'd0 , 5'd19, 16'd100};
			// sub $s4, $s0, $s1
			8'd5:    Instruction <= {6'h00, 5'd16, 5'd17, 5'd20, 5'd0 , 6'h22};
			// add $t0, $0, $0
			8'd6:    Instruction <= {6'h00, 5'd0 , 5'd0 , 5'd8 , 5'd0 , 6'h20};
            // for_i:
			// sub $t8, $t0, $s4
			8'd7:    Instruction <= {6'h00, 5'd8 , 5'd20, 5'd24, 5'd0, 6'h22};
			// bgtz $t8, end_i
			8'd8:    Instruction <= {6'h07, 5'd24, 5'd0 , 16'd15};
			// add $t1, $0, $0
			8'd9:    Instruction <= {6'h00, 5'd0 , 5'd0 , 5'd9 , 5'd0 , 6'h20};
            // for_j:
			// sub $t8, $s1, $t1
			8'd10:   Instruction <= {6'h00, 5'd17, 5'd9 , 5'd24, 5'd0 , 6'h22};
            // blez	$t8, end_j
			8'd11:   Instruction <= {6'h06, 5'd24, 5'd0 , 16'd8};
			// add $t2, $t0, $t1
			8'd12:   Instruction <= {6'h00, 5'd8 , 5'd9 , 5'd10, 5'd0 , 6'h20};
			// add $t2, $s2, $t2
			8'd13:   Instruction <= {6'h00, 5'd18, 5'd10, 5'd10, 5'd0 , 6'h20};
			// lbu $t2, 0($t2)
			8'd14:   Instruction <= {6'h24, 5'd10, 5'd10, 16'd0};
			// add $t3, $s3, $t1
			8'd15:   Instruction <= {6'h00, 5'd19, 5'd9 , 5'd11, 5'd0 , 6'h20};
			// lbu $t3, 0($t3)
			8'd16:   Instruction <= {6'h24, 5'd11, 5'd11, 16'd0};
			// bne $t2, $t3, end_j
			8'd17:   Instruction <= {6'h05, 5'd10, 5'd11, 16'd2};
			// j for_j
			8'd18:   Instruction <= {6'h02, 26'd10};
			// addi	$t1, $t1, 1
			8'd19:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
            // end_j:
			// addi	$t0, $t0, 1
			8'd20:   Instruction <= {6'h08, 5'd8 , 5'd8 , 16'd1};
            // bne $t1, $s1, for_i
            8'd21:   Instruction <= {6'h05, 5'd9 , 5'd17, 16'hfff1};
            // j for_i
            8'd22:   Instruction <= {6'h02, 26'd7};
            // addi	$v0, $v0, 1
            8'd23:   Instruction <= {6'h08, 5'd2 , 5'd2 , 16'd1};
			// end_i: 
			// lui $t8, 16384
			8'd24:	 Instruction <= {6'h0f, 5'd0 , 5'd24, 16'h4000};
			// addi $t9, $0, 347
			8'd25:   Instruction <= {6'h08, 5'd0 , 5'd25, 16'h015B};
			// sw $t9, 16($t8)
			8'd26:   Instruction <= {6'h2b, 5'd24, 5'd25, 16'd16};
            // j end_i 
            8'd27:   Instruction <= {6'h02, 26'd24};
			// nop
			8'd28:   Instruction <= 32'h00000000;
			
			default: Instruction <= 32'h00000000;
		endcase
		
endmodule
