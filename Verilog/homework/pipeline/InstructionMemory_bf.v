
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
			// show: 
			// add $t0, $0, $0
			8'd24:	 Instruction <= {6'h00, 5'd0 , 5'd0 , 5'd8 , 5'd0 , 6'h20};
			// addi $s0, $0, 256
			8'd25:   Instruction <= {6'h08, 5'd0 , 5'd16, 16'h0100};
			// addi $s1, $0, 15
			8'd26:   Instruction <= {6'h08, 5'd0 , 5'd17, 16'h000F};
			// lui $s2, 16384
			8'd27:   Instruction <= {6'h0f, 5'd0 , 5'd18, 16'h4000};
			// addi $s2, $s2, 16
			8'd28:   Instruction <= {6'h08, 5'd18, 5'd18, 16'h0010};
			// add $s3, $v0, $0
			8'd29:   Instruction <= {6'h00, 5'd2 , 5'd0 , 5'd19, 5'd0 , 6'h20};
			// lui $s4, 0x0000
			8'd30:   Instruction <= {6'h0f, 5'd0 , 5'd20, 16'h0000};
			// addi $t1, $0, 0x7840
			8'd31:   Instruction <= {6'h08, 5'd0 , 5'd9 , 16'h7840};
			// or $s4, $s4, $t1
			8'd32:   Instruction <= {6'h00, 5'd20, 5'd9 , 5'd20, 5'd0, 6'h25};
			// for:
			// addi $t8, $t0, -3
			8'd33:   Instruction <= {6'h08, 5'd8 , 5'd24, 16'hFFFD};
			// bgtz $t8, end_for
			8'd34:	 Instruction <= {6'h07, 5'd24, 5'd0 , 16'd75};
			// addi $t1, $0, 0
			8'd35:   Instruction <= {6'h08, 5'd0 , 5'd9 , 16'h0};
			// and $t2, $s3, $s1
			8'd36:   Instruction <= {6'h00, 5'd19, 5'd17, 5'd10, 5'd0 , 6'h24};
			// beq $t2, $t1, L0
			8'd37:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd38:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L1
			8'd39:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd40:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L2
			8'd41:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd42:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L3
			8'd43:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd44:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L4
			8'd45:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd46:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L5
			8'd47:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd48:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L6
			8'd49:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd50:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L7
			8'd51:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd52:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L8
			8'd53:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd54:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, L9
			8'd55:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd56:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, LA
			8'd57:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd58:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, LB
			8'd59:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd60:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, LC
			8'd61:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd62:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, LD
			8'd63:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// addi $t1, $t1, 1
			8'd64:   Instruction <= {6'h08, 5'd9 , 5'd9 , 16'd1};
			// beq $t2, $t1, LE
			8'd65:   Instruction <= {6'h04, 5'd10, 5'd9 , 16'd30};
			// j LF
			8'd66:   Instruction <= {6'h02, 26'd95};
			// nop
			8'd67:   Instruction <= 32'h00000000;
			// L0:
			// j L_end
			8'd68:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 63
			8'd69:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd63};
			// L1:
			// j L_end
			8'd70:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 6
			8'd71:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd6};
			// L2:
			// j L_end
			8'd72:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 91
			8'd73:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd91};
			// L3:
			// j L_end
			8'd74:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 79
			8'd75:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd79};
			// L4:
			// j L_end
			8'd76:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 102
			8'd77:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd102};
			// L5:
			// j L_end
			8'd78:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 109
			8'd79:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd109};
			// L6:
			// j L_end
			8'd80:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 125
			8'd81:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd125};
			// L7:
			// j L_end
			8'd82:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 7
			8'd83:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd7};
			// L8:
			// j L_end
			8'd84:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 127
			8'd85:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd127};
			// L9:
			// j L_end
			8'd86:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 111
			8'd87:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd111};
			// LA:
			// j L_end
			8'd88:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 119
			8'd89:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd119};
			// LB:
			// j L_end
			8'd90:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 124
			8'd91:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd124};
			// LC:
			// j L_end
			8'd92:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 57
			8'd93:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd57};
			// LD:
			// j L_end
			8'd94:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 94
			8'd95:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd94};
			// LE:
			// j L_end
			8'd96:   Instruction <= {6'h02, 26'd99};
			// addi $t3, $0, 121
			8'd97:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd121};
			// LF:
			// addi $t3, $0, 113
			8'd98:   Instruction <= {6'h08, 5'd0 , 5'd11, 16'd113};
			// L_end:
			// or $t3, $t3, $s0
			8'd99:   Instruction <= {6'h00, 5'd11, 5'd16, 5'd11, 5'd0 , 6'h25};
			// sw $t3, 0($s2)
			8'd100:  Instruction <= {6'h2b, 5'd18, 5'd11, 16'h0};
			// add $t4, $0, $0
			8'd101:  Instruction <= {6'h00, 5'd0 , 5'd0 , 5'd12, 5'd0 , 6'h20};
			// for_count:
			// slt $t9, $t4, $s4
			8'd102:  Instruction <= {6'h00, 5'd12, 5'd20, 5'd25, 5'd0 , 6'h2a};
			// beq $t9, $0, end_count
			8'd103:  Instruction <= {6'h04, 5'd25, 5'd0 , 16'd2};
			// j for_count
			8'd104:  Instruction <= {6'h02, 26'd102};
			// addi $t4, $t4, 1
			8'd105:  Instruction <= {6'h08, 5'd12, 5'd12, 16'd1};
			// end_count: 
			// addi $t0, $t0, 1
			8'd106:  Instruction <= {6'h08, 5'd8 , 5'd8 , 16'd1};
			// sll $s0, $s0, 1
			8'd107:  Instruction <= {6'h00, 5'd0 , 5'd16, 5'd16, 5'd1 , 6'h00};
			// j for
			8'd108:  Instruction <= {6'h02, 26'd33};
			// srl $s3, $s3, 4
			8'd109:  Instruction <= {6'h00, 5'd0 , 5'd19, 5'd19, 5'd4 , 6'h02};
			// end_for:
			// j show
			8'd110:  Instruction <= {6'h02, 26'd24};
			// nop
			8'd111:  Instruction <= 32'h00000000;
			
			default: Instruction <= 32'h00000000;
		endcase
		
endmodule
